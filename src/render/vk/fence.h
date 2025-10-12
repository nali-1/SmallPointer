#ifndef SMPT_RD_VKhF
	#define SMPT_RD_VKhF

	#define SMPT_RD_VKFmMAKE(Udevice, Pvkfence) \
		SMPT_DBmR2L \
		( \
			"vkCreateFence %d", \
			vkCreateFence \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkFenceCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, \
					.flags = VK_FENCE_CREATE_SIGNALED_BIT, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				Pvkfence \
			) \
		)
#endif
