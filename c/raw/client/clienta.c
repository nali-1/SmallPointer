//! check leak
#ifdef SMPT_CM_VK
	VkDescriptorSet *smptr_ceaPvkdescriptorset;

	static VkMappedMemoryRange *Pvkmappedmemoryrange;
	static uint32_t Lvkmappedmemoryrange;
	SMPT_RD_VK_BFmFREE_F
#endif

struct SMPTR_CEAsA *smptr_ceaPa;
uint32_t smptr_ceaLa = 0;

void smptr_ceaMset()
{
	smptr_ceaPa = malloc(sizeof(struct SMPTR_CEAsA));

	#ifdef SMPT_CM_VK
		SMPT_RD_VK_BFmFREE_SET
	#endif
}

#ifdef SMPT_CM_VK
	void smptr_ceaMvk()
	{
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		VkWriteDescriptorSet Pvkwritedescriptorset[SMPT_RD_VKW_DSTS_LOlGP * smpt_rd_vk_swcUimage];
		VkDescriptorBufferInfo Pvkdescriptorbufferinfo[4 + smpt_rd_vk_swcUimage];
		smptr_ceaPvkdescriptorset = malloc(sizeof(VkDescriptorSet) * smpt_rd_vk_swcUimage);
		VkDescriptorSetLayout *Pvkdescriptorsetlayout = malloc(sizeof(VkDescriptorSetLayout) * smpt_rd_vk_swcUimage);
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
			Pvkdescriptorsetlayout[l0] = smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuGP];
		SMPT_RD_VKW_DSTSmMAKE(SMPT_RD_VKQuGP, SMPT_RD_VKW_DSTSuGP, Pvkdescriptorsetlayout, smpt_rd_vk_swcUimage, smptr_ceaPvkdescriptorset)
		free(Pvkdescriptorsetlayout);
		//.i bindpose s 1+
		Pvkdescriptorbufferinfo[0] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M],
			.offset = 0,
			.range = 1
		};
		//.i src_color s
		Pvkdescriptorbufferinfo[1] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M],
			.offset = SMPTR_CE_MDuRGBA,
			.range = smptr_ce_mdLrgba
		};

		//.i animate d
		Pvkdescriptorbufferinfo[2] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_D],
			.offset = 0,
			.range = sizeof(float) * 4 * 3
		};
		//.i color d
		Pvkdescriptorbufferinfo[3] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_D],
			.offset = SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 4 * 3),
			.range = sizeof(uint32_t)
		};
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
		{
			//.i gui/world d
			Pvkdescriptorbufferinfo[4 + l0] = (VkDescriptorBufferInfo)
			{
				.buffer = smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_VP_P + l0],
				.offset = 0,
				.range = sizeof(float) * 16 * 2
			};
			SMPT_RD_VKWmDSTS(0, NULL, Pvkdescriptorbufferinfo + 4 + l0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOlGP]);
			SMPT_RD_VKWmDSTS(1, NULL, Pvkdescriptorbufferinfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOlGP + 1]);
			SMPT_RD_VKWmDSTS(2, NULL, Pvkdescriptorbufferinfo + 2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOlGP + 2]);
			SMPT_RD_VKWmDSTS(3, NULL, Pvkdescriptorbufferinfo + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOlGP + 3]);
			SMPT_RD_VKWmDSTS(4, NULL, Pvkdescriptorbufferinfo + 3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOlGP + 4]);
		}
		vkUpdateDescriptorSets(Vvkdevice, SMPT_RD_VKW_DSTS_LOlGP * smpt_rd_vk_swcUimage, Pvkwritedescriptorset, 0, NULL);

		Pvkmappedmemoryrange = malloc(sizeof(VkMappedMemoryRange));
	}
#endif

static void Mfree_a(SMPTRtA Us, SMPTRtA Ue)
{
	for (SMPTRtA l0 = Us; l0 < Ue; ++l0)
	{
		free(smptr_ceaPa[l0].Sa.Pv);
		free(smptr_ceaPa[l0].Sa.Pc);
	}
}

static void Mfree_vk(SMPTRtA Us, SMPTRtA Ue)
{
//	SMPT_DBmN2L("Us %d", Us)
//	SMPT_DBmN2L("Ue %d", Ue)
//	SMPT_DBmN2L("Lfree %d", Lfree)
	SMPT_RD_VK_BFmFREE_HELP(smptr_ce_mdPvkbuffer + SMPTR_CE_MDuBUFFER_A, smptr_ce_mdPvkdevicememory + SMPTR_CE_MDuBUFFER_A, 1)
//	SMPT_DBmN2L("Lfree %d", Lfree)
}

//.i sync n-mn
static SMPTRtA La0 = 0;
void smptr_ceaMread()
{
	//.i get data
	SMPTRtA Ucount = *(SMPTRtA *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(SMPTRtA);

	Mfree_a(Ucount, smptr_ceaLa);
	//SMPT_DBmN2L("smptr_ceaLa %d", smptr_ceaLa)
	//SMPT_DBmN2L("Ucount %d", Ucount)
	smptr_ceaPa = realloc(smptr_ceaPa, Ucount ? sizeof(struct SMPTR_CEAsA) * Ucount : sizeof(struct SMPTR_CEAsA));
	for (SMPTRtA l0 = smptr_ceaLa; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;

		Pa->Sa.Pv = malloc(sizeof(float));
		Pa->Sa.Pc = malloc(sizeof(uint8_t));

		//.i Usync > 0
		Pa->Sa.Usync = 0;
	}
	smptr_ceaLa = Ucount;

	//SMPT_DBmN2L("Ucount %d", Ucount)
	for (SMPTRtA l0 = 0; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;

		Pa->Sa.Ua = *(SMPTRtA *)(smptr_cePnet + smptr_ceLnet);
		smptr_ceLnet += sizeof(SMPTRtA);
		//SMPT_DBmN2L("Pa->Sa.Ua %d", Pa->Sa.Ua)
		if (Pa->Sa.Ua == l0)
		{
			Pa->Sa.Lv = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pa->Sa.Pv = realloc(Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv);
			memcpy(Pa->Sa.Pv, smptr_cePnet + smptr_ceLnet, sizeof(float) * 3 * Pa->Sa.Lv);
			smptr_ceLnet += sizeof(float) * 3 * Pa->Sa.Lv;

			Pa->Sa.Pc = realloc(Pa->Sa.Pc, sizeof(uint8_t) * Pa->Sa.Lv);
			memcpy(Pa->Sa.Pc, smptr_cePnet + smptr_ceLnet, sizeof(uint8_t) * Pa->Sa.Lv);
			smptr_ceLnet += sizeof(uint8_t) * Pa->Sa.Lv;

			Pa->Sa.Usync = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);
		}
	}

	//.i clean a0
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		if (smptr_ceaLa < La0)
			Mfree_vk(smptr_ceaLa, La0);
		smptr_ce_mdPvkbuffer = realloc(smptr_ce_mdPvkbuffer, sizeof(VkBuffer) * (SMPTR_CE_MDuBUFFER_A + smptr_ceaLa));
		smptr_ce_mdPvkdevicememory = realloc(smptr_ce_mdPvkdevicememory, sizeof(VkDeviceMemory) * (SMPTR_CE_MDuBUFFER_A + smptr_ceaLa));
		smptr_ce_mdPbuffer_map = realloc(smptr_ce_mdPbuffer_map, sizeof(void *) * (SMPTR_CE_MDuBUFFER_A + smptr_ceaLa));
		for (SMPTRtA l0 = La0; l0 < smptr_ceaLa; ++l0)
			smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0] = 0;
	#endif

	//.i update a
	for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;

		if (Pa->Sa.Ua != l0)
		{
			if (smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0])
			{
				//SMPT_DBmN2L("a0")
				Mfree_vk(l0, l0 + 1);
				smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0] = 0;
			}
		}
		else
		{
			#ifdef SMPT_CM_VK
				if
				(
					La0 <= l0 || !smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0] ||
					Pa->Sa.Usync != Pa->Usync
				)
			#endif
			{
				//SMPT_DBmN2L("a1")
				#ifdef SMPT_CM_VK
					if (smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0])
					{
						Mfree_vk(l0, l0 + 1);
						smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0] = 0;
					}

					Pvkmappedmemoryrange = realloc(Pvkmappedmemoryrange, sizeof(VkMappedMemoryRange) * (Lvkmappedmemoryrange + 1));
					VkDeviceSize vkdevicesize = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, (sizeof(float) * 3 + sizeof(uint8_t) + sizeof(uint8_t)) * Pa->Sa.Lv);
					//VkDeviceSize vkdevicesize = (sizeof(float) * 3 + sizeof(uint32_t)) * Pa->Sa.Lv;

					VkMemoryRequirements vkmemoryrequirements;
					//! compute then draw
					SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuGP, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0], smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_A + l0], vkmemoryrequirements)
					vkMapMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_A + l0], 0, vkdevicesize, 0, &smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_A + l0]);
					for (uint8_t l2 = 0; l2 < Pa->Sa.Lv; ++l2)
					{
						memcpy(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_A + l0] + l2 * (sizeof(float) * 3 + sizeof(uint8_t) + sizeof(uint8_t)), Pa->Sa.Pv + l2 * 3, sizeof(float) * 3);
						*(uint8_t *)(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_A + l0] + l2 * (sizeof(float) * 3 + sizeof(uint8_t) + sizeof(uint8_t)) + sizeof(float) * 3) = Pa->Sa.Pc[l2];
						*(uint8_t *)(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_A + l0] + l2 * (sizeof(float) * 3 + sizeof(uint8_t) + sizeof(uint8_t)) + sizeof(float) * 3 + sizeof(uint8_t)) = 0;
					}

					Pvkmappedmemoryrange[Lvkmappedmemoryrange++] = (VkMappedMemoryRange)
					{
						.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
						.memory = smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_A + l0],
						.offset = 0,
						.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, (sizeof(float) * 3 + sizeof(uint8_t) + sizeof(uint8_t)) * Pa->Sa.Lv),
						.pNext = NULL
					};
				#endif

				Pa->Usync = Pa->Sa.Usync;
			}
		}
	}
	if (Lvkmappedmemoryrange)
	{
		vkFlushMappedMemoryRanges(Vvkdevice, Lvkmappedmemoryrange, Pvkmappedmemoryrange);
		Pvkmappedmemoryrange = realloc(Pvkmappedmemoryrange, sizeof(VkMappedMemoryRange));
		Lvkmappedmemoryrange = 0;
	}
	La0 = smptr_ceaLa;
}

//! update Stsp_e to sync later
void smptr_ceaMloop()
{
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		//.i free
		uint32_t Ufree = Lfree;
		for (uint32_t l0 = 0; l0 < Lfree; ++l0)
		{
			if (SMPT_RD_VK_BFmFREE_ABLE(l0))
			{
				if (Pvkbuffer_free[l0])
				{
					SMPT_RD_VK_BFmFREE_DO(Vvkdevice, l0, l1, 1)
					Pvkbuffer_free[l0] = 0;
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
		SMPT_RD_VK_BFmFREE_RE(1)

		//.i a to m1
	#endif
}

void smptr_ceaMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		if (Lfree)
		{
			for (uint32_t l0 = 0; l0 < Lfree; ++l0)
			{
				if (Pvkbuffer_free[l0])
				{
					SMPT_RD_VK_BFmFREE_DO(Vvkdevice, l0, l1, 1)
				}
			}
		}
		SMPT_RD_VK_BFmFREE_CLEAN

		vkFreeDescriptorSets(Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], smpt_rd_vk_swcUimage, smptr_ceaPvkdescriptorset);
		//SMPT_DBmN2L("smptr_ceaLa %d", smptr_ceaLa)
		for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
		{
			//SMPT_DBmN2L("smptr_ceaPa[l0].Sa.Ua %d", smptr_ceaPa[l0].Sa.Ua)
			//SMPT_DBmN2L("l0 %d", l0)
			if (smptr_ceaPa[l0].Sa.Ua == l0)
			{
				vkUnmapMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_A + l0]);
				vkDestroyBuffer(Vvkdevice, smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + l0], NULL);
				vkFreeMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_A + l0], NULL);
			}
		}
		smptr_ce_mdPvkbuffer = realloc(smptr_ce_mdPvkbuffer, sizeof(VkBuffer) * SMPTR_CE_MDuBUFFER_A);
		smptr_ce_mdPvkdevicememory = realloc(smptr_ce_mdPvkdevicememory, sizeof(VkDeviceMemory) * SMPTR_CE_MDuBUFFER_A);
		smptr_ce_mdPbuffer_map = realloc(smptr_ce_mdPbuffer_map, sizeof(void *) * SMPTR_CE_MDuBUFFER_A);

		free(smptr_ceaPvkdescriptorset);
	#endif

	Mfree_a(0, smptr_ceaLa);
	free(smptr_ceaPa);

	free(Pvkmappedmemoryrange);
}
