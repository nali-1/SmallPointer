#ifndef SMPT_RD_VKhSWC
	#define SMPT_RD_VKhSWC

	extern VkSwapchainKHR smpt_rd_vk_swcVkhr;
	extern VkExtent2D smpt_rd_vk_swcVet2d;
	extern VkRenderPass smpt_rd_vk_swcVrdp;

	extern VkImage *smpt_rd_vk_swcPim;
	extern VkImageView *smpt_rd_vk_swcPimv;
	extern VkFramebuffer *smpt_rd_vk_swcPfbf;

	extern uint8_t smpt_rd_vk_swcUimage;
	extern uint8_t smpt_rd_vk_swcUframe;
	extern uint8_t smpt_rd_vk_swcUframe_buffer;

	void smpt_rd_vk_swcMset();
	void smpt_rd_vk_swcMfree();
#endif
