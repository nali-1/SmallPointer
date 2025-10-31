#ifndef SMPT_RD_VKhW
	#define SMPT_RD_VKhW

	#define SMPT_RD_VKWmDSTS(Ubind, Pvkdescriptorimageinfo, Pvkdescriptorbufferinfo, Vvkdescriptortype, Vvkdescriptorset, Vvkwritedescriptorset) \
		Vvkwritedescriptorset = (VkWriteDescriptorSet) \
		{ \
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, \
			.dstSet = Vvkdescriptorset, \
			.dstBinding = Ubind, \
			.dstArrayElement = 0, \
			.descriptorType = Vvkdescriptortype, \
			.descriptorCount = 1, \
			.pImageInfo = Pvkdescriptorimageinfo, \
			.pBufferInfo = Pvkdescriptorbufferinfo, \
			.pTexelBufferView = VK_NULL_HANDLE, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
