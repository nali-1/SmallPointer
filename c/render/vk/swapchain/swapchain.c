VkSwapchainKHR smpt_rd_vk_swcVkhr;
VkExtent2D smpt_rd_vk_swcVet2d;
VkRenderPass smpt_rd_vk_swcVrdp;

VkImage *smpt_rd_vk_swcPim;
VkImageView *smpt_rd_vk_swcPimv;
VkFramebuffer *smpt_rd_vk_swcPfbf;

uint8_t smpt_rd_vk_swcUimage;
uint8_t smpt_rd_vk_swcUframe = 0;
uint8_t smpt_rd_vk_swcUframe_buffer = 0;

static uint32_t Uimage;

static VkImage vkimage_depth;
static VkImageView vkimageview_depth;
static VkDeviceMemory vkdevicememory_depth;

static VkImage vkimage_color;
static VkImageView vkimageview_color;
static VkDeviceMemory vkdevicememory_color;

static VkPresentModeKHR vkpresentmodekhr;
static VkSurfaceFormatKHR vksurfaceformatkhr;

void smpt_rd_vk_swcMset()
{
	const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;
	VkPhysicalDevice Vvkphysicaldevice = Pinfo->Vvkphysicaldevice;
	VkDevice Vvkdevice = Pinfo->Vvkdevice;

	uint32_t Usurface_format;
	SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(Vvkphysicaldevice, smpt_rd_vk_sfVkhr, &Usurface_format, NULL))
	VkSurfaceFormatKHR *Pvksurfaceformatkhr = malloc(Usurface_format * sizeof(VkSurfaceFormatKHR));
	SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(Vvkphysicaldevice, smpt_rd_vk_sfVkhr, &Usurface_format, Pvksurfaceformatkhr))
	SMPT_DBmN2L("Usurface_format %d", Usurface_format)
	vksurfaceformatkhr = Pvksurfaceformatkhr[0];
	for (uint32_t l0 = 0; l0 < Usurface_format; ++l0)
	{
		SMPT_DBmN2L("format %d", Pvksurfaceformatkhr[l0].format)
		SMPT_DBmN2L("colorSpace %d", Pvksurfaceformatkhr[l0].colorSpace)

		if
		(
			Pvksurfaceformatkhr[l0].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR &&
			(Pvksurfaceformatkhr[l0].format == VK_FORMAT_B8G8R8A8_UNORM || Pvksurfaceformatkhr[l0].format == VK_FORMAT_R8G8B8A8_UNORM)
		)
		{
			vksurfaceformatkhr = Pvksurfaceformatkhr[l0];
			#ifndef SMPT_CM_DEBUG
				break;
			#endif
		}
	}
	free(Pvksurfaceformatkhr);

	uint32_t Usurface_present;
	SMPT_DBmR2L("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(Vvkphysicaldevice, smpt_rd_vk_sfVkhr, &Usurface_present, NULL))
	VkPresentModeKHR *Pvkpresentmodekhr = malloc(Usurface_present * sizeof(VkPresentModeKHR));
	SMPT_DBmR2L("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(Vvkphysicaldevice, smpt_rd_vk_sfVkhr, &Usurface_present, Pvkpresentmodekhr))
	SMPT_DBmN2L("Usurface_present %d", Usurface_present)
	vkpresentmodekhr = Pvkpresentmodekhr[0];
	for (uint32_t l0 = 0; l0 < Usurface_present; ++l0)
	{
		SMPT_DBmN2L("VkPresentModeKHR %d", Pvkpresentmodekhr[l0])

		if (Pvkpresentmodekhr[l0] == VK_PRESENT_MODE_FIFO_KHR)
		{
			vkpresentmodekhr = Pvkpresentmodekhr[l0];
			#ifndef SMPT_CM_DEBUG
				break;
			#endif
		}
	}
	free(Pvkpresentmodekhr);

	const uint32_t Udepth = VK_FORMAT_D32_SFLOAT;
	#ifndef SMPT_CM_DEBUG
		SMPT_DBmN2L("Udepth %d", Udepth);
		VkFormatProperties vkformatproperties;
		vkGetPhysicalDeviceFormatProperties(Vvkphysicaldevice, Udepth, &vkformatproperties);
		SMPT_DBmN2L("linearTilingFeatures %d", vkformatproperties.linearTilingFeatures);
		SMPT_DBmN2L("optimalTilingFeatures %d", vkformatproperties.optimalTilingFeatures);
		SMPT_DBmN2L("bufferFeatures %d", vkformatproperties.bufferFeatures);
	#endif

	VkSurfaceCapabilitiesKHR vksurfacecapabilitieskhr;
	SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Vvkphysicaldevice, smpt_rd_vk_sfVkhr, &vksurfacecapabilitieskhr))
	SMPT_DBmR2L("smpt_rd_vk_swcUimage %d", smpt_rd_vk_swcUimage = vksurfacecapabilitieskhr.minImageCount)

	if (vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	{
		smpt_rd_vk_swcVet2d.width = smpt_sfUheight;
		smpt_rd_vk_swcVet2d.height = smpt_sfUwidth;
	}
	else
	{
		smpt_rd_vk_swcVet2d.height = smpt_sfUheight;
		smpt_rd_vk_swcVet2d.width = smpt_sfUwidth;
	}

	VkCompositeAlphaFlagBitsKHR Vvkcompositealphaflagbitskhr = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	if (vksurfacecapabilitieskhr.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
		Vvkcompositealphaflagbitskhr = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	else if (vksurfacecapabilitieskhr.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR)
		Vvkcompositealphaflagbitskhr = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;
	else if (vksurfacecapabilitieskhr.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
		Vvkcompositealphaflagbitskhr = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
	else if (vksurfacecapabilitieskhr.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
		Vvkcompositealphaflagbitskhr = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;

	SMPT_DBmR2L
	(
		"vkCreateSwapchainKHR %d",
		vkCreateSwapchainKHR
		(
			Vvkdevice,
			&(VkSwapchainCreateInfoKHR)
			{
				.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
				.surface = smpt_rd_vk_sfVkhr,
				.minImageCount = vksurfacecapabilitieskhr.minImageCount,
				.imageFormat = vksurfaceformatkhr.format,
				.imageColorSpace = vksurfaceformatkhr.colorSpace,
				.imageExtent = smpt_rd_vk_swcVet2d,
				.imageArrayLayers = 1,
				.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

				.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
				.compositeAlpha = Vvkcompositealphaflagbitskhr,
				.presentMode = vkpresentmodekhr,
				.clipped = VK_TRUE,

				.queueFamilyIndexCount = smpt_rd_vkqUq_gp == smpt_rd_vkqUq_sf ? 1 : 2,
				.pQueueFamilyIndices = Pinfo->Pfamily,

				.oldSwapchain = VK_NULL_HANDLE,

				.imageSharingMode = smpt_rd_vkqUq_gp == smpt_rd_vkqUq_sf ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT,

				.flags = 0,
				.pNext = NULL
			},
			NULL,
			&smpt_rd_vk_swcVkhr
		)
	)

	SMPT_DBmR2L("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(Vvkdevice, smpt_rd_vk_swcVkhr, &Uimage, NULL))
	SMPT_DBmN2L("Uimage %d", Uimage)
	smpt_rd_vk_swcPim = malloc(sizeof(VkImage) * Uimage);
	smpt_rd_vk_swcPimv = malloc(sizeof(VkImageView) * Uimage);
	smpt_rd_vk_swcPfbf = malloc(sizeof(VkFramebuffer) * Uimage);
	SMPT_DBmR2L("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(Vvkdevice, smpt_rd_vk_swcVkhr, &Uimage, smpt_rd_vk_swcPim))

	SMPT_RD_VK_RDPmMAKE(SMPT_RD_VKQuGP, vksurfaceformatkhr.format, Udepth, &smpt_rd_vk_swcVrdp)

	SMPT_RD_VK_IMmMAKE
	(
		SMPT_RD_VKQuGP,
		Udepth,
		((VkExtent3D)
		{
			.width = smpt_rd_vk_swcVet2d.width,
			.height = smpt_rd_vk_swcVet2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		Pinfo->Usample_count,
		&vkimage_depth
	)
	VkMemoryRequirements vkmemoryrequirements;
	SMPT_RD_VK_IMmGEN(SMPT_RD_VKQuGP, vkimage_depth, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_depth, vkmemoryrequirements)
	SMPT_RD_VK_IMVmMAKE(SMPT_RD_VKQuGP, vkimage_depth, Udepth, VK_IMAGE_ASPECT_DEPTH_BIT, 1, &vkimageview_depth)

	SMPT_RD_VK_IMmMAKE
	(
		SMPT_RD_VKQuGP,
		vksurfaceformatkhr.format,
		((VkExtent3D)
		{
			.width = smpt_rd_vk_swcVet2d.width,
			.height = smpt_rd_vk_swcVet2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		Pinfo->Usample_count,
		&vkimage_color
	)
	SMPT_RD_VK_IMmGEN(SMPT_RD_VKQuGP, vkimage_color, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_color, vkmemoryrequirements)
	if (smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Usample_count != VK_SAMPLE_COUNT_1_BIT)
		SMPT_RD_VK_IMVmMAKE(SMPT_RD_VKQuGP, vkimage_color, vksurfaceformatkhr.format, VK_IMAGE_ASPECT_COLOR_BIT, 1, &vkimageview_color)

	for (uint32_t i = 0; i < Uimage; ++i)
	{
		SMPT_RD_VK_IMVmMAKE(SMPT_RD_VKQuGP, smpt_rd_vk_swcPim[i], vksurfaceformatkhr.format, VK_IMAGE_ASPECT_COLOR_BIT, 1, &smpt_rd_vk_swcPimv[i])
		SMPT_RD_VK_FBFmMAKE
		(
			SMPT_RD_VKQuGP,
			smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Usample_count == VK_SAMPLE_COUNT_1_BIT ?
			((VkImageView[])
			{
				smpt_rd_vk_swcPimv[i],
				vkimageview_depth
			}) :
			((VkImageView[])
			{
				vkimageview_color,
				vkimageview_depth,
				smpt_rd_vk_swcPimv[i]
			}),
			smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Usample_count == VK_SAMPLE_COUNT_1_BIT ? 2 : 3,
			smpt_rd_vk_swcVrdp,
			&smpt_rd_vk_swcPfbf[i]
		)
	}
}

void smpt_rd_vk_swcMfree()
{
	VkDevice Vvkdevice = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;

	vkDestroyImageView(Vvkdevice, vkimageview_depth, NULL);
	vkDestroyImage(Vvkdevice, vkimage_depth, NULL);
	vkFreeMemory(Vvkdevice, vkdevicememory_depth, NULL);

	if (smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Usample_count != VK_SAMPLE_COUNT_1_BIT)
		vkDestroyImageView(Vvkdevice, vkimageview_color, NULL);
	vkDestroyImage(Vvkdevice, vkimage_color, NULL);
	vkFreeMemory(Vvkdevice, vkdevicememory_color, NULL);

	for (uint32_t i = 0; i < Uimage; ++i)
	{
		vkDestroyFramebuffer(Vvkdevice, smpt_rd_vk_swcPfbf[i], NULL);
		vkDestroyImageView(Vvkdevice, smpt_rd_vk_swcPimv[i], NULL);
	}

	vkDestroyRenderPass(Vvkdevice, smpt_rd_vk_swcVrdp, NULL);
	vkDestroySwapchainKHR(Vvkdevice, smpt_rd_vk_swcVkhr, NULL);

	free(smpt_rd_vk_swcPim);
	free(smpt_rd_vk_swcPimv);
	free(smpt_rd_vk_swcPfbf);
}
