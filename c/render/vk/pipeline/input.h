#ifndef SMPT_RD_VK_PLhIP
	#define SMPT_RD_VK_PLhIP

	#define SMPT_RD_VK_PL_IPmAEB_SACAIF(n) \
		VkPipelineInputAssemblyStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, \
			.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, \
			.primitiveRestartEnable = VK_FALSE, \
			.flags = 0, \
			.pNext = NULL \
		};
#endif
