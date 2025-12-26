#ifndef SMPT_CM_ST_JAVA
	//.c log
	#define SMPT_DBmR2L(Pformat, ...) __VA_ARGS__;

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

	struct sM
	{
		struct SMPTRsM Sm;
		struct SMPTRsM0 Sm0;
		SMPTRtM Um;
		SMPTRtMK Uk;
		SMPTRtMT Pt[2];
		float Ptr[10];
	};
	static struct sM *Pm_s;
	static SMPTRtMI Lm_s = 0;

	struct SMPTR_CEMsM *smptr_cemPm;
	uint32_t smptr_cemLm = 0;

	static float Mwrap_rad(float Fa)
	{
		Fa = fmodf(Fa + M_PI, 2.0f * M_PI);
		if (Fa < 0) Fa += 2.0f * M_PI;
		return Fa - M_PI;
	}

	void smptr_cemMset()
	{
		Pm_s = malloc(0);

		smptr_cemPm = malloc(0);

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
			const struct sM *Pm = Pm_s + l0;
			free(Pm->Sm.Pa);
			free(Pm->Sm.Sm0.Ptr);

			free(Pm->Sm0.Ptr);
		}
	}

	static void Mfree_vk(SMPTRtMI Us, SMPTRtMI Ue)
	{
	//	SMPT_DBmN2L("Us %d", Us)
	//	SMPT_DBmN2L("Ue %d", Ue)
	//	SMPT_DBmN2L("Lfree %d", Lfree)
		Pvkdescriptorset_free = realloc(Pvkdescriptorset_free, sizeof(VkDescriptorSet) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage);
		memcpy(Pvkdescriptorset_free + Lfree * smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + Us * smpt_rd_vk_swcUimage, sizeof(VkDescriptorSet) * (Ue - Us) * smpt_rd_vk_swcUimage);
		SMPT_RD_VK_BFmFREE_HELP(smptr_cemPvkbuffer, Pvkdevicememory, smpt_rd_vk_swcUimage)
	//	SMPT_DBmN2L("Lfree %d", Lfree)
	}

	//.i sync n-mn
	static SMPTRtMI Lm0 = 0;
	void smptr_cemMread()
	{
		//.i get data
		SMPTRtMI Ucount = *(SMPTRtMI *)(smptr_cePnet + smptr_ceLnet);
		smptr_ceLnet += sizeof(SMPTRtMI);

		Mfree_m(Ucount, Lm_s);
		Pm_s = realloc(Pm_s, sizeof(struct sM) * Ucount);
		for (SMPTRtMI l0 = Lm_s; l0 < Ucount; ++l0)
		{
			struct sM *Pm = Pm_s + l0;

			Pm->Sm.Pa = malloc(0);

			Pm->Sm.Sm0.Ptr = malloc(0);

			Pm->Sm0.Ptr = malloc(0);
		}
		Lm_s = Ucount;

		//SMPT_DBmN2L("Ucount %d", Ucount)
		for (SMPTRtMI l0 = 0; l0 < Ucount; ++l0)
		{
			struct sM *Pm = Pm_s + l0;

			Pm->Sm.Um = *(SMPTRtM *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(SMPTRtM);
			//SMPT_DBmN2L("Pm->Sm.Um %d", Pm->Sm.Um)
			if (Pm->Sm.Um != SMPTRvM)
			{
				Pm->Sm.La = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
				smptr_ceLnet += sizeof(uint8_t);

				Pm->Sm.Pa = realloc(Pm->Sm.Pa, sizeof(SMPTRtMA) * Pm->Sm.La);
				memcpy(Pm->Sm.Pa, smptr_cePnet + smptr_ceLnet, sizeof(SMPTRtMA) * Pm->Sm.La);
				smptr_ceLnet += sizeof(SMPTRtMA) * Pm->Sm.La;

				Pm->Sm.Uk = *(SMPTRtMK *)(smptr_cePnet + smptr_ceLnet);
				smptr_ceLnet += sizeof(SMPTRtMK);

				Pm->Sm.Ut = *(SMPTRtMT *)(smptr_cePnet + smptr_ceLnet);
				smptr_ceLnet += sizeof(SMPTRtMT);
				//SMPT_DBmN2L("Pm->Sm.Ut %d", Pm->Sm.Ut)

				Pm->Sm.Sm0.Ltr = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
				smptr_ceLnet += sizeof(uint8_t);

				Pm->Sm0.Ptr = realloc(Pm->Sm0.Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);

				Pm->Sm.Sm0.Ptr = realloc(Pm->Sm.Sm0.Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
				memcpy(Pm->Sm.Sm0.Ptr, smptr_cePnet + smptr_ceLnet, sizeof(float) * Pm->Sm.Sm0.Ltr);
				smptr_ceLnet += sizeof(float) * Pm->Sm.Sm0.Ltr;

				Pm->Sm.Sm0.Usync = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
				smptr_ceLnet += sizeof(uint8_t);
			}
		}

		//.i clean m0
		#ifdef SMPT_CM_VK
			VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

			if (Lm_s < Lm0)
				Mfree_vk(Lm_s, Lm0);
			smptr_cemPvkdescriptorset = realloc(smptr_cemPvkdescriptorset, sizeof(VkDescriptorSet) * smpt_rd_vk_swcUimage * Lm_s);
			smptr_cemPvkbuffer = realloc(smptr_cemPvkbuffer, sizeof(VkBuffer) * smpt_rd_vk_swcUimage * Lm_s);
			Pbuffer_map = realloc(Pbuffer_map, sizeof(void *) * smpt_rd_vk_swcUimage * Lm_s);
			Pvkdevicememory = realloc(Pvkdevicememory, sizeof(VkDeviceMemory) * smpt_rd_vk_swcUimage * Lm_s);
			for (SMPTRtMI l0 = Lm0; l0 < Lm_s; ++l0)
					smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;
		#endif

		//.i update m
		smptr_cemLm = 0;
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, SMPT_RD_VKW_DSTS_LOlMAIN * smpt_rd_vk_swcUimage * Lm_s * sizeof(VkWriteDescriptorSet) * 2);
		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, (2 + 3 * smpt_rd_vk_swcUimage) * Lm_s * sizeof(VkDescriptorBufferInfo) * 2);
		for (SMPTRtMI l0 = 0; l0 < Lm_s; ++l0)
		{
			struct sM *Pm = Pm_s + l0;

			if (Pm->Sm.Um == SMPTRvM)
			{
				Pm->Um = SMPTRvM;
				if (smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage])
				{
					//SMPT_DBmN2L("m0")
					Mfree_vk(l0, l0 + 1);
					smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;
				}
			}
			else
			{
				#ifdef SMPT_CM_VK
					if
					(
						Lm0 <= l0 || !smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] ||
						Pm->Um != Pm->Sm.Um
					)
				#endif
				{
					//SMPT_DBmN2L("m1")
					#ifdef SMPT_CM_VK
						if (smptr_cemPvkdescriptorset[l0 * smpt_rd_vk_swcUimage])
						{
							Mfree_vk(l0, l0 + 1);
						}

						const uint8_t j = Pm->Sm.Um;
						const uint8_t mj = smptr_ce_mdPj[Pm->Sm.Um];
						for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
						{
							VkDeviceSize vkdevicesize = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 4 * 3 * mj) + sizeof(uint32_t));

							VkMemoryRequirements vkmemoryrequirements;
							SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuGP, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage], Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], vkmemoryrequirements)
							SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(Vvkdevice, Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], 0, vkdevicesize, 0, &Pbuffer_map[l1 + l0 * smpt_rd_vk_swcUimage]))
						}

						++Ldst;
						//SMPT_DBmN2L("Ldst %d", Ldst)

						VkDescriptorSetLayout *Pvkdescriptorsetlayout = malloc(sizeof(VkDescriptorSetLayout) * smpt_rd_vk_swcUimage);
						for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
							Pvkdescriptorsetlayout[l1] = smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuGP];
						SMPT_RD_VKW_DSTSmMAKE(SMPT_RD_VKQuGP, SMPT_RD_VKW_DSTSuGP, Pvkdescriptorsetlayout, smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage)
						free(Pvkdescriptorsetlayout);
						VkDescriptorSet *Pvkdescriptorset = smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage;
						VkDescriptorBufferInfo *Pvkdescriptorbufferinfo0 = Pvkdescriptorbufferinfo + (Ldst - 1) * (2 + 3 * smpt_rd_vk_swcUimage);
						VkWriteDescriptorSet *Pvkwritedescriptorset0 = Pvkwritedescriptorset + (Ldst - 1) * SMPT_RD_VKW_DSTS_LOlMAIN * smpt_rd_vk_swcUimage;
						//.i bindpose s 1+
						//SMPT_DBmN2L("smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M] %p", smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M])
						Pvkdescriptorbufferinfo0[0] = (VkDescriptorBufferInfo)
						{
							.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M],
							.offset = smptr_ce_mdPvkdevicesize[j],
							.range = mj * sizeof(float) * 16 * 2
						};
						//.i src_color s
						Pvkdescriptorbufferinfo0[1] = (VkDescriptorBufferInfo)
						{
							.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M],
							.offset = SMPTR_CE_MDuRGBA,
							.range = smptr_ce_mdLrgba
						};
						for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
						{
							//.i gui/world d
							Pvkdescriptorbufferinfo0[2 + l1 * 3 + 2] = (VkDescriptorBufferInfo)
							{
								.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_VP_P + l1],
								.offset = 0,
								.range = sizeof(float) * 16 * 2
							};
							//.i animate d
							Pvkdescriptorbufferinfo0[2 + l1 * 3] = (VkDescriptorBufferInfo)
							{
								.buffer = smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage],
								.offset = 0,
								.range = mj * sizeof(float) * 4 * 3
							};
							//.i color d
							Pvkdescriptorbufferinfo0[2 + l1 * 3 + 1] = (VkDescriptorBufferInfo)
							{
								.buffer = smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage],
								.offset = SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, mj * sizeof(float) * 4 * 3),
								.range = sizeof(uint32_t)
							};
							SMPT_RD_VKWmDSTS(0, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 2 + l1 * 3 + 2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN]);
							SMPT_RD_VKWmDSTS(1, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 1]);
							SMPT_RD_VKWmDSTS(2, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 2 + l1 * 3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 2]);
							SMPT_RD_VKWmDSTS(3, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 3]);
							SMPT_RD_VKWmDSTS(4, VK_NULL_HANDLE, Pvkdescriptorbufferinfo0 + 2 + l1 * 3 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l1], Pvkwritedescriptorset0[l1 * SMPT_RD_VKW_DSTS_LOlMAIN + 4]);
//							SMPT_DBmN2L("Pvkwritedescriptorset0 + 1 %p", Pvkwritedescriptorset0 + 1)
//							SMPT_DBmN2L("Pvkwritedescriptorset + 1 %p", Pvkwritedescriptorset + 1)
//
//							SMPT_DBmN2L("Pvkwritedescriptorset0[1].pBufferInfo %p", Pvkwritedescriptorset0[1].pBufferInfo)
//							SMPT_DBmN2L("Pvkwritedescriptorset[1].pBufferInfo %p", Pvkwritedescriptorset[1].pBufferInfo)
//
//							SMPT_DBmN2L("Pvkdescriptorbufferinfo0 %p", Pvkdescriptorbufferinfo0)
//							SMPT_DBmN2L("Pvkdescriptorbufferinfo %p", Pvkdescriptorbufferinfo)
//
//							SMPT_DBmN2L("Pvkdescriptorbufferinfo0->buffer %p", Pvkdescriptorbufferinfo0->buffer)
//							SMPT_DBmN2L("Pvkdescriptorbufferinfo->buffer %p", Pvkdescriptorbufferinfo->buffer)
//
//
//							SMPT_DBmN2L("Pvkwritedescriptorset0[1].pBufferInfo->buffer %p", Pvkwritedescriptorset0[1].pBufferInfo->buffer)
//							SMPT_DBmN2L("Pvkwritedescriptorset[1].pBufferInfo->buffer %p", Pvkwritedescriptorset[1].pBufferInfo->buffer)
//
//							SMPT_DBmN2L("smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M] %p", smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M])
						}
					#endif

					Pm->Uk = Pm->Sm.Uk;
					Pm->Um = Pm->Sm.Um;
					Pm->Pt[0] = Pm->Sm.Ut;
					Pm->Pt[1] = Pm->Sm.Ut;
					memcpy(Pm->Ptr, Pm->Sm.Sm0.Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
					memcpy(Pm->Sm0.Ptr, Pm->Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
					Pm->Sm0.Ltr = Pm->Sm.Sm0.Ltr;
					Pm->Sm0.Usync = Pm->Sm.Sm0.Usync;
				}
				else if
				(
					Pm->Uk != Pm->Sm.Uk ||
					Pm->Sm.Sm0.Usync != Pm->Sm0.Usync
				)
				{
					//SMPT_DBmN2L("m2")
					if (Pm->Uk != Pm->Sm.Uk)
					{
						Pm->Pt[0] = Pm->Sm.Ut;
						Pm->Pt[1] = Pm->Sm.Ut;
						Pm->Uk = Pm->Sm.Uk;
					}
					if (Pm->Sm.Sm0.Ltr != Pm->Sm0.Ltr)
					{
						Pm->Sm0.Ptr = realloc(Pm->Sm0.Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
						Pm->Sm0.Ltr = Pm->Sm.Sm0.Ltr;
					}
					if (Pm->Sm.Sm0.Usync != Pm->Sm0.Usync)
					{
						memcpy(Pm->Ptr, Pm->Sm.Sm0.Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
						memcpy(Pm->Sm0.Ptr, Pm->Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
						Pm->Sm0.Usync = Pm->Sm.Sm0.Usync;
					}
				}
				else
				{
						Pm->Pt[0] = Pm->Pt[1];
						Pm->Pt[1] = Pm->Sm.Ut;
						memcpy(Pm->Sm0.Ptr, Pm->Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
						memcpy(Pm->Ptr, Pm->Sm.Sm0.Ptr, sizeof(float) * Pm->Sm.Sm0.Ltr);
				}

				smptr_cemLm += Pm->Sm.La;
			}
		}
		Lm0 = Lm_s;
		#ifdef SMPT_CM_VK
			//SMPT_DBmN2L("Ldst %d", Ldst)
			//SMPT_DBmN2L("smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M] %p", smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M])
			//SMPT_DBmN2L("Pvkdescriptorbufferinfo[1].buffer %p", Pvkdescriptorbufferinfo[1].buffer)
			vkUpdateDescriptorSets(Vvkdevice, SMPT_RD_VKW_DSTS_LOlMAIN * smpt_rd_vk_swcUimage * Ldst, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
			Ldst = 0;
		#endif

		//! clean
		//.i add SMPTR_CEMsM
		smptr_cemPm = realloc(smptr_cemPm, sizeof(struct SMPTR_CEMsM) * (smptr_cemLm + smptr_ceaLa));
		smptr_cemLm = 0;
		for (SMPTRtMI l0 = 0; l0 < Lm_s; ++l0)
		{
			const struct sM *Pm = Pm_s + l0;
			if (Pm->Sm.Um != SMPTRvM)
				for (uint8_t l1 = 0; l1 < Pm->Sm.La; ++l1)
				{
					struct SMPTR_CEMsM *Pm1 = smptr_cemPm + smptr_cemLm++;
					Pm1->Us = SMPTR_CEMuM_N;
					Pm1->Ui = l0;
					Pm1->Ua = Pm->Sm.Pa[l1];
					//! find depth
					Pm1->Fd = 0;
				}
		}
		//.i add a to SMPTR_CEMsM
		for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
		{
			struct SMPTR_CEAsA Sa = smptr_ceaPa[l0];
			struct SMPTR_CEMsM *Pm1 = smptr_cemPm + smptr_cemLm++;
			if (Sa.Sa.Ua == l0)
			{
				Pm1->Us = SMPTR_CEMuM_A;
				Pm1->Ui = l0;
				Pm1->Ua = Sa.Sa.Lv;
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
						SMPT_RD_VK_BFmFREE_DO(Vvkdevice, l0, l1, smpt_rd_vk_swcUimage)
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
			SMPT_RD_VK_BFmFREE_RE(smpt_rd_vk_swcUimage)

			//! find depth
			//.i update buffer
			//SMPT_DBmN2L("Lm_s %d", Lm_s)
			SMPTRtMI L = 0;
			for (SMPTRtMI l0 = 0; l0 < Lm_s; ++l0)
			{
				struct sM *Pm = Pm_s + l0;
				//SMPT_DBmN2L("Pm->Sm.Um %d", Pm->Sm.Um)

				if (Pm->Sm.Um != SMPTRvM)
				{
					float *Pbuffer = Pbuffer_map[smpt_rd_vk_swcUframe_buffer + l0 * smpt_rd_vk_swcUimage];
					memcpy(Pbuffer, smptr_ce_mdPb[Pm->Sm.Um], smptr_ce_mdPj[Pm->Sm.Um] * 4 * 3 * sizeof(float));
					const SMPTRtMK *Pk = smptrPmk[Pm->Sm.Uk];

//					//! wait frame
//					{
//						{
//							float Ft;
//							if (Pm->Sm.Ut < Pm->Ft * 255.0F)
//							{
//								Ft = Pk[2] - Pm->Ft + Pm->Sm.Ut / 255.0F - Pk[1];
//							}
//							else
//							{
//								Ft = Pm->Sm.Ut / 255.0F - Pm->Ft;
//							}
//	//						if (Pm->Ut[1] < Pm->Ft * 255.0F)
//	//						{
//	//							Ft = Pk[2] - Pm->Ft + Pm->Ut[1] / 255.0F - Pk[1];
//	//						}
//	//						else
//	//						{
//	//							Ft = Pm->Ut[1] / 255.0F - Pm->Ft;
//	//						}
//							Ft *= smptr_ceDdelta * smptr_ceDpartial_tick;
//							Pm->Ft += Ft;
//						}
//						Pm->Ft = SMPTMmWRAP_F(Pm->Ft, Pk[1], Pk[2]);
//					}

					//! c
//					const uint8_t Ury = 5;
//					{
//						//for (uint8_t l0 = 0; l0 < Ury; ++l0)
//						{
//							//Pm->Sm0.Ptr[l0] += (Pm->Sm.Sm0.Ptr[l0] - Pm->Sm0.Ptr[l0]) * smptr_ceDdelta * smptr_ceDpartial_tick;
//						}
//						for (uint8_t l0 = Ury; l0 < Ury + 2; ++l0)
//						{
//							float Ftr;
//							Ftr = fmodf((Pm->Sm.Sm0.Ptr[l0] - Pm->Sm0.Ptr[l0] + M_PI), 2 * M_PI);
//							if (Ftr < 0)
//							{
//								Ftr += 2 * M_PI;
//							}
//							Ftr -= M_PI;
//							Ftr *= smptr_ceDdelta * smptr_ceDpartial_tick;
//							//Pm->Sm0.Ptr[l0] += Ftr;
//						}
//					}
//					for (uint8_t l0 = Ury; l0 < Ury + 2; ++l0)
//						Pm->Sm0.Ptr[l0] = SMPTMmNORM_NF(Pm->Sm0.Ptr[l0], SMPTMmD2R(360));

					//! fix
//					float Ft;
//					if (Pm->Sm.Ut < Pm->Ft * 255.0F)
//					{
//						Ft = Pk[2] - Pm->Ft + Pm->Sm.Ut / 255.0F - Pk[1];
//					}
//					else
//					{
//						Ft = Pm->Sm.Ut / 255.0F - Pm->Ft;
//					}
//					Pm->Ft += Ft;
//					Pm->Sm0.Ptr[5] + Pm->Ft * smptr_ceDpartial_tick,
					//Pm->Ft = SMPTMmWRAP_F(Pm->Ft, Pk[1], Pk[2])
					float Ft = SMPTMmWRAP_F(Pm->Pt[1] / 255.0F, Pk[1], Pk[2]);
					float Ft_p = SMPTMmWRAP_F(Pm->Pt[0] / 255.0F, Pk[1], Pk[2]);
					//Ft = Pm->Sm0.Ptr[0] + (Ft - Pm->Sm0.Ptr[0]) * smptr_ceDpartial_tick;
					Ft = SMPTMmWRAP_F(Ft_p + SMPTMmWRAP_F(Ft - Ft_p, Pk[1], Pk[2]) * smptr_ceDpartial_tick, Pk[1], Pk[2]);
					SMPTRtMK Uks = Ft;
					float Fkf = Ft - Uks;
					SMPTRtMK Uke = SMPTMmWRAP_I(Uks + 1, Pk[1], Pk[2]);
					struct SMPTR_CE_KFs Skf = smptr_ce_kfP[Pk[0]][Uks];
					//SMPT_DBmN2L("Uks %d", Uks)
					//SMPT_DBmN2L("Fkf %f", Fkf)
					//SMPT_DBmN2L("Uke %d", Uke)
					for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
					{
						memcpy(Pbuffer + Skf.Pbone[l_0] * 4 * 3, Skf.Ps[l_0], sizeof(float) * 3);
						memcpy(Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4, Skf.Pr[l_0], sizeof(float) * 4);
						memcpy(Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4 * 2, Skf.Pt[l_0], sizeof(float) * 3);
					}

					Skf = smptr_ce_kfP[Pk[0]][Uke];
					for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
					{
						for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
						{
							(Pbuffer + Skf.Pbone[l_0] * 4 * 3)[l_3] = SMPTMmLERP((Pbuffer + Skf.Pbone[l_0] * 4 * 3)[l_3], Skf.Ps[l_0][l_3], Fkf);
							(Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4 * 2)[l_3] = SMPTMmLERP((Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4 * 2)[l_3], Skf.Pt[l_0][l_3], Fkf);
						}

//						for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
//						{
//							(Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4)[l_3] = SMPTMmLERP((Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4)[l_3], Skf.Pr[l_0][l_3], Fkf);
//						}
						smptm_v4Mnlerp(Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4, Skf.Pr[l_0], Fkf, Pbuffer + Skf.Pbone[l_0] * 4 * 3 + 4);
					}

					//.i fix
					//! c
					//! head body apply srt to fix bone
					float Pq0[4], Pq1[4];
					//SMPT_DBmN2L("lerp %f %f", Pm->Sm0.Ptr[5], Pm->Sm.Sm0.Ptr[5]);
					smptm_v4Mq
					(
						Pm->Sm0.Ptr[3] + (Pm->Sm.Sm0.Ptr[3] - Pm->Sm0.Ptr[3]) * smptr_ceDpartial_tick,
						Pm->Sm0.Ptr[5] + Mwrap_rad(Pm->Sm.Sm0.Ptr[5] - Pm->Sm0.Ptr[5]) * smptr_ceDpartial_tick,
						SMPTMmD2R(180),
						Pq0
					);
					memcpy(Pq1, Pbuffer + 4, sizeof(float) * 4);
					smptm_v4Mm(Pq1, Pq0, Pbuffer + 4);
					*(Pbuffer + 4 * 2) = Pm->Sm0.Ptr[0] + (Pm->Sm.Sm0.Ptr[0] - Pm->Sm0.Ptr[0]) * smptr_ceDpartial_tick;
					*(Pbuffer + 4 * 2 + 1) = Pm->Sm0.Ptr[1] + (Pm->Sm.Sm0.Ptr[1] - Pm->Sm0.Ptr[1]) * smptr_ceDpartial_tick;
					*(Pbuffer + 4 * 2 + 2) = Pm->Sm0.Ptr[2] + (Pm->Sm.Sm0.Ptr[2] - Pm->Sm0.Ptr[2]) * smptr_ceDpartial_tick;
					*((uint32_t *)(((uint8_t *)Pbuffer) + SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 4 * 3 * smptr_ce_mdPj[Pm->Sm.Um]))) = 0xFFFFFFFFu;
					Pvkmappedmemoryrange = realloc(Pvkmappedmemoryrange, sizeof(VkMappedMemoryRange) * (L + 1));
					Pvkmappedmemoryrange[L++] = (VkMappedMemoryRange)
					{
						.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
						.memory = Pvkdevicememory[smpt_rd_vk_swcUframe_buffer],
						.offset = 0,
						.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 4 * 3 * smptr_ce_mdPj[Pm->Sm.Um]) + sizeof(uint32_t)),
						.pNext = VK_NULL_HANDLE
					};
				}
			}
			//! animate a
	//		for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
	//		{
	//			struct SMPTR_CEAsA Sa = smptr_ceaPa[l0];
	//			if (Sa.Sa.Ua == l0)
	//			{
	//			}
	//		}
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
					if (Pvkdescriptorset_free[l0 * smpt_rd_vk_swcUimage])
					{
						vkFreeDescriptorSets(Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], smpt_rd_vk_swcUimage, Pvkdescriptorset_free + l0 * smpt_rd_vk_swcUimage);
						SMPT_RD_VK_BFmFREE_DO(Vvkdevice, l0, l1, smpt_rd_vk_swcUimage)
					}
				}
			}
			SMPT_RD_VK_BFmFREE_CLEAN
			free(Pvkdescriptorset_free);

			free(Pvkmappedmemoryrange);

			free(Pvkdescriptorbufferinfo);
			free(Pvkwritedescriptorset);

			for (SMPTRtMI l0 = 0; l0 < Lm_s; ++l0)
			{
				const struct sM *Pm = Pm_s + l0;
				if (Pm->Sm.Um != SMPTRvM)
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

		free(smptr_cemPm);

		Mfree_m(0, Lm_s);
		free(Pm_s);
	}
#endif
