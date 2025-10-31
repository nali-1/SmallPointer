const char *smpt_rd_vk_dbPlayer[] =
{
	"VK_LAYER_KHRONOS_validation"
};

static VkDebugUtilsMessengerEXT vkdebugutilsmessengerext;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT vkdebugutilsmessageseverityflagbitsext, VkDebugUtilsMessageTypeFlagsEXT vkdebugutilsmessagetypeflagsext, const VkDebugUtilsMessengerCallbackDataEXT *vkdebugutilsmessengercallbackdataext, void *data)
{
	SMPT_DBmW2L("vk_debug %s", vkdebugutilsmessengercallbackdataext->pMessage)
	return 0;
}

static VkResult createDebugUtilsMessengerEXT(VkInstance vkinstance, const VkDebugUtilsMessengerCreateInfoEXT *vkdebugutilsmessengercreateinfoext, const VkAllocationCallbacks *vkallocationcallbacks, VkDebugUtilsMessengerEXT *vkdebugutilsmessengerext)
{
	PFN_vkCreateDebugUtilsMessengerEXT Vpfn_vkcreatedebugutilsmessengerext = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vkinstance, "vkCreateDebugUtilsMessengerEXT");

	if (Vpfn_vkcreatedebugutilsmessengerext)
	{
		return Vpfn_vkcreatedebugutilsmessengerext(vkinstance, vkdebugutilsmessengercreateinfoext, vkallocationcallbacks, vkdebugutilsmessengerext);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void smpt_rd_vk_dbMset()
{
	SMPT_DBmR2L
	(
		"createDebugUtilsMessengerEXT %d",
		createDebugUtilsMessengerEXT
		(
			smpt_rd_vkqVit,
			&(VkDebugUtilsMessengerCreateInfoEXT)
			{
				.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
				.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
				.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
				.pfnUserCallback = debugCallback,

				.flags = 0,
				.pNext = VK_NULL_HANDLE,
				.pUserData = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&vkdebugutilsmessengerext
		)
	)
}

void smpt_rd_vk_dbMfree()
{
	PFN_vkDestroyDebugUtilsMessengerEXT Vpfn_vkdestroydebugutilsmessengerext = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(smpt_rd_vkqVit, "vkDestroyDebugUtilsMessengerEXT");
	if (Vpfn_vkdestroydebugutilsmessengerext)
	{
		Vpfn_vkdestroydebugutilsmessengerext(smpt_rd_vkqVit, vkdebugutilsmessengerext, VK_NULL_HANDLE);
	}
}
