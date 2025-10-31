#define nK \
	X("SuperCutePomiWalk")

static const char *Pc[] =
{
	#define X(n) SMPTFcFACTORY_KEYFRAME "/" n ".bin",
		nK
	#undef X
};

void smptg_kfMsend()
{
	FILE *Pfile = fopen(SMPTFcHOME_ASSET, "ab");
	fwrite((uint8_t[]){sizeof(Pc) / sizeof(Pc[0])}, sizeof(uint8_t), 1, Pfile);

	uint32_t Ldata;
	uint8_t *Pdata;
	for (uint8_t l0 = 0; l0 < sizeof(Pc) / sizeof(Pc[0]); ++l0)
	{
		Pdata = smptfMread(Pc[l0], &Ldata);
		Ldata = 0;

		uint8_t Lkeyframe = *(uint8_t *)(Pdata + Ldata);
		fwrite(&Lkeyframe, sizeof(uint8_t), 1, Pfile);
		Ldata += sizeof(uint8_t);

		for (uint32_t l1 = 0; l1 < Lkeyframe; ++l1)
		{
			uint8_t Lbone = *(uint8_t *)(Pdata + Ldata);
			fwrite(&Lbone, sizeof(uint8_t), 1, Pfile);
			Ldata += sizeof(uint8_t);

			for (uint32_t l2 = 0; l2 < Lbone; ++l2)
			{
				fwrite(Pdata + Ldata, sizeof(uint8_t), 1, Pfile);
				Ldata += sizeof(uint8_t);

				fwrite(Pdata + Ldata, sizeof(float), 3, Pfile);
				Ldata += sizeof(float) * 3;

				float Pr[4];
				Pr[3] = *(float *)(Pdata + Ldata);
				Pr[0] = *(float *)(Pdata + Ldata + sizeof(float));
				Pr[1] = *(float *)(Pdata + Ldata + sizeof(float) * 2);
				Pr[2] = *(float *)(Pdata + Ldata + sizeof(float) * 3);
				SMPTM_V4mQI(Pr, 0)
				fwrite(Pr, sizeof(float), 4, Pfile);
				Ldata += sizeof(float) * 4;

				fwrite(Pdata + Ldata, sizeof(float), 3, Pfile);
				Ldata += sizeof(float) * 3;
			}
		}

		free(Pdata);
	}

	fclose(Pfile);
}
