void smpt_rd_vkfMmake(uint8_t Udevice, VkFence *Pvkfence)
{
	SMPT_DBmR2L
	(
		"vkCreateFence %d",
		vkCreateFence
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkFenceCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
				.flags = VK_FENCE_CREATE_SIGNALED_BIT,
				.pNext = NULL
			},
			NULL,
			Pvkfence
		)
	)
}
