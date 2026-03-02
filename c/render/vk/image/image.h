#ifndef SMPT_RD_VKhIM
	#define SMPT_RD_VKhIM

	/*mipmap 1
	vksamplecountflagbits VK_SAMPLE_COUNT_1_BIT
	vkimagetiling VK_IMAGE_TILING_OPTIMAL
	vkimagelayout VK_IMAGE_LAYOUT_UNDEFINED*/
	void smpt_rd_vk_imMmake(uint8_t Udevice, VkFormat Vvkformat, VkExtent3D Vvkextent3d, uint8_t Umipmap, VkImageTiling Vvkimagetiling, VkImageUsageFlags Vvkimageusageflags, VkImageLayout Vvkimagelayout, VkSampleCountFlagBits Vvksamplecountflagbits, VkImage *Pvkimage);

	//vkmemoryrequirements f
	void smpt_rd_vk_imMgen(uint8_t Udevice, VkImage Vvkimage, VkMemoryPropertyFlags Vvkmemorypropertyflags, VkDeviceMemory *Pvkdevicememory, VkMemoryRequirements Vvkmemoryrequirements);
#endif
