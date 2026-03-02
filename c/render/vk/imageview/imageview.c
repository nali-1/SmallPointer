void smpt_rd_vk_imvMmake(uint8_t Udevice, VkImage Vvkimage, VkFormat Vvkformat, VkImageAspectFlags Vvkimageaspectflags, uint8_t Umipmap, VkImageView *Pvkimageview)
{
	SMPT_DBmR2L
	(
		"vkCreateImageView %d",
		vkCreateImageView
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkImageViewCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
				.image = Vvkimage,
				.viewType = VK_IMAGE_VIEW_TYPE_2D,
				.format = Vvkformat,
				.subresourceRange.aspectMask = Vvkimageaspectflags,
				.subresourceRange.baseMipLevel = 0,
				.subresourceRange.levelCount = Umipmap,
				.subresourceRange.baseArrayLayer = 0,
				.subresourceRange.layerCount = 1,
				.components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
				.components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
				.components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
				.components.a = VK_COMPONENT_SWIZZLE_IDENTITY,
				.flags = 0,
				.pNext = NULL
			},
			NULL,
			Pvkimageview
		)
	)
}
