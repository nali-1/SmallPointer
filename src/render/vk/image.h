#ifndef SMPT_RD_VKhIM
	#define SMPT_RD_VKhIM

	/*mipmap 1
	vksamplecountflagbits VK_SAMPLE_COUNT_1_BIT
	vkimagetiling VK_IMAGE_TILING_OPTIMAL
	vkimagelayout VK_IMAGE_LAYOUT_UNDEFINED*/
	#define SMPT_RD_VK_IMmMAKE(Udevice, Vvkformat, Vvkextent3d, Umipmap, Vvkimagetiling, Vvkimageusageflags, Vvkimagelayout, Vvksamplecountflagbits, Pvkimage) \
		SMPT_DBmR2L \
		( \
			"vkCreateImage %d", \
			vkCreateImage \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkImageCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, \
					.imageType = VK_IMAGE_TYPE_2D, \
					.format = Vvkformat, \
					.extent = Vvkextent3d, \
					.mipLevels = Umipmap, \
					.arrayLayers = 1, \
					.samples = Vvksamplecountflagbits, \
					.tiling = Vvkimagetiling, \
					.usage = Vvkimageusageflags, \
					.sharingMode = VK_SHARING_MODE_EXCLUSIVE, \
					.initialLayout = Vvkimagelayout, \
					.queueFamilyIndexCount = 0, \
					.pQueueFamilyIndices = VK_NULL_HANDLE, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				Pvkimage \
			) \
		)

	//vkmemoryrequirements f
	#define SMPT_RD_VK_IMmGEN(Udevice, Vvkimage, Vvkmemorypropertyflags, Pvkdevicememory, Vvkmemoryrequirements) \
		vkGetImageMemoryRequirements(smpt_rd_vkqPinfo[Udevice].Vvkdevice, Vvkimage, &Vvkmemoryrequirements); \
		SMPT_DBmR2L \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.allocationSize = Vvkmemoryrequirements.size, \
					.memoryTypeIndex = smpt_rd_vk_bfMtype(Udevice, Vvkmemoryrequirements.memoryTypeBits, Vvkmemorypropertyflags), \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				Pvkdevicememory \
			) \
		) \
		SMPT_DBmR2L("vkBindImageMemory %d", vkBindImageMemory(smpt_rd_vkqPinfo[Udevice].Vvkdevice, Vvkimage, *Pvkdevicememory, 0))
#endif
