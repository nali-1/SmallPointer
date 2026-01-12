#define SMPT_RD_VK_PL_SDmMD(Udevice, Pcode, Lcode, Pvkshadermodule) \
	SMPT_DBmR2L \
	( \
		"vkCreateShaderModule %d", \
		vkCreateShaderModule \
		( \
			smpt_rd_vkqPinfo[Udevice].Vvkdevice, \
			&(VkShaderModuleCreateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, \
				.pCode = Pcode, \
				.codeSize = Lcode, \
				.flags = 0, \
				.pNext = NULL \
			}, \
			NULL, \
			Pvkshadermodule \
		) \
	)

#define SMPT_RD_VK_PL_SDmSA_CA_IF(Vvkpipelineshaderstagecreateinfo, Vstage, Vvkshadermodule) \
	Vvkpipelineshaderstagecreateinfo = (VkPipelineShaderStageCreateInfo) \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, \
		.stage = Vstage, \
		.module = Vvkshadermodule, \
		.pName = "main", \
		.flags = 0, \
		.pNext = NULL, \
		.pSpecializationInfo = NULL \
	};

void smpt_rd_vk_pl_sdMgp(uint32_t Udevice, VkShaderModule Pvkshadermodule[2], VkPipelineShaderStageCreateInfo Pvkpipelineshaderstagecreateinfo[2])
{
	uint64_t Lcode = 0;
	void *Pcode = smptfMread(SMPTFcHOME_VERT, &Lcode);
	SMPT_RD_VK_PL_SDmMD(Udevice, Pcode, Lcode, Pvkshadermodule)
	free(Pcode);

	Pcode = smptfMread(SMPTFcHOME_FRAG, &Lcode);
	SMPT_RD_VK_PL_SDmMD(Udevice, Pcode, Lcode, Pvkshadermodule + 1)
	free(Pcode);

	SMPT_RD_VK_PL_SDmSA_CA_IF(Pvkpipelineshaderstagecreateinfo[0], VK_SHADER_STAGE_VERTEX_BIT, Pvkshadermodule[0])
	SMPT_RD_VK_PL_SDmSA_CA_IF(Pvkpipelineshaderstagecreateinfo[1], VK_SHADER_STAGE_FRAGMENT_BIT, Pvkshadermodule[1])
}

void smpt_rd_vk_pl_sdMcp(uint32_t Udevice, VkShaderModule *Pvkshadermodule, VkPipelineShaderStageCreateInfo *Pvkpipelineshaderstagecreateinfo)
{
	uint64_t Lcode = 0;
	void *Pcode = smptfMread(SMPTFcHOME_COMP, &Lcode);
	SMPT_RD_VK_PL_SDmMD(Udevice, Pcode, Lcode, Pvkshadermodule)
	free(Pcode);

	SMPT_RD_VK_PL_SDmSA_CA_IF(Pvkpipelineshaderstagecreateinfo[0], VK_SHADER_STAGE_COMPUTE_BIT, Pvkshadermodule[0])
}
