struct SMPTRsM *smptr_svmPm;
SMPTRtMI smptr_svmLm = 0;

void smptr_svmMset()
{
	smptr_svmPm = malloc(0);

	//! test
	smptr_svmPm = realloc(smptr_svmPm, sizeof(struct SMPTRsM));
	smptr_svmPm[0].Um = SMPTReM_POMI_PAPI;
	smptr_svmPm[0].Uk = SMPTReMK_POMI_WALK_LOOP;
	smptr_svmPm[0].Ut = 255 * smptrPmk[smptr_svmPm[0].Uk][1];

	smptr_svmPm[0].La = 9;
	smptr_svmPm[0].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[0].La);
	smptr_svmPm[0].Pa[0] = SMPTReMAc + SMPTReM_POMI_PAPI;
	smptr_svmPm[0].Pa[1] = SMPTReMA_FE0000_000;
	smptr_svmPm[0].Pa[2] = SMPTReMA_FE0000_001;
	smptr_svmPm[0].Pa[3] = SMPTReMA_FE00_000;
	smptr_svmPm[0].Pa[4] = SMPTReMA_FE00_001;
	smptr_svmPm[0].Pa[5] = SMPTReMA_FE0_000;
	smptr_svmPm[0].Pa[6] = SMPTReMA_FE0_001;
	smptr_svmPm[0].Pa[7] = SMPTReMA_M0;
	smptr_svmPm[0].Pa[8] = SMPTReMA_IShovel;

	smptr_svmPm[0].Sm0.Ltr = 3 + 1 + 2;
	//smptr_svmPm[0].Sm0.Ltr = 3 + 4 + 4 * 2;
	smptr_svmPm[0].Sm0.Ptr = malloc(sizeof(float) * smptr_svmPm[0].Sm0.Ltr);
	memset(smptr_svmPm[0].Sm0.Ptr, 0, sizeof(float) * smptr_svmPm[0].Sm0.Ltr);
	smptr_svmPm[0].Sm0.Ptr[1] = -0.5;
	smptr_svmPm[0].Sm0.Ptr[2] = 6;

	++smptr_svmLm;
}

void smptr_svmMloop()
{
	//! test
	const SMPTRtMK *Pk = smptrPmk[smptr_svmPm[0].Uk];
	//smptr_svmPm[0].Ut += 255 / SMPTRuRW;
	smptr_svmPm[0].Ut += 1;
	//SMPT_DBmN2L("S0 Ut %d", smptr_svmPm[0].Ut)
	smptr_svmPm[0].Ut = SMPTMmWRAP_I(smptr_svmPm[0].Ut, Pk[1] * 255, Pk[2] * 255);
	//SMPT_DBmN2L("S1 Ut %d", smptr_svmPm[0].Ut)
}

void smptr_svmMsend(SMPT_NWtU u)
{
	*(SMPTRtMI *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = smptr_svmLm;
	smptr_svPnet[u].Lnet += sizeof(SMPTRtMI);

	for (SMPTRtMI l0 = 0; l0 < smptr_svmLm; ++l0)
	{
		struct SMPTRsM m = smptr_svmPm[l0];

		if (smptr_svuPm[u][l0 / 8] & 1 << (l0 % 8))
		{
			*(SMPTRtM *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.Um;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtM);

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.La;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, m.Pa, sizeof(SMPTRtMA) * m.La);
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMA) * m.La;

			*(SMPTRtMK *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.Uk;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMK);

			*(SMPTRtMT *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.Ut;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMT);

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.Sm0.Ltr;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, m.Sm0.Ptr, sizeof(float) * m.Sm0.Ltr);
			smptr_svPnet[u].Lnet += sizeof(float) * m.Sm0.Ltr;
		}
		else
		{
			*(SMPTRtM *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = SMPTRvM;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtM);
		}
	}
}

void smptr_svmMfread()
{
}

void smptr_svmMfsend()
{
}

void smptr_svmMfree()
{
	for (SMPTRtMI l0 = 0; l0 < smptr_svmLm; ++l0)
	{
		if (smptr_svmPm[l0].Um != SMPTRvM)
		{
			free(smptr_svmPm[l0].Pa);
			free(smptr_svmPm[l0].Sm0.Ptr);
		}
	}
	free(smptr_svmPm);
}
