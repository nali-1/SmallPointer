struct SMPTR_CE_KFs *smptr_ce_kfP[SMPTR_MDc];
uint8_t smptr_ce_kfPl[SMPTR_MDc];

void smptr_ce_kfMset()
{
	SMPT_DBmN2L("SMPTR_MDc %d", SMPTR_MDc)
	SMPT_DBmN2L("smptrPcache->d_bl_p[1] %ld", smptrPcache->d_bl_p[1])

	for (uint8_t U0 = 0; U0 < SMPTR_MDc; ++U0)
	{
		smptr_ce_kfPl[U0] = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(uint8_t);
		smptr_ce_kfP[U0] = malloc(smptr_ce_kfPl[U0] * sizeof(struct SMPTR_CE_KFs));
		SMPT_DBmN2L("smptr_ce_kfPl[%d] %d", U0, smptr_ce_kfPl[U0])

		for (SMPTRtMK U1 = 0; U1 < smptr_ce_kfPl[U0]; ++U1)
		{
			smptr_ce_kfP[U0][U1].Lbone = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			SMPT_DBmN2L("smptr_ce_kfP[%d][%d].Lbone %d", U0, U1, smptr_ce_kfP[U0][U1].Lbone)
			smptrPcache->d_bl_p[1] += sizeof(uint8_t);

			smptr_ce_kfP[U0][U1].Pbone = malloc(smptr_ce_kfP[U0][U1].Lbone);
			smptr_ce_kfP[U0][U1].Ps = malloc(sizeof(float *) * smptr_ce_kfP[U0][U1].Lbone);
			smptr_ce_kfP[U0][U1].Pr = malloc(sizeof(float *) * smptr_ce_kfP[U0][U1].Lbone);
			smptr_ce_kfP[U0][U1].Pt = malloc(sizeof(float *) * smptr_ce_kfP[U0][U1].Lbone);

			for (SMPTRtJWL U2 = 0; U2 < smptr_ce_kfP[U0][U1].Lbone; ++U2)
			{
				smptr_ce_kfP[U0][U1].Pbone[U2] = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
				SMPT_DBmN2L("smptr_ce_kfP[%d][%d].Pbone[%d] %d", U0, U1, U2, smptr_ce_kfP[U0][U1].Pbone[U2])
				smptrPcache->d_bl_p[1] += sizeof(uint8_t);

				smptr_ce_kfP[U0][U1].Ps[U2] = malloc(sizeof(float) * 3);
				memcpy(smptr_ce_kfP[U0][U1].Ps[U2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3);
//				for (SMPTRtJWL U3 = 0; U3 < 3; ++U3)
//					SMPT_DBmN2L("smptr_ce_kfP[%d][%d].Ps[%d][%d] %f", U0, U1, U2, U3, smptr_ce_kfP[U0][U1].Ps[U2][U3])
				smptrPcache->d_bl_p[1] += sizeof(float) * 3;

				smptr_ce_kfP[U0][U1].Pr[U2] = malloc(sizeof(float) * 4);
				memcpy(smptr_ce_kfP[U0][U1].Pr[U2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 4);
//				for (SMPTRtJWL U3 = 0; U3 < 4; ++U3)
//					SMPT_DBmN2L("smptr_ce_kfP[%d][%d].Pr[%d][%d] %f", U0, U1, U2, U3, smptr_ce_kfP[U0][U1].Pr[U2][U3])
				smptrPcache->d_bl_p[1] += sizeof(float) * 4;

				smptr_ce_kfP[U0][U1].Pt[U2] = malloc(sizeof(float) * 3);
				memcpy(smptr_ce_kfP[U0][U1].Pt[U2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3);
//				for (SMPTRtJWL U3 = 0; U3 < 3; ++U3)
//					SMPT_DBmN2L("smptr_ce_kfP[%d][%d].Pt[%d][%d] %f", U0, U1, U2, U3, smptr_ce_kfP[U0][U1].Pt[U2][U3])
				smptrPcache->d_bl_p[1] += sizeof(float) * 3;
			}
		}
	}
}

void smptr_ce_kfMfree()
{
	for (uint8_t U0 = 0; U0 < SMPTR_MDc; ++U0)
	{
		for (uint32_t U1 = 0; U1 < smptr_ce_kfPl[U0]; ++U1)
		{
			free(smptr_ce_kfP[U0][U1].Pbone);

			for (uint32_t U2 = 0; U2 < smptr_ce_kfP[U0][U1].Lbone; ++U2)
			{
				free(smptr_ce_kfP[U0][U1].Pr[U2]);
				free(smptr_ce_kfP[U0][U1].Pt[U2]);
				free(smptr_ce_kfP[U0][U1].Ps[U2]);
			}

			free(smptr_ce_kfP[U0][U1].Pr);
			free(smptr_ce_kfP[U0][U1].Pt);
			free(smptr_ce_kfP[U0][U1].Ps);
		}

		free(smptr_ce_kfP[U0]);
	}
}
