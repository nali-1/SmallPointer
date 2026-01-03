VkDescriptorSetLayout smpt_rd_vkw_dsts_loP[2];

static void Mgp()
{
	const uint8_t Udevice = SMPT_RD_VKQuGP;
	const uint8_t Ui = SMPT_RD_VKW_DSTSuGP;
	SMPT_DBmR2L
	(
		"vkCreateDescriptorSetLayout %d",
		vkCreateDescriptorSetLayout
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkDescriptorSetLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
				.bindingCount = SMPT_RD_VKW_DSTS_LOlGP,
				.pBindings = (VkDescriptorSetLayoutBinding[])
				{
					{
						.binding = 0,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = NULL,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 1,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = NULL,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 2,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = NULL,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 3,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = NULL,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 4,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = NULL,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					}
				},
				.flags = 0,
				.pNext = NULL
			},
			NULL,
			smpt_rd_vkw_dsts_loP + Ui
		)
	)
}

static void Mcp()
{
	const uint8_t Udevice = smpt_rd_vkqUdv_cp;
	const uint8_t Ui = SMPT_RD_VKW_DSTSuCP;
	SMPT_DBmR2L
	(
		"vkCreateDescriptorSetLayout %d",
		vkCreateDescriptorSetLayout
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkDescriptorSetLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
				.bindingCount = SMPT_RD_VKW_DSTS_LOlCP,
				.pBindings = (VkDescriptorSetLayoutBinding[])
				{
					{
						.binding = 0,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
						.pImmutableSamplers = NULL,
						.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT
					}
				},
				.flags = 0,
				.pNext = NULL
			},
			NULL,
			smpt_rd_vkw_dsts_loP + Ui
		)
	)
}

void smpt_rd_vkw_dsts_loMset()
{
	Mgp();
	Mcp();
}

void smpt_rd_vkw_dsts_loMfree()
{
	vkDestroyDescriptorSetLayout(smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice, smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuGP], NULL);
	vkDestroyDescriptorSetLayout(smpt_rd_vkqPinfo[smpt_rd_vkqUdv_cp].Vvkdevice, smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuCP], NULL);
}
