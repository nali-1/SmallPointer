uint8_t smptr_cePnet[SMPTRlNET];
SMPTRtNET smptr_ceLnet = 0;

double smptr_ceDdelta = 0;

void smptr_ceMset()
{
	smptr_ce_kfMset();
	smptr_ce_mdMset();

	smptr_cemMset();
	smptr_ceaMset();

	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMset();
	#endif

	smpt_sfUstate |= SMPT_SFuS_RAW;
}

void smptr_ceMsend()
{
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_cePnet);
	smptr_ceLnet = sizeof(struct timespec);

	//SMPT_DBmN2L("smptr_ceLnet %d", smptr_ceLnet)

	smptr_ceuMsend();
}

static struct timespec Stsp_s = {0}, Stsp_e;
void smptr_ceMread()
{
	Stsp_s = *(struct timespec *)smptr_cePnet;
	//SMPT_DBmN2L("C tv_sec %ld", Stsp_s.tv_sec)
	//SMPT_DBmN2L("C tv_nsec %ld", Stsp_s.tv_nsec)

	if ((Stsp_s.tv_sec > Stsp_e.tv_sec) || (Stsp_s.tv_sec == Stsp_e.tv_sec && Stsp_s.tv_nsec > Stsp_e.tv_nsec))
	{
		smptr_ceLnet = sizeof(struct timespec);

		smptr_ceuMread();
		smptr_cemMread();
		smptr_ceaMread();

		Stsp_e = Stsp_s;
	}
}

static struct timespec Stsp_ds = {0}, Stsp_de;
void smptr_ceMloop()
{
	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMread();
	#endif

	smptr_ceuMloop();
	smptr_ceaMloop();
	smptr_cemMloop();

	clock_gettime(CLOCK_MONOTONIC, &Stsp_de);
	smptr_ceDdelta = Stsp_de.tv_sec + (double)Stsp_de.tv_nsec / 1e9 - Stsp_ds.tv_sec - (double)Stsp_ds.tv_nsec / 1e9;
	Stsp_ds = Stsp_de;

	smptr_ceMsend();
	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMsend();
	#endif
}

void smptr_ceMfree()
{
	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMfree();
	#endif

	#ifdef SMPT_CM_VK
		const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;

		while (!(smpt_sfUstate & SMPT_SFuS_EXIT_RENDER))
		{
			SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
			SMPT_DBmN2L("smpt_sfUstate %d", smpt_sfUstate)
		}

		SMPT_DBmR2L("vkQueueWaitIdle %d", vkQueueWaitIdle(Pinfo->Pvkqueue[smpt_rd_vkqUq_gp]))
		SMPT_DBmR2L("vkQueueWaitIdle %d", vkQueueWaitIdle(Pinfo->Pvkqueue[smpt_rd_vkqUq_sf]))

		smptr_ceaMfree();
		smptr_cemMfree();

		smptr_ce_mdMfree();
		smpt_rd_vk_cmdMfree();
	#endif

	smptr_ce_kfMfree();
}
