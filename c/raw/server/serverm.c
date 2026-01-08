struct SMPTRsM *smptr_svmPm;
SMPTRtMI smptr_svmLm = 0;

uint8_t smptr_svmPsync[SMPTRlMI] = {0};

void smptr_svmMset()
{
	smptr_svmPm = malloc(0);

//	uint8_t Ui = smptr_svmLm;
//	Ui = smptr_svmLm;
//	++smptr_svmLm;
//	smptr_svmPm = realloc(smptr_svmPm, smptr_svmLm * sizeof(struct SMPTRsM));
//	smptr_svmPm[Ui].Um = SMPTR_MDeUI;
//	smptr_svmPm[Ui].Uk = SMPTReMK_UI_IDLE;
//	smptr_svmPm[Ui].Ut = 255 * smptrPmk[smptr_svmPm[Ui].Uk][1];
//
//	smptr_svmPm[Ui].La = 7;
//	smptr_svmPm[Ui].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[Ui].La);
//	smptr_svmPm[Ui].Pa[0] = SMPTR_MDeM_UI_RAIN;
//	smptr_svmPm[Ui].Pa[1] = SMPTR_MDeM_UI_001;
//	smptr_svmPm[Ui].Pa[2] = SMPTR_MDeM_UI_M;
//	smptr_svmPm[Ui].Pa[3] = SMPTR_MDeM_UI_IClover;
//	smptr_svmPm[Ui].Pa[4] = SMPTR_MDeM_UI_MF0;
//	smptr_svmPm[Ui].Pa[5] = SMPTR_MDeM_UI_MF02;
//	smptr_svmPm[Ui].Pa[6] = SMPTR_MDeM_UI_MM0;
//
//	smptr_svmPm[Ui].Sm0.Ptr = malloc(sizeof(float) * SMPTRMlTR);
//	memset(smptr_svmPm[Ui].Sm0.Ptr, 0, sizeof(float) * SMPTRMlTR);
//	smptr_svmPm[Ui].Sm0.Ptr[2] = 6;
//	smptr_svmPsync[Ui] = smptr_svmPsync[Ui] % 255 + 1;
//	smptr_svmPm[Ui].Sm0.Usync = smptr_svmPsync[Ui];
//
//	Ui = smptr_svmLm;
//	++smptr_svmLm;
//	smptr_svmPm = realloc(smptr_svmPm, smptr_svmLm * sizeof(struct SMPTRsM));
//	smptr_svmPm[Ui].Um = SMPTR_MDeCROAKIE;
//	smptr_svmPm[Ui].Uk = SMPTReMK_CROAKIE_IDLE;
//	smptr_svmPm[Ui].Ut = 255 * smptrPmk[smptr_svmPm[Ui].Uk][1];
//
//	smptr_svmPm[Ui].La = 2;
//	smptr_svmPm[Ui].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[Ui].La);
//	smptr_svmPm[Ui].Pa[0] = SMPTR_MDeM_CROAKIE_RAIN;
//	smptr_svmPm[Ui].Pa[1] = SMPTR_MDeM_CROAKIE_C0;
//
//	smptr_svmPm[Ui].Sm0.Ptr = malloc(sizeof(float) * SMPTRMlTR);
//	memset(smptr_svmPm[Ui].Sm0.Ptr, 0, sizeof(float) * SMPTRMlTR);
//	smptr_svmPm[Ui].Sm0.Ptr[2] = 6;
//	smptr_svmPsync[Ui] = smptr_svmPsync[Ui] % 255 + 1;
//	smptr_svmPm[Ui].Sm0.Usync = smptr_svmPsync[Ui];
}

void smptr_svmMloop()
{
	smptr_sv_ettMloop();
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

			*(SMPTRtMK *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Uk;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMK);

			*(SMPTRtMT *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sm.Ut;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMT);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, Sm.Sm0.Ptr, sizeof(float) * SMPTRMlTR);
			smptr_svPnet[u].Lnet += sizeof(float) * SMPTRMlTR;

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
	free(smptr_svmPm);
}
