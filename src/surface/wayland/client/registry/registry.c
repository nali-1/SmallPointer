struct wl_registry *smpt_sf_wl_ce_rgtP;

static void wl_registry_listener_global(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version)
{
	SMPT_DBmN2L("wl_registry_listener_global_interface %s", interface)
	if (!strcmp(interface, wl_compositor_interface.name))
	{
		SMPT_DBmR2L("wl_registry_bind %p", smpt_sf_wl_cePcpst = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1))
	}
	else if (!strcmp(interface, xdg_wm_base_interface.name))
	{
		SMPT_DBmR2L("wl_registry_bind %p", smpt_sf_wl_ce_xdg_wmPb = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, 1))
		SMPT_DBmR2L("xdg_wm_base_add_listener %d", xdg_wm_base_add_listener(smpt_sf_wl_ce_xdg_wmPb, &smpt_sf_wl_ce_xdg_wmSb_listener, NULL))
	}
	else if (!strcmp(interface, wl_seat_interface.name))
	{
		SMPT_DBmR2L("wl_registry_bind %p", smpt_sf_wl_cesP = wl_registry_bind(wl_registry, name, &wl_seat_interface, 1))
		SMPT_DBmR2L("wl_seat_add_listener %d", wl_seat_add_listener(smpt_sf_wl_cesP, &smpt_sf_wl_cesSlistener, NULL))
	}
	else if (!strcmp(interface, zwp_pointer_constraints_v1_interface.name))
	{
		SMPT_DBmR2L("wl_registry_bind %p", smpt_sf_wl_ce_zwp_ptPcst = wl_registry_bind(wl_registry, name, &zwp_pointer_constraints_v1_interface, 1))
	}
	else if (!strcmp( interface, zwp_relative_pointer_manager_v1_interface.name))
	{
		SMPT_DBmR2L("wl_registry_bind %p", smpt_sf_wl_ce_zwp_rltPpt_mng = wl_registry_bind(wl_registry, name, &zwp_relative_pointer_manager_v1_interface, 1))
	}
}

static void wl_registry_listener_global_remove(void *data, struct wl_registry *wl_registry, uint32_t name)
{
}

struct wl_registry_listener smpt_sf_wl_ce_rgtSlistener =
{
	.global = wl_registry_listener_global,
	.global_remove = wl_registry_listener_global_remove
};

void smpt_sf_wl_ce_rgtMset()
{
	SMPT_DBmR2L("wl_display_get_registry %p", smpt_sf_wl_ce_rgtP = wl_display_get_registry(smpt_sf_wl_ce_Pdp))
	SMPT_DBmR2L("wl_registry_add_listener %d", wl_registry_add_listener(smpt_sf_wl_ce_rgtP, &smpt_sf_wl_ce_rgtSlistener, NULL))
}

void smpt_sf_wl_ce_rgtMfree()
{
	wl_registry_destroy(smpt_sf_wl_ce_rgtP);
}
