struct xdg_wm_base *smpt_sf_wl_ce_xdg_wmPb;

static void xdg_wm_base_handle_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
	xdg_wm_base_pong(xdg_wm_base, serial);
}

struct xdg_wm_base_listener smpt_sf_wl_ce_xdg_wmSb_listener =
{
	.ping = xdg_wm_base_handle_ping,
};

void smpt_sf_wl_ce_xdg_wmMfree()
{
	smpt_sf_wl_ce_xdg_tlvMfree();
	smpt_sf_wl_ce_xdg_sfMfree();

	xdg_wm_base_destroy(smpt_sf_wl_ce_xdg_wmPb);
}
