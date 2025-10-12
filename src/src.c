//.i linux
int main()
{
	#ifdef SMPT_CM_DEBUG
		smpt_dbMset();
	#endif

	SMPT_DBmR2L("signal %d", signal(SIGINT, SIG_IGN))

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
