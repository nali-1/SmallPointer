#ifndef SMPT_RD_VKhSMP
	#define SMPT_RD_VKhSMP

	#define SMPT_RD_VK_SMPmMAKE(Udevice, Pvksemaphore) \
		SMPT_DBmR2L \
		( \
			"vkCreateSemaphore %d", \
			vkCreateSemaphore \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkSemaphoreCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, \
					.pNext = NULL, \
					.flags = 0 \
				}, \
				NULL, \
				Pvksemaphore \
			) \
		)
#endif
