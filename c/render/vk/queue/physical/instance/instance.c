VkInstance smpt_rd_vkqVit;

static const char *Pextension[] =
{
	VK_KHR_SURFACE_EXTENSION_NAME,
	#ifdef SMPT_CM_ST_ANDROID
		VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
	#endif
	#ifdef SMPT_CM_DRM
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_DISPLAY_EXTENSION_NAME,
	#endif
	#ifdef SMPT_CM_WL
		VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
	#endif

	#ifdef SMPT_CM_VK_DEBUG_UTILS
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	#endif
	#ifdef SMPT_CM_VK_DEBUG_REPORT
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME
	#endif
};

void smpt_rd_vkq_psc_itMset()
{
	#ifdef SMPT_CM_DEBUG
		uint32_t Lvkextensionproperties = 0;
		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(NULL, &Lvkextensionproperties, NULL))
		SMPT_DBmR2L("Lvkextensionproperties %d", Lvkextensionproperties)
		VkExtensionProperties *Pvkextensionproperties = malloc(sizeof(VkExtensionProperties) * Lvkextensionproperties);
		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(NULL, &Lvkextensionproperties, Pvkextensionproperties))
		for (uint32_t l0 = 0; l0 < Lvkextensionproperties; ++l0)
		{
			SMPT_DBmN2L("%d %s", l0, Pvkextensionproperties[l0].extensionName)
		}
		free(Pvkextensionproperties);

		uint32_t Lvklayerproperties = 0;
		SMPT_DBmR2L("vkEnumerateInstanceLayerProperties %d", vkEnumerateInstanceLayerProperties(&Lvklayerproperties, NULL))
		SMPT_DBmR2L("Lvklayerproperties %d", Lvklayerproperties)
		VkLayerProperties *Pvklayerproperties = malloc(sizeof(VkLayerProperties) * Lvklayerproperties);
		SMPT_DBmR2L("vkEnumerateInstanceLayerProperties %d", vkEnumerateInstanceLayerProperties(&Lvklayerproperties, Pvklayerproperties))
		for (uint32_t l0 = 0; l0 < Lvklayerproperties; ++l0)
		{
			SMPT_DBmN2L("Pvklayerproperties %p", Pvklayerproperties + l0)
			SMPT_DBmN2L("layerName %s", Pvklayerproperties[l0].layerName)
			SMPT_DBmN2L("description %s", Pvklayerproperties[l0].description)
			SMPT_DBmN2L("specVersion %d", Pvklayerproperties[l0].specVersion)
			SMPT_DBmN2L("implementationVersion %d", Pvklayerproperties[l0].implementationVersion)
		}
		free(Pvklayerproperties);
	#endif

	SMPT_DBmR2L
	(
		"vkCreateInstance %d",
		vkCreateInstance
		(
			&(VkInstanceCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
				.pApplicationInfo = &(VkApplicationInfo)
				{
					.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
					.pApplicationName = NULL,
					.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
					.pEngineName = NULL,
					.engineVersion = VK_MAKE_VERSION(1, 0, 0),
					.apiVersion = VK_API_VERSION_1_0,

					.pNext = NULL
				},
				.enabledExtensionCount = sizeof(Pextension) / sizeof(Pextension[0]),
				.ppEnabledExtensionNames = Pextension,

				.flags = 0,
				.pNext = NULL,

				#if SMPT_CM_VK_DEBUG_UTILS || SMPT_CM_VK_DEBUG_REPORT
					.enabledLayerCount = sizeof(smpt_rd_vk_dbPlayer) / sizeof(smpt_rd_vk_dbPlayer[0]),
					.ppEnabledLayerNames = smpt_rd_vk_dbPlayer
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = NULL
				#endif
			},
			NULL,
			&smpt_rd_vkqVit
		)
	)
}

void smpt_rd_vkq_psc_itMfree()
{
	vkDestroyInstance(smpt_rd_vkqVit, NULL);
}
