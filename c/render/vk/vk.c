void smpt_rd_vkMset()
{
	//SMPT_DBmN2L("smpt_rd_vkMset")
	smpt_rd_vkq_psc_itMset();
	#if SMPT_CM_VK_DEBUG_UTILS || SMPT_CM_VK_DEBUG_REPORT
		smpt_rd_vk_dbMset();
	#endif
	smpt_rd_vkq_pscMset();
	#ifdef SMPT_CM_MAIN
		smpt_rd_vk_sfMmake();
	#endif
	smpt_rd_vkqMset();

	#ifdef SMPT_CM_MAIN
		smpt_rd_vk_swcMset();
	#endif

	smpt_rd_vk_cmpMset();
	smpt_rd_vk_cm_bfMset();

	smpt_rd_vkw_dstspMset();
	smpt_rd_vkw_dsts_loMset();

	while (!(smpt_sfUstate & SMPT_SFuS_RAW))
		SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))

	smptr_ce_mdMvk();
	smptr_ceaMvk();

	#ifdef SMPT_CM_MAIN
		smpt_rd_vk_cmdMset();
	#endif
}

void smpt_rd_vkMfree()
{
	smpt_rd_vkw_dsts_loMfree();
	smpt_rd_vkw_dstspMfree();

	smpt_rd_vk_cm_bfMfree();
	smpt_rd_vk_cmpMfree();

	#ifdef SMPT_CM_MAIN
		smpt_rd_vk_swcMfree();
	#endif

	smpt_rd_vkqMfree();
	#ifdef SMPT_CM_MAIN
		smpt_rd_vk_sfMfree();
	#endif
	smpt_rd_vkq_pscMfree();
	#if SMPT_CM_VK_DEBUG_UTILS || SMPT_CM_VK_DEBUG_REPORT
		smpt_rd_vk_dbMfree();
	#endif
	smpt_rd_vkq_psc_itMfree();
}
