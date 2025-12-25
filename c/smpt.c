#ifdef SMPT_CM_ST_ANDROID
	ANativeActivity *smptPanative_activity;

	static int Mset(void *p)
	{
		smptm_v4Mset();

		smptrMset();
		#if SMPT_CM_SERVER
			smptr_svMset();
		#endif
		#ifdef SMPT_CM_CLIENT
			smptr_ceMset();

			smpt_rd_vkMset();
			//! audio math
			//smpt_adoMset();
		#endif
		smpt_ip_aipMloop();
		return 0;
	}

	void ANativeActivity_onCreate(ANativeActivity *Panativeactivity, void *Psaved_state, size_t Lsaved_state)
	{
		if (!(smpt_sfUstate & SMPT_SFuS_ANDROID_CREATE))
		{
			#ifdef SMPT_CM_DEBUG
				smpt_dbMset();
			#endif

			smpt_sfUstate |= SMPT_SFuS_ANDROID_CREATE;
			SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, Mset, NULL))

			Panativeactivity->callbacks->onNativeWindowCreated = smpt_sf_awdMcreated;
			Panativeactivity->callbacks->onNativeWindowResized = smpt_sf_awdMresized;
			Panativeactivity->callbacks->onNativeWindowDestroyed = smpt_sf_awdMdestroyed;
			Panativeactivity->callbacks->onInputQueueCreated = smpt_ip_aipMcreated;
			Panativeactivity->callbacks->onInputQueueDestroyed = smpt_ip_aipMdestroyed;
			smptPanative_activity = Panativeactivity;
		}
		SMPT_DBmN2L("ANativeActivity_onCreate")
	}
#endif

#ifdef SMPT_CM_ST_LINUX
	int main()
	{
		smpt_dbMset();
		SMPT_DBmR2L("signal %d", signal(SIGINT, SIG_IGN))

		smptm_v4Mset();

		#ifdef SMPT_CM_GEN
			smptgMsend();
		#endif
		smptrMset();
		#ifdef SMPT_CM_SERVER
			smptr_svMset();
		#endif
		#ifdef SMPT_CM_CLIENT
			smptr_ceMset();

			#ifdef SMPT_CM_LIBINPUT
				smpt_ip_lipMset();
			#endif

			#ifdef SMPT_CM_WL
				smpt_sf_wl_ceMset();
			#else
				#ifdef SMPT_CM_VK
					smpt_rd_vkMset();
				#endif
			#endif

			//! audio math
			//smpt_adoMset();
			//! switch to pipewire
			// al_set();
			//! test with wl
			#ifdef SMPT_CM_LIBINPUT
				smpt_ip_lipMloop();
			#endif

			SMPT_DBmR2L("tcflush %d", tcflush(STDIN_FILENO, TCIFLUSH))
			smpt_dbMfree();
		#endif
	}
#endif
