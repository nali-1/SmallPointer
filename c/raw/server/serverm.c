struct SMPTRsM *smptr_svmPm;
SMPTRtMI smptr_svmLm = 0;

static uint8_t Psync[SMPTRlMI] = {0};

void smptr_svmMset()
{
	smptr_svmPm = malloc(0);

	//! test
	//! fix
	uint8_t Ui = smptr_svmLm;
//	smptr_svmPm = realloc(smptr_svmPm, sizeof(struct SMPTRsM));
//	smptr_svmPm[Ui].Um = SMPTReM_POMI;
//	smptr_svmPm[Ui].Uk = SMPTReMK_POMI_WALK_LOOP;
//	smptr_svmPm[Ui].Ut = 255 * smptrPmk[smptr_svmPm[Ui].Uk][1];
//
//	smptr_svmPm[Ui].La = 7;
//	smptr_svmPm[Ui].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[Ui].La);
//	smptr_svmPm[Ui].Pa[0] = SMPTReMA_POMI_2CORE;
//	smptr_svmPm[Ui].Pa[1] = SMPTReMA_POMI_MF0000;
//	smptr_svmPm[Ui].Pa[2] = SMPTReMA_POMI_MF00;
//	smptr_svmPm[Ui].Pa[3] = SMPTReMA_POMI_MF0;
//	smptr_svmPm[Ui].Pa[4] = SMPTReMA_POMI_MM1;
//	smptr_svmPm[Ui].Pa[5] = SMPTReMA_POMI_M;
//	smptr_svmPm[Ui].Pa[6] = SMPTReMA_POMI_IShovel;
//
//	smptr_svmPm[Ui].Sm0.Ltr = 3 + 2 + 2;
//	//smptr_svmPm[0].Sm0.Ltr = 3 + 4 + 4 * 2;
//	smptr_svmPm[Ui].Sm0.Ptr = malloc(sizeof(float) * smptr_svmPm[Ui].Sm0.Ltr);
//	memset(smptr_svmPm[Ui].Sm0.Ptr, 0, sizeof(float) * smptr_svmPm[Ui].Sm0.Ltr);
//	smptr_svmPm[Ui].Sm0.Ptr[2] = 6;
//	//smptr_svmPm[0].Sm0.Ptr[3] = SMPTMmD2R(45);
//	smptr_svmPm[Ui].Sm0.Usync = ++Psync[Ui];
//
//	++smptr_svmLm;
	Ui = smptr_svmLm;
	++smptr_svmLm;
	smptr_svmPm = realloc(smptr_svmPm, smptr_svmLm * sizeof(struct SMPTRsM));
	smptr_svmPm[Ui].Um = SMPTReM_UI;
	smptr_svmPm[Ui].Uk = SMPTReMK_UI_IDLE;
	smptr_svmPm[Ui].Ut = 255 * smptrPmk[smptr_svmPm[Ui].Uk][1];

	smptr_svmPm[Ui].La = 8;
	smptr_svmPm[Ui].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[Ui].La);
	smptr_svmPm[Ui].Pa[0] = SMPTReMA_UI_RAIN;
	smptr_svmPm[Ui].Pa[1] = SMPTReMA_UI_001;
	smptr_svmPm[Ui].Pa[2] = SMPTReMA_UI_M;
	smptr_svmPm[Ui].Pa[3] = SMPTReMA_UI_IClover;
	smptr_svmPm[Ui].Pa[4] = SMPTReMA_UI_MF;
	smptr_svmPm[Ui].Pa[5] = SMPTReMA_UI_MF0;
	smptr_svmPm[Ui].Pa[6] = SMPTReMA_UI_MF01;
	smptr_svmPm[Ui].Pa[7] = SMPTReMA_UI_MM0;

	smptr_svmPm[Ui].Sm0.Ltr = 3 + 2 + 2;
	smptr_svmPm[Ui].Sm0.Ptr = malloc(sizeof(float) * smptr_svmPm[Ui].Sm0.Ltr);
	memset(smptr_svmPm[Ui].Sm0.Ptr, 0, sizeof(float) * smptr_svmPm[Ui].Sm0.Ltr);
	smptr_svmPm[Ui].Sm0.Ptr[2] = 6;
	smptr_svmPm[Ui].Sm0.Usync = ++Psync[Ui];

	Ui = smptr_svmLm;
	++smptr_svmLm;
	smptr_svmPm = realloc(smptr_svmPm, smptr_svmLm * sizeof(struct SMPTRsM));
	smptr_svmPm[Ui].Um = SMPTReM_CROAKIE;
	smptr_svmPm[Ui].Uk = SMPTReMK_CROAKIE_IDLE;
	smptr_svmPm[Ui].Ut = 255 * smptrPmk[smptr_svmPm[Ui].Uk][1];

	smptr_svmPm[Ui].La = 2;
	smptr_svmPm[Ui].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[Ui].La);
	smptr_svmPm[Ui].Pa[0] = SMPTReMA_CROAKIE_RAIN;
	smptr_svmPm[Ui].Pa[1] = SMPTReMA_CROAKIE_C0;

	smptr_svmPm[Ui].Sm0.Ltr = 3 + 2 + 2;
	smptr_svmPm[Ui].Sm0.Ptr = malloc(sizeof(float) * smptr_svmPm[Ui].Sm0.Ltr);
	memset(smptr_svmPm[Ui].Sm0.Ptr, 0, sizeof(float) * smptr_svmPm[Ui].Sm0.Ltr);
	smptr_svmPm[Ui].Sm0.Ptr[2] = 6;
	smptr_svmPm[Ui].Sm0.Usync = ++Psync[Ui];
}

void smptr_svmMloop()
{
	//! test
	const SMPTRtMK *Pk0 = smptrPmk[smptr_svmPm[0].Uk];
	smptr_svmPm[0].Ut += 255 / SMPTRuRW;
	smptr_svmPm[0].Ut = SMPTMmWRAP_I(smptr_svmPm[0].Ut, Pk0[1] * 255, Pk0[2] * 255);

//	smptr_svmPm[0].Ut += (255 + 255 + 255) / SMPTRuRW;
//	smptr_svmPm[0].Ut = SMPTMmWRAP_I(smptr_svmPm[0].Ut, Pk0[1] * (255 + 255 + 255), Pk0[2] * (255 + 255 + 255));

	smptr_svmPm[0].Sm0.Ptr[5] += SMPTMmD2R(20) / SMPTRuRW;
	smptr_svmPm[0].Sm0.Ptr[5] = SMPTMmNORM_NF(smptr_svmPm[0].Sm0.Ptr[5], SMPTMmD2R(360));

	const SMPTRtMK *Pk1 = smptrPmk[smptr_svmPm[1].Uk];
	smptr_svmPm[1].Ut += 255 / SMPTRuRW;
	smptr_svmPm[1].Ut = SMPTMmWRAP_I(smptr_svmPm[1].Ut, Pk1[1] * 255, Pk1[2] * 255);

	smptr_svmPm[1].Sm0.Ptr[5] += SMPTMmD2R(20) / SMPTRuRW;
	smptr_svmPm[1].Sm0.Ptr[5] = SMPTMmNORM_NF(smptr_svmPm[1].Sm0.Ptr[5], SMPTMmD2R(360));
}

void smptr_svmMsend(SMPT_NWtU u)
{
	*(SMPTRtMI *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = smptr_svmLm;
	smptr_svPnet[u].Lnet += sizeof(SMPTRtMI);

	for (SMPTRtMI l0 = 0; l0 < smptr_svmLm; ++l0)
	{
		struct SMPTRsM Sm = smptr_svmPm[l0];

		//! clean
		//if (smptr_svuPm[u][l0 / 8] & 1 << (l0 % 8))
		{
			*(SMPTRtM *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Um;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtM);

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.La;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, Sm.Pa, sizeof(SMPTRtMA) * Sm.La);
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMA) * Sm.La;

			*(SMPTRtMK *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Uk;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMK);

			*(SMPTRtMT *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Ut;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMT);

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Sm0.Ltr;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, Sm.Sm0.Ptr, sizeof(float) * Sm.Sm0.Ltr);
			smptr_svPnet[u].Lnet += sizeof(float) * Sm.Sm0.Ltr;

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Sm0.Usync;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);
		}
//		else
//		{
//			*(SMPTRtM *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = SMPTRvM;
//			smptr_svPnet[u].Lnet += sizeof(SMPTRtM);
//		}
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
