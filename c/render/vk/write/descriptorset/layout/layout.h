#ifndef SMPT_RD_VKW_DSTShLO
	#define SMPT_RD_VKW_DSTShLO

	#define SMPT_RD_VKW_DSTS_LOlGP 5
	#define SMPT_RD_VKW_DSTS_LOlCP 1

	extern VkDescriptorSetLayout smpt_rd_vkw_dsts_loP[2];

	void smpt_rd_vkw_dsts_loMset();
	void smpt_rd_vkw_dsts_loMfree();
#endif
