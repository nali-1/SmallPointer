const SMPTRtMA smptrPmr[] =
{
	#define X(v, r, f) r,
		SMPTR_MDx
	#undef X
};

SMPTRtI *smptr_mdPi[SMPTR_MDcO];
SMPTRtI smptr_mdPil[SMPTR_MDcO];
uint8_t *smptr_mdPa;
uint32_t smptr_mdLa;

void smptr_mdMset()
{
	SMPT_DBmN2L("smptrPcache->d_bl_p[1] %d", smptrPcache->d_bl_p[1])

	uint32_t Ustep = 0;
	for (uint8_t U0 = 0; U0 < SMPTR_MDcO; ++U0)
	{
		smptr_mdPil[U0] = sizeof(SMPTRtI) * *(SMPTRtI *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(SMPTRtI);

		smptr_mdPi[U0] = malloc(smptr_mdPil[U0]);
		memcpy(smptr_mdPi[U0], smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_mdPil[U0]);
		smptrPcache->d_bl_p[1] += smptr_mdPil[U0];
	}
	smptr_mdLa = (sizeof(float) * 3) * *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptrPcache->d_bl_p[1] += sizeof(uint32_t);
	smptr_mdPa = malloc(smptr_mdLa);
	memcpy(smptr_mdPa, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_mdLa);
	smptrPcache->d_bl_p[1] += smptr_mdLa;
}

void smptr_mdMfree()
{
	for (uint8_t U0 = 0; U0 < SMPTR_MDcO; ++U0)
	{
		free(smptr_mdPi[U0]);
	}
	free(smptr_mdPa);
}
