#ifndef SMPT_RD_VK_PLhMT
	#define SMPT_RD_VK_PLhMT

	#define SMPT_RD_VK_PL_MTmSPSACAIF(Udevice, n) \
		VkPipelineMultisampleStateCreateInfo n = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, \
			.sampleShadingEnable = smpt_rd_vkqPinfo[Udevice].Usample_count == VK_SAMPLE_COUNT_1_BIT ? VK_FALSE : VK_TRUE, \
			.rasterizationSamples = smpt_rd_vkqPinfo[Udevice].Usample_count, \
			.minSampleShading = 1.0F, \
			.pSampleMask = VK_NULL_HANDLE, \
			.alphaToCoverageEnable = VK_FALSE, \
			.alphaToOneEnable = VK_FALSE, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
