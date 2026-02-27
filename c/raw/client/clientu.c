struct SMPTRsU smptr_ceuSu = {0};
uint8_t smpt_ceuPinput[SMPT_IPlL] = {0};
float smpt_ceuPpoint[2] = {0};

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

void smptr_ceuMsend()
{
	//SMPT_DBmN2L("smptr_ceuMsend")

	memcpy(smptr_cePnet + smptr_ceLnet, &smptr_ceuSu, sizeof(struct SMPTRsU));
	smptr_ceLnet += sizeof(struct SMPTRsU);
}

void smptr_ceuMread()
{
	//SMPT_DBmN2L("smptr_ceuMread")
	if (!(smptr_ceUstate & 1))
	{
//		SMPT_DBmN2L("smptr_ceLnet %d", smptr_ceLnet)
		memcpy(&smptr_ceuSu, smptr_cePnet + smptr_ceLnet, sizeof(struct SMPTRsU));
//		for (uint8_t l0 = 0; l0 < 5; ++l0)
//			SMPT_DBmN2L("(float *)(smptr_cePnet + smptr_ceLnet)[%d] %f", l0, ((float *)(smptr_cePnet + smptr_ceLnet))[l0])
//		for (uint8_t l0 = 0; l0 < 5; ++l0)
//			SMPT_DBmN2L("smptr_ceuSu.Ptr[%d] %f", l0, smptr_ceuSu.Ptr[l0])
		smptr_ceUstate |= 1;
	}
	smptr_ceLnet += sizeof(struct SMPTRsU);
}

void smptr_ceuMloop()
{
	if (!(smptr_ceUstate & 1))
		return;
	//SMPT_DBmN2L("smptr_ceuMloop")

	float *Pbuffer = smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_VP_P + smpt_rd_vk_swcUframe_buffer];

	//! get from server
	const float Fspeed = 5.0F;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_SPACE)
		smptr_ceuSu.Ptr[1] += 2 * Fspeed * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_LEFT_SHIFT)
		smptr_ceuSu.Ptr[1] -= 2 * Fspeed * smptr_ceDdelta;

	smptr_ceuSu.Ptr[4] += smpt_ceuPpoint[0] * smptr_ceDdelta;
	smptr_ceuSu.Ptr[3] -= smpt_ceuPpoint[1] * smptr_ceDdelta;
	memset(smpt_ceuPpoint, 0, sizeof(float) * 2);

	if (smptr_ceuSu.Ptr[3] > smptmMd2r(90.0F))
	{
		smptr_ceuSu.Ptr[3] = smptmMd2r(90.0F);
	}
	else if (smptr_ceuSu.Ptr[3] < smptmMd2r(-90.0F))
	{
		smptr_ceuSu.Ptr[3] = smptmMd2r(-90.0F);
	}
	smptr_ceuSu.Ptr[4] = smptmMnr(smptr_ceuSu.Ptr[4], smptmMd2r(360));

	VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

	memcpy(Pbuffer, smptm_m4x4P, sizeof(float) * 16);

	smptm_v4Mq(0, smptr_ceuSu.Ptr[4], 0, Pt);
	smptm_v4Mq2m(Pt, Pq0_m4x4);
	memcpy(Pq1_m4x4, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(Pq1_m4x4, Pq0_m4x4, Pbuffer);

	//.i fix t
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_A)
		Pt[2] += 2 * Fspeed * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_D)
		Pt[2] -= 2 * Fspeed * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_W)
		Pt[0] -= 2 * Fspeed * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_S)
		Pt[0] += 2 * Fspeed * smptr_ceDdelta;
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
		.pNext = NULL
	});
}

void smptr_ceuMfree()
{
}
