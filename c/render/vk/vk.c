void smpt_rd_vkMset()
{
	//SMPT_DBmN2L("smpt_rd_vkMset")
	smpt_rd_vkq_psc_itMset();
	#if SMPT_CM_VK_DEBUG_UTILS || SMPT_CM_VK_DEBUG_REPORT
		smpt_rd_vk_dbMset();
	#endif
	smpt_rd_vkq_pscMset();
	smpt_rd_vk_sfMmake();
	smpt_rd_vkqMset();

	smpt_rd_vk_swcMset();

	smpt_rd_vk_cmpMset();
	smpt_rd_vk_cm_bfMset();

	smpt_rd_vkw_dstspMset();
	smpt_rd_vkw_dsts_loMset();

	while (!(smpt_sfUstate & SMPT_SFuS_RAW))
		SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))

	smptr_ce_mdMvk();
	smptr_ceaMvk();

	smpt_rd_vk_cmdMset();
}

void smpt_rd_vkMfree()
{
	smpt_rd_vkw_dsts_loMfree();
	smpt_rd_vkw_dstspMfree();

	smpt_rd_vk_cm_bfMfree();
	smpt_rd_vk_cmpMfree();

	smpt_rd_vk_swcMfree();

	smpt_rd_vkqMfree();
	smpt_rd_vk_sfMfree();
	smpt_rd_vkq_pscMfree();
	#if SMPT_CM_VK_DEBUG_UTILS || SMPT_CM_VK_DEBUG_REPORT
		smpt_rd_vk_dbMfree();
	#endif
	smpt_rd_vkq_psc_itMfree();
}
