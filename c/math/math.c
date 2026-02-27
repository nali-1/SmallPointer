float smptmMnr(float Fr, float F1)
{
	return fmodf(fmodf(Fr + F1 / 2.0F, F1) + F1, F1) - F1 / 2.0F;
}

uint32_t smptmMnu(uint32_t Uv, uint32_t U0, uint32_t U1)
{
	return U0 + (((Uv - U0) % (U1 - U0)) + (U1 - U0)) % (U1 - U0);
}

float smptmMnf(float Fv, float F0, float F1)
{
	return F0 + fmodf((fmodf((Fv - F0), (F1 - F0)) + (F1 - F0)), (F1 - F0));
}

float smptmMd2r(float Fd)
{
	return Fd * (float)M_PI / 180.0F;
}

float smptmMa2b(float Fa, float Fb, float Ft)
{
	return Fa + (Fb - Fa) * Ft;
}
