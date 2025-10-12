#ifndef SMPT_RD_VKhBF
	#define SMPT_RD_VKhBF

	uint32_t smpt_rd_vk_bfMtype(uint32_t Udevice, uint32_t Utypefilter, VkMemoryPropertyFlags Uvkmemorypropertyflags);

	//.i VkMemoryRequirements Vvkmemoryrequirements
	#define SMPT_RD_VK_BFmMAKE(Udevice, Uvkdevicesize, Uvkbufferusageflags, Uvkmemorypropertyflags, Vvkbuffer, Vvkdevicememory, Vvkmemoryrequirements) \
		SMPT_DBmR2L \
		( \
			"vkCreateBuffer %d", \
			vkCreateBuffer \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkBufferCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, \
					.size = Uvkdevicesize, \
					.sharingMode = VK_SHARING_MODE_EXCLUSIVE, \
					.usage = Uvkbufferusageflags, \
					.queueFamilyIndexCount = 0, \
					.pQueueFamilyIndices = VK_NULL_HANDLE, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&Vvkbuffer \
			) \
		) \
		vkGetBufferMemoryRequirements(smpt_rd_vkqPinfo[Udevice].Vvkdevice, Vvkbuffer, &Vvkmemoryrequirements); \
		SMPT_DBmR2L \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.memoryTypeIndex = smpt_rd_vk_bfMtype(Udevice, Vvkmemoryrequirements.memoryTypeBits, Uvkmemorypropertyflags), \
					.allocationSize = Vvkmemoryrequirements.size, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&Vvkdevicememory \
			) \
		) \
		SMPT_DBmR2L("vkBindBufferMemory %d", vkBindBufferMemory(smpt_rd_vkqPinfo[Udevice].Vvkdevice, Vvkbuffer, Vvkdevicememory, 0))

	//void *Pdata
	#define SMPT_RD_VK_BFmMAP(Udevice, Uvkdevicesize, Pbuffer_data, Pvkdevicememory, Pdata) \
		SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkqPinfo[Udevice].Vvkdevice, *Pvkdevicememory, 0, Uvkdevicesize, 0, &Pdata)) \
		memcpy(Pdata, Pbuffer_data, Uvkdevicesize); \
		vkUnmapMemory(smpt_rd_vkqPinfo[Udevice].Vvkdevice, *Pvkdevicememory);

	#define SMPT_RD_VK_BFmFREE_F \
		static VkBuffer *Pvkbuffer_free; \
		static VkDeviceMemory *Pvkdevicememory_free; \
		static uint8_t *Pfree; \
		static uint32_t Lfree = 0;
	#define SMPT_RD_VK_BFmFREE_SET \
		Pvkbuffer_free = malloc(0); \
		Pvkdevicememory_free = malloc(0); \
		Pfree = malloc(0);
	#define SMPT_RD_VK_BFmFREE_HELP(Pvkbuffer, Pvkdevicememory) \
		Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage); \
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage); \
		Pfree = realloc(Pfree, sizeof(uint8_t) * (Lfree + Ue - Us)); \
		for (uint32_t l0 = Lfree; l0 < Lfree + Ue - Us; ++l0) \
		{ \
			Pfree[l0] = 1 << smpt_rd_vk_swcUimage; \
		} \
		memcpy(Pvkbuffer_free + Lfree * smpt_rd_vk_swcUimage, Pvkbuffer + Us * smpt_rd_vk_swcUimage, sizeof(VkBuffer) * (Ue - Us) * smpt_rd_vk_swcUimage); \
		memcpy(Pvkdevicememory_free + Lfree * smpt_rd_vk_swcUimage, Pvkdevicememory + Us * smpt_rd_vk_swcUimage, sizeof(VkDeviceMemory) * (Ue - Us) * smpt_rd_vk_swcUimage); \
		Lfree += Ue - Us;
	#define SMPT_RD_VK_BFmFREE_ABLE(ls) !(Pfree[ls] = Pfree[ls] >> 1)
	#define SMPT_RD_VK_BFmFREE_DO(Vvkdevice, ls, ln) \
		for (uint8_t ln = 0; ln < smpt_rd_vk_swcUimage; ++ln) \
		{ \
			vkUnmapMemory(Vvkdevice, Pvkdevicememory_free[ls * smpt_rd_vk_swcUimage + ln]); \
			vkDestroyBuffer(Vvkdevice, Pvkbuffer_free[ls * smpt_rd_vk_swcUimage + ln], VK_NULL_HANDLE); \
			vkFreeMemory(Vvkdevice, Pvkdevicememory_free[ls * smpt_rd_vk_swcUimage + ln], VK_NULL_HANDLE); \
		}
	#define SMPT_RD_VK_BFmFREE_RE \
		Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * Lfree * smpt_rd_vk_swcUimage); \
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * Lfree * smpt_rd_vk_swcUimage); \
		Pfree = realloc(Pfree, sizeof(uint8_t) * Lfree);
	#define SMPT_RD_VK_BFmFREE_CLEAN \
		free(Pfree); \
		free(Pvkdevicememory_free); \
		free(Pvkbuffer_free);
#endif
