const SMPTRtMA smptrPmr[] =
{
	#define X(v, r, f) r,
		SMPTR_MDx
	#undef X
};

SMPTRtI *smptr_mdPi[SMPTR_MDcM];
SMPTRtI smptr_mdPil[SMPTR_MDcM];
uint8_t *smptr_mdPa;
uint32_t smptr_mdLa;

void smptr_mdMset()
{
	uint32_t Ustep = 0;
	for (SMPTRtJWL l0 = 0; l0 < SMPTR_MDcO; ++l0)
	{
		smptr_mdPil[l0] = *(SMPTRtI *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]) * sizeof(SMPTRtI);
		smptrPcache->d_bl_p[1] += sizeof(SMPTRtI);

		smptr_mdPi[l0] = malloc(smptr_mdPil[l0]);
		memcpy(smptr_mdPi[l0], smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_mdPil[l0]);
		smptrPcache->d_bl_p[1] += smptr_mdPil[l0];
	}
	smptr_mdLa = (sizeof(float) * 3) * *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptr_mdPa = malloc(smptr_mdLa);
	memcpy(smptr_mdPa, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_mdLa);
}

void smptr_mdMfree()
{
}
