struct SMPTRsCACHE *smptrPcache;

void smptrMset()
{
	smptrPcache = malloc(sizeof(struct SMPTRsCACHE));
	smptrPcache->d_bl_p[1] = 0;
	smptrPcache->d_p = smptfMread(SMPTFcHOME_ASSET, smptrPcache->d_bl_p);

	#ifdef SMPT_CM_MAIN
		smptr_mdMset();
	#endif

	#if SMPT_CM_SERVER
		smptr_svMset();
	#endif

	#ifdef SMPT_CM_CLIENT
		smptr_ceMset();
	#endif
}

void smptrMfree0()
{
	free(smptrPcache->d_p);
	free(smptrPcache);
}

void smptrMfree1()
{
	#if SMPT_CM_DRM || SMPT_CM_AWINDOW || SMPT_CM_WL || SMPT_CM_X11
		smpt_sfUstate |= SMPT_SFuS_EXIT;
	#endif

	#ifdef SMPT_CM_SERVER
		smptr_svMfree();
	#endif

	#ifdef SMPT_CM_CLIENT
		smptr_ceMfree();
	#endif

	//! switch to pipewire
	// al_clean();

	#ifdef SMPT_CM_WL
		smpt_sf_wl_ceMfree();
	#endif

	#ifdef SMPT_CM_MAIN
		smptr_mdMfree();
	#endif
}
