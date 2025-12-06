struct SMPTR_CE_KFs **smptr_ce_kfP;
uint8_t *smptr_ce_kfPl;

static uint8_t Lkf;
void smptr_ce_kfMset()
{
	Lkf = *(uint8_t *)smptrPcache->d_p;
	smptrPcache->d_bl_p[1] += sizeof(uint8_t);
	smptr_ce_kfPl = malloc(Lkf);
	smptr_ce_kfP = malloc(Lkf * sizeof(struct SMPTR_CE_KFs *));
	memset(smptr_ce_kfP, 0, Lkf * sizeof(struct SMPTR_CE_KFs *));

	for (uint8_t U0 = 0; U0 < Lkf; ++U0)
	{
		smptr_ce_kfPl[U0] = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(uint8_t);
		smptr_ce_kfP[U0] = malloc(smptr_ce_kfPl[U0] * sizeof(struct SMPTR_CE_KFs));

		for (SMPTRtMK U1 = 0; U1 < smptr_ce_kfPl[U0]; ++U1)
		{
			smptr_ce_kfP[U0][U1].Lbone = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			smptrPcache->d_bl_p[1] += sizeof(uint8_t);

			smptr_ce_kfP[U0][U1].Pbone = malloc(smptr_ce_kfP[U0][U1].Lbone);
			smptr_ce_kfP[U0][U1].Ps = malloc(sizeof(float *) * smptr_ce_kfP[U0][U1].Lbone);
			smptr_ce_kfP[U0][U1].Pr = malloc(sizeof(float *) * smptr_ce_kfP[U0][U1].Lbone);
			smptr_ce_kfP[U0][U1].Pt = malloc(sizeof(float *) * smptr_ce_kfP[U0][U1].Lbone);

			for (SMPTRtJWL U2 = 0; U2 < smptr_ce_kfP[U0][U1].Lbone; ++U2)
			{
				smptr_ce_kfP[U0][U1].Pbone[U2] = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
				smptrPcache->d_bl_p[1] += sizeof(uint8_t);

				smptr_ce_kfP[U0][U1].Ps[U2] = malloc(sizeof(float) * 3);
				memcpy(smptr_ce_kfP[U0][U1].Ps[U2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3);
				smptrPcache->d_bl_p[1] += sizeof(float) * 3;

				smptr_ce_kfP[U0][U1].Pr[U2] = malloc(sizeof(float) * 4);
				memcpy(smptr_ce_kfP[U0][U1].Pr[U2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 4);
				smptrPcache->d_bl_p[1] += sizeof(float) * 4;

				smptr_ce_kfP[U0][U1].Pt[U2] = malloc(sizeof(float) * 3);
				memcpy(smptr_ce_kfP[U0][U1].Pt[U2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3);
				smptrPcache->d_bl_p[1] += sizeof(float) * 3;
			}
		}
	}
}

void smptr_ce_kfMfree()
{
	for (uint8_t U0 = 0; U0 < Lkf; ++U0)
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

	free(smptr_ce_kfP);
	free(smptr_ce_kfPl);
}
