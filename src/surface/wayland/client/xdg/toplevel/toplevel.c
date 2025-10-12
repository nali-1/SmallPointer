struct xdg_toplevel *smpt_sf_wl_ce_xdg_tlvP;

static void xdg_toplevel_listener_configure(void *data, struct xdg_toplevel *_xdg_toplevel, int32_t width, int32_t height, struct wl_array *states)
{
	if (smpt_sfUwidth != width || smpt_sfUheight != height)
	{
		wl_surface_commit(smpt_sf_wl_cePsf);

		smpt_sfUwidth = width;
		smpt_sfUheight = height;
		smpt_sfUstate |= SMPT_SFuS_RE;
	}
}

static void xdg_toplevel_listener_close(void *data, struct xdg_toplevel *xdg_toplevel)
{
	smptrMfree1();
}

static void xdg_toplevel_listener_configure_bounds(void *data, struct xdg_toplevel *xdg_toplevel, int32_t width, int32_t height)
{
	// info("xdg_toplevel_listener_configure_bounds")
}

static void xdg_toplevel_listener_wm_capabilities(void *data, struct xdg_toplevel *xdg_toplevel, struct wl_array *capabilities)
{
	// info("xdg_toplevel_listener_wm_capabilities")
}

struct xdg_toplevel_listener smpt_sf_wl_ce_xdg_tlvSlistener =
{
	.configure = xdg_toplevel_listener_configure,
	.close = xdg_toplevel_listener_close,
	.configure_bounds = xdg_toplevel_listener_configure_bounds,
	.wm_capabilities = xdg_toplevel_listener_wm_capabilities
};

void smpt_sf_wl_ce_xdg_tlvMset()
{
	SMPT_DBmR2L("xdg_surface_get_toplevel %p", smpt_sf_wl_ce_xdg_tlvP = xdg_surface_get_toplevel(smpt_sf_wl_ce_xdg_sfP))
	SMPT_DBmR2L("xdg_toplevel_add_listener %d", xdg_toplevel_add_listener(smpt_sf_wl_ce_xdg_tlvP, &smpt_sf_wl_ce_xdg_tlvSlistener, NULL))
}

void smpt_sf_wl_ce_xdg_tlvMfree()
{
	xdg_toplevel_destroy(smpt_sf_wl_ce_xdg_tlvP);
}
