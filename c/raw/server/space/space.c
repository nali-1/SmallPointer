uint32_t smptr_sv_spUrw = 0;

void smptr_sv_spMstart()
{
	#ifdef SMPTR_MDxM0
		for (uint8_t U0 = 0; U0 < 10; ++U0)
			smptr_sv_ett_pmMadd();
	#endif
}
