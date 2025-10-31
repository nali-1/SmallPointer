#ifndef SMPT_RD_VK_PLhVP
	#define SMPT_RD_VK_PLhVP

	#define SMPT_RD_VK_PL_VPmSACAIF(n) \
		VkPipelineViewportStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, \
			.viewportCount = 1, \
			.pViewports = VK_NULL_HANDLE, \
			.scissorCount = 1, \
			.pScissors = VK_NULL_HANDLE, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
