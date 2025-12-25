static snd_pcm_t *Psnd_pcm_t;

static float Pdata[SMPT_ADOuFRAME * SMPT_ADOuCHANNEL_COUNT];
int smpt_ado_alsaMset(void *P)
{
	snd_pcm_hw_params_t *Psnd_pcm_hw_params_t;

	snd_pcm_open(&Psnd_pcm_t, "default", SND_PCM_STREAM_PLAYBACK, 0);

	snd_pcm_hw_params_alloca(&Psnd_pcm_hw_params_t);
	snd_pcm_hw_params_any(Psnd_pcm_t, Psnd_pcm_hw_params_t);

	snd_pcm_hw_params_set_access(Psnd_pcm_t, Psnd_pcm_hw_params_t, SND_PCM_ACCESS_RW_INTERLEAVED);

	snd_pcm_hw_params_set_format(Psnd_pcm_t, Psnd_pcm_hw_params_t, SND_PCM_FORMAT_FLOAT_LE);

	snd_pcm_hw_params_set_channels(Psnd_pcm_t, Psnd_pcm_hw_params_t, SMPT_ADOuCHANNEL_COUNT);

	snd_pcm_hw_params_set_rate_near(Psnd_pcm_t, Psnd_pcm_hw_params_t, (unsigned int[]){SMPT_ADOfSAMPLE_RATE}, NULL);

	snd_pcm_hw_params(Psnd_pcm_t, Psnd_pcm_hw_params_t);
	snd_pcm_prepare(Psnd_pcm_t);

	smpt_sfUstate |= SMPT_SFuS_LINUX_ALSA;
	while (smpt_sfUstate & SMPT_SFuS_LINUX_ALSA)
	{
		smpt_adoMgen(Pdata, SMPT_ADOuFRAME);
		if (snd_pcm_writei(Psnd_pcm_t, Pdata, SMPT_ADOuFRAME) < 0)
		{
			snd_pcm_prepare(Psnd_pcm_t);
			continue;
		}
	}
	smpt_sfUstate |= SMPT_SFuS_LINUX_ALSA;
	return 0;
}

void smpt_ado_alsaMfree()
{
	while (!(smpt_sfUstate & SMPT_SFuS_LINUX_ALSA))
	{
		SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
	}
	snd_pcm_drain(Psnd_pcm_t);
	snd_pcm_close(Psnd_pcm_t);
}
