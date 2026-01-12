void smptr_sv_ett_pmMset()
{
}

void smptr_sv_ett_pmMadd()
{
	const SMPTRtMI Umi = smptr_svmLm;
	smptr_svmPm = realloc(smptr_svmPm, sizeof(struct SMPTRsM) * (Umi + 1));

	struct SMPTRsM *Sm = smptr_svmPm + Umi;
	Sm->Um = (uint8_t)rand() % 6 + SMPTR_ETTeM_POMI_TEA0;
	Sm->Uk = (uint8_t)rand() % 2 == 0 ? SMPTReMK_POMI_JUMP : SMPTReMK_POMI_IDLE;
	Sm->Ut = 255 * smptrPmk[Sm->Uk][1];

	memset(Sm->Sm0.Ptr, 0, sizeof(float) * SMPTRMlTR);
	Sm->Sm0.Ptr[SMPTRMuX] = (uint8_t)rand() % 16 - (uint8_t)rand() % 16;
	Sm->Sm0.Ptr[SMPTRMuZ] = (uint8_t)rand() % 16 - (uint8_t)rand() % 16;
	Sm->Sm0.Ptr[SMPTRMuBY] = SMPTMmD2R((float)((uint8_t)rand() % 180 - (uint8_t)rand() % 180));
	smptr_svmPsync[Umi] = smptr_svmPsync[Umi] % 255 + 1;
	Sm->Sm0.Usync = smptr_svmPsync[Umi];

	smptr_sv_ettP = realloc(smptr_sv_ettP, sizeof(struct SMPTR_SV_ETTs) * (Umi + 1));
	struct SMPTR_SV_ETTs *Pt = smptr_sv_ettP + Umi;
	Pt->Uwork = SMPTR_ETTePOMI;
	//memcpy(Pt->Ptr, Sm->Sm0.Ptr, sizeof(float) * SMPTRMlTR);
	Pt->Umove = (SMPTRtRW)rand() % SMPTRuRW;
	Pt->Ueye = (SMPTRtRW)rand() % SMPTRuRW;
	Pt->Umouth = (SMPTRtRW)rand() % SMPTRuRW;
	//Pt->Ulooku = (SMPTRtRW)rand() % SMPTRuRW;
	memcpy(Pt->Fmove, Sm->Sm0.Ptr, sizeof(float) * 3);

	++smptr_svmLm;
}

float yaw_delta_deg(float yawA, float yawB)
{
	float d = fmodf(yawB - yawA, 360.0F);
	if (d > 180.0F)
		d -= 360.0F;
	if (d < -180.0F)
		d += 360.0F;
	return d;
}

void smptr_sv_ett_pmMwork(SMPTRtMI Umi)
{
	//SMPT_DBmN2L("smptr_sv_ett_pmMwork")

	struct SMPTRsM *Sm = smptr_svmPm + Umi;
//	Sm->Ut += (255*2) / SMPTRuRW;
//	Sm->Ut = (SMPTRtMT)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);

//	Sm->Sm0.Ptr[SMPTRMuBY] += SMPTMmD2R(20) / SMPTRuRW;
//	Sm->Sm0.Ptr[SMPTRMuBY] = SMPTMmNORM_NF(Sm->Sm0.Ptr[SMPTRMuBY], SMPTMmD2R(360));

	struct SMPTR_SV_ETTs *Pt = smptr_sv_ettP + Umi;
	//const struct SMPTRsU *Pu = smptr_svuSu + 0;

//	//.i u
//	if (smptr_sv_spUrw % (SMPTRuRW * 4) == 0)
//	{
//		if (Pt->Ulooku == 0)
//		{
//			Pt->Ulooku = rand() % 3;
//		}
//		else
//		{
//			--Pt->Ulooku;
//		}
//	}

	//.i m
	if (smptr_sv_spUrw % (SMPTRuRW * 2) == 0)
	{
		if (Pt->Ueye == 0)
		{
			Pt->Ueye = (SMPTRtRW)rand() % SMPTRuRW;
			Sm->Um = SMPTR_ETTeM_POMI_TEA0;
		}
		else
		{
			if (Sm->Um == SMPTR_ETTeM_POMI_TEA0)
			{
				Sm->Um = rand() % 6 + SMPTR_ETTeM_POMI_TEA0;
			}
			--Pt->Ueye;
		}
	}

	//.i m
	if (smptr_sv_spUrw % (SMPTRuRW * 2) == 0)
	{
		if (Pt->Umouth == 0)
		{
			Pt->Umouth = (SMPTRtRW)rand() % SMPTRuRW;
			if (Sm->Um != SMPTR_ETTeM_POMI_TEA5)
				++Sm->Um;
		}
		else
		{
			--Pt->Umouth;
		}
	}

	//.i move
	if (smptr_sv_spUrw % (SMPTRuRW * 2) == 0)
	{
		if (Pt->Umove == 0)
		{
			Pt->Umove = (SMPTRtRW)rand() % SMPTRuRW;
			Pt->Fmove[SMPTRMuX] = Sm->Sm0.Ptr[SMPTRMuX] + (float)((uint8_t)rand() % 8 - (uint8_t)rand() % 8);
			Pt->Fmove[SMPTRMuZ] = Sm->Sm0.Ptr[SMPTRMuZ] + (float)((uint8_t)rand() % 8 - (uint8_t)rand() % 8);
		}
		else
		{
			--Pt->Umove;
		}
	}

	SMPTRtMT Uts = Sm->Ut;
	if (Sm->Uk == SMPTReMK_POMI_JUMP || Sm->Uk == SMPTReMK_POMI_IDLE)
	{
		const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
		Sm->Ut += (255*2) / SMPTRuRW;
		Sm->Ut = (SMPTRtMT)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);
	}
	float Fx = Pt->Fmove[SMPTRMuX] - Sm->Sm0.Ptr[SMPTRMuX];
	float Fy = Pt->Fmove[SMPTRMuY] - Sm->Sm0.Ptr[SMPTRMuY];
	float Fz = Pt->Fmove[SMPTRMuZ] - Sm->Sm0.Ptr[SMPTRMuZ];
	float Fdist = sqrtf(Fx * Fx + Fy * Fy + Fz * Fz);
	float Fmax_step = 0.25F / SMPTRuRW;
	//if (!Pt->Ulooku && Fdist > 1e-4F && ((Sm->Uk != SMPTReMK_POMI_JUMP && Sm->Uk != SMPTReMK_POMI_IDLE) || (Uts > Sm->Ut && (Sm->Uk == SMPTReMK_POMI_JUMP || Sm->Uk == SMPTReMK_POMI_IDLE))))
	if (Fdist > 1e-4F && ((Sm->Uk != SMPTReMK_POMI_JUMP && Sm->Uk != SMPTReMK_POMI_IDLE) || (Uts > Sm->Ut && (Sm->Uk == SMPTReMK_POMI_JUMP || Sm->Uk == SMPTReMK_POMI_IDLE))))
	{
		if (Fdist <= Fmax_step)
		{
			Sm->Sm0.Ptr[SMPTRMuX] = Pt->Fmove[SMPTRMuX];
			Sm->Sm0.Ptr[SMPTRMuY] = Pt->Fmove[SMPTRMuY];
			Sm->Sm0.Ptr[SMPTRMuZ] = Pt->Fmove[SMPTRMuZ];
		}
		else
		{
			Sm->Sm0.Ptr[SMPTRMuX] += Fx * (Fmax_step / Fdist);
			Sm->Sm0.Ptr[SMPTRMuY] += Fy * (Fmax_step / Fdist);
			Sm->Sm0.Ptr[SMPTRMuZ] += Fz * (Fmax_step / Fdist);

			if (Sm->Uk == SMPTReMK_POMI_WALK_MID)
			{
				const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
				Sm->Ut += (255*4) / SMPTRuRW;
				Sm->Ut = (SMPTRtMT)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);
			}
			else
			{
				if (Sm->Uk != SMPTReMK_POMI_WALK_START)
				{
					Sm->Uk = SMPTReMK_POMI_WALK_START;
					const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
					Sm->Ut = Pk0[1] * 255;
				}

				Sm->Ut += (255*4) / SMPTRuRW;
				const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
				const SMPTRtMK *Pk1 = smptrPmk[SMPTReMK_POMI_WALK_MID];
				float Ute = (float)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);
				if (Pk1[1] * 255 < Ute)
				{
					Sm->Uk = SMPTReMK_POMI_WALK_MID;
					Pk0 = smptrPmk[Sm->Uk];
				}
			}
			float Fh = -SMPTRMmXZ2H(Pt->Fmove[SMPTRMuX] - Sm->Sm0.Ptr[SMPTRMuX], Pt->Fmove[SMPTRMuZ] - Sm->Sm0.Ptr[SMPTRMuZ]);
			Sm->Sm0.Ptr[SMPTRMuBY] += yaw_delta_deg(Sm->Sm0.Ptr[SMPTRMuBY], Fh) / SMPTRuRW;
		}
	}
	else
	{
		if (Sm->Uk == SMPTReMK_POMI_WALK_START)
		{
			const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
			const SMPTRtMK *Pk1 = smptrPmk[SMPTReMK_POMI_WALK_MID];
			Sm->Ut += (255*4) / SMPTRuRW;
			float Ute = (float)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);
			if (Pk1[1] * 255 < Ute)
			{
				Sm->Uk = SMPTReMK_POMI_WALK_MID;
				Pk0 = smptrPmk[Sm->Uk];
			}
		}
		if (Sm->Uk == SMPTReMK_POMI_WALK_MID)
		{
			SMPTRtMT Ut = Sm->Ut;
			const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
			Sm->Ut += (255*4) / SMPTRuRW;
			float Ute = (float)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);
			if (Ut > Ute)
			{
				Sm->Uk = SMPTReMK_POMI_WALK_END;
				Pk0 = smptrPmk[Sm->Uk];
			}
		}
		if (Sm->Uk == SMPTReMK_POMI_WALK_END)
		{
			SMPTRtMT Ut = Sm->Ut;
			const SMPTRtMK *Pk0 = smptrPmk[Sm->Uk];
			Sm->Ut += (255*4) / SMPTRuRW;
			float Ute = (float)SMPTMmWRAP_I(Sm->Ut, Pk0[1] * 255, Pk0[2] * 255);
			if (Ut > Ute)
			{
				Sm->Uk = rand() % 2 == 0 ? SMPTReMK_POMI_JUMP : SMPTReMK_POMI_IDLE;
				Pk0 = smptrPmk[Sm->Uk];
				Sm->Ut = Pk0[1] * 255;
			}
		}
	}

//	if (Pt->Ulooku)
//	{
//		//.i look u0
//		//! check
//		float Fh = -SMPTRMmXZ2H(Pu->Ptr[SMPTRMuX] + Sm->Sm0.Ptr[SMPTRMuX], Pu->Ptr[SMPTRMuZ] + Sm->Sm0.Ptr[SMPTRMuZ]) + SMPTMmD2R(180);
//		Sm->Sm0.Ptr[SMPTRMuBY] += yaw_delta_deg(Sm->Sm0.Ptr[SMPTRMuBY], Fh) / SMPTRuRW;
//		//Sm->Sm0.Ptr[SMPTRMuBY] = SMPTMmNORM_NF(Sm->Sm0.Ptr[SMPTRMuBY], SMPTMmD2R(360));
//	}
}

void smptr_sv_ett_pmMremove()
{
}

void smptr_sv_ett_pmMfree()
{
}
