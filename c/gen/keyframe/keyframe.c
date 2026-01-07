static const char *Pc[] =
{
	#define X(v, r, f) SMPTFcFACTORY_KEYFRAME "/" f ".bin",
		SMPTR_MDx
	#undef X
};

void smptg_kfMsend()
{
	//! clean
	FILE *Pfile = fopen(SMPTFcHOME_ASSET, "ab");

	uint32_t Ldata;
	uint8_t *Pdata;
	for (uint8_t U0 = 0; U0 < sizeof(Pc) / sizeof(Pc[0]); ++U0)
	{
		Pdata = smptfMread(Pc[U0], &Ldata);
		Ldata = 0;

		uint8_t Lkeyframe = *(uint8_t *)(Pdata + Ldata);
		Ldata += sizeof(uint8_t);
		fwrite(&Lkeyframe, sizeof(uint8_t), 1, Pfile);

		for (SMPTRtMK U1 = 0; U1 < Lkeyframe; ++U1)
		{
			uint8_t Lbone = *(uint8_t *)(Pdata + Ldata);
			Ldata += sizeof(uint8_t);

			uint8_t Pb[Lbone * (sizeof(uint8_t) + sizeof(float) * (3+4+3))];
			uint8_t Lb = 0;
//			SMPT_DBmN2L("test0 %d", *(Pdata + Ldata))
//			SMPT_DBmN2L("test1 %f", *(float *)(Pdata + Ldata))
//			SMPT_DBmN2L("test2 %f", *(float *)(Pdata + Ldata + 1))
			for (SMPTRtJWL U2 = 0; U2 < Lbone; ++U2)
			{
				uint8_t *Pd = Pdata + Ldata + sizeof(uint8_t);
				uint8_t *Pb0 = Pb + (sizeof(uint8_t) + sizeof(float) * (3+4+3)) * Lb;
				//! another way to sort
//				if
//				(
//					memcmp(Pd, smptm_v4Psrt, sizeof(float) * 3) ||
//					memcmp(Pd + sizeof(float) * 3, smptm_v4Psrt + 7, sizeof(float) * 4) ||
//					memcmp(Pd + sizeof(float) * (3+4), smptm_v4Psrt + 4, sizeof(float) * 3)
//				)
				{
					//.i clean vbone on blender
//					if (*(Pd - sizeof(uint8_t)) >= 52)
//						continue;
					Pb0[0] = *(Pd - sizeof(uint8_t));
//					SMPT_DBmN2L("Pb0[%d] %d", Lb, Pb0[0])
					memcpy(Pb0 + sizeof(uint8_t), Pd, sizeof(float) * 3);
//					SMPT_DBmN2L("s[0] %f", *(float *)(Pb0 + sizeof(uint8_t)))
//					SMPT_DBmN2L("s[1] %f", *(float *)(Pb0 + sizeof(uint8_t) + sizeof(float)))
//					SMPT_DBmN2L("s[2] %f", *(float *)(Pb0 + sizeof(uint8_t) + sizeof(float) * 2))
					float Pr[4];
					Pd += sizeof(float) * 3;
					Pr[3] = *(float *)Pd;
					Pr[0] = *(float *)(Pd + sizeof(float));
					Pr[1] = *(float *)(Pd + sizeof(float) * 2);
					Pr[2] = *(float *)(Pd + sizeof(float) * 3);
//					SMPT_DBmN2L("Pr[0] %f", Pr[0])
//					SMPT_DBmN2L("Pr[1] %f", Pr[1])
//					SMPT_DBmN2L("Pr[2] %f", Pr[2])
//					SMPT_DBmN2L("Pr[3] %f", Pr[3])
					SMPTM_V4mQI(Pr, 0)
					memcpy(Pb0 + sizeof(uint8_t) + sizeof(float) * 3, Pr, sizeof(float) * 4);
					memcpy(Pb0 + sizeof(uint8_t) + sizeof(float) * (3+4), Pd + sizeof(float) * 4, sizeof(float) * 3);
//					SMPT_DBmN2L("t[0] %f", *(float *)(Pb0 + sizeof(uint8_t) + sizeof(float) * (3+4)))
//					SMPT_DBmN2L("t[1] %f", *(float *)(Pb0 + sizeof(uint8_t) + sizeof(float) * (3+4) + sizeof(float)))
//					SMPT_DBmN2L("t[2] %f", *(float *)(Pb0 + sizeof(uint8_t) + sizeof(float) * (3+4) + sizeof(float) * 2))
					++Lb;
				}
				Ldata += sizeof(uint8_t) + sizeof(float) * (3+4+3);
			}
			fwrite(&Lb, sizeof(uint8_t), 1, Pfile);
			fwrite(Pb, sizeof(uint8_t) + sizeof(float) * (3+4+3), Lb, Pfile);
		}
		free(Pdata);
	}
	fclose(Pfile);
}
