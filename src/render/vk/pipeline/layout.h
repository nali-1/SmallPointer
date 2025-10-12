#ifndef SMPT_RD_VK_PLhLO
	#define SMPT_RD_VK_PLhLO

	#define SMPT_RD_VK_PL_LOmMAKE(Udevice, Ui, Pvkpipelinelayout) \
		SMPT_DBmR2L \
		( \
			"vkCreatePipelineLayout %d", \
			vkCreatePipelineLayout \
			( \
				smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
				&(VkPipelineLayoutCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, \
					.setLayoutCount = 1, \
					.pSetLayouts = smpt_rd_vkw_dsts_loP + Ui, \
					.pushConstantRangeCount = 0, \
					.pPushConstantRanges = VK_NULL_HANDLE, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				Pvkpipelinelayout \
			) \
		)
#endif
