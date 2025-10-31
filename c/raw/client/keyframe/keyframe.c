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

	for (uint8_t l0 = 0; l0 < Lkf; ++l0)
	{
		smptr_ce_kfPl[l0] = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(uint8_t);
		smptr_ce_kfP[l0] = malloc(smptr_ce_kfPl[l0] * sizeof(struct SMPTR_CE_KFs));

		for (uint32_t l1 = 0; l1 < smptr_ce_kfPl[l0]; ++l1)
		{
			smptr_ce_kfP[l0][l1].Lbone = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			smptrPcache->d_bl_p[1] += sizeof(uint8_t);

			smptr_ce_kfP[l0][l1].Pbone = malloc(smptr_ce_kfP[l0][l1].Lbone);
			smptr_ce_kfP[l0][l1].Ps = malloc(sizeof(float *) * smptr_ce_kfP[l0][l1].Lbone);
			smptr_ce_kfP[l0][l1].Pr = malloc(sizeof(float *) * smptr_ce_kfP[l0][l1].Lbone);
			smptr_ce_kfP[l0][l1].Pt = malloc(sizeof(float *) * smptr_ce_kfP[l0][l1].Lbone);

			for (uint32_t l2 = 0; l2 < smptr_ce_kfP[l0][l1].Lbone; ++l2)
			{
				smptr_ce_kfP[l0][l1].Pbone[l2] = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
				smptrPcache->d_bl_p[1] += sizeof(uint8_t);

				smptr_ce_kfP[l0][l1].Ps[l2] = malloc(sizeof(float) * 3);
				memcpy(smptr_ce_kfP[l0][l1].Ps[l2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3);
				smptrPcache->d_bl_p[1] += sizeof(float) * 3;

				smptr_ce_kfP[l0][l1].Pr[l2] = malloc(sizeof(float) * 4);
				memcpy(smptr_ce_kfP[l0][l1].Pr[l2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 4);
				smptrPcache->d_bl_p[1] += sizeof(float) * 4;

				smptr_ce_kfP[l0][l1].Pt[l2] = malloc(sizeof(float) * 3);
				memcpy(smptr_ce_kfP[l0][l1].Pt[l2], smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3);
				smptrPcache->d_bl_p[1] += sizeof(float) * 3;
			}
		}
	}
}

void smptr_ce_kfMfree()
{
	for (uint8_t l0 = 0; l0 < Lkf; ++l0)
	{
		for (uint32_t l1 = 0; l1 < smptr_ce_kfPl[l0]; ++l1)
		{
			free(smptr_ce_kfP[l0][l1].Pbone);

			for (uint32_t l2 = 0; l2 < smptr_ce_kfP[l0][l1].Lbone; ++l2)
			{
				free(smptr_ce_kfP[l0][l1].Pr[l2]);
				free(smptr_ce_kfP[l0][l1].Pt[l2]);
				free(smptr_ce_kfP[l0][l1].Ps[l2]);
			}

			free(smptr_ce_kfP[l0][l1].Pr);
			free(smptr_ce_kfP[l0][l1].Pt);
			free(smptr_ce_kfP[l0][l1].Ps);
		}

		free(smptr_ce_kfP[l0]);
	}

	free(smptr_ce_kfP);
	free(smptr_ce_kfPl);
}
