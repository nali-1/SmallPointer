#ifndef SMPT_RD_VKhIMV
	#define SMPT_RD_VKhIMV

	//mipmap 1
	#define SMPT_RD_VK_IMVmMAKE(Udevice, Vvkimage, Vvkformat, Vvkimageaspectflags, Umipmap, Pvkimageview) \
		SMPT_DBmR2L \
		( \
			"vkCreateImageView %d", \
			vkCreateImageView \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkImageViewCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, \
					.image = Vvkimage, \
					.viewType = VK_IMAGE_VIEW_TYPE_2D, \
					.format = Vvkformat, \
					.subresourceRange.aspectMask = Vvkimageaspectflags, \
					.subresourceRange.baseMipLevel = 0, \
					.subresourceRange.levelCount = Umipmap, \
					.subresourceRange.baseArrayLayer = 0, \
					.subresourceRange.layerCount = 1, \
					.components.r = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.components.g = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.components.b = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.components.a = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				Pvkimageview \
			) \
		)
#endif
