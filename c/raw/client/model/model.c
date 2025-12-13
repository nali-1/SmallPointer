SMPTRtJW *smptr_ce_mdPj;
SMPTRtJWL smptr_ce_mdLj;
uint8_t **smptr_ce_mdPb;

SMPTRtRGBAL smptr_ce_mdLrgba;

#ifdef SMPT_CM_VK
	VkDeviceSize smptr_ce_mdPli[SMPTRcMA + 1];
	uint32_t smptr_ce_mdPil[SMPTRcMA];

	VkBuffer *smptr_ce_mdPvkbuffer;
	VkDeviceMemory *smptr_ce_mdPvkdevicememory;
	void **smptr_ce_mdPbuffer_map;
	VkDeviceSize *smptr_ce_mdPvkdevicesize;
#endif

struct sBONE
{
	SMPTRtJW *Pj;
	SMPTRtJWL Lj;
};

//! free and clean
static struct sBONE *Pbone;

#ifdef SMPT_CM_GL
	SMPTRtI *smptr_ce_mdPi[SMPTRcMA];
	SMPTRtI smptr_ce_mdPil_l[SMPTRcMA];
	uint8_t *smptr_ce_mdPa;
	uint32_t smptr_ce_mdLa;
	float **smptr_ce_mdPbp;
	uint32_t *smptr_ce_mdPrgba;
#else
	static SMPTRtI *smptr_ce_mdPi[SMPTRcMA];
	static SMPTRtI smptr_ce_mdPil_l[SMPTRcMA];
	static uint8_t *smptr_ce_mdPa;
	static uint32_t smptr_ce_mdLa;
	static float **smptr_ce_mdPbp;
	static uint32_t *smptr_ce_mdPrgba;
#endif

void smptr_ce_mdMset()
{
	smptr_ce_mdLj = *(SMPTRtJWL *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptrPcache->d_bl_p[1] += sizeof(uint8_t);

	smptrPcache->bs_p = malloc(sizeof(uint16_t *) * smptr_ce_mdLj);
	smptrPcache->be_p = malloc(sizeof(uint16_t *) * smptr_ce_mdLj);

	smptr_ce_mdPj = malloc(sizeof(SMPTRtJW) * smptr_ce_mdLj);
	memcpy(smptr_ce_mdPj, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_ce_mdLj);
	smptrPcache->d_bl_p[1] += smptr_ce_mdLj;

	uint16_t Lbone = 0;
	Pbone = malloc(0);

	smptr_ce_mdPbp = malloc(sizeof(float *) * smptr_ce_mdLj);
	smptr_ce_mdPb = malloc(sizeof(uint8_t *) * smptr_ce_mdLj);

	#ifdef SMPT_CM_VK
		smptr_ce_mdPvkdevicesize = malloc(sizeof(VkDeviceSize) * smptr_ce_mdLj);
	#endif

	for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		SMPT_DBmN2L("U0 %d", l0);
		#ifdef SMPT_CM_DEBUG
			uint32_t Lloop_bone_all = 0;
			uint32_t Lloop_bone_true = 0;
		#endif
		smptrPcache->bs_p[l0] = malloc(sizeof(uint16_t) * smptr_ce_mdPj[l0]);
		smptrPcache->be_p[l0] = malloc(sizeof(uint16_t) * smptr_ce_mdPj[l0]);
		smptrPcache->bs_p[l0][0] = 0;

		Pbone = realloc(Pbone, sizeof(struct sBONE) * (Lbone + smptr_ce_mdPj[l0]));
		smptr_ce_mdPbp[l0] = malloc(sizeof(float) * 16 * 2 * (smptr_ce_mdPj[l0] - 1));

		for (SMPTRtJW l_1 = 0; l_1 < smptr_ce_mdPj[l0]; ++l_1)
		{
			SMPTRtJWL size = *(SMPTRtJWL *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			#ifdef SMPT_CM_DEBUG
				SMPT_DBmN2L("size %d", size);
				Lloop_bone_all += size + 2;
				Lloop_bone_true += size;
			#endif
			smptrPcache->d_bl_p[1] += sizeof(uint8_t);

			memset(Pbone + Lbone + l_1, 0, sizeof(struct sBONE));
			if (l_1 != 0)
			{
				smptrPcache->bs_p[l0][l_1] = smptrPcache->be_p[l0][l_1 - 1];
			}
			Pbone[Lbone + l_1].Lj = size;
			Pbone[Lbone + l_1].Pj = malloc(size);
			memcpy(Pbone[Lbone + l_1].Pj, smptrPcache->d_p + smptrPcache->d_bl_p[1], size);
			smptrPcache->be_p[l0][l_1] = smptrPcache->bs_p[l0][l_1] + size;
			smptrPcache->d_bl_p[1] += size;
		}
		SMPT_DBmN2L("Lloop_bone_all %d", Lloop_bone_all + 1);
		SMPT_DBmN2L("Lloop_bone_true %d", Lloop_bone_true);
		smptrPcache->bs_p[l0][0] = 0xFFFFu;

		Lbone += smptr_ce_mdPj[l0];
	}

	for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		for (SMPTRtJW l_1 = 0; l_1 < smptr_ce_mdPj[l0] - 1; ++l_1)
		{
			memcpy(smptr_ce_mdPbp[l0] + l_1 * 16 * 2, smptrPcache->d_p + smptrPcache->d_bl_p[1] + l_1 * sizeof(float) * 16, sizeof(float) * 16);
			memcpy(smptr_ce_mdPbp[l0] + l_1 * 16 * 2 + 16, smptr_ce_mdPbp[l0] + l_1 * 16 * 2, sizeof(float) * 16);
			smptm_m4x4Mi(smptr_ce_mdPbp[l0] + l_1 * 16 * 2 + 16);
		}
		smptrPcache->d_bl_p[1] += sizeof(float) * 16 * (smptr_ce_mdPj[l0] - 1);
	}

	SMPT_DBmN2L("smptrPcache->d_bl_p[1] %d", smptrPcache->d_bl_p[1])
	uint32_t l_step = 0;

	for (SMPTRtMA l0 = 0; l0 < SMPTRcMA; ++l0)
	{
		smptr_ce_mdPil_l[l0] = *(SMPTRtI *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]) * sizeof(SMPTRtI);
		smptrPcache->d_bl_p[1] += sizeof(SMPTRtI);

		SMPT_DBmN2L("smptr_ce_mdPil_l[%d] %d", l0, smptr_ce_mdPil_l[l0])

		smptr_ce_mdPi[l0] = malloc(smptr_ce_mdPil_l[l0]);
		memcpy(smptr_ce_mdPi[l0], smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_ce_mdPil_l[l0]);
		smptrPcache->d_bl_p[1] += smptr_ce_mdPil_l[l0];
		#ifdef SMPT_CM_VK
			smptr_ce_mdPil[l0] = smptr_ce_mdPil_l[l0] / sizeof(SMPTRtI);
		#endif
	}
	SMPT_DBmN2L("smptrPcache->d_bl_p[1] %d", smptrPcache->d_bl_p[1])

	smptr_ce_mdLrgba = *(SMPTRtRGBAL *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]) * sizeof(uint32_t);
	smptrPcache->d_bl_p[1] += sizeof(SMPTRtRGBAL);

	SMPT_DBmN2L("Lrgba %d", smptr_ce_mdLrgba / sizeof(uint32_t))
	smptr_ce_mdPrgba = malloc(smptr_ce_mdLrgba);
	memcpy(smptr_ce_mdPrgba, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_ce_mdLrgba);
	smptrPcache->d_bl_p[1] += smptr_ce_mdLrgba;
	//.i pow Prgba
	for (uint32_t l0 = 0; l0 < smptr_ce_mdLrgba / sizeof(uint32_t); ++l0)
	{
		smptr_ce_mdPrgba[l0] =
			(uint8_t)(powf((smptr_ce_mdPrgba[l0] >> (8+8+8)) / 255.0F, 1.0F / 5.0F) * 255) << (8+8+8) |
			(uint8_t)(powf((smptr_ce_mdPrgba[l0] >> (8+8) & 255) / 255.0F, 1.0F / 5.0F) * 255) << (8+8) |
			(uint8_t)(powf(((smptr_ce_mdPrgba[l0] >> 8) & 255) / 255.0F, 1.0F / 5.0F) * 255) << 8 |
			(uint8_t)(smptr_ce_mdPrgba[l0] & 255);
		SMPT_DBmN2L("Uc %d", l0)
		SMPT_DBmN2L("U32 %08X", smptr_ce_mdPrgba[l0])
		SMPT_DBmN2L("rf %f", (smptr_ce_mdPrgba[l0] >> (8+8+8)) / 255.0F)
		SMPT_DBmN2L("gf %f", ((smptr_ce_mdPrgba[l0] >> (8+8)) & 255) / 255.0F)
		SMPT_DBmN2L("bf %f", ((smptr_ce_mdPrgba[l0] >> 8) & 255) / 255.0F)
		SMPT_DBmN2L("af %f", (smptr_ce_mdPrgba[l0] & 255) / 255.0F)
	}

	smptr_ce_mdLa = smptrPcache->d_bl_p[0] - smptrPcache->d_bl_p[1];
//		uint32_t La0 = smptr_ce_mdLa / (sizeof(float) * 3 + 2);
//		smptr_ce_mdLa += La0 * 2;
	smptr_ce_mdPa = malloc(smptr_ce_mdLa);
//		for (uint32_t l0 = 0; l0 < La0; ++l0)
//		{
//			memcpy(smptr_ce_mdPa + l0 * (sizeof(float) * 3 + sizeof(uint32_t)), smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3 + 2);
//			memset((smptr_ce_mdPa + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 2)), 0, 2);
//			//t. s0-test j
//			//memset((smptr_ce_mdPa + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)), 0, 3);
//			//*(uint8_t *)(smptr_ce_mdPa + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)) = 40;
//			//t. e0-test j
////			if ((smptrPcache->d_p + smptrPcache->d_bl_p[1] + sizeof(float) * 3 + 1) == 0)
////			{
////				SMPT_DBmN2L("nali_buffer c1j1 j0 %d", (smptrPcache->d_p + smptrPcache->d_bl_p[1] + sizeof(float) * 3 + 1))
////			}
//			smptrPcache->d_bl_p[1] += sizeof(float) * 3 + 2;
//		}
	memcpy(smptr_ce_mdPa, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_ce_mdLa);
	smptrPcache->d_bl_p[1] += smptr_ce_mdLa;
	if (smptrPcache->d_bl_p[0] != smptrPcache->d_bl_p[1])
		SMPT_DBmW2L("smptr_ce_mdMset")

	//.i set default a
	for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		l_step = 0;
		smptr_ce_mdPb[l0] = malloc(sizeof(float) * 4 * 3 * smptr_ce_mdPj[l0]);

		for (SMPTRtJW l_1 = 0; l_1 < smptr_ce_mdPj[l0]; ++l_1)
		{
			//.i s
			for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
			{
				*(float *)(smptr_ce_mdPb[l0] + l_step + l_2 * sizeof(float)) = 1;
			}
			//.i b_s b_e
			*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float)) = smptrPcache->bs_p[l0][l_1] | smptrPcache->be_p[l0][l_1] << (8 + 8);
			//.t bs_p be_p
			//*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float)) = 51 | 51 << (8 + 8);
			l_step += 4 * sizeof(float);

			//.i r
			memcpy(smptr_ce_mdPb[l0] + l_step, smptm_m4x4P + 12, 4 * sizeof(float));
			l_step += 4 * sizeof(float);

			//.i t
			memset(smptr_ce_mdPb[l0] + l_step, 0, 4 * sizeof(float));
			//.t a->t vec4
			//*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float)) = 0xFFFFFFFFu;
			l_step += 4 * sizeof(float);
		}

		free(smptrPcache->bs_p[l0]);
		free(smptrPcache->be_p[l0]);
	}
	free(smptrPcache->bs_p);
	free(smptrPcache->be_p);

	//.i b
	Lbone = 0;
	for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		l_step = 0;
		uint8_t l_0_0 = 0;

		for (SMPTRtJW l_1 = 0; l_1 < smptr_ce_mdPj[l0]; ++l_1)
		{
			for (SMPTRtJWL l_2 = 0; l_2 < Pbone[Lbone + l_1].Lj; ++l_2)
			{
				*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float) + sizeof(float) * 4 * 2) |= Pbone[Lbone + l_1].Pj[l_2] << l_0_0 * 8;
				//.t Pbone
				//*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float) + sizeof(float) * 4 * 2) |= 51 << l_0_0 * 8;

				if (++l_0_0 == 4)
				{
					l_step += sizeof(float) * 4 * 3;
					l_0_0 = 0;
				}
			}
		}

		Lbone += smptr_ce_mdPj[l0];
	}
}

#ifdef SMPT_CM_VK
	void smptr_ce_mdMvk()
	{
		VkMappedMemoryRange Pvkmappedmemoryrange[2 + smpt_rd_vk_swcUimage];
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		smptr_ce_mdPvkbuffer = malloc(sizeof(VkBuffer) * SMPTR_CE_MDuBUFFER_A);
		smptr_ce_mdPvkdevicememory = malloc(sizeof(VkDeviceMemory) * SMPTR_CE_MDuBUFFER_A);
		smptr_ce_mdPbuffer_map = malloc(sizeof(void *) * SMPTR_CE_MDuBUFFER_A);

		VkDeviceSize Vvkdevicesize = SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, smptr_ce_mdLrgba);

		for (SMPTRtMA l0 = 0; l0 < SMPTRcMA; ++l0)
		{
			smptr_ce_mdPli[l0] = Vvkdevicesize;
			Vvkdevicesize += smptr_ce_mdPil_l[l0];
		}

		smptr_ce_mdPli[SMPTRcMA] = Vvkdevicesize;
		Vvkdevicesize += smptr_ce_mdLa;
		Vvkdevicesize = SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, Vvkdevicesize);

		for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
		{
			smptr_ce_mdPvkdevicesize[l0] = Vvkdevicesize;
			Vvkdevicesize += SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 16 * 2 * smptr_ce_mdPj[l0]);
		}

		VkMemoryRequirements vkmemoryrequirements;
		Vvkdevicesize = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, Vvkdevicesize);
		SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuGP, Vvkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M], smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_M], vkmemoryrequirements)
		SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_M], 0, Vvkdevicesize, 0, &smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_M]))

		//.i a
		Vvkdevicesize = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 4 * 3) + sizeof(uint32_t));
		SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuGP, Vvkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_D], smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_D], vkmemoryrequirements)
		SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_D], 0, Vvkdevicesize, 0, &smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_D]))
		memcpy(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_D], smptm_v4Psrt, sizeof(float) * 4 * 3);
		*((uint32_t *)(((uint8_t *)smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_D]) + SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 4 * 3))) = 0xFFFFFFFFu;
		Pvkmappedmemoryrange[1] = (VkMappedMemoryRange)
		{
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.memory = smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_D],
			.offset = 0,
			.size = Vvkdevicesize,
			.pNext = VK_NULL_HANDLE
		};

		//.i gui world
		Vvkdevicesize = sizeof(float) * 16 * 2;
		for (uint8_t l0 = SMPTR_CE_MDuBUFFER_VP_P; l0 < SMPTR_CE_MDuBUFFER_A; ++l0)
		{
			SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuGP, Vvkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[l0], smptr_ce_mdPvkdevicememory[l0], vkmemoryrequirements)
			SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[l0], 0, Vvkdevicesize, 0, &smptr_ce_mdPbuffer_map[l0]))
		}
		for (uint8_t l0 = SMPTR_CE_MDuBUFFER_VP_P; l0 < SMPTR_CE_MDuBUFFER_VP_N; ++l0)
		{
			memset(smptr_ce_mdPbuffer_map[l0] + sizeof(float) * 16, 0, sizeof(float) * 16);
		}
		for (uint8_t l0 = SMPTR_CE_MDuBUFFER_VP_N; l0 < SMPTR_CE_MDuBUFFER_A; ++l0)
		{
			memcpy(smptr_ce_mdPbuffer_map[l0], smptm_m4x4P, sizeof(float) * 16);
			memcpy(smptr_ce_mdPbuffer_map[l0] + sizeof(float) * 16, smptm_m4x4P, sizeof(float) * 16);

			Pvkmappedmemoryrange[2 + l0 - SMPTR_CE_MDuBUFFER_VP_N] = (VkMappedMemoryRange)
			{
				.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
				.memory = smptr_ce_mdPvkdevicememory[l0],
				.offset = 0,
				.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, sizeof(float) * 16 * 2),
				.pNext = VK_NULL_HANDLE
			};
		}

		//.i rgba
		memcpy(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_M], smptr_ce_mdPrgba, smptr_ce_mdLrgba);
		Vvkdevicesize = SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, smptr_ce_mdLrgba);

		//.i ai index
		for (SMPTRtMA l0 = 0; l0 < SMPTRcMA; ++l0)
		{
			memcpy(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_M] + Vvkdevicesize, smptr_ce_mdPi[l0], smptr_ce_mdPil_l[l0]);
			Vvkdevicesize += smptr_ce_mdPil_l[l0];
		}

		//.i a
		memcpy(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_M] + Vvkdevicesize, smptr_ce_mdPa, smptr_ce_mdLa);
		Vvkdevicesize += smptr_ce_mdLa;
		Vvkdevicesize = SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, Vvkdevicesize);

		//.i UBOB
		for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
		{
			memcpy(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_M] + Vvkdevicesize + sizeof(float) * 16 * 2, smptr_ce_mdPbp[l0], sizeof(float) * 16 * 2 * (smptr_ce_mdPj[l0] - 1));
			Vvkdevicesize += SMPT_RD_VKQmSIZE_UBO(SMPT_RD_VKQuGP, sizeof(float) * 16 * 2 * smptr_ce_mdPj[l0]);
		}
		Pvkmappedmemoryrange[0] = (VkMappedMemoryRange)
		{
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.memory = smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_M],
			.offset = 0,
			.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, Vvkdevicesize),
			.pNext = VK_NULL_HANDLE
		};

		vkFlushMappedMemoryRanges(Vvkdevice, 2 + smpt_rd_vk_swcUimage, Pvkmappedmemoryrange);
	}
#endif

void smptr_ce_mdMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

		for (uint8_t l0 = 0; l0 < SMPTR_CE_MDuBUFFER_A; ++l0)
		{
			vkUnmapMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[l0]);
			vkDestroyBuffer(Vvkdevice, smptr_ce_mdPvkbuffer[l0], VK_NULL_HANDLE);
			vkFreeMemory(Vvkdevice, smptr_ce_mdPvkdevicememory[l0], VK_NULL_HANDLE);
		}
		free(smptr_ce_mdPvkbuffer);
		free(smptr_ce_mdPvkdevicememory);
		free(smptr_ce_mdPbuffer_map);

		free(smptr_ce_mdPvkdevicesize);
	#endif

	for (SMPTRtJWL l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		free(smptr_ce_mdPbp[l0]);
		free(smptr_ce_mdPb[l0]);

		free(Pbone[l0].Pj);
	}
	free(smptr_ce_mdPbp);
	free(smptr_ce_mdPb);

	free(smptr_ce_mdPj);

	free(Pbone);

	for (SMPTRtMA l0 = 0; l0 < SMPTRcMA; ++l0)
	{
		free(smptr_ce_mdPi[l0]);
	}

	free(smptr_ce_mdPa);

	free(smptr_ce_mdPrgba);
}
