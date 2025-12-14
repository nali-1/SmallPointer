struct SMPTR_SVtNET smptr_svPnet[SMPT_NWlU];

FILE *smptr_svPfile;
uint32_t smptr_svUrw = 0;

void smptr_svMset()
{
	SMPT_DBmR2L("mkdir %d", mkdir(SMPTFcSAVE, S_IRUSR | S_IWUSR | S_IXUSR))

	smptr_svuMset();
	smptr_svmMset();
	smptr_svaMset();

	#ifdef SMPT_CM_UDP
		smpt_nw_udp_svMset();
	#endif

	smptr_svMfread();

	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smptr_svMloop, NULL))
}

void smptr_svMsend(SMPT_NWtU u)
{
//	SMPT_DBmN2L("S u %d", u)
//	SMPT_DBmN2L("S smptr_svPnet[u].Lnet %d", smptr_svPnet[u].Lnet)
	*(uint32_t *)smptr_svPnet[u].Pnet = smptr_svUrw;
	smptr_svPnet[u].Lnet = sizeof(uint32_t);

	smptr_svuMsend(u);
	smptr_svmMsend(u);
	smptr_svaMsend(u);
//	SMPT_DBmN2L("S smptr_svPnet[u].Lnet %d", smptr_svPnet[u].Lnet)
}

static struct timespec Ptsp_e[SMPT_NWlU] = {0}, Ptsp_s[SMPT_NWlU];
static struct timespec Stimespec = {0};
void smptr_svMread(SMPT_NWtU u)
{
	Ptsp_s[u] = *(struct timespec *)smptr_svPnet[u].Pnet;
	//SMPT_DBmN2L("S tv_sec %ld", Ptsp_s[u].tv_sec)
	//SMPT_DBmN2L("S tv_nsec %ld", Ptsp_s[u].tv_nsec)
	if (!memcmp(Ptsp_s + u, &Stimespec, sizeof(struct timespec)))
	{
		return;
	}

	if ((Ptsp_s[u].tv_sec > Ptsp_e[u].tv_sec) || (Ptsp_s[u].tv_sec == Ptsp_e[u].tv_sec && Ptsp_s[u].tv_nsec > Ptsp_e[u].tv_nsec))
	{
		//SMPT_DBmN2L("W")
		smptr_svPnet[u].Lnet = sizeof(struct timespec);

		smptr_svuMread(u);

		Ptsp_e[u] = Ptsp_s[u];
	}
}

//static inline double now_sec()
//{
//	struct timespec ts;
//	clock_gettime(CLOCK_MONOTONIC, &ts);
//	return ts.tv_sec + ts.tv_nsec * 1e-9;
//}

int smptr_svMloop(void *P)
{
	struct timespec Stsp_s, Stsp_e, Stsp_n = {0};
	double Dn;
	clock_gettime(CLOCK_MONOTONIC, &Stsp_s);
	while (!(smpt_sfUstate & SMPT_SFuS_EXIT))
	{
		#ifdef SMPT_CM_UDP
			smpt_nw_udp_svMread();
		#endif

		smptr_svuMloop();
		smptr_svmMloop();
		smptr_svaMloop();

		for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
		{
			smptr_svMsend(l0);
			#ifdef SMPT_CM_UDP
				smpt_nw_udp_svMsend(l0);
			#endif
		}

		if (++smptr_svUrw % SMPTRuRW == 0)
		{
			clock_gettime(CLOCK_MONOTONIC, &Stsp_e);
			Dn = Stsp_e.tv_sec + (double)Stsp_e.tv_nsec / 1e9 - Stsp_s.tv_sec - (double)Stsp_s.tv_nsec / 1e9;
			SMPT_DBmN2L("s %f", Stsp_s.tv_sec + (double)Stsp_s.tv_nsec / 1e9)
			SMPT_DBmN2L("e %f", Stsp_e.tv_sec + (double)Stsp_e.tv_nsec / 1e9)
			SMPT_DBmN2L("Dn %f", Dn)
			SMPT_DBmN2L("smptr_svUrw %d", smptr_svUrw)
			if (Dn < 1.0)
			{
				Stsp_n.tv_nsec = (1.0 - Dn) * 1e9;
				thrd_sleep(&Stsp_n, NULL);
			}
			clock_gettime(CLOCK_MONOTONIC, &Stsp_s);
		}

//		double next_tick = now_sec();
//		double t = now_sec();
//		if (t >= next_tick)
//		{
//			++smptr_svUrw;
//			#ifdef SMPT_CM_UDP
//				smpt_nw_udp_svMread();
//			#endif
//
//			smptr_svuMloop();
//			smptr_svmMloop();
//			smptr_svaMloop();
//
//			for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
//			{
//				smptr_svMsend(l0);
//				#ifdef SMPT_CM_UDP
//					smpt_nw_udp_svMsend(l0);
//				#endif
//			}
//
//			next_tick += 1 / SMPTRuRW;
//		}
//		else
//		{
//			double sleep_time = next_tick - t;
//			struct timespec ts =
//			{
//				.tv_sec = (time_t)sleep_time,
//				.tv_nsec = (long)((sleep_time - (time_t)sleep_time) * 1e9)
//			};
//			nanosleep(&ts, NULL);
//		}
	}
	smptr_svMfsend();
	smpt_sfUstate |= SMPT_SFuS_EXIT_SERVER;
	return 0;
}

void smptr_svMfread()
{
	SMPT_DBmR2L("fopen %p", smptr_svPfile = fopen(SMPTFcSAVE_SPACE, "rb"))

	smptr_svuMfread();
	smptr_svmMfread();

	if (smptr_svPfile)
	{
		fclose(smptr_svPfile);
	}
}

void smptr_svMfsend()
{
	SMPT_DBmR2L("fopen %p", smptr_svPfile = fopen(SMPTFcSAVE_SPACE, "wb"))

	smptr_svuMfsend();
	smptr_svmMfsend();

	fclose(smptr_svPfile);
}

void smptr_svMfree()
{
	while (!(smpt_sfUstate & SMPT_SFuS_EXIT_SERVER))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	smptr_svmMfree();
	smptr_svuMfree();

	#ifdef SMPT_CM_UDP
		smpt_nw_udp_svMfree();
	#endif
}
