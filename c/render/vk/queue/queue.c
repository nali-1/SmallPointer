struct SMPT_RD_VKQsINFO *smpt_rd_vkqPinfo;
uint32_t smpt_rd_vkqLinfo;

uint8_t
	smpt_rd_vkqUq_gp,
	smpt_rd_vkqUq_sf,
	smpt_rd_vkqUq_cp,
	smpt_rd_vkqUdv_cp;

static const char *Pextension[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

static void Mdv(struct SMPT_RD_VKQsINFO *Pinfo, uint8_t Ui, uint32_t Ugp, uint32_t Usf, uint32_t Ucp)
{
	//! check
	uint8_t
		*Pqueue_count = malloc(sizeof(uint8_t)),
		Lqueue_count = 1;
	Pqueue_count[0] = 1;
	float **Pqueue_priorities = malloc(sizeof(float *));
	Pqueue_priorities[0] = malloc(sizeof(float));
	Pqueue_priorities[0][0] = 1.0F;
	Pinfo->Pfamily = malloc(sizeof(uint32_t));
	if (Ui == SMPT_RD_VKQuGP)
	{
		if (Usf == Ugp)
		{
			smpt_rd_vkqUq_gp = 0;
		}
		else
		{
			Pinfo->Pfamily = realloc(Pinfo->Pfamily, sizeof(uint32_t) * (Lqueue_count + 1));
			Pinfo->Pfamily[Lqueue_count] = Ugp;
			Pqueue_count = realloc(Pqueue_count, sizeof(uint8_t) * (Lqueue_count + 1));
			Pqueue_count[Lqueue_count] = 1;
			Pqueue_priorities = realloc(Pqueue_priorities, sizeof(float *) * (Lqueue_count + 1));
			Pqueue_priorities[Lqueue_count] = malloc(sizeof(float));
			Pqueue_priorities[Lqueue_count][0] = 1.0F;
			++Lqueue_count;

			smpt_rd_vkqUq_gp = 1;
		}
		Pinfo->Pfamily[0] = Usf;

		smpt_rd_vkqUq_sf = 0;
	}

	if (Ui == SMPT_RD_VKQuGP && smpt_rd_vkqLinfo == 1)
	{
		if (Ugp == Ucp)
		{
			Pqueue_priorities[smpt_rd_vkqUq_gp] = realloc(Pqueue_priorities[smpt_rd_vkqUq_gp], sizeof(float) * (Pqueue_count[smpt_rd_vkqUq_gp] + 1));
			Pqueue_priorities[smpt_rd_vkqUq_gp][Pqueue_count[smpt_rd_vkqUq_gp]] = 1.0F;
			++Pqueue_count[smpt_rd_vkqUq_gp];
		}
		else
		{
			Pinfo->Pfamily = realloc(Pinfo->Pfamily, sizeof(uint32_t) * (Lqueue_count + 1));
			Pinfo->Pfamily[Lqueue_count] = Ucp;
			Pqueue_count = realloc(Pqueue_count, sizeof(uint8_t) * (Lqueue_count + 1));
			Pqueue_count[Lqueue_count] = 1;
			Pqueue_priorities = realloc(Pqueue_priorities, sizeof(float *) * (Lqueue_count + 1));
			Pqueue_priorities[Lqueue_count] = malloc(sizeof(float));
			Pqueue_priorities[Lqueue_count][0] = 1.0F;
			++Lqueue_count;
		}

		smpt_rd_vkqUq_cp = smpt_rd_vkqUq_gp + 1;
	}
	else if (Ui == smpt_rd_vkqUdv_cp)
	{
		Pinfo->Pfamily[0] = Ucp;

		smpt_rd_vkqUq_cp = 0;
	}

	VkDeviceQueueCreateInfo *Pvkdevicequeuecreateinfo = malloc(sizeof(VkDeviceQueueCreateInfo) * Lqueue_count);
	for (uint32_t l0 = 0; l0 < Lqueue_count; ++l0)
	{
		Pvkdevicequeuecreateinfo[l0] = (VkDeviceQueueCreateInfo)
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = Pinfo->Pfamily[l0],
			.queueCount = Pqueue_count[l0],
			.pQueuePriorities = Pqueue_priorities[l0],
			.flags = 0,
			.pNext = NULL
		};
	}
	VkPhysicalDeviceFeatures vkphysicaldevicefeatures;
	vkGetPhysicalDeviceFeatures(Pinfo->Vvkphysicaldevice, &vkphysicaldevicefeatures);
	SMPT_DBmR2L
	(
		"vkCreateDevice %d",
		vkCreateDevice
		(
			Pinfo->Vvkphysicaldevice,
			&(VkDeviceCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
				.queueCreateInfoCount = Lqueue_count,
				.pQueueCreateInfos = Pvkdevicequeuecreateinfo,
				.pEnabledFeatures = &vkphysicaldevicefeatures,
				.enabledExtensionCount = sizeof(Pextension) / sizeof(Pextension[0]),
				.ppEnabledExtensionNames = Pextension,

				#ifdef SMPT_CM_VK_DEBUG_UTILS
					#ifdef SMPT_CM_VK_DEBUG_REPORT
						.enabledLayerCount = sizeof(smpt_rd_vk_dbPlayer) / sizeof(smpt_rd_vk_dbPlayer[0]),
						.ppEnabledLayerNames = smpt_rd_vk_dbPlayer,
					#endif
				#endif
				#ifndef SMPT_CM_VK_DEBUG_UTILS
					#ifndef SMPT_CM_VK_DEBUG_REPORT
						.enabledLayerCount = 0,
						.ppEnabledLayerNames = NULL,
					#endif
				#endif

				.flags = 0,
				.pNext = NULL,
			},
			NULL,
			&Pinfo->Vvkdevice
		)
	)

	Pinfo->Pvkqueue = malloc(sizeof(VkQueue));
	uint8_t Lqueue = 0;
	for (uint32_t l0 = 0; l0 < Lqueue_count; ++l0)
	{
		for (uint32_t l1 = 0; l1 < Pqueue_count[l0]; ++l1)
		{
			Pinfo->Pvkqueue = realloc(Pinfo->Pvkqueue, sizeof(VkQueue) * (Lqueue + 1));
			vkGetDeviceQueue(Pinfo->Vvkdevice, Pinfo->Pfamily[l0], l1, Pinfo->Pvkqueue + Lqueue);
			++Lqueue;
		}

		free(Pqueue_priorities[l0]);
	}
	free(Pqueue_priorities);
	free(Pqueue_count);

	free(Pvkdevicequeuecreateinfo);
}

static void Mgp()
{
	struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;

	uint32_t Lqueue_family;
	vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, NULL);
	VkQueueFamilyProperties *Pvkqueuefamilyproperties = malloc(Lqueue_family * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, Pvkqueuefamilyproperties);

	VkBool32 Usurface_support;
	uint32_t
		Usf = 0xFFFFFFFF,
		Ugp = 0xFFFFFFFF,
		Ucp = 0xFFFFFFFF;
	for (uint32_t l0 = 0; l0 < Lqueue_family; ++l0)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = Pvkqueuefamilyproperties[l0];
		SMPT_DBmN2L("queueCount %d", vkqueuefamilyproperties.queueCount);
		SMPT_DBmN2L("queueFlags %d", vkqueuefamilyproperties.queueFlags);
		SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(Pinfo->Vvkphysicaldevice, l0, smpt_rd_vk_sfVkhr, &Usurface_support))
		SMPT_DBmN2L("Usurface_support %d", Usurface_support);

		if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			if (Usurface_support)
			{
				Usf = l0;
				Ugp = l0;
			}
			else if (Ugp == 0xFFFFFFFF)
			{
				Ugp = l0;
			}
		}
		else if (Usurface_support && Usf == 0xFFFFFFFF)
		{
			Usf = l0;
		}

		if
		(
			smpt_rd_vkqLinfo == 1 &&
			vkqueuefamilyproperties.queueFlags & VK_QUEUE_COMPUTE_BIT &&
			Ucp == 0xFFFFFFFF &&
			(Ugp != l0 || vkqueuefamilyproperties.queueCount > 1)
		)
			Ucp = l0;
	}

	Mdv(Pinfo, SMPT_RD_VKQuGP, Ugp, Usf, Ucp);

	free(Pvkqueuefamilyproperties);
}

static void Mcp()
{
	struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + smpt_rd_vkqUdv_cp;

	uint32_t Lqueue_family;
	vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, NULL);
	VkQueueFamilyProperties *Pvkqueuefamilyproperties = malloc(Lqueue_family * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, Pvkqueuefamilyproperties);

	uint32_t Ucp = 0xFFFFFFFF;
	for (uint32_t l0 = 0; l0 < Lqueue_family; ++l0)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = Pvkqueuefamilyproperties[l0];
		SMPT_DBmN2L("queueCount %d", vkqueuefamilyproperties.queueCount);
		SMPT_DBmN2L("queueFlags %d", vkqueuefamilyproperties.queueFlags);

		if ((vkqueuefamilyproperties.queueFlags & VK_QUEUE_COMPUTE_BIT || vkqueuefamilyproperties.queueFlags & VK_QUEUE_COMPUTE_BIT) && Ucp == 0xFFFFFFFF)
			Ucp = l0;
	}

	Mdv(Pinfo, smpt_rd_vkqUdv_cp, 0xFFFFFFFF, 0xFFFFFFFF, Ucp);

	free(Pvkqueuefamilyproperties);
}

void smpt_rd_vkqMset()
{
	if (smpt_rd_vkqLinfo == 1)
		smpt_rd_vkqUdv_cp = 0;
	else
		smpt_rd_vkqUdv_cp = SMPT_RD_VKQuCP;

	Mgp();
	if (smpt_rd_vkqLinfo != 1)
		Mcp();
}

static void Mfree(const struct SMPT_RD_VKQsINFO *Pinfo)
{
	free(Pinfo->Pfamily);
	free(Pinfo->Pvkqueue);
	vkDestroyDevice(Pinfo->Vvkdevice, NULL);
}

void smpt_rd_vkqMfree()
{
	Mfree(smpt_rd_vkqPinfo + SMPT_RD_VKQuGP);
	if (smpt_rd_vkqLinfo != 1)
		Mfree(smpt_rd_vkqPinfo + smpt_rd_vkqUdv_cp);
}
