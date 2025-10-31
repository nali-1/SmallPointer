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

	#ifdef SMPT_CM_DEBUG
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	#endif
};

void smpt_rd_vkq_psc_itMset()
{
	#ifdef SMPT_CM_DEBUG
		uint32_t Lvkextensionproperties = 0;
		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &Lvkextensionproperties, VK_NULL_HANDLE))
		VkExtensionProperties *Pvkextensionproperties = malloc(sizeof(VkExtensionProperties) * Lvkextensionproperties);
		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &Lvkextensionproperties, Pvkextensionproperties))
		for (uint32_t l0 = 0; l0 < Lvkextensionproperties; ++l0)
		{
			SMPT_DBmN2L("%d %s", l0, Pvkextensionproperties[l0].extensionName)
		}
		free(Pvkextensionproperties);
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
					.pApplicationName = VK_NULL_HANDLE,
					.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
					.pEngineName = VK_NULL_HANDLE,
					.engineVersion = VK_MAKE_VERSION(1, 0, 0),
					.apiVersion = VK_API_VERSION_1_0,

					.pNext = VK_NULL_HANDLE
				},
				.enabledExtensionCount = sizeof(Pextension) / sizeof(Pextension[0]),
				.ppEnabledExtensionNames = Pextension,

				.flags = 0,
				.pNext = VK_NULL_HANDLE,

				#ifdef SMPT_CM_VK_DEBUG
					.enabledLayerCount = sizeof(smpt_rd_vk_dbPlayer) / sizeof(smpt_rd_vk_dbPlayer[0]),
					.ppEnabledLayerNames = smpt_rd_vk_dbPlayer
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE
				#endif
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkqVit
		)
	)
}

void smpt_rd_vkq_psc_itMfree()
{
	vkDestroyInstance(smpt_rd_vkqVit, VK_NULL_HANDLE);
}
