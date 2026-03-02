void smpt_rd_vkw_dstsMmake(uint8_t Udevice, uint8_t Up, VkDescriptorSetLayout *Pvkdescriptorsetlayout, uint8_t Lvkdescriptorset, VkDescriptorSet *Pvkdescriptorset)
{
	SMPT_DBmR2L
	(
		"vkAllocateDescriptorSets %d",
		vkAllocateDescriptorSets
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			&(VkDescriptorSetAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
				.descriptorPool = smpt_rd_vkw_dstspP[Up],
				.descriptorSetCount = Lvkdescriptorset,
				.pSetLayouts = Pvkdescriptorsetlayout,
				.pNext = NULL
			},
			Pvkdescriptorset
		)
	)
}
