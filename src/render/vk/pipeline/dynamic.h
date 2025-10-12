#ifndef SMPT_RD_VK_PLhDNM
	#define SMPT_RD_VK_PLhDNM

	//VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE
	#define SMPT_RD_VK_PL_DNMmP(n) \
		VkDynamicState n[] = \
		{ \
			VK_DYNAMIC_STATE_VIEWPORT, \
			VK_DYNAMIC_STATE_SCISSOR \
		};

	#define SMPT_RD_VK_PL_DNMmSACAIF(Pvkdynamicstate, Lvkdynamicstate, n) \
		VkPipelineDynamicStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO, \
			.dynamicStateCount = Lvkdynamicstate, \
			.pDynamicStates = Pvkdynamicstate, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
