struct SMPTRsU smptr_ceuSu = {0};
uint8_t smpt_ceuPinput[SMPT_IPlL] = {0};
float smpt_ceuPpoint[2] = {0};

//! use on m
//static struct SMPTRsU smptr_ceuSu0 = {0}, smptr_ceuSu1 = {0}, smptr_ceuSu2 = {0};
//static uint8_t smptr_ceuUu0 = 0;
//static float smptr_ceuPu1[sizeof(smptr_ceuSu0.Ptr)] = {0};

void smptr_ceuMset()
{
}

static float
	Pt[4],

	Pq0_m4x4[16] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	},
	Pq1_m4x4[16],
	Pq2_m4x4[16];

static uint8_t Ustate = 0;
void smptr_ceuMsend()
{
	if (!(Ustate & 1))
		return;
	memcpy(smptr_cePnet + smptr_ceLnet, &smptr_ceuSu, sizeof(struct SMPTRsU));
	smptr_ceLnet += sizeof(struct SMPTRsU);
}

void smptr_ceuMread()
{
	if (!(Ustate & 1))
	{
		memcpy(&smptr_ceuSu, smptr_cePnet + smptr_ceLnet, sizeof(struct SMPTRsU));
		Ustate |= 1;
	}
	smptr_ceLnet += sizeof(struct SMPTRsU);
}

void smptr_ceuMloop()
{
	if (!(Ustate & 1))
		return;
	//! use on m
//	if (memcmp(smptr_ceuSu2.Ptr, smptr_ceuSu.Ptr, sizeof(smptr_ceuSu.Ptr)))
//	{
//		smptr_ceuUu0 = 0;
//		for (uint8_t l0 = 0; l0 < 4; ++l0)
//		{
//			smptr_ceuPu1[l0] = (smptr_ceuSu.Ptr[l0] - smptr_ceuSu0.Ptr[l0]) * SMPTR_CEuDELTA;
//		}
//		smptr_ceuPu1[4] = fmodf((smptr_ceuSu.Ptr[4] - smptr_ceuSu0.Ptr[4] + M_PI), 2 * M_PI);
//		if (smptr_ceuPu1[4] < 0)
//		{
//			smptr_ceuPu1[4] += 2 * M_PI;
//		}
//		smptr_ceuPu1[4] -= M_PI;
//		smptr_ceuPu1[4] *= SMPTR_CEuDELTA;
//		memcpy(smptr_ceuSu2.Ptr, smptr_ceuSu.Ptr, sizeof(smptr_ceuSu.Ptr));
//	}
//	if (smptr_ceuUu0 != SMPTR_CEuFPS)
//	{
//		for (uint8_t l0 = 0; l0 < 5; ++l0)
//		{
//			smptr_ceuSu0.Ptr[l0] += smptr_ceuPu1[l0];
//		}
//		smptr_ceuSu0.Ptr[4] = SMPTMmNORM_NF(smptr_ceuSu0.Ptr[4], SMPTMmD2R(360));
//		++smptr_ceuUu0;
//	}
	float *Pbuffer = smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_VP_P + smpt_rd_vk_swcUframe_buffer];

	if (smpt_ceuPinput[0] & SMPT_IPuKEY_SPACE)
		smptr_ceuSu.Ptr[1] += 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_LEFT_SHIFT)
		smptr_ceuSu.Ptr[1] -= 2 * smptr_ceDdelta;

	smptr_ceuSu.Ptr[4] += smpt_ceuPpoint[0] * smptr_ceDdelta;
	smptr_ceuSu.Ptr[3] -= smpt_ceuPpoint[1] * smptr_ceDdelta;
	memset(smpt_ceuPpoint, 0, sizeof(float) * 2);

	if (smptr_ceuSu.Ptr[3] > SMPTMmD2R(90.0F))
	{
		smptr_ceuSu.Ptr[3] = SMPTMmD2R(90.0F);
	}
	else if (smptr_ceuSu.Ptr[3] < SMPTMmD2R(-90.0F))
	{
		smptr_ceuSu.Ptr[3] = SMPTMmD2R(-90.0F);
	}
	smptr_ceuSu.Ptr[4] = SMPTMmNORM_NF(smptr_ceuSu.Ptr[4], SMPTMmD2R(360));

	VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

	memcpy(Pbuffer, smptm_m4x4P, sizeof(float) * 16);

	smptm_v4Mq(0, smptr_ceuSu.Ptr[4], 0, Pt);
	smptm_v4Mq2m(Pt, Pq0_m4x4);
	memcpy(Pq1_m4x4, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(Pq1_m4x4, Pq0_m4x4, Pbuffer);

	//.i fix t
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_A)
		Pt[2] += 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_D)
		Pt[2] -= 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_W)
		Pt[0] -= 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_S)
		Pt[0] += 2 * smptr_ceDdelta;
	Pt[3] = 0;
	smptm_v4Mm4(Pbuffer, Pt, Pq1_m4x4);
	smptr_ceuSu.Ptr[0] += Pq1_m4x4[2];
	smptr_ceuSu.Ptr[2] += Pq1_m4x4[0];

	smptm_v4Mq(smptr_ceuSu.Ptr[3], 0, 0, Pt);
	smptm_v4Mq2m(Pt, Pq0_m4x4);
	memcpy(Pq1_m4x4, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(Pq1_m4x4, Pq0_m4x4, Pbuffer);

	memcpy(Pq2_m4x4, smptm_m4x4P, sizeof(float) * 16);

	Pq2_m4x4[12] = smptr_ceuSu.Ptr[0];
	Pq2_m4x4[13] = smptr_ceuSu.Ptr[1];
	Pq2_m4x4[14] = smptr_ceuSu.Ptr[2];
	memcpy(Pq1_m4x4, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(Pq2_m4x4, Pq1_m4x4, Pbuffer);

	vkFlushMappedMemoryRanges(Vvkdevice, 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_VP_P + smpt_rd_vk_swcUframe_buffer],
		.offset = 0,
		.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, sizeof(float) * 16),
		.pNext = VK_NULL_HANDLE
	});
}

void smptr_ceuMfree()
{
}
