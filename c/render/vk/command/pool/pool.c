#define SMPT_RD_VK_CMPm(Pvkcommandpool, Up, Ufamily) \
	SMPT_DBmR2L \
	( \
		"vkCreateCommandPool %d", \
		vkCreateCommandPool \
		( \
			Pinfo->Vvkdevice, \
			&(VkCommandPoolCreateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, \
				.queueFamilyIndex = Pinfo->Pfamily[Ufamily], \
				.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, \
				.pNext = NULL \
			}, \
			NULL, \
			Pvkcommandpool + Up \
		) \
	)

static void Mgp()
{
	struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;

	if (smpt_rd_vkqLinfo == 1 && smpt_rd_vkqUq_gp != smpt_rd_vkqUq_cp)
	{
		Pinfo->Pvkcommandpool = malloc(sizeof(VkCommandPool) * 2);
		SMPT_RD_VK_CMPm(Pinfo->Pvkcommandpool, 1, smpt_rd_vkqUq_cp)
	}
	else
	{
		Pinfo->Pvkcommandpool = malloc(sizeof(VkCommandPool));
	}
	SMPT_RD_VK_CMPm(Pinfo->Pvkcommandpool, 0, smpt_rd_vkqUq_gp)
}

static void Mcp()
{
	struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + smpt_rd_vkqUdv_cp;

	Pinfo->Pvkcommandpool = malloc(sizeof(VkCommandPool));
	SMPT_RD_VK_CMPm(Pinfo->Pvkcommandpool, 0, smpt_rd_vkqUq_cp)
}

void smpt_rd_vk_cmpMset()
{
	Mgp();
	if (smpt_rd_vkqLinfo != 1)
		Mcp();
}

static void Mfree(const struct SMPT_RD_VKQsINFO *Pinfo)
{
	free(Pinfo->Pvkcommandpool);
}

static void Mfree_gp()
{
	const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;

	if (smpt_rd_vkqLinfo == 1 && smpt_rd_vkqUq_gp != smpt_rd_vkqUq_cp)
		for (uint32_t l0 = 0; l0 < 2; ++l0)
			vkDestroyCommandPool(Pinfo->Vvkdevice, Pinfo->Pvkcommandpool[l0], NULL);
	else
		vkDestroyCommandPool(Pinfo->Vvkdevice, Pinfo->Pvkcommandpool[0], NULL);

	Mfree(Pinfo);
}

static void Mfree_cp()
{
	const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + smpt_rd_vkqUdv_cp;

	vkDestroyCommandPool(Pinfo->Vvkdevice, Pinfo->Pvkcommandpool[0], NULL);

	Mfree(Pinfo);
}

void smpt_rd_vk_cmpMfree()
{
	Mfree_gp();
	if (smpt_rd_vkqLinfo != 1)
		Mfree_cp();
}
