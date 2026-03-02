void smpt_rd_vk_smpMmake(uint8_t Udevice, VkSemaphore* Pvksemaphore)
{
	SMPT_DBmR2L
	(
		"vkCreateSemaphore %d",
		vkCreateSemaphore
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkSemaphoreCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
				.pNext = NULL,
				.flags = 0
			},
			NULL,
			Pvksemaphore
		)
	)
}
