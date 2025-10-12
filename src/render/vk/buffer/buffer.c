uint32_t smpt_rd_vk_bfMtype(uint32_t Udevice, uint32_t Utypefilter, VkMemoryPropertyFlags Uvkmemorypropertyflags)
{
	VkPhysicalDevice Vvkphysicaldevice = smpt_rd_vkqPinfo[Udevice].Vvkphysicaldevice;
	VkPhysicalDeviceMemoryProperties Vvkphysicaldevicememoryproperties;
	vkGetPhysicalDeviceMemoryProperties(Vvkphysicaldevice, &Vvkphysicaldevicememoryproperties);

	for (uint32_t t = 0; t < Vvkphysicaldevicememoryproperties.memoryTypeCount; ++t)
	{
		if ((Utypefilter & (1 << t)) && (Vvkphysicaldevicememoryproperties.memoryTypes[t].propertyFlags & Uvkmemorypropertyflags) == Uvkmemorypropertyflags)
		{
			return t;
		}
	}

	return 0;
}
