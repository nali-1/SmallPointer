struct zwp_pointer_constraints_v1 *smpt_sf_wl_ce_zwp_ptPcst;

void smpt_sf_wl_ce_zwp_ptMset()
{
	if (smpt_sf_wl_ce_zwplPpt)
	{
		zwp_locked_pointer_v1_destroy(smpt_sf_wl_ce_zwplPpt);
		smpt_sf_wl_ce_zwplPpt = NULL;

		zwp_relative_pointer_v1_destroy(smpt_sf_wl_ce_zwp_rltPpt);
		smpt_sf_wl_ce_zwp_rltPpt = NULL;
	}
	else
	{
		SMPT_DBmR2L("zwp_pointer_constraints_v1_lock_pointer %p", smpt_sf_wl_ce_zwplPpt = zwp_pointer_constraints_v1_lock_pointer(smpt_sf_wl_ce_zwp_ptPcst, smpt_sf_wl_cePsf, smpt_sf_wl_cesPtP, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT))
		SMPT_DBmR2L("zwp_locked_pointer_v1_add_listener %d", zwp_locked_pointer_v1_add_listener(smpt_sf_wl_ce_zwplPpt, &smpt_sf_wl_ce_zwplSpt_listener, NULL))

		SMPT_DBmR2L("zwp_relative_pointer_manager_v1_get_relative_pointer %p", smpt_sf_wl_ce_zwp_rltPpt = zwp_relative_pointer_manager_v1_get_relative_pointer(smpt_sf_wl_ce_zwp_rltPpt_mng, smpt_sf_wl_cesPtP))
		SMPT_DBmR2L("zwp_relative_pointer_v1_add_listener %d", zwp_relative_pointer_v1_add_listener(smpt_sf_wl_ce_zwp_rltPpt, &smpt_sf_wl_ce_zwp_rltSpt_listener, NULL))
	}
}

void smpt_sf_wl_ce_zwp_ptMfree()
{
	zwp_pointer_constraints_v1_destroy(smpt_sf_wl_ce_zwp_ptPcst);
}
