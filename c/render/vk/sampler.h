#ifndef SMPT_RD_VKhSP
	#define SMPT_RD_VKhSP

	//.i mipmap 0
	#define SMPT_RD_VK_SPmMAKE(Udevice, Umipmap, Uline, Pvksampler) \
		VkSamplerCreateInfo vksamplercreateinfo = \
		{ \
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO, \
			.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT, \
			.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT, \
			.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT, \
			.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK, \
			.unnormalizedCoordinates = VK_FALSE, \
			.compareEnable = VK_FALSE, \
			.compareOp = VK_COMPARE_OP_ALWAYS, \
			.anisotropyEnable = smpt_rd_vkFmax_sampler_anisotropy == 0 ? VK_FALSE : VK_TRUE, \
			.maxAnisotropy = smpt_rd_vkFmax_sampler_anisotropy, \
			.mipLodBias = 0, \
			.minLod = 0, \
			.maxLod = Umipmap, \
			.flags = 0, \
			.pNext = NULL \
		}; \
		if (Uline) \
		{ \
			vksamplercreateinfo.magFilter = VK_FILTER_LINEAR; \
			vksamplercreateinfo.minFilter = VK_FILTER_LINEAR; \
			vksamplercreateinfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR; \
		} \
		else \
		{ \
			vksamplercreateinfo.magFilter = VK_FILTER_NEAREST; \
			vksamplercreateinfo.minFilter = VK_FILTER_NEAREST; \
			vksamplercreateinfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST; \
		} \
		SMPT_DBmR2L("vkCreateSampler %d", vkCreateSampler(smpt_rd_vkqPinfo[Udevice].Vvkdevice, &vksamplercreateinfo, NULL, Pvksampler))

#endif
