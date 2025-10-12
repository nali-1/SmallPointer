struct wl_pointer *smpt_sf_wl_cesPtP;

static void wl_pointer_listener_enter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	wl_pointer_set_cursor(smpt_sf_wl_cesPtP, serial, NULL, 0, 0);
}

static void wl_pointer_listener_leave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
}

static float x = 0, y = 0;
static void wl_pointer_listener_motion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	float
		l_x = wl_fixed_to_double(surface_x),
		l_y = wl_fixed_to_double(surface_y);
	mtx_lock(lb_mtx_t_p);
	lcu_xy_p[0] = l_x - x;
	lcu_xy_p[1] = l_y - y;
	mtx_unlock(lb_mtx_t_p);
	x = l_x;
	y = l_y;
}

static void wl_pointer_listener_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	switch (button)
	{
		case BTN_LEFT:
			break;
		case BTN_RIGHT:
			break;
		case BTN_MIDDLE:
			mtx_lock(lb_mtx_t_p);
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				lcu_k |= SMPTRB_K_REROTATE;
			else
				lcu_k &= 0xFFu - SMPTRB_K_REROTATE;
			mtx_unlock(lb_mtx_t_p);
	}
}

static void wl_pointer_listener_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
	float scroll = wl_fixed_to_double(value);
	mtx_lock(lb_mtx_t_p);
	lcu_xy_p[0] = axis == WL_POINTER_AXIS_VERTICAL_SCROLL ? scroll : 0;
	lcu_xy_p[1] = axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL ? scroll : 0;
	mtx_unlock(lb_mtx_t_p);
}

struct wl_pointer_listener smpt_sf_wl_cesPtSlistener =
{
	.enter = wl_pointer_listener_enter,
	.leave = wl_pointer_listener_leave,
	.motion = wl_pointer_listener_motion,
	.button = wl_pointer_listener_button,
	.axis = wl_pointer_listener_axis,
};

void smpt_sf_wl_cesPtMfree()
{
	wl_pointer_destroy(smpt_sf_wl_cesPtP);
}
