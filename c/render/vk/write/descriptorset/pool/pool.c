VkDescriptorPool smpt_rd_vkw_dstspP[2];

#define SMPT_RD_VKW_DSTSPm(Udevice, Umax_set, Udescriptor_count, Ui) \
	SMPT_DBmR2L \
	( \
		"vkCreateDescriptorPool %d", \
		vkCreateDescriptorPool \
		( \
			smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
			&(VkDescriptorPoolCreateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, \
				.poolSizeCount = 1, \
				.pPoolSizes = &(VkDescriptorPoolSize) \
				{ \
					.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
					.descriptorCount = Udescriptor_count \
				}, \
				.maxSets = Umax_set, \
				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, \
				.pNext = VK_NULL_HANDLE \
			}, \
			VK_NULL_HANDLE, \
			smpt_rd_vkw_dstspP + Ui \
		) \
	)

void smpt_rd_vkw_dstspMset()
{
	SMPT_RD_VKW_DSTSPm(SMPT_RD_VKQuGP, SMPTRlMI, SMPTRlMI * SMPT_RD_VKW_DSTS_LOlMAIN, SMPT_RD_VKW_DSTSuGP)
	SMPT_RD_VKW_DSTSPm(smpt_rd_vkqUdv_cp, 1, 1, SMPT_RD_VKW_DSTSuCP)
}

void smpt_rd_vkw_dstspMfree()
{
	vkDestroyDescriptorPool(smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], VK_NULL_HANDLE);
	vkDestroyDescriptorPool(smpt_rd_vkqPinfo[smpt_rd_vkqUdv_cp].Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuCP], VK_NULL_HANDLE);
}
