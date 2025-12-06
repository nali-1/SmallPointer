void smpt_rd_vk_plMmake(uint32_t Udevice, VkPipelineShaderStageCreateInfo *Pvkpipelineshaderstagecreateinfo, VkRenderPass Vvkrenderpass, VkPipelineLayout Vvkpipelinelayout, VkPipeline *Pvkpipeline)
{
	SMPT_RD_VK_PL_VTmIPBIDST(Vvkvertexinputbindingdescription)
	SMPT_RD_VK_PL_VTmIPATBDST(Pvkvertexinputattributedescription)
	SMPT_RD_VK_PL_VTmIPSACAIF(&Vvkvertexinputbindingdescription, Pvkvertexinputattributedescription, 3, Vvkpipelinevertexinputstatecreateinfo)

	SMPT_RD_VK_PL_IPmAEB_SACAIF(Vvkpipelineinputassemblystatecreateinfo)

	SMPT_RD_VK_PL_VPmSACAIF(Vvkpipelineviewportstatecreateinfo)

	SMPT_RD_VK_PL_RTITmSACAIF(Vvkpipelinerasterizationstatecreateinfo)
	SMPT_RD_VK_PL_MTmSPSACAIF(Udevice, Vvkpipelinemultisamplestatecreateinfo)

	SMPT_RD_VK_PL_CLmBATMST(Vvkpipelinecolorblendattachmentstate)
	SMPT_RD_VK_PL_CLmBSACAIF(&Vvkpipelinecolorblendattachmentstate, Vvkpipelinecolorblendstatecreateinfo)

	SMPT_RD_VK_PL_DNMmP(Pvkdynamicstate)
	SMPT_RD_VK_PL_DNMmSACAIF(Pvkdynamicstate, 2, Vvkpipelinedynamicstatecreateinfo)

	SMPT_RD_VK_PLDmSC_SACAIF(Vvkpipelinedepthstencilstatecreateinfo)

	SMPT_DBmR2L
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			smpt_rd_vkqPinfo[Udevice].Vvkdevice,
			VK_NULL_HANDLE,
			1,
			&(VkGraphicsPipelineCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
				.stageCount = 2,
				.pStages = Pvkpipelineshaderstagecreateinfo,
				.pVertexInputState = &Vvkpipelinevertexinputstatecreateinfo,
				.pInputAssemblyState = &Vvkpipelineinputassemblystatecreateinfo,
				.pTessellationState = VK_NULL_HANDLE,
				.pViewportState = &Vvkpipelineviewportstatecreateinfo,
				.pRasterizationState = &Vvkpipelinerasterizationstatecreateinfo,
				.pMultisampleState = &Vvkpipelinemultisamplestatecreateinfo,
				.pDepthStencilState = &Vvkpipelinedepthstencilstatecreateinfo,
				.pColorBlendState = &Vvkpipelinecolorblendstatecreateinfo,
				.pDynamicState = &Vvkpipelinedynamicstatecreateinfo,
				.layout = Vvkpipelinelayout,
				.renderPass = Vvkrenderpass,
				.subpass = 0,
				.basePipelineHandle = VK_NULL_HANDLE,

				.basePipelineIndex = 0,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			Pvkpipeline
		)
	)
}
