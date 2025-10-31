#define SMPT_RD_VK_CM_BFm(Pvkcommandbuffer, Ub, Up) \
	SMPT_DBmR2L \
	( \
		"vkAllocateCommandBuffers %d", \
		vkAllocateCommandBuffers \
		( \
			Pinfo->Vvkdevice, \
			&(VkCommandBufferAllocateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, \
				.commandPool = Pinfo->Pvkcommandpool[Up], \
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, \
				.commandBufferCount = 1, \
				.pNext = VK_NULL_HANDLE \
			}, \
			Pvkcommandbuffer + Ub \
		) \
	)

static void Mgp()
{
	struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;

	if (smpt_rd_vkqLinfo == 1)
	{
		Pinfo->Pvkcommandbuffer = malloc(sizeof(VkCommandBuffer) * (smpt_rd_vk_swcUimage + 1));
		SMPT_RD_VK_CM_BFm(Pinfo->Pvkcommandbuffer, smpt_rd_vk_swcUimage, 1)
	}
	else
	{
		Pinfo->Pvkcommandbuffer = malloc(sizeof(VkCommandBuffer) * smpt_rd_vk_swcUimage);
	}
	for (uint32_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
		SMPT_RD_VK_CM_BFm(Pinfo->Pvkcommandbuffer, l0, 0)
}

static void Mcp()
{
	struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + smpt_rd_vkqUdv_cp;

	Pinfo->Pvkcommandbuffer = malloc(sizeof(VkCommandBuffer));
	SMPT_RD_VK_CM_BFm(Pinfo->Pvkcommandbuffer, 0, 0)
}

void smpt_rd_vk_cm_bfMset()
{
	Mgp();
	if (smpt_rd_vkqLinfo != 1)
		Mcp();
}

static void Mfree(const struct SMPT_RD_VKQsINFO *Pinfo)
{
	free(Pinfo->Pvkcommandbuffer);
}

static void Mfree_gp()
{
	const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;

	vkFreeCommandBuffers(Pinfo->Vvkdevice, Pinfo->Pvkcommandpool[0], smpt_rd_vk_swcUimage, Pinfo->Pvkcommandbuffer);

	if (smpt_rd_vkqLinfo == 1)
		vkFreeCommandBuffers(Pinfo->Vvkdevice, Pinfo->Pvkcommandpool[1], 1, Pinfo->Pvkcommandbuffer + smpt_rd_vk_swcUimage);

	Mfree(Pinfo);
}

static void Mfree_cp()
{
	const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + smpt_rd_vkqUdv_cp;

	vkFreeCommandBuffers(Pinfo->Vvkdevice, Pinfo->Pvkcommandpool[0], 1, Pinfo->Pvkcommandbuffer);

	Mfree(Pinfo);
}

void smpt_rd_vk_cm_bfMfree()
{
	Mfree_gp();
	if (smpt_rd_vkqLinfo != 1)
		Mfree_cp();
}
