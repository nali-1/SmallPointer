#ifndef SMPT_RD_VK_PLhVT
	#define SMPT_RD_VK_PLhVT

	#define SMPT_RD_VK_PL_VTmIPBIDST(n) \
		VkVertexInputBindingDescription n = \
		{ \
			.binding = 0, \
			.stride = sizeof(float) * 3 + sizeof(uint8_t) + sizeof(uint8_t), \
			.inputRate = VK_VERTEX_INPUT_RATE_VERTEX \
		};

	#define SMPT_RD_VK_PL_VTmIPATBDST(n) \
		VkVertexInputAttributeDescription n[] = \
		{ \
			(VkVertexInputAttributeDescription) \
			{ \
				.binding = 0, \
				.location = 0, \
				.format = VK_FORMAT_R32G32B32_SFLOAT, \
				.offset = 0 \
			}, \
			(VkVertexInputAttributeDescription) \
			{ \
				.binding = 0, \
				.location = 1, \
				.format = VK_FORMAT_R8_UINT, \
				.offset = sizeof(float) * 3 \
			}, \
			(VkVertexInputAttributeDescription) \
			{ \
				.binding = 0, \
				.location = 2, \
				.format = VK_FORMAT_R8_UINT, \
				.offset = sizeof(float) * 3 + sizeof(uint8_t) \
			} \
		};

	#define SMPT_RD_VK_PL_VTmIPSACAIF(Pvkvertexinputbindingdescription, Pvkvertexinputattributedescription, Lvkvertexinputattributedescription, n) \
		VkPipelineVertexInputStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, \
			.vertexBindingDescriptionCount = 1, \
			.pVertexBindingDescriptions = Pvkvertexinputbindingdescription, \
			.vertexAttributeDescriptionCount = Lvkvertexinputattributedescription, \
			.pVertexAttributeDescriptions = Pvkvertexinputattributedescription, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
