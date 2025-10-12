#ifdef SMPT_CM_VK
	VkDescriptorSet *smptr_cemPvkdescriptorset;

	VkBuffer *smptr_cemPvkbuffer;
	static void **Pbuffer_map;
	static VkDeviceMemory *Pvkdevicememory;

	static VkWriteDescriptorSet *Pvkwritedescriptorset;
	static VkDescriptorBufferInfo *Pvkdescriptorbufferinfo;
	static SMPTRtMI Ldst = 0;

	static VkMappedMemoryRange *Pvkmappedmemoryrange;

	static VkDescriptorSet *Pvkdescriptorset_free;
	SMPT_RD_VK_BFmFREE_F
#endif

struct SMPTR_CEMsM
{
	struct SMPTRsM Sm;
	float Ft;
	//float Pttr[3 + 1 + 2];
};
static struct SMPTR_CEMsM *smptr_cemPm;
static SMPTRtMI Lm = 0;

struct SMPTR_CEMsM0
{
	SMPTRtM Um;
	SMPTRtMK Uk;
	SMPTRtMT Ut;
	//float Ptr[3 + 1 + 2];
};
static struct SMPTR_CEMsM0 smptr_cemPm0[SMPTRlMI];

struct SMPTR_CEMsM01
{
	uint8_t Uf;
	float Ft;
	//float Ptr[3 + 1 + 2];
};
static struct SMPTR_CEMsM01 smptr_cemPm01[SMPTRlMI];

struct SMPTR_CEMsM1 *smptr_cemPm1;
uint32_t smptr_cemLm1 = 0;

void smptr_cemMset()
{
	smptr_cemPm = malloc(0);

	smptr_cemPm1 = malloc(0);

	#ifdef SMPT_CM_VK
		smptr_cemPvkdescriptorset = malloc(0);

		smptr_cemPvkbuffer = malloc(0);
		Pbuffer_map = malloc(0);
		Pvkdevicememory = malloc(0);

		Pvkwritedescriptorset = malloc(0);
		Pvkdescriptorbufferinfo = malloc(0);

		Pvkmappedmemoryrange = malloc(0);

		Pvkdescriptorset_free = malloc(0);
		SMPT_RD_VK_BFmFREE_SET
	#endif
}

static void Mfree_m(SMPTRtMI Us, SMPTRtMI Ue)
{
	for (SMPTRtMI l0 = Us; l0 < Ue; ++l0)
	{
		if (smptr_cemPm[l0].Sm.Um != SMPTRvM)
		{
			free(smptr_cemPm[l0].Sm.Pa);
			free(smptr_cemPm[l0].Sm.Sm0.Ptr);
		}
	}
}

static void Mfree_vk(SMPTRtMI Us, SMPTRtMI Ue)
{
//	SMPT_DBmN2L("Us %d", Us)
//	SMPT_DBmN2L("Ue %d", Ue)
//	SMPT_DBmN2L("Lfree %d", Lfree)
	Pvkdescriptorset_free = realloc(Pvkdescriptorset_free, sizeof(VkDescriptorSet) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage);
	memcpy(Pvkdescriptorset_free + Lfree * smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + Us * smpt_rd_vk_swcUimage, sizeof(VkDescriptorSet) * (Ue - Us) * smpt_rd_vk_swcUimage);
	SMPT_RD_VK_BFmFREE_HELP(smptr_cemPvkbuffer, Pvkdevicememory)
//	SMPT_DBmN2L("Lfree %d", Lfree)
}

//.i sync n-mn
static SMPTRtMI Lm0 = 0;
void smptr_cemMread()
{
	//.i get data
	SMPTRtMI Ucount = *(SMPTRtMI *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(SMPTRtMI);

	Mfree_m(Ucount, Lm);
	Lm = Ucount;
	smptr_cemPm = realloc(smptr_cemPm, sizeof(struct SMPTR_CEMsM) * Lm);

	//SMPT_DBmN2L("Ucount %d", Ucount)
	for (SMPTRtMI l0 = 0; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEMsM *Pm = smptr_cemPm + l0;

		Pm->Sm.Um = *(SMPTRtM *)(smptr_cePnet + smptr_ceLnet);
		smptr_ceLnet += sizeof(SMPTRtM);
		//SMPT_DBmN2L("Pm->Sm.Um %d", Pm->Sm.Um)
		if (Pm->Sm.Um != SMPTRvM)
		{
			Pm->Sm.La = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pm->Sm.Pa = malloc(sizeof(SMPTRtMA) * Pm->Sm.La);
			memcpy(Pm->Sm.Pa, smptr_cePnet + smptr_ceLnet, sizeof(SMPTRtMA) * Pm->Sm.La);
			smptr_ceLnet += sizeof(SMPTRtMA) * Pm->Sm.La;

			Pm->Sm.Uk = *(SMPTRtMK *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(SMPTRtMK);

			Pm->Sm.Ut = *(SMPTRtMT *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(SMPTRtMT);
			//SMPT_DBmN2L("Pm->Sm.Ut %d", Pm->Sm.Ut)

			Pm->Sm.Sm0.Ltr = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pm->Sm.Sm0.Ptr = malloc(sizeof(float) * Pm->Sm.Sm0.Ltr);
			memcpy(Pm->Sm.Sm0.Ptr, smptr_cePnet + smptr_ceLnet, sizeof(float) * Pm->Sm.Sm0.Ltr);
			smptr_ceLnet += sizeof(float) * Pm->Sm.Sm0.Ltr;
		}
	}

	//.i clean m0
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		if (Lm < Lm0)
			Mfree_vk(Lm, Lm0);
		smptr_cemPvkdescriptorset = realloc(smptr_cemPvkdescriptorset, sizeof(VkDescriptorSet) * smpt_rd_vk_swcUimage * Lm);
		smptr_cemPvkbuffer = realloc(smptr_cemPvkbuffer, sizeof(VkBuffer) * smpt_rd_vk_swcUimage * Lm);
		Pbuffer_map = realloc(Pbuffer_map, sizeof(void *) * smpt_rd_vk_swcUimage * Lm);
		Pvkdevicememory = realloc(Pvkdevicememory, sizeof(VkDeviceMemory) * smpt_rd_vk_swcUimage * Lm);
		for (SMPTRtMI l0 = Lm0; l0 < Lm; ++l0)
			smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;

		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
	#endif

	//.i update m
	smptr_cemLm1 = 0;
	for (SMPTRtMI l0 = 0; l0 < Lm; ++l0)
	{
		struct SMPTR_CEMsM *Pm = smptr_cemPm + l0;
		struct SMPTR_CEMsM0 *Pm0 = smptr_cemPm0 + l0;

		if (Pm->Sm.Um == SMPTRvM)
		{
			Pm0->Um = SMPTRvM;
			if (smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage])
			{
				Mfree_vk(l0, l0 + 1);
				smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;
			}
		}
		else
		{
			struct SMPTR_CEMsM01 *Pm01 = smptr_cemPm01 + l0;

			#ifdef SMPT_CM_VK
				if (Lm0 <= l0 || !smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] || Pm0->Um != Pm->Sm.Um)
			#endif
			{
				#ifdef SMPT_CM_VK
					if (smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage])
					{
						Mfree_vk(l0, l0 + 1);
						smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;
					}

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * smptr_ce_mdPj[Pm->Sm.Um];

						VkMemoryRequirements vkmemoryrequirements;
						SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuGP, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage], Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], vkmemoryrequirements)
						SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(Vvkdevice, Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], 0, vkdevicesize, 0, &Pbuffer_map[l1 + l0 * smpt_rd_vk_swcUimage]))
					}

					++Ldst;
					Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, SMPT_RD_VKW_DSTS_LOlMAIN * smpt_rd_vk_swcUimage * Ldst * sizeof(VkWriteDescriptorSet));
					Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, (2 + 3 * smpt_rd_vk_swcUimage * Ldst) * sizeof(VkDescriptorBufferInfo));

					VkDescriptorSetLayout *Pvkdescriptorsetlayout = malloc(sizeof(VkDescriptorSetLayout) * smpt_rd_vk_swcUimage);
					for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
						Pvkdescriptorsetlayout[l0] = smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuGP];
					SMPT_RD_VKW_DSTSmMAKE(SMPT_RD_VKQuGP, SMPT_RD_VKW_DSTSuGP, Pvkdescriptorsetlayout, smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage)
					free(Pvkdescriptorsetlayout);
					VkDescriptorSet *Pvkdescriptorset = smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage;
					VkDescriptorBufferInfo *Pvkdescriptorbufferinfo0 = Pvkdescriptorbufferinfo + (Ldst - 1) * smpt_rd_vk_swcUimage;
					VkWriteDescriptorSet *Pvkwritedescriptorset0 = Pvkwritedescriptorset + (Ldst - 1) * smpt_rd_vk_swcUimage;
					const uint8_t j = Pm->Sm.Um;
					const uint8_t mj = smptr_ce_mdPj[Pm->Sm.Um];
					//.i bindpose s 1+
					Pvkdescriptorbufferinfo0[0] = (VkDescriptorBufferInfo)
					{
						.buffer = smptr_ce_mdPvkbuffer[0],
						.offset = smptr_ce_mdPvkdevicesize[j] - sizeof(float) * 16 * 2,
						.range = (mj - 1) * sizeof(float) * 16 * 2
					};
					//.i src_color s
					Pvkdescriptorbufferinfo0[1] = (VkDescriptorBufferInfo)
					{
						.buffer = smptr_ce_mdPvkbuffer[0],
						.offset = 0,
						.range = smptr_ce_mdLrgba
					};
					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						//.i gui/world d
						Pvkdescriptorbufferinfo0[2 + l1 * 3 + 2] = (VkDescriptorBufferInfo)
						{
							.buffer = smptr_ce_mdPvkbuffer[1 + 2 * smpt_rd_vk_swcUimage + l1],
							.offset = 0,
							.range = sizeof(float) * 16 * 2
						};
						//.i animate d
						Pvkdescriptorbufferinfo0[2 + l1 * 3] = (VkDescriptorBufferInfo)
						{
							.buffer = smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage],
							.offset = mj * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * l0 + sizeof(float) * 4,
							.range = mj * sizeof(float) * 4 * 3
						};
						//.i color d
						Pvkdescriptorbufferinfo0[2 + l1 * 3 + 1] = (VkDescriptorBufferInfo)
						{
							.buffer = smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage],
							.offset = mj * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * l0,
							.range = sizeof(float) * 4
						};
						SMPT_RD_VKWmDSTS(0, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 2 + l1 * 3 + 2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN]);
						SMPT_RD_VKWmDSTS(1, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 1]);
						SMPT_RD_VKWmDSTS(2, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 2 + l1 * 3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 2]);
						SMPT_RD_VKWmDSTS(3, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 3]);
						SMPT_RD_VKWmDSTS(4, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 2 + l1 * 3 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 4]);
					}
				#endif

				Pm01->Uf = SMPTR_CEuFPS;
				Pm01->Ft = Pm->Sm.Ut / 255.0F;
				Pm0->Uk = Pm->Sm.Uk;
				Pm0->Ut = Pm->Sm.Ut;
				Pm0->Um = Pm->Sm.Um;
			}
			else if (Pm0->Uk != Pm->Sm.Uk)
			{
				Pm01->Uf = SMPTR_CEuFPS;
				Pm01->Ft = Pm->Sm.Ut / 255.0F;
				Pm0->Uk = Pm->Sm.Uk;
				Pm0->Ut = Pm->Sm.Ut;
			}
			else if (Pm0->Ut != Pm->Sm.Ut)
			{
				const SMPTRtMK *Pk = smptrPmk[Pm->Sm.Uk];

				Pm01->Uf = 0;
//				Pm->Ft = (Pm->Sm.Ut - Pm0->Ut) / 255.0F * SMPTR_CEuDELTA;
				if (Pm->Sm.Ut < Pm0->Ut)
				{
					Pm->Ft = Pk[2] * 255 - Pm0->Ut + Pm->Sm.Ut - Pk[1] * 255;
				}
				else
				{
					Pm->Ft = Pm->Sm.Ut - Pm0->Ut;
				}
				//Pm->Ft /= 255.0F;
				Pm->Ft *= SMPTR_CEuDELTA;

				Pm0->Ut = Pm->Sm.Ut;
			}

			smptr_cemLm1 += Pm->Sm.La;
		}
	}
	Lm0 = Lm;
	#ifdef SMPT_CM_VK
		vkUpdateDescriptorSets(Vvkdevice, SMPT_RD_VKW_DSTS_LOlMAIN * smpt_rd_vk_swcUimage * Ldst, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
		Ldst = 0;
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
	#endif

	//.i add m1
	smptr_cemPm1 = realloc(smptr_cemPm1, sizeof(struct SMPTR_CEMsM1) * (smptr_cemLm1 + smptr_ceaLa));
	smptr_cemLm1 = 0;
	for (SMPTRtMI l0 = 0; l0 < Lm; ++l0)
	{
		struct SMPTR_CEMsM m = smptr_cemPm[l0];
		if (m.Sm.Um != SMPTRvM)
			for (uint8_t l1 = 0; l1 < m.Sm.La; ++l1)
			{
				struct SMPTR_CEMsM1 *Pm1 = smptr_cemPm1 + smptr_cemLm1++;
				Pm1->Ui = l0;
				Pm1->Ua = m.Sm.Pa[l1];
				Pm1->Ub = smptrPmb[Pm1->Ua];
				//! find depth
				Pm1->Fd = 0;
			}
	}
	//.i add a to m1
	for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
	{
		struct SMPTR_CEAsA Sa = smptr_ceaPa[l0];
		struct SMPTR_CEMsM1 *Pm1 = smptr_cemPm1 + smptr_cemLm1 + l0;
		if (Sa.Sa.Ua == l0)
		{
			Pm1->Ui = l0;
			Pm1->Ua = Sa.Sa.Lv;
			Pm1->Ub = SMPTR_CE_MDlA;
			//! find depth
			Pm1->Fd = 0;
		}
	}
}

void smptr_cemMloop()
{
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		//.i free
		uint32_t Ufree = Lfree;
		for (uint32_t l0 = 0; l0 < Lfree; ++l0)
		{
			if (SMPT_RD_VK_BFmFREE_ABLE(l0))
			{
				if (Pvkdescriptorset_free[l0 * smpt_rd_vk_swcUimage])
				{
					vkFreeDescriptorSets(Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], smpt_rd_vk_swcUimage, Pvkdescriptorset_free + l0 * smpt_rd_vk_swcUimage);
					SMPT_RD_VK_BFmFREE_DO(Vvkdevice, l0, l1)
					Pvkdescriptorset_free[l0 * smpt_rd_vk_swcUimage] = 0;
				}
				if (Ufree == Lfree)
					Ufree = l0;
			}
			else
			{
				Ufree = Lfree;
			}
		}
		Lfree = Ufree;
		Pvkdescriptorset_free = realloc(Pvkdescriptorset_free, sizeof(VkDescriptorSet) * Lfree * smpt_rd_vk_swcUimage);
		SMPT_RD_VK_BFmFREE_RE

		//! find depth
		//.i update buffer
		//SMPT_DBmN2L("Lm %d", Lm)
		SMPTRtMI L = 0;
		for (SMPTRtMI l0 = 0; l0 < Lm; ++l0)
		{
			struct SMPTR_CEMsM m = smptr_cemPm[l0];
			struct SMPTR_CEMsM01 *Pm01 = smptr_cemPm01 + l0;
			//SMPT_DBmN2L("m.Sm.Um %d", m.Sm.Um)

			if (m.Sm.Um != SMPTRvM)
			{
				float *Pbuffer = Pbuffer_map[smpt_rd_vk_swcUframe_buffer + l0 * smpt_rd_vk_swcUimage];
				for (uint8_t l1 = 0; l1 < 4; ++l1)
				{
					*(float *)(Pbuffer + l1) = 1.0;
				}
				memcpy(Pbuffer + 4, smptr_ce_mdPb[m.Sm.Um], smptr_ce_mdPj[m.Sm.Um] * 4 * 3 * sizeof(float));
				const SMPTRtMK *Pk = smptrPmk[m.Sm.Uk];

				if (Pm01->Uf >= SMPTR_CEuFPS - 1)
				{
					if (Pm01->Uf == SMPTR_CEuFPS)
						--Pm01->Uf;
					else
						Pm01->Ft = m.Sm.Ut / 255.0F;
				}
				else
				{
					Pm01->Ft += m.Ft;
					Pm01->Ft = SMPTMmWRAP_F(Pm01->Ft, Pk[1], Pk[2]);
				}
				++Pm01->Uf;

				SMPTRtMK Uks = Pm01->Ft;
				float Fkf = Pm01->Ft - Uks;
				SMPTRtMK Uke = SMPTMmWRAP_I(Uks + 1, Pk[1], Pk[2]);
				struct SMPTR_CE_KFs Skf = smptr_ce_kfP[Pk[0]][Uks];
				//SMPT_DBmN2L("Uks %d", Uks)
				//SMPT_DBmN2L("Fkf %f", Fkf)
				//SMPT_DBmN2L("Uke %d", Uke)
				for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
				{
					memcpy(Pbuffer + 4 + Skf.Pbone[l_0] * 4 * 3, Skf.Ps[l_0], sizeof(float) * 3);
					memcpy(Pbuffer + 4 + Skf.Pbone[l_0] * 4 * 3 + 4, Skf.Pr[l_0], sizeof(float) * 4);
					memcpy(Pbuffer + 4 + Skf.Pbone[l_0] * 4 * 3 + 4 * 2, Skf.Pt[l_0], sizeof(float) * 3);
				}

				Skf = smptr_ce_kfP[Pk[0]][Uke];
				for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
				{
					for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
					{
						SMPTMmLERP(((float *)(Pbuffer + 4 + Skf.Pbone[l_0] * 4 * 3))[l_3], Skf.Ps[l_0][l_3], Fkf);
						SMPTMmLERP(((float *)(Pbuffer + 4 + Skf.Pbone[l_0] * 4 * 3 + 4 * 2))[l_3], Skf.Pt[l_0][l_3], Fkf);
					}

					for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
					{
						SMPTMmLERP(((float *)(Pbuffer + 4 + Skf.Pbone[l_0] * 4 * 3 + 4))[l_3], Skf.Pr[l_0][l_3], Fkf);
					}
				}

//				smptm_v4Mq(0, SMPTMmD2R(-45), 0, Pbuffer + 4 + 4);
				*(float *)(Pbuffer + 4 + 4 * 2) = m.Sm.Sm0.Ptr[0];
				*(float *)(Pbuffer + 4 + 4 * 2 + 1) = m.Sm.Sm0.Ptr[1];
				*(float *)(Pbuffer + 4 + 4 * 2 + 2) = m.Sm.Sm0.Ptr[2];
				Pvkmappedmemoryrange = realloc(Pvkmappedmemoryrange, sizeof(VkMappedMemoryRange) * (L + 1));
				Pvkmappedmemoryrange[L++] = (VkMappedMemoryRange)
				{
					.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
					.memory = Pvkdevicememory[smpt_rd_vk_swcUframe_buffer],
					.offset = 0,
					.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, sizeof(float) * 4 * 4 * smptr_ce_mdPj[m.Sm.Um]),
					.pNext = VK_NULL_HANDLE
				};
			}
		}
		//! animate a
		for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
		{
			struct SMPTR_CEAsA Sa = smptr_ceaPa[l0];
			if (Sa.Sa.Ua == l0)
			{
			}
		}
		//SMPT_DBmN2L("L %d", L)
		if (L)
			vkFlushMappedMemoryRanges(Vvkdevice, L, Pvkmappedmemoryrange);
	#endif
}

void smptr_cemMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		if (Lfree)
		{
			for (uint32_t l0 = 0; l0 < Lfree; ++l0)
			{
				if (SMPT_RD_VK_BFmFREE_ABLE(l0))
				{
					if (Pvkdescriptorset_free[l0 * smpt_rd_vk_swcUimage])
					{
						vkFreeDescriptorSets(Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], smpt_rd_vk_swcUimage, Pvkdescriptorset_free + l0 * smpt_rd_vk_swcUimage);
						SMPT_RD_VK_BFmFREE_DO(Vvkdevice, l0, l1)
						Pvkdescriptorset_free[l0 * smpt_rd_vk_swcUimage] = 0;
					}
				}
			}
		}
		SMPT_RD_VK_BFmFREE_CLEAN
		free(Pvkdescriptorset_free);

		free(Pvkmappedmemoryrange);

		free(Pvkdescriptorbufferinfo);
		free(Pvkwritedescriptorset);

		for (SMPTRtMI l0 = 0; l0 < Lm; ++l0)
		{
			struct SMPTR_CEMsM m = smptr_cemPm[l0];
			if (m.Sm.Um != SMPTRvM)
			{
				vkFreeDescriptorSets(Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage);

				for (SMPTRtMI l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(Vvkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(Vvkdevice, smptr_cemPvkbuffer[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(Vvkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
			}
		}
		free(Pvkdevicememory);
		free(Pbuffer_map);
		free(smptr_cemPvkbuffer);

		free(smptr_cemPvkdescriptorset);
	#endif

	free(smptr_cemPm1);

	Mfree_m(0, Lm);
	free(smptr_cemPm);
}
