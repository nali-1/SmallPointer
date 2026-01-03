#ifndef SMPT_RD_VK_PLhCL
	#define SMPT_RD_VK_PLhCL

	#define SMPT_RD_VK_PL_CLmBATMST(n) \
		VkPipelineColorBlendAttachmentState n = \
		{ \
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT, \
			.blendEnable = VK_TRUE, \
			.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA, \
			.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, \
			.colorBlendOp = VK_BLEND_OP_ADD, \
			.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE, \
			.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO, \
			.alphaBlendOp = VK_BLEND_OP_ADD, \
		};

	#define SMPT_RD_VK_PL_CLmBSACAIF(Pvkpipelinecolorblendattachmentstate, n) \
		VkPipelineColorBlendStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO, \
			.logicOpEnable = VK_FALSE, \
			.logicOp = VK_LOGIC_OP_COPY, \
			.attachmentCount = 1, \
			.pAttachments = Pvkpipelinecolorblendattachmentstate, \
			.blendConstants[0] = 0.0F, \
			.blendConstants[1] = 0.0F, \
			.blendConstants[2] = 0.0F, \
			.blendConstants[3] = 0.0F, \
			.flags = 0, \
			.pNext = NULL \
		};
#endif
