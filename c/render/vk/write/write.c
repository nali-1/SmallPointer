void smpt_rd_vkwMdsts(uint8_t Ubind, VkDescriptorImageInfo* Pvkdescriptorimageinfo, VkDescriptorBufferInfo *Pvkdescriptorbufferinfo, VkDescriptorType Vvkdescriptortype, VkDescriptorSet Vvkdescriptorset, VkWriteDescriptorSet *Pvkwritedescriptorset)
{
	*Pvkwritedescriptorset = (VkWriteDescriptorSet)
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.dstSet = Vvkdescriptorset,
		.dstBinding = Ubind,
		.dstArrayElement = 0,
		.descriptorType = Vvkdescriptortype,
		.descriptorCount = 1,
		.pImageInfo = Pvkdescriptorimageinfo,
		.pBufferInfo = Pvkdescriptorbufferinfo,
		.pTexelBufferView = NULL,
		.pNext = NULL
	};
}
