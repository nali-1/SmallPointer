const char *smpt_rd_vk_dbPlayer[] =
{
	"VK_LAYER_KHRONOS_validation"
};

#ifdef SMPT_CM_VK_DEBUG_UTILS
	static VkDebugUtilsMessengerEXT Vvkdebugutilsmessengerext;
	static VKAPI_ATTR VkBool32 VKAPI_CALL Mpfn_vkdebugutilsmessengercallbackext(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		SMPT_DBmW2L("vk_debug")
		SMPT_DBmW2L("messageSeverity %d", messageSeverity)
		SMPT_DBmW2L("messageTypes %d", messageTypes)
		SMPT_DBmW2L("pCallbackData->pMessageIdName %s", pCallbackData->pMessageIdName)
		SMPT_DBmW2L("pCallbackData->pMessage %s", pCallbackData->pMessage)
		SMPT_DBmW2L("pUserData %p", pUserData)
		return VK_FALSE;
	}
#endif
#ifdef SMPT_CM_VK_DEBUG_REPORT
	static VkDebugReportCallbackEXT Vvkdebugreportcallbackext;
	VKAPI_ATTR VkBool32 VKAPI_CALL Mpfn_vkdebugreportcallbackext(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
	{
		SMPT_DBmW2L("vk_debug")
		SMPT_DBmW2L("flags %d", flags)
		SMPT_DBmW2L("objectType %d", objectType)
		SMPT_DBmW2L("object %ld", object)
		SMPT_DBmW2L("location %ld", location)
		SMPT_DBmW2L("messageCode %d", messageCode)
		SMPT_DBmW2L("pLayerPrefix %s", pLayerPrefix)
		SMPT_DBmW2L("pMessage %s", pMessage)
		SMPT_DBmW2L("pUserData %p", pUserData)
		return VK_FALSE;
	}
#endif

void smpt_rd_vk_dbMset()
{
	#ifdef SMPT_CM_VK_DEBUG_UTILS
		PFN_vkCreateDebugUtilsMessengerEXT Vpfn_vkcreatedebugutilsmessengerext = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vkinstance, "vkCreateDebugUtilsMessengerEXT");
		SMPT_DBmN2L("Vpfn_vkcreatedebugutilsmessengerext %p", Vpfn_vkcreatedebugutilsmessengerext)
		SMPT_DBmR2L
		(
			"PFN_vkCreateDebugUtilsMessengerEXT %d",
			Vpfn_vkcreatedebugutilsmessengerext
			(
				smpt_rd_vkqVit,
				&(VkDebugUtilsMessengerCreateInfoEXT)
				{
					.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
					.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
					.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
					.pfnUserCallback = Mpfn_vkdebugutilsmessengercallbackext,

					.flags = 0,
					.pNext = VK_NULL_HANDLE,
					.pUserData = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&Vvkdebugutilsmessengerext
			)
		)
	#endif
	#ifdef SMPT_CM_VK_DEBUG_REPORT
		VkDebugReportCallbackCreateInfoEXT Vvkdebugreportcallbackcreateinfoext =
		{
			.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
			.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT,
			.pfnCallback = Mpfn_vkdebugreportcallbackext,
			.pNext = VK_NULL_HANDLE,
			.pUserData = VK_NULL_HANDLE
		};
		PFN_vkCreateDebugReportCallbackEXT Vpfn_vkcreatedebugreportcallbackext = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(smpt_rd_vkqVit, "vkCreateDebugReportCallbackEXT");
		SMPT_DBmN2L("Vpfn_vkcreatedebugreportcallbackext %p", Vpfn_vkcreatedebugreportcallbackext)
		SMPT_DBmR2L
		(
			"PFN_vkCreateDebugReportCallbackEXT %d",
			Vpfn_vkcreatedebugreportcallbackext
			(
				smpt_rd_vkqVit,
				&Vvkdebugreportcallbackcreateinfoext,
				VK_NULL_HANDLE,
				&Vvkdebugreportcallbackext
			)
		)
	#endif
}

void smpt_rd_vk_dbMfree()
{
	#ifdef SMPT_CM_VK_DEBUG_UTILS
		PFN_vkDestroyDebugUtilsMessengerEXT Vpfn_vkdestroydebugutilsmessengerext = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(smpt_rd_vkqVit, "vkDestroyDebugUtilsMessengerEXT");
		SMPT_DBmN2L("Vpfn_vkdestroydebugutilsmessengerext %p", Vpfn_vkdestroydebugutilsmessengerext)
		Vpfn_vkdestroydebugutilsmessengerext(smpt_rd_vkqVit, Vvkdebugutilsmessengerext, VK_NULL_HANDLE);
	#endif
	#ifdef SMPT_CM_VK_DEBUG_REPORT
		PFN_vkDestroyDebugReportCallbackEXT Vpfn_vkdestroydebugreportcallbackext = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(smpt_rd_vkqVit, "vkDestroyDebugReportCallbackEXT");
		SMPT_DBmN2L("Vpfn_vkdestroydebugreportcallbackext %p", Vpfn_vkdestroydebugreportcallbackext)
		Vpfn_vkdestroydebugreportcallbackext(smpt_rd_vkqVit, Vvkdebugreportcallbackext, VK_NULL_HANDLE);
	#endif
}
