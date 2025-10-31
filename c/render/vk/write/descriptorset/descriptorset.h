#ifndef SMPT_RD_VKWhDSTS
	#define SMPT_RD_VKWhDSTS

	#define SMPT_RD_VKW_DSTSuGP 0
	#define SMPT_RD_VKW_DSTSuCP 1

	#define SMPT_RD_VKW_DSTSmMAKE(Udevice, Up, Pvkdescriptorsetlayout, Lvkdescriptorset, Pvkdescriptorset) \
		SMPT_DBmR2L \
		( \
			"vkAllocateDescriptorSets %d", \
			vkAllocateDescriptorSets \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkDescriptorSetAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, \
					.descriptorPool = smpt_rd_vkw_dstspP[Up], \
					.descriptorSetCount = Lvkdescriptorset, \
					.pSetLayouts = Pvkdescriptorsetlayout, \
					.pNext = VK_NULL_HANDLE \
				}, \
				Pvkdescriptorset \
			) \
		)
#endif
