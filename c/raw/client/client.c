void smptr_ceMset()
{
	smptr_ce_kfMset();
	smptr_ce_mdMset();

	#ifndef SMPT_CM_ST_JAVA
		smptr_cemMset();
		smptr_ceaMset();
	#endif

	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMset();
	#endif

	#ifdef SMPT_CM_VK
		smpt_sfUstate |= SMPT_SFuS_RAW;
	#endif
}

#ifndef SMPT_CM_ST_JAVA
	#ifdef SMPT_CM_UDP
		uint8_t smptr_cePnet[SMPTRlNET];
		SMPTRtNET smptr_ceLnet = 0;
	#endif

	double
		smptr_ceDdelta = 0,
		smptr_ceDalpha = 0;
	uint8_t smptr_ceUstate = 0;

	void smptr_ceMsend()
	{
		if (!(smptr_ceUstate & 1))
		{
			memset(smptr_cePnet, 0, sizeof(struct timespec));
			smptr_ceLnet = sizeof(struct timespec);
		}
		else
		{
			clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_cePnet);
			smptr_ceLnet = sizeof(struct timespec);

			smptr_ceuMsend();
		}
	}

	static uint32_t Urw_a = 0;
//	static struct timespec Stsp_s_net = {0}, Stsp_e_net;
//	static double smptr_ceDdelta_net;
	void smptr_ceMread()
	{
		uint32_t Urw_b = *(uint32_t *)smptr_cePnet;
		if (Urw_b > Urw_a && smptr_ceLnet == 0)
		//if (Urw_b > Urw_a)
		{
//			clock_gettime(CLOCK_MONOTONIC, &Stsp_e_net);
//			smptr_ceDdelta_net = Stsp_e_net.tv_sec + (double)Stsp_e_net.tv_nsec / 1e9 - Stsp_s_net.tv_sec - (double)Stsp_s_net.tv_nsec / 1e9;
//			Stsp_s_net = Stsp_e_net;
//			double Da = (double)Urw_a * (1.0 / (double)SMPTRuRW);
//			double Db = (double)Urw_b * (1.0 / (double)SMPTRuRW);
//			SMPT_DBmN2L("smptr_ceDdelta_net %f", smptr_ceDdelta_net)
//			SMPT_DBmN2L("rw %f", Db - Da)
//			smptr_ceDalpha = ((smptr_ceDdelta_net + Da) - Da) / (Db - Da);
//			SMPT_DBmN2L("alpha %f", smptr_ceDalpha)
			smptr_ceLnet = sizeof(uint32_t);

			smptr_ceuMread();
			smptr_cemMread();
			smptr_ceaMread();

			Urw_a = Urw_b;
		}
	}

	static struct timespec Stsp_ds = {0}, Stsp_de;
	static double accumulator = 0.0;
	float smptr_ceDpartial_tick;
	void smptr_ceMloop()
	{
		smptr_ceuMloop();
		smptr_ceaMloop();
		smptr_cemMloop();

		clock_gettime(CLOCK_MONOTONIC, &Stsp_de);
		smptr_ceDdelta = Stsp_de.tv_sec + (double)Stsp_de.tv_nsec / 1e9 - Stsp_ds.tv_sec - (double)Stsp_ds.tv_nsec / 1e9;
		Stsp_ds = Stsp_de;

		//SMPT_DBmN2L("smptr_ceDdelta %f", smptr_ceDdelta)
		accumulator += smptr_ceDdelta;
		while (accumulator >= 1.0 / SMPTRuRW)
		{
			//! work
			//SMPT_DBmN2L("accumulator %f", accumulator)
			#ifdef SMPT_CM_UDP
				smpt_nw_udp_ceMread();
			#endif

			smptr_ceMread();
			accumulator -= 1.0 / SMPTRuRW;
		}
		smptr_ceDpartial_tick = (float)(accumulator / (1.0F / SMPTRuRW));

		smptr_ceMsend();
		#ifdef SMPT_CM_UDP
			smpt_nw_udp_ceMsend();
		#endif
	}
#endif

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
