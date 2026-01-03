#ifndef SMPT_RD_VK_PLhVP
	#define SMPT_RD_VK_PLhVP

	#define SMPT_RD_VK_PL_VPmSACAIF(n) \
		VkPipelineViewportStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, \
			.viewportCount = 1, \
			.pViewports = NULL, \
			.scissorCount = 1, \
			.pScissors = NULL, \
			.flags = 0, \
			.pNext = NULL \
		};
#endif
