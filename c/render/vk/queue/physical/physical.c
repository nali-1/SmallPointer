void smpt_rd_vkq_pscMset()
{
	SMPT_DBmR2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(smpt_rd_vkqVit, &smpt_rd_vkqLinfo, VK_NULL_HANDLE))
	SMPT_DBmN2L("smpt_rd_vkqLinfo %d", smpt_rd_vkqLinfo)
	VkPhysicalDevice *Pvkphysicaldevice = malloc(sizeof(VkPhysicalDevice) * smpt_rd_vkqLinfo);
	SMPT_DBmR2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(smpt_rd_vkqVit, &smpt_rd_vkqLinfo, Pvkphysicaldevice))

	smpt_rd_vkqPinfo = malloc(sizeof(struct SMPT_RD_VKQsINFO) * smpt_rd_vkqLinfo);
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + l0;
		Pinfo->Vvkphysicaldevice = Pvkphysicaldevice[l0];

		#ifdef SMPT_CM_DEBUG
			VkPhysicalDeviceFeatures vkphysicaldevicefeatures;
			vkGetPhysicalDeviceFeatures(Pvkphysicaldevice[l0], &vkphysicaldevicefeatures);
			SMPT_DBmN2L("samplerAnisotropy %d", vkphysicaldevicefeatures.samplerAnisotropy)

			uint32_t Lvkextensionproperties = 0;
			SMPT_DBmR2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(Pvkphysicaldevice[l0], VK_NULL_HANDLE, &Lvkextensionproperties, VK_NULL_HANDLE))
			VkExtensionProperties *Pvkextensionproperties = malloc(Lvkextensionproperties * sizeof(VkExtensionProperties));
			SMPT_DBmR2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(Pvkphysicaldevice[l0], VK_NULL_HANDLE, &Lvkextensionproperties, Pvkextensionproperties))

			SMPT_DBmN2L("Lvkextensionproperties %d", Lvkextensionproperties)
			for (uint32_t x = 0; x < Lvkextensionproperties; ++x)
			{
				VkExtensionProperties vkextensionproperties = Pvkextensionproperties[x];
				SMPT_DBmN2L("extensionName %s", vkextensionproperties.extensionName)
			}

			free(Pvkextensionproperties);
		#endif

		VkPhysicalDeviceProperties vkphysicaldeviceproperties;
		vkGetPhysicalDeviceProperties(Pvkphysicaldevice[l0], &vkphysicaldeviceproperties);
		SMPT_DBmN2L("Name %s", vkphysicaldeviceproperties.deviceName)
		SMPT_DBmN2L
		(
			"Vulkan MAJOR MINOR PATCH %d.%d.%d",
			VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
			VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
			VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
		)
		SMPT_DBmN2L("maxUniformBufferRange %d", vkphysicaldeviceproperties.limits.maxUniformBufferRange)
		SMPT_DBmN2L("maxPerStageDescriptorUniformBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorUniformBuffers)
		SMPT_DBmN2L("maxDescriptorSetUniformBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetUniformBuffers)
		SMPT_DBmN2L("maxStorageBufferRange %d", vkphysicaldeviceproperties.limits.maxStorageBufferRange)
		SMPT_DBmN2L("maxPerStageDescriptorStorageBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorStorageBuffers)
		SMPT_DBmN2L("maxDescriptorSetStorageBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetStorageBuffers)

		SMPT_DBmN2L("maxPerStageResources %d", vkphysicaldeviceproperties.limits.maxPerStageResources)

		SMPT_DBmR2L("maxSamplerAnisotropy %f", Pinfo->Fmax_sampler_anisotropy = vkphysicaldeviceproperties.limits.maxSamplerAnisotropy)

		SMPT_DBmR2L("framebufferColorSampleCounts %d", Pinfo->Usample_count = vkphysicaldeviceproperties.limits.framebufferColorSampleCounts)
		SMPT_DBmN2L("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts)
		Pinfo->Usample_count &= vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts;

		if (Pinfo->Usample_count & VK_SAMPLE_COUNT_64_BIT)
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_64_BIT;
		}
		else if (Pinfo->Usample_count & VK_SAMPLE_COUNT_32_BIT)
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_32_BIT;
		}
		else if (Pinfo->Usample_count & VK_SAMPLE_COUNT_16_BIT)
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_16_BIT;
		}
		else if (Pinfo->Usample_count & VK_SAMPLE_COUNT_8_BIT)
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_8_BIT;
		}
		else if (Pinfo->Usample_count & VK_SAMPLE_COUNT_4_BIT)
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_4_BIT;
		}
		else if (Pinfo->Usample_count & VK_SAMPLE_COUNT_2_BIT)
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_2_BIT;
		}
		else
		{
			Pinfo->Usample_count = VK_SAMPLE_COUNT_1_BIT;
		}
		//! config
		Pinfo->Usample_count = VK_SAMPLE_COUNT_1_BIT;

		SMPT_DBmR2L("nonCoherentAtomSize %d", Pinfo->Unon_coherent_atom_size = vkphysicaldeviceproperties.limits.nonCoherentAtomSize)
		SMPT_DBmR2L("minUniformBufferOffsetAlignment %d", Pinfo->Umin_uniform_buffer_offset_alignment = vkphysicaldeviceproperties.limits.minUniformBufferOffsetAlignment)
	}

	free(Pvkphysicaldevice);
}

void smpt_rd_vkq_pscMfree()
{
	free(smpt_rd_vkqPinfo);
}
