struct zwp_relative_pointer_manager_v1 *smpt_sf_wl_ce_zwp_rltPpt_mng;
struct zwp_relative_pointer_v1 *smpt_sf_wl_ce_zwp_rltPpt = NULL;

static void zwp_relative_pointer_v1_listener_relative_motion(void *data, struct zwp_relative_pointer_v1 *zwp_relative_pointer_v1, uint32_t utime_hi, uint32_t utime_lo, wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t dx_unaccel, wl_fixed_t dy_unaccel)
{
	SMPT_DBmN2L("x %f", wl_fixed_to_double(dx))
	SMPT_DBmN2L("y %f", wl_fixed_to_double(dy))
}

struct zwp_relative_pointer_v1_listener smpt_sf_wl_ce_zwp_rltSpt_listener =
{
	.relative_motion = zwp_relative_pointer_v1_listener_relative_motion
};

void smpt_sf_wl_ce_zwp_rltMfree()
{
	if (smpt_sf_wl_ce_zwp_rltPpt)
	{
		zwp_relative_pointer_v1_destroy(smpt_sf_wl_ce_zwp_rltPpt);
		smpt_sf_wl_ce_zwp_rltPpt = NULL;
	}

	zwp_relative_pointer_manager_v1_destroy(smpt_sf_wl_ce_zwp_rltPpt_mng);
}
