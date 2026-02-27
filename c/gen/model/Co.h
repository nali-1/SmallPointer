#define lO_A (sizeof(float) * 3)

static void Mo_write()
{
	FILE *Pfile = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", Pfile)
	SMPT_DBmN2L("ftell %ld", ftell(Pfile))

	for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcO; ++U0)
	{
		fwrite(Ph14_il + U0, sizeof(SMPTRtI), 1, Pfile);
		fwrite(Ph14_i[U0], sizeof(SMPTRtI), Ph14_il[U0], Pfile);
//		SMPT_DBmN2L("Ph14_il + %d %p", U0, Ph14_il + U0)
//		SMPT_DBmN2L("Ph14_il[%d] %d", U0, Ph14_il[U0])
	}

	uint8_t *Pa = malloc(lO_A * Lh14_i);
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		//SMPT_DBmN2L("Ph14_tl[%d] %d", U0, Ph14_tl[U0])
		for (uint32_t U1 = 0; U1 < Ph14_tl[U0]; ++U1)
		{
			SMPTRtI Uh14ti = Ph14_ti[U0][U1];
			memcpy(Pa + Uh14ti * lO_A, Ph14_t[U0] + lO_A * U1, lO_A);
		}
	}
//	SMPT_DBmN2L("Lh14_i %d", Lh14_i)
//	for (uint32_t U0 = 0; U0 < (lH14T * lO_A) / sizeof(float); ++U0)
//		SMPT_DBmN2L("0Pa %d %f", U0, *(float *)(Pa + U0 * sizeof(float)))
	fwrite(&Lh14_i, sizeof(uint32_t), 1, Pfile);
	fwrite(Pa, lO_A, Lh14_i, Pfile);
	free(Pa);

	SMPT_DBmR2L("fclose %d", fclose(Pfile))
}
