const float smptm_m4x4P[] =
{
	1.0F, 0.0F, 0.0F, 0.0F,
	0.0F, 1.0F, 0.0F, 0.0F,
	0.0F, 0.0F, 1.0F, 0.0F,
	0.0F, 0.0F, 0.0F, 1.0F
};

void smptm_m4x4Mi(float Pm[16])
{
	int32_t l_0, l_1, l_2;
	float Ps[16];
	float Pt[16];
	memcpy(Ps, smptm_m4x4P, sizeof(smptm_m4x4P));
	memcpy(Pt, Pm, sizeof(float) * 16);

	for (l_0 = 0; l_0 < 3; l_0++)
	{
		int32_t pivot = l_0;

		float pivotsize = Pt[l_0 * 4 + l_0];

		if (pivotsize < 0)
		{
			pivotsize = -pivotsize;
		}

		for (l_1 = l_0 + 1; l_1 < 4; l_1++)
		{
			float l_f = Pt[l_1 * 4 + l_0];

			if (l_f < 0)
				l_f = -l_f;

			if (l_f > pivotsize)
			{
				pivot = l_1;
				pivotsize = l_f;
			}
		}

		if (pivotsize == 0)
		{
			memcpy(Pm, smptm_m4x4P, sizeof(float) * 16);
			return;
		}

		if (pivot != l_0)
		{
			for (l_1 = 0; l_1 < 4; l_1++)
			{
				int32_t i4j = l_0 * 4 + l_1;
				int32_t p4j = pivot * 4 + l_1;
				float tmp;

				tmp = Pt[i4j];
				Pt[i4j] = Pt[p4j];
				Pt[p4j] = tmp;

				tmp = Ps[i4j];
				Ps[i4j] = Ps[p4j];
				Ps[p4j] = tmp;
			}
		}

		for (l_1 = l_0 + 1; l_1 < 4; l_1++)
		{
			float l_f = Pt[l_1 * 4 + l_0] / Pt[l_0 * 4 + l_0];

			for (l_2 = 0; l_2 < 4; l_2++)
			{
				int32_t j4k = l_1 * 4 + l_2;
				int32_t i4k = l_0 * 4 + l_2;
				Pt[j4k] -= l_f * Pt[i4k];
				Ps[j4k] -= l_f * Ps[i4k];
			}
		}
	}

	for (l_0 = 3; l_0 >= 0; --l_0)
	{
		float l_f;

		if (!(l_f = Pt[l_0 * 4 + l_0]))
		{
			memcpy(Pm, smptm_m4x4P, sizeof(float) * 16);
			return;
		}

		for (l_1 = 0; l_1 < 4; l_1++)
		{
			int32_t i4j = l_0 * 4 + l_1;

			Pt[i4j] /= l_f;
			Ps[i4j] /= l_f;
		}

		for (l_1 = 0; l_1 < l_0; l_1++)
		{
			l_f = Pt[l_1 * 4 + l_0];

			for (l_2 = 0; l_2 < 4; l_2++)
			{
				int32_t j4k = l_1 * 4 + l_2;
				int32_t i4k = l_0 * 4 + l_2;
				Pt[j4k] -= l_f * Pt[i4k];
				Ps[j4k] -= l_f * Ps[i4k];
			}
		}
	}

	memcpy(Pm, Ps, sizeof(float) * 16);
}

void smptm_m4x4Mm(const float Pa[16], const float Pb[16], float Pm[16])
{
	for (uint8_t l_0 = 0; l_0 < 4; l_0++)
	{
		for (uint8_t l_1 = 0; l_1 < 4; l_1++)
		{
			Pm[l_0 * 4 + l_1] = Pa[l_0 * 4] * Pb[l_1] + Pa[l_0 * 4 + 1] * Pb[4 + l_1] + Pa[l_0 * 4 + 2] * Pb[8 + l_1] + Pa[l_0 * 4 + 3] * Pb[12 + l_1];
		}
	}
}

void smptm_m4x4Mp(float Pm[16])
{
	float Ff = 1.0F / tanf(smptmMd2r(SMPTM_M4X4fFOV * 0.5F));
	float Fa = SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR;
	Pm[0] = Ff / ((float)smpt_sfUwidth / (float)smpt_sfUheight);
	Pm[5] = Ff;
	Pm[10] = SMPTM_M4X4fZ_FAR / Fa;
	Pm[11] = 1.0F;
	Pm[14] = -(SMPTM_M4X4fZ_FAR * SMPTM_M4X4fZ_NEAR) / Fa;
}
