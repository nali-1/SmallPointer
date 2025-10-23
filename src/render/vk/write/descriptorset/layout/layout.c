VkDescriptorSetLayout smpt_rd_vkw_dsts_loP[2];

#define SMPT_RD_VKW_DSTS_LOm(Udevice, Ui) \
	SMPT_DBmR2L \
	( \
		"vkCreateDescriptorSetLayout %d", \
		vkCreateDescriptorSetLayout \
		( \
			smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
			&(VkDescriptorSetLayoutCreateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, \
				.bindingCount = SMPT_RD_VKW_DSTS_LOlMAIN, \
				.pBindings = (VkDescriptorSetLayoutBinding[]) \
				{ \
					{ \
						.binding = 0, \
						.descriptorCount = 1, \
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
						.pImmutableSamplers = VK_NULL_HANDLE, \
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
					}, \
					{ \
						.binding = 1, \
						.descriptorCount = 1, \
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
						.pImmutableSamplers = VK_NULL_HANDLE, \
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
					}, \
					{ \
						.binding = 2, \
						.descriptorCount = 1, \
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
						.pImmutableSamplers = VK_NULL_HANDLE, \
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
					}, \
					{ \
						.binding = 3, \
						.descriptorCount = 1, \
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
						.pImmutableSamplers = VK_NULL_HANDLE, \
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
					}, \
					{ \
						.binding = 4, \
						.descriptorCount = 1, \
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
						.pImmutableSamplers = VK_NULL_HANDLE, \
						.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT \
					} \
				}, \
				.flags = 0, \
				.pNext = VK_NULL_HANDLE \
			}, \
			VK_NULL_HANDLE, \
			smpt_rd_vkw_dsts_loP + Ui \
		) \
	)

void smpt_rd_vkw_dsts_loMset()
{
	SMPT_RD_VKW_DSTS_LOm(SMPT_RD_VKQuGP, SMPT_RD_VKW_DSTSuGP)
	SMPT_RD_VKW_DSTS_LOm(smpt_rd_vkqUdv_cp, SMPT_RD_VKW_DSTSuCP)
}

void smpt_rd_vkw_dsts_loMfree()
{
	vkDestroyDescriptorSetLayout(smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice, smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuGP], VK_NULL_HANDLE);
	vkDestroyDescriptorSetLayout(smpt_rd_vkqPinfo[smpt_rd_vkqUdv_cp].Vvkdevice, smpt_rd_vkw_dsts_loP[SMPT_RD_VKW_DSTSuCP], VK_NULL_HANDLE);
}
