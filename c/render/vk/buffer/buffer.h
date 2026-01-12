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
					.pQueueFamilyIndices = NULL, \
					.flags = 0, \
					.pNext = NULL \
				}, \
				NULL, \
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
					.pNext = NULL \
				}, \
				NULL, \
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
		Pvkbuffer_free = malloc(sizeof(VkBuffer)); \
		Pvkdevicememory_free = malloc(sizeof(VkDeviceMemory)); \
		Pfree = malloc(sizeof(uint8_t));
	#define SMPT_RD_VK_BFmFREE_HELP(Pvkbuffer, Pvkdevicememory, L) \
		Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * (Lfree + Ue - Us) * L); \
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * (Lfree + Ue - Us) * L); \
		Pfree = realloc(Pfree, sizeof(uint8_t) * (Lfree + Ue - Us)); \
		for (uint32_t l0 = Lfree; l0 < Lfree + Ue - Us; ++l0) \
		{ \
			Pfree[l0] = 1 << smpt_rd_vk_swcUimage; \
		} \
		memcpy(Pvkbuffer_free + Lfree * L, Pvkbuffer + Us * L, sizeof(VkBuffer) * (Ue - Us) * L); \
		memcpy(Pvkdevicememory_free + Lfree * L, Pvkdevicememory + Us * L, sizeof(VkDeviceMemory) * (Ue - Us) * L); \
		Lfree += Ue - Us;
	#define SMPT_RD_VK_BFmFREE_ABLE(ls) !(Pfree[ls] = Pfree[ls] >> 1)
	#define SMPT_RD_VK_BFmFREE_DO(Vvkdevice, ls, ln, L) \
		for (uint8_t ln = 0; ln < L; ++ln) \
		{ \
			vkUnmapMemory(Vvkdevice, Pvkdevicememory_free[ls * L + ln]); \
			vkDestroyBuffer(Vvkdevice, Pvkbuffer_free[ls * L + ln], NULL); \
			vkFreeMemory(Vvkdevice, Pvkdevicememory_free[ls * L + ln], NULL); \
		}
	#define SMPT_RD_VK_BFmFREE_RE(L) \
		Pvkbuffer_free = realloc(Pvkbuffer_free, Lfree ? sizeof(VkBuffer) * Lfree * L : sizeof(VkBuffer)); \
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, Lfree ? sizeof(VkDeviceMemory) * Lfree * L : sizeof(VkDeviceMemory)); \
		Pfree = realloc(Pfree, Lfree ? sizeof(uint8_t) * Lfree : sizeof(uint8_t));
	#define SMPT_RD_VK_BFmFREE_CLEAN \
		free(Pfree); \
		free(Pvkdevicememory_free); \
		free(Pvkbuffer_free);
#endif
