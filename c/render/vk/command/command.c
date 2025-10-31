//void vk_cmd(VkCommandBuffer vkcommandbuffer, VkCommandBufferBeginInfo *vkcommandbufferbegininfo_p, VkQueue vkqueue_graphic)
//{
//	// SMPT_DBmR2L("vkBeginCommandBuffer %d", vkBeginCommandBuffer(vkcommandbuffer, vkcommandbufferbegininfo_p))
//	// vk_cmdImage(vkcommandbuffer, vkqueue_graphic);
//	// SMPT_DBmR2L("vkEndCommandBuffer %d", vkEndCommandBuffer(vkcommandbuffer))
//	// SMPT_DBmR2L
//	// (
//	// 	"vkQueueSubmit %d",
//	// 	vkQueueSubmit
//	// 	(
//	// 		vkqueue_graphic,
//	// 		1,
//	// 		&(VkSubmitInfo)
//	// 		{
//	// 			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
//
//	// 			.commandBufferCount = 1,
//	// 			.pCommandBuffers = &vkcommandbuffer,
//
//	// 			.waitSemaphoreCount = 0,
//	// 			.pWaitSemaphores = VK_NULL_HANDLE,
//	// 			.pWaitDstStageMask = VK_NULL_HANDLE,
//
//	// 			.signalSemaphoreCount = 0,
//	// 			.pSignalSemaphores = VK_NULL_HANDLE,
//
//	// 			.pNext = VK_NULL_HANDLE
//	// 		},
//	// 		VK_NULL_HANDLE
//	// 	)
//	// )
//	// SMPT_DBmR2L("vkQueueWaitIdle %d", vkQueueWaitIdle(vkqueue_graphic))
//
//	// //s0-freeImage
//	// VkDevice vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];
//	// for (uint32_t i = 0; i < m_nali_g_max_image; ++i)
//	// {
//	// 	vkDestroyBuffer(vkdevice, m_nali_g_image_vkbuffer_p[i], VK_NULL_HANDLE);
//	// 	vkFreeMemory(vkdevice, m_nali_g_image_vkbuffer_vkdevicememory_p[i], VK_NULL_HANDLE);
//	// 	free(m_nali_g_image_uint8_t_p[i]);
//	// }
//
//	// free(m_nali_g_image_vkbuffer_p);
//	// free(m_nali_g_image_vkbuffer_vkdevicememory_p);
//	// free(m_nali_g_image_uint8_t_p);
//	// //e0-freeImage
//}
