VkDescriptorPool smpt_rd_vkw_dstspP[2];

static void Mgp()
{
	const uint8_t Udevice = SMPT_RD_VKQuGP;
	const SMPTRtMI Umax_set = SMPTRlMI;
	const uint32_t Udescriptor_count = SMPTRlMI * SMPT_RD_VKW_DSTS_LOlGP;
	const uint8_t Ui = SMPT_RD_VKW_DSTSuGP;
	SMPT_DBmR2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = 1,
				.pPoolSizes = &(VkDescriptorPoolSize)
				{
					.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
					.descriptorCount = Udescriptor_count
				},
				.maxSets = Umax_set,
				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = NULL
			},
			NULL,
			smpt_rd_vkw_dstspP + Ui
		)
	)
}

static void Mcp()
{
	const uint8_t Udevice = smpt_rd_vkqUdv_cp;
	const SMPTRtA Umax_set = SMPTRlA;
	const uint32_t Udescriptor_count = SMPTRlA * SMPT_RD_VKW_DSTS_LOlCP;
	const uint8_t Ui = SMPT_RD_VKW_DSTSuCP;
	SMPT_DBmR2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = 1,
				.pPoolSizes = &(VkDescriptorPoolSize)
				{
					.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
					.descriptorCount = Udescriptor_count
				},
				.maxSets = Umax_set,
				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = NULL
			},
			NULL,
			smpt_rd_vkw_dstspP + Ui
		)
	)
}

void smpt_rd_vkw_dstspMset()
{
	Mgp();
	Mcp();
}

void smpt_rd_vkw_dstspMfree()
{
	vkDestroyDescriptorPool(smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuGP], NULL);
	vkDestroyDescriptorPool(smpt_rd_vkqPinfo[smpt_rd_vkqUdv_cp].Vvkdevice, smpt_rd_vkw_dstspP[SMPT_RD_VKW_DSTSuCP], NULL);
}
