struct wl_display *smpt_sf_wl_ce_Pdp;
struct wl_compositor *smpt_sf_wl_cePcpst;
struct wl_surface *smpt_sf_wl_cePsf;

void smpt_sf_wl_ceMset()
{
	SMPT_DBmR2L("wl_display_connect %p", smpt_sf_wl_ce_Pdp = wl_display_connect(getenv("WAYLAND_DISPLAY")))

	smpt_sf_wl_ce_rgtMset();

	SMPT_DBmR2L("wl_display_roundtrip %d", wl_display_roundtrip(smpt_sf_wl_ce_Pdp))

	SMPT_DBmR2L("wl_compositor_create_surface %p", smpt_sf_wl_cePsf = wl_compositor_create_surface(smpt_sf_wl_cePcpst))

	smpt_sf_wl_ce_xdg_sfMset();
	smpt_sf_wl_ce_xdg_tlvMset();

	wl_surface_commit(smpt_sf_wl_cePsf);
	SMPT_DBmR2L("wl_display_dispatch %d", wl_display_dispatch(smpt_sf_wl_ce_Pdp));

	//.i loop
	int r = 0;

	while (!(smpt_sfUstate & SMPT_SFuS_RENDER))
	{
		SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		SMPT_DBmN2L("smpt_sfUstate %d", smpt_sfUstate)
	}

	while (r != INT_MAX)
	{
		if (smpt_sfUstate & SMPT_SFuS_EXIT)
		{
			r = INT_MAX;
		}
		else
		{
			r = wl_display_dispatch(smpt_sf_wl_ce_Pdp);
		}
	}

	smpt_sf_wl_ceMfree();
	SMPT_DBmN2L("r %d", r);
}

void smpt_sf_wl_ceMfree()
{
	smpt_sf_wl_cesMfree();

	smpt_sf_wl_ce_xdg_wmMfree();

	smpt_sf_wl_ce_zwplMfree();
	smpt_sf_wl_ce_zwp_ptMfree();

	smpt_sf_wl_ce_zwp_rltMfree();

	wl_surface_destroy(smpt_sf_wl_cePsf);
	wl_compositor_destroy(smpt_sf_wl_cePcpst);

	smpt_sf_wl_ce_rgtMfree();

	wl_display_disconnect(smpt_sf_wl_ce_Pdp);
}
