void smpt_rd_vk_fbfMmake(uint8_t Udevice, VkImageView *Pvkimageview, uint8_t Lvkimageview, VkRenderPass Vvkrenderpass, VkFramebuffer *Pvkframebuffer)
{
	SMPT_DBmR2L
	(
		"vkCreateFramebuffer %d",
		vkCreateFramebuffer
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkFramebufferCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				.renderPass = Vvkrenderpass,
				.attachmentCount = Lvkimageview,
				.pAttachments = Pvkimageview,
				.width = smpt_rd_vk_swcVet2d.width,
				.height = smpt_rd_vk_swcVet2d.height,
				.layers = 1,
				.flags = 0,
				.pNext = NULL
			},
			NULL,
			Pvkframebuffer
		)
	)
}
