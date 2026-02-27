#ifdef SMPT_CM_SERVER
	const uint32_t smpt_nwPu[SMPT_NWlU] =
	{
		//.c client ip
		SMPT_NWmIP(127, 0, 0, 1)
	};
#endif

#ifdef SMPT_CM_CLIENT
	float smpt_nwMwrap_a2b(float Fa, float Fb, float F0, float F1, float Ft)
	{
		const float Frange = F1 - F0;
		const float Fdiff = Fb - Fa;

		if (Fdiff > Frange * 0.5F) Fb -= Frange;
		if (Fdiff < -Frange * 0.5F) Fb += Frange;

		return smptmMnf(Fa + (Fb - Fa) * Ft, F0, F1);
	}

	float smpt_nwMwrap_r(float Fr)
	{
		Fr = fmodf(Fr + M_PI, 2.0f * M_PI);
		if (Fr < 0) Fr += 2.0f * M_PI;
		return Fr - M_PI;
	}
#endif
