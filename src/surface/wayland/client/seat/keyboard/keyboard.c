struct wl_keyboard *smpt_sf_wl_ces_kbP;

static void wl_keyboard_listener_keymap(void *data, struct wl_keyboard *wl_keyboard, uint32_t format, int32_t fd, uint32_t size)
{
	// SMPT_DBmN2L("wl_keyboard_listener_keymap fd %d", fd)
}

static void wl_keyboard_listener_key(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
	// SMPT_DBmN2L("wl_keyboard_listener_key key %d", key)
	if (state == WL_KEYBOARD_KEY_STATE_PRESSED)
	{
		if (key == KEY_TAB)
			smpt_sf_wl_ce_zwp_ptMset();

		if (key == KEY_W)
			lcu_k ^= SMPTRB_K_W;
		if (key == KEY_S)
			lcu_k ^= SMPTRB_K_S;
		if (key == KEY_A)
			lcu_k ^= SMPTRB_K_A;
		if (key == KEY_D)
			lcu_k ^= SMPTRB_K_D;
		if (key == KEY_SPACE)
			lcu_k ^= SMPTRB_K_JUMP;
		if (key == KEY_LEFTCTRL)
			lcu_k ^= SMPTRB_K_DIG;
		//KEY_LEFTSHIFT
	}
	else
	{
		if (key == KEY_W)
			lcu_k ^= SMPTRB_K_W;
		if (key == KEY_S)
			lcu_k ^= SMPTRB_K_S;
		if (key == KEY_A)
			lcu_k ^= SMPTRB_K_A;
		if (key == KEY_D)
			lcu_k ^= SMPTRB_K_D;
		if (key == KEY_SPACE)
			lcu_k ^= SMPTRB_K_JUMP;
		if (key == KEY_LEFTCTRL)
			lcu_k ^= SMPTRB_K_DIG;
	}
}

static void wl_keyboard_listener_enter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys)
{
	// SMPT_DBmN2L("wl_keyboard_listener_enter")
}

static void wl_keyboard_listener_leave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface)
{
	// SMPT_DBmN2L("wl_keyboard_listener_leave")
}

static void wl_keyboard_listener_modifiers(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
{
	// SMPT_DBmN2L("wl_keyboard_listener_modifiers group %d", group)
}

static void wl_keyboard_listener_repeat_info(void *data, struct wl_keyboard *wl_keyboard, int32_t rate, int32_t delay)
{
	// SMPT_DBmN2L("wl_keyboard_listener_repeat_info")
}

struct wl_keyboard_listener smpt_sf_wl_ces_kbSlistener =
{
	.keymap = wl_keyboard_listener_keymap,
	.enter = wl_keyboard_listener_enter,
	.leave = wl_keyboard_listener_leave,
	.key = wl_keyboard_listener_key,
	.modifiers = wl_keyboard_listener_modifiers,
	.repeat_info = wl_keyboard_listener_repeat_info
};

void smpt_sf_wl_ces_kbMfree()
{
	wl_keyboard_destroy(smpt_sf_wl_ces_kbP);
}
