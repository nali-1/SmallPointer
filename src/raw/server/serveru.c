struct SMPTRsU smptr_svuSu[SMPT_NWlU];
uint8_t *smptr_svuPm[SMPT_NWlU];

void smptr_svuMset()
{
//	SMPT_DBmN2L("SMPTMmD2R(45) %f", SMPTMmD2R(45))
//	SMPT_DBmN2L("SMPTMmD2R(90) %f", SMPTMmD2R(90))
//	SMPT_DBmN2L("SMPTMmD2R(180) %f", SMPTMmD2R(180))
//	SMPT_DBmN2L("SMPTMmD2R(360) %f", SMPTMmD2R(360))
//	SMPT_DBmN2L("SMPTMmXZ2H(0, 1) %f", SMPTMmXZ2H(0, 1))
//	SMPT_DBmN2L("SMPTMmXYZ2V(0, 0, 1) %f", SMPTMmXYZ2V(0, 0, 1))
	for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
		smptr_svuPm[l0] = malloc(0);
}

void smptr_svuMloop()
{
	//! test look
	//! test ray / point box
	for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
	{
		smptr_svuPm[l0] = realloc(smptr_svuPm[l0], sizeof(uint8_t) * smptr_svmLm);
		memset(smptr_svuPm[l0], 0, sizeof(uint8_t) * smptr_svmLm);

		float *Ptr_u = smptr_svuSu[l0].Ptr;
		//! check
		//.i fix Pr_u
		float Pr_u[] =
		{
			Ptr_u[3],
			-Ptr_u[4]
		};
//		SMPT_DBmN2L("Pr_u[0] %f", Pr_u[0])
//		SMPT_DBmN2L("Pr_u[1] %f", Pr_u[1])
		for (SMPTRtMI l1 = 0; l1 < smptr_svmLm; ++l1)
		{
			float Pt_m[3];
			for (SMPTRtMI l2 = 0; l2 < 3; ++l2)
			{
				Pt_m[l2] = smptr_svmPm[l1].Sm0.Ptr[l2] + Ptr_u[l2];
//				SMPT_DBmN2L("l2 %d", l2)
//				SMPT_DBmN2L("Ptr_u[l2] %f", Ptr_u[l2])
//				SMPT_DBmN2L("smptr_svmPm[l1].Sm0.Ptr[l2] %f", smptr_svmPm[l1].Sm0.Ptr[l2])
			}

			float
				Fh_m = SMPTMmXZ2H(Pt_m[0], Pt_m[2]),
				Fv_m = SMPTMmXYZ2V(Pt_m[0], Pt_m[1], Pt_m[2]),
				Fh2 = fabsf(Pr_u[1] - Fh_m),
				Fv2 = fabsf(Pr_u[0] - Fv_m);
//			SMPT_DBmN2L("Fh_m %f", Fh_m)
//			SMPT_DBmN2L("Fv_m %f", Fv_m)
			if (Fh2 >= SMPTMmD2R(180))
				Fh2 = SMPTMmD2R(360) - Fh2;
//			SMPT_DBmN2L("Fh2 %f", Fh2)
//			SMPT_DBmN2L("Fv2 %f", Fv2)
			if (Fh2 <= SMPTMmD2R(45) && Fv2 <= SMPTMmD2R(45))
				smptr_svuPm[l0][l1 / 8] |= 1 << (l1 % 8);

			//! test dot
			float
				Pt_u[3] =
				{
//					SMPTMmHV2X(Pr_u[1], Pr_u[0]) + Ptr_u[0],
//					SMPTMmV2Y(Pr_u[0]) + Ptr_u[1],
//					SMPTMmHV2Z(Pr_u[1], Pr_u[0]) + Ptr_u[2]
					SMPTMmHV2X(Pr_u[1], Pr_u[0]),
					SMPTMmV2Y(Pr_u[0]),
					SMPTMmHV2Z(Pr_u[1], Pr_u[0])
				},
				Fh_u = SMPTMmXZ2H(Ptr_u[0], Ptr_u[2]),
				Fv_u = SMPTMmXYZ2V(Ptr_u[0], Ptr_u[1], Ptr_u[2]),
				Ps[3] =
				{
//					smptr_svmPm[l1].Sm0.Ptr[0] - Pt_u[0],
//					smptr_svmPm[l1].Sm0.Ptr[1] - Pt_u[1],
//					smptr_svmPm[l1].Sm0.Ptr[2] - Pt_u[2]
					smptr_svmPm[l1].Sm0.Ptr[0] - Ptr_u[0],
					smptr_svmPm[l1].Sm0.Ptr[1] - Ptr_u[1],
					smptr_svmPm[l1].Sm0.Ptr[2] - Ptr_u[2]
				},
				Fl = SMPTM_V3mLENGTH(Ps[0], Ps[1], Ps[2]),
				Ffl = cosf(SMPTM_M4X4fFOV * (M_PI / 180.0F));
			SMPTM_V3mNORM(Ps[0], Ps[1], Ps[2], Fl)

//			SMPT_DBmN2L("SMPTM_V3mDOT(Pt_u[0], Pt_u[1], Pt_u[2], Ps[0], Ps[1], Ps[2]) %f", SMPTM_V3mDOT(Pt_u[0], Pt_u[1], Pt_u[2], Ps[0], Ps[1], Ps[2]))
//			SMPT_DBmN2L("Ffl %f", Ffl)
			//! need a to test
			//if (SMPTM_V3mDOT(Pt_u[0], Pt_u[1], Pt_u[2], Ps[0], Ps[1], Ps[2]) < Ffl)
			//if (Ffl > 0)
			//if (SMPTM_V3mDOT(Pt_u[0], Pt_u[1], Pt_u[2], Ps[0], Ps[1], Ps[2]) > 0)
			//if (SMPTM_V3mDOT(Pt_u[0], Pt_u[1], Pt_u[2], Ps[0], Ps[1], Ps[2]) > 0.2)
			//	smptr_svuPm[l0][l1 / 8] |= 1 << (l1 % 8);
		}
	}
}

void smptr_svuMsend(SMPT_NWtU u)
{
	memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, &smptr_svuSu[u], sizeof(struct SMPTRsU));

	for (uint8_t l0 = 0; l0 < 5; ++l0)
		SMPT_DBmN2L("(float *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet)[%d] %f", l0, ((float *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet))[l0])
	for (uint8_t l0 = 0; l0 < 5; ++l0)
		SMPT_DBmN2L("smptr_svuSu[u].Ptr[%d] %f", l0, smptr_svuSu[u].Ptr[l0])

	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

void smptr_svuMread(SMPT_NWtU u)
{
	memcpy(&smptr_svuSu[u], smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, sizeof(struct SMPTRsU));
	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

void smptr_svuMfread()
{
	if (smptr_svPfile)
	{
		fread(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWlU, smptr_svPfile);

		for (uint8_t l0 = 0; l0 < 5; ++l0)
			SMPT_DBmN2L("smptr_svuSu[0].Ptr[%d] %f", l0, smptr_svuSu[0].Ptr[l0])
	}
	else
	{
		memset(smptr_svuSu, 0, sizeof(struct SMPTRsU) * SMPT_NWlU);
	}
}

void smptr_svuMfsend()
{
	for (uint8_t l0 = 0; l0 < 5; ++l0)
		SMPT_DBmN2L("smptr_svuSu[0].Ptr[%d] %f", l0, smptr_svuSu[0].Ptr[l0])
	fwrite(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWlU, smptr_svPfile);
}

void smptr_svuMfree()
{
	for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
		free(smptr_svuPm[l0]);
}
