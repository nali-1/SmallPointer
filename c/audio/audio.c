static float Fphase = 0.0F;
void smpt_adoMgen(float *Pdata, int32_t Iframe)
{
	const float Ffreq = 440.0F;
	const float Fvolume = 0.2F;
	const float Fstep = 2.0F * M_PI * Ffreq / SMPT_ADOfSAMPLE_RATE;
	for (int32_t I0 = 0; I0 < Iframe; I0++)
	{
			float Fs = sinf(Fphase) * Fvolume;
			Fphase += Fstep;

			if (Fphase > 2.0F * M_PI)
				Fphase -= 2.0F * M_PI;

			//.i left
			Pdata[I0 * SMPT_ADOuCHANNEL_COUNT] = Fs;
			//.i right
			Pdata[I0 * SMPT_ADOuCHANNEL_COUNT + 1] = Fs;
	}
}
