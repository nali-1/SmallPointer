// //vkCmdBlitImage vkCmdCopyImage VK_QUEUE_TRANSFER_BIT
// static void cmdMipmap(VkCommandBuffer vkcommandbuffer, VkImageMemoryBarrier *vkimagememorybarrier_p, VkImageBlit *vkimageblit_p, VkImage vkimage, uint32_t width, uint32_t height, uint32_t mipmap, VkFilter vkfilter)
// {
// 	uint32_t half_width = width;
// 	uint32_t half_height = height;

// 	for (uint32_t i = 1; i < mipmap; i++)
// 	{
// 		vkimagememorybarrier_p->subresourceRange.baseMipLevel = i - 1;
// 		vkimagememorybarrier_p->oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
// 		vkimagememorybarrier_p->newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
// 		vkimagememorybarrier_p->srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
// 		vkimagememorybarrier_p->dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

// 		vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, vkimagememorybarrier_p);

// 		vkimageblit_p->srcOffsets[1].x = half_width;
// 		vkimageblit_p->srcOffsets[1].y = half_height;
// 		vkimageblit_p->srcSubresource.mipLevel = i - 1;
// 		vkimageblit_p->dstOffsets[1].x = half_width > 1 ? half_width / 2 : 1;
// 		vkimageblit_p->dstOffsets[1].y = half_height > 1 ? half_height / 2 : 1;
// 		vkimageblit_p->dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
// 		vkimageblit_p->dstSubresource.mipLevel = i;

// 		vkCmdBlitImage(vkcommandbuffer, vkimage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, vkimage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, vkimageblit_p, vkfilter);

// 		vkimagememorybarrier_p->oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
// 		vkimagememorybarrier_p->newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
// 		vkimagememorybarrier_p->srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
// 		vkimagememorybarrier_p->dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

// 		vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, vkimagememorybarrier_p);

// 		half_width = half_width > 1 ? half_width / 2 : 1;
// 		half_height = half_height > 1 ? half_height / 2 : 1;
// 	}

// 	vkimagememorybarrier_p->subresourceRange.baseMipLevel = mipmap - 1;
// 	vkimagememorybarrier_p->oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
// 	vkimagememorybarrier_p->newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
// 	vkimagememorybarrier_p->srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
// 	vkimagememorybarrier_p->dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

// 	vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, vkimagememorybarrier_p);
// }

// void vk_cmdImage(VkCommandBuffer vkcommandbuffer, VkQueue vkqueue_graphic)
// {
// 	VkImageMemoryBarrier vkimagememorybarrier_array[3];
// 	vkimagememorybarrier_array[0] = (VkImageMemoryBarrier)
// 	{
// 		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
// 		.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
// 		.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
// 		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
// 		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,

// 		.subresourceRange = (VkImageSubresourceRange)
// 		{
// 			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
// 			.baseMipLevel = 0,
// 			// .levelCount = 1,
// 			.baseArrayLayer = 0,
// 			.layerCount = 1
// 		},

// 		.srcAccessMask = VK_ACCESS_NONE,
// 		.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,

// 		.pNext = VK_NULL_HANDLE
// 	};
// 	vkimagememorybarrier_array[1] = (VkImageMemoryBarrier)
// 	{
// 		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
// 		.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
// 		.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
// 		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
// 		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,

// 		.subresourceRange = (VkImageSubresourceRange)
// 		{
// 			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
// 			.baseMipLevel = 0,
// 			.levelCount = 1,
// 			.baseArrayLayer = 0,
// 			.layerCount = 1
// 		},

// 		.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
// 		.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,

// 		.pNext = VK_NULL_HANDLE
// 	};
// 	vkimagememorybarrier_array[2] = (VkImageMemoryBarrier)
// 	{
// 		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
// 		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
// 		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,

// 		.subresourceRange = (VkImageSubresourceRange)
// 		{
// 			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
// 			.levelCount = 1,
// 			.baseArrayLayer = 0,
// 			.layerCount = 1
// 		},

// 		.pNext = VK_NULL_HANDLE
// 	};
// 	VkImageBlit vkimageblit =
// 	{
// 		.srcOffsets[0] = (VkOffset3D){0, 0, 0},
// 		.srcOffsets[1].z = 1,
// 		.srcSubresource = (VkImageSubresourceLayers)
// 		{
// 			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
// 			.baseArrayLayer = 0,
// 			.layerCount = 1
// 		},
// 		.dstOffsets[0] = (VkOffset3D){0, 0, 0},
// 		.dstOffsets[1].z = 1,
// 		.dstSubresource = (VkImageSubresourceLayers)
// 		{
// 			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
// 			.baseArrayLayer = 0,
// 			.layerCount = 1
// 		},
// 	};

// 	VkBufferImageCopy vkbufferimagecopy =
// 	{
// 		.imageSubresource = (VkImageSubresourceLayers)
// 		{
// 			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
// 			.mipLevel = 0,
// 			.baseArrayLayer = 0,
// 			.layerCount = 1
// 		},
// 		.imageExtent = (VkExtent3D)
// 		{
// 			.depth = 1
// 		},
// 		.bufferOffset = 0,
// 		.bufferRowLength = 0,
// 		.bufferImageHeight = 0,
// 		.imageOffset = 0
// 	};

// 	for (uint16_t i = 0; i < m_nali_g_max_image; ++i)
// 	{
// 		uint32_t i2 = i * 2;
// 		uint32_t i2_1 = i2 + 1;

// 		vkimagememorybarrier_array[0].image = m_nali_g_image_vkimage_p[i];
// 		vkbufferimagecopy.imageExtent.width = m_nali_g_image_wh_uint32_t_p[i2];
// 		vkbufferimagecopy.imageExtent.height = m_nali_g_image_wh_uint32_t_p[i2_1];

// 		if (m_nali_g_image_state_uint8_t_p[i / (8/2)] & 1 << (i % (8/2)) * 2)
// 		{
// 			vkimagememorybarrier_array[0].subresourceRange.levelCount = M_MIPMAP(m_nali_g_image_wh_uint32_t_p[i2], m_nali_g_image_wh_uint32_t_p[i2_1]);
// 			vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, vkimagememorybarrier_array);
// 			vkCmdCopyBufferToImage(vkcommandbuffer, m_nali_g_image_vkbuffer_p[i], m_nali_g_image_vkimage_p[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vkbufferimagecopy);

// 			vkimagememorybarrier_array[2].image = m_nali_g_image_vkimage_p[i];
// 			cmdMipmap(vkcommandbuffer, &vkimagememorybarrier_array[2], &vkimageblit, m_nali_g_image_vkimage_p[i], m_nali_g_image_wh_uint32_t_p[i2], m_nali_g_image_wh_uint32_t_p[i2_1], vkimagememorybarrier_array[0].subresourceRange.levelCount, m_nali_g_image_state_uint8_t_p[i / (8/2)] & 2 << (i % (8/2)) * 2 ? VK_FILTER_LINEAR : VK_FILTER_NEAREST);
// 		}
// 		else
// 		{
// 			vkimagememorybarrier_array[0].subresourceRange.levelCount = 1;
// 			vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, vkimagememorybarrier_array);
// 			vkCmdCopyBufferToImage(vkcommandbuffer, m_nali_g_image_vkbuffer_p[i], m_nali_g_image_vkimage_p[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vkbufferimagecopy);

// 			vkimagememorybarrier_array[1].image = m_nali_g_image_vkimage_p[i];
// 			vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &vkimagememorybarrier_array[1]);
// 		}
// 	}
// }