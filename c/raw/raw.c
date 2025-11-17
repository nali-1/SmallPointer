const SMPTRtMB smptrPmb[SMPTRcMA] =
{
	#define X(v, b, ...) b,
		SMPTRxM0
	#undef X
	#define X(v, b, ...) b,
		SMPTRxM1
	#undef X
};
const SMPTRtMK smptrPmk[SMPTRcMK][3] =
{
	#define X(v, k0, k1, k2) {k0, k1, k2},
		SMPTRxMK
	#undef X
};

const SMPTRtMA smptrPmr[SMPTRcM] =
{
	#define X(v, r) r,
		SMPTRxM
	#undef X
};

struct SMPTRsCACHE *smptrPcache;

void smptrMset()
{
	smptrPcache = malloc(sizeof(struct SMPTRsCACHE));
	smptrPcache->d_bl_p = malloc(sizeof(uint32_t) * 2);
	smptrPcache->d_bl_p[1] = 0;
	smptrPcache->d_p = smptfMread(SMPTFcHOME_ASSET, smptrPcache->d_bl_p);

	//! load data
}

void smptrMfree0()
{
	free(smptrPcache->d_bl_p);
	free(smptrPcache->d_p);
	free(smptrPcache);
}

void smptrMfree1()
{
	#if SMPT_CM_DRM || SMPT_CM_ASURFACE || SMPT_CM_WL || SMPT_CM_X11
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
}
