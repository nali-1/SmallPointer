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
				.pNext = VK_NULL_HANDLE \
			}, \
			VK_NULL_HANDLE, \
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
		.pNext = VK_NULL_HANDLE, \
		.pSpecializationInfo = VK_NULL_HANDLE \
	};

void smpt_rd_vk_pl_sdMset(uint32_t Udevice, char *Pvert, char *Pfrag, VkShaderModule *Pvkshadermodule_vert, VkShaderModule *Pvkshadermodule_frag, VkPipelineShaderStageCreateInfo *Pvkpipelineshaderstagecreateinfo)
{
	uint32_t Lcode = 0;
	void *Pcode = smptfMread(Pvert, &Lcode);
	SMPT_RD_VK_PL_SDmMD(Udevice, Pcode, Lcode, Pvkshadermodule_vert)
	free(Pcode);

	Pcode = smptfMread(Pfrag, &Lcode);
	SMPT_RD_VK_PL_SDmMD(Udevice, Pcode, Lcode, Pvkshadermodule_frag)
	free(Pcode);

	SMPT_RD_VK_PL_SDmSA_CA_IF(Pvkpipelineshaderstagecreateinfo[0], VK_SHADER_STAGE_VERTEX_BIT, *Pvkshadermodule_vert)
	SMPT_RD_VK_PL_SDmSA_CA_IF(Pvkpipelineshaderstagecreateinfo[1], VK_SHADER_STAGE_FRAGMENT_BIT, *Pvkshadermodule_frag)
}
