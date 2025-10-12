struct xdg_surface *smpt_sf_wl_ce_xdg_sfP;

static void xdg_surface_listener_configure(void *data, struct xdg_surface *_xdg_surface, uint32_t serial)
{
	xdg_surface_ack_configure(smpt_sf_wl_ce_xdg_sfP, serial);
	wl_surface_commit(smpt_sf_wl_cePsf);
	#ifdef SMPT_CM_VK
		smpt_rd_vkMset();
	#endif
}

struct xdg_surface_listener smpt_sf_wl_ce_xdg_sfSlistener =
{
	.configure = xdg_surface_listener_configure
};

void smpt_sf_wl_ce_xdg_sfMset()
{
	SMPT_DBmR2L("xdg_wm_base_get_xdg_surface %p", smpt_sf_wl_ce_xdg_sfP = xdg_wm_base_get_xdg_surface(smpt_sf_wl_ce_xdg_wmPb, smpt_sf_wl_cePsf))
	SMPT_DBmR2L("xdg_surface_add_listener %d", xdg_surface_add_listener(smpt_sf_wl_ce_xdg_sfP, &smpt_sf_wl_ce_xdg_sfSlistener, NULL))
}

void smpt_sf_wl_ce_xdg_sfMfree()
{
	xdg_surface_destroy(smpt_sf_wl_ce_xdg_sfP);
}
