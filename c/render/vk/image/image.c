void smpt_rd_vk_imMmake(uint8_t Udevice, VkFormat Vvkformat, VkExtent3D Vvkextent3d, uint8_t Umipmap, VkImageTiling Vvkimagetiling, VkImageUsageFlags Vvkimageusageflags, VkImageLayout Vvkimagelayout, VkSampleCountFlagBits Vvksamplecountflagbits, VkImage *Pvkimage)
{
	SMPT_DBmR2L
	(
		"vkCreateImage %d",
		vkCreateImage
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkImageCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
				.imageType = VK_IMAGE_TYPE_2D,
				.format = Vvkformat,
				.extent = Vvkextent3d,
				.mipLevels = Umipmap,
				.arrayLayers = 1,
				.samples = Vvksamplecountflagbits,
				.tiling = Vvkimagetiling,
				.usage = Vvkimageusageflags,
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
				.initialLayout = Vvkimagelayout,
				.queueFamilyIndexCount = 0,
				.pQueueFamilyIndices = NULL,
				.flags = 0,
				.pNext = NULL
			},
			NULL,
			Pvkimage
		)
	)
}

void smpt_rd_vk_imMgen(uint8_t Udevice, VkImage Vvkimage, VkMemoryPropertyFlags Vvkmemorypropertyflags, VkDeviceMemory *Pvkdevicememory, VkMemoryRequirements Vvkmemoryrequirements)
{
	vkGetImageMemoryRequirements(smpt_rd_vkqPinfo[Udevice].Vvkdevice, Vvkimage, &Vvkmemoryrequirements);
	SMPT_DBmR2L
	(
		"vkAllocateMemory %d",
		vkAllocateMemory
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkMemoryAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.allocationSize = Vvkmemoryrequirements.size,
				.memoryTypeIndex = smpt_rd_vk_bfMtype(Udevice, Vvkmemoryrequirements.memoryTypeBits, Vvkmemorypropertyflags),
				.pNext = NULL
			},
			NULL,
			Pvkdevicememory
		)
	)
	SMPT_DBmR2L("vkBindImageMemory %d", vkBindImageMemory(smpt_rd_vkqPinfo[Udevice].Vvkdevice, Vvkimage, *Pvkdevicememory, 0))
}
