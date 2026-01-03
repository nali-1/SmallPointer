VkSurfaceKHR smpt_rd_vk_sfVkhr = VK_NULL_HANDLE;

void smpt_rd_vk_sfMmake()
{
	VkPhysicalDevice Vvkphysicaldevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkphysicaldevice;

	#ifdef SMPT_CM_ST_ANDROID
		while (smpt_sf_awdPnative_window == NULL)
		{
			SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		}
		SMPT_DBmR2L
		(
			"vkCreateAndroidSurfaceKHR %d",
			vkCreateAndroidSurfaceKHR
			(
				smpt_rd_vkqVit,
				&(VkAndroidSurfaceCreateInfoKHR)
				{
					.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
					.window = smpt_sf_awdPnative_window,
					.flags = 0,
					.pNext = NULL
				},
				NULL,
				&smpt_rd_vk_sfVkhr
			)
		)
	#else
		#ifdef SMPT_CM_DRM
			uint32_t display_count = 0;
			SMPT_DBmR2L("vkGetPhysicalDeviceDisplayPropertiesKHR %d", vkGetPhysicalDeviceDisplayPropertiesKHR(Vvkphysicaldevice, &display_count, NULL))
			VkDisplayPropertiesKHR *vkdisplaypropertieskhr_p = malloc(sizeof(VkDisplayPropertiesKHR) * display_count);
			SMPT_DBmR2L("vkGetPhysicalDeviceDisplayPropertiesKHR %d", vkGetPhysicalDeviceDisplayPropertiesKHR(Vvkphysicaldevice, &display_count, vkdisplaypropertieskhr_p))
			SMPT_DBmN2L("display_count %d", display_count)
			for (uint32_t l_0 = 0; l_0 < display_count; ++l_0)
			{
				SMPT_DBmN2L("%d %s", l_0, vkdisplaypropertieskhr_p[l_0].displayName)
			}

			uint32_t display_mode_count = 0;
			SMPT_DBmR2L("vkGetDisplayModePropertiesKHR %d", vkGetDisplayModePropertiesKHR(Vvkphysicaldevice, vkdisplaypropertieskhr_p[0].display, &display_mode_count, NULL))
			VkDisplayModePropertiesKHR *vkdisplaymodepropertieskhr_p = malloc(sizeof(VkDisplayModePropertiesKHR) * display_mode_count);
			SMPT_DBmR2L("vkGetDisplayModePropertiesKHR %d", vkGetDisplayModePropertiesKHR(Vvkphysicaldevice, vkdisplaypropertieskhr_p[0].display, &display_mode_count, vkdisplaymodepropertieskhr_p))
			SMPT_DBmN2L("display_mode_count %d", display_mode_count)
			for (uint32_t l_0 = 0; l_0 < display_mode_count; ++l_0)
			{
				SMPT_DBmN2L("width %d", vkdisplaymodepropertieskhr_p[l_0].parameters.visibleRegion.width)
				SMPT_DBmN2L("hieght %d", vkdisplaymodepropertieskhr_p[l_0].parameters.visibleRegion.height)
				SMPT_DBmN2L("refreshRate %d", vkdisplaymodepropertieskhr_p[l_0].parameters.refreshRate)
			}
			smpt_sfUwidth = vkdisplaymodepropertieskhr_p[0].parameters.visibleRegion.width;
			smpt_sfUheight = vkdisplaymodepropertieskhr_p[0].parameters.visibleRegion.height;
			//.i project m4x4
			smpt_sfUstate |= SMPT_SFuS_RE;

			uint32_t plane_count = 0;
			SMPT_DBmR2L("vkGetPhysicalDeviceDisplayPlanePropertiesKHR %d", vkGetPhysicalDeviceDisplayPlanePropertiesKHR(Vvkphysicaldevice, &plane_count, NULL))
			VkDisplayPlanePropertiesKHR *vkdisplayplanepropertieskhr_p = malloc(sizeof(VkDisplayPlanePropertiesKHR) * plane_count);
			SMPT_DBmR2L("vkGetPhysicalDeviceDisplayPlanePropertiesKHR %d", vkGetPhysicalDeviceDisplayPlanePropertiesKHR(Vvkphysicaldevice, &plane_count, vkdisplayplanepropertieskhr_p))
			SMPT_DBmN2L("plane_count %d", plane_count)

			uint32_t plane = UINT32_MAX;
			uint32_t stack_index = 0;
			for (uint32_t l_0 = 0; l_0 < plane_count; ++l_0)
			{
				if (!vkdisplayplanepropertieskhr_p[l_0].currentDisplay || vkdisplayplanepropertieskhr_p[l_0].currentDisplay == vkdisplaypropertieskhr_p[0].display)
				{
					plane = l_0;
					stack_index = vkdisplayplanepropertieskhr_p[l_0].currentStackIndex;
					break;
				}
			}

			SMPT_DBmR2L
			(
				"vkCreateDisplayPlaneSurfaceKHR %d",
				vkCreateDisplayPlaneSurfaceKHR
				(
					smpt_rd_vkqVit,
					&(VkDisplaySurfaceCreateInfoKHR)
					{
						.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR,
						.displayMode = vkdisplaymodepropertieskhr_p[0].displayMode,
						.planeIndex = plane,
						.planeStackIndex = stack_index,
						.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
						.globalAlpha = 0,
						.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR,
						.imageExtent = vkdisplaymodepropertieskhr_p[0].parameters.visibleRegion,
						.flags = 0,
						.pNext = NULL
					},
					NULL,
					&smpt_rd_vk_sfVkhr
				)
			)
			free(vkdisplaypropertieskhr_p);
			free(vkdisplaymodepropertieskhr_p);
		#endif
		#ifdef SMPT_CM_WL
			SMPT_DBmR2L
			(
				"vkCreateWaylandSurfaceKHR %d",
				vkCreateWaylandSurfaceKHR
				(
					smpt_rd_vkqVit,
					&(VkWaylandSurfaceCreateInfoKHR)
					{
						.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
						.display = smpt_sf_wl_ce_Pdp,
						.surface = smpt_sf_wl_cePsf,
						.flags = 0,
						.pNext = NULL
					},
					NULL,
					&smpt_rd_vk_sfVkhr
				)
			)
		#endif
	#endif
}

void smpt_rd_vk_sfMfree()
{
	vkDestroySurfaceKHR(smpt_rd_vkqVit, smpt_rd_vk_sfVkhr, NULL);
	smpt_rd_vk_sfVkhr = VK_NULL_HANDLE;
}
