#ifdef SMPT_CM_MAIN
	static VkPipelineLayout Vvkpipelinelayout_gp;
	static VkPipelineLayout Vvkpipelinelayout_cp;
	static VkPipeline Vvkpipeline_gp;
	static VkPipeline Vvkpipeline_cp;

	static VkFence *Pvkfence;
	static VkSemaphore *Pvksemaphore;

	static VkCommandBufferBeginInfo vkcommandbufferbegininfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pInheritanceInfo = NULL,

		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pNext = NULL
	};
	static VkClearValue Pvkclearvalue[2] =
	{
		{
			.color =
			{
				.float32 = {0.0F, 0.0F, 0.0F, 1.0F}
			}
		},
		{
			.depthStencil =
			{
				.depth = 1.0F,
				.stencil = 0.0F
			}
		}
	};
	static VkRenderPassBeginInfo vkrenderpassbegininfo =
	{
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderArea.offset = {0, 0},
		.clearValueCount = 2,
		.pClearValues = Pvkclearvalue,

		.pNext = NULL
	};
	static VkViewport vkviewport =
	{
		.x = 0.0F,
		.y = 0.0F,
		.minDepth = 0.0F,
		.maxDepth = 1.0F
	};
	static VkRect2D vkrect2d =
	{
		.offset = {0, 0}
	};
	static VkSubmitInfo image_vksubmitinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitDstStageMask = (VkPipelineStageFlags[]){VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
		.commandBufferCount = 1,
		.signalSemaphoreCount = 1,

		.pNext = NULL
	};
	static VkPresentInfoKHR vkpresentinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,

		.swapchainCount = 1,
		.pSwapchains = &smpt_rd_vk_swcVkhr,

		.pResults = NULL,
		.pNext = NULL
	};

	static void Mset_semaphore(VkDevice Vvkdevice)
	{
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
			for (uint8_t l1 = 0; l1 < 2; ++l1)
				smpt_rd_vk_smpMmake(SMPT_RD_VKQuGP, Pvksemaphore + l0 * 2 + l1);
	}
	static void Mfree_semaphore(VkDevice Vvkdevice)
	{
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
			for (uint8_t l1 = 0; l1 < 2; ++l1)
				vkDestroySemaphore(Vvkdevice, Pvksemaphore[l0 * 2 + l1], NULL);
	}
	static void Mre_sc()
	{
		const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;
		VkDevice Vvkdevice = Pinfo->Vvkdevice;

		vkQueueWaitIdle(Pinfo->Pvkqueue[smpt_rd_vkqUq_gp]);
		vkQueueWaitIdle(Pinfo->Pvkqueue[smpt_rd_vkqUq_sf]);

		smpt_rd_vk_swcMfree();

		#ifdef SMPT_CM_ST_ANDROID
			while (!smpt_sf_awdPnative_window)
			{
				smpt_sfUstate |= SMPT_SFuS_ANDROID_RE;
				thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
			}

			if (smpt_sfUstate & SMPT_SFuS_ANDROID_RE)
			{
				smpt_rd_vk_sfMfree();
				smpt_rd_vk_sfMmake();

				smpt_sfUstate &= 255 - SMPT_SFuS_ANDROID_RE;
			}
		#endif

		smpt_rd_vk_swcMset();

		vkrenderpassbegininfo.renderPass = smpt_rd_vk_swcVrdp;
		vkviewport.width = smpt_rd_vk_swcVet2d.width;
		vkviewport.height = smpt_rd_vk_swcVet2d.height;
		vkrenderpassbegininfo.renderArea.extent = smpt_rd_vk_swcVet2d;
		vkrect2d.extent = smpt_rd_vk_swcVet2d;

		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
		{
			smptm_m4x4Mp(smptr_ce_mdPbuffer_map[SMPTR_CE_MDuBUFFER_VP_P + l0] + sizeof(float) * 16);
			vkFlushMappedMemoryRanges(Vvkdevice, 1, &(VkMappedMemoryRange)
			{
				.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
				.memory = smptr_ce_mdPvkdevicememory[SMPTR_CE_MDuBUFFER_VP_P + l0],
				.offset = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, sizeof(float) * 16),
				.size = SMPT_RD_VKQmSIZE(SMPT_RD_VKQuGP, sizeof(float) * 16),
				.pNext = NULL
			});
		}
		smpt_sfUstate &= 0xFFu - SMPT_SFuS_RE;
	}

	//static VkSubmitInfo Vvksubmitinfo_cp =
	//{
	//	.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
	//	.waitSemaphoreCount = 0,
	//	.pWaitSemaphores = NULL,
	//	.pWaitDstStageMask = NULL,
	//	.commandBufferCount = 0,
	//	.pCommandBuffers = NULL,
	//	.signalSemaphoreCount = 0,
	//	.pSignalSemaphores = 0,
	//	.pNext = NULL
	//};
	//static VkMemoryBarrier2 Vvkmemorybarrier2 =
	//{
	//	.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2,
	//	.srcStageMask = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT,
	//	.srcAccessMask = VK_ACCESS_2_SHADER_WRITE_BIT,
	//	.dstStageMask = VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT,
	//	.dstAccessMask = VK_ACCESS_2_SHADER_READ_BIT,
	//	.pNext = NULL
	//};
	//static VkDependencyInfo Vvkdependencyinfo =
	//{
	//	.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
	//	.memoryBarrierCount = 1,
	//	.pMemoryBarriers = &Vvkmemorybarrier2,
	//	.bufferMemoryBarrierCount = 0,
	//	.pBufferMemoryBarriers = NULL,
	//	.imageMemoryBarrierCount = 0,
	//	.pImageMemoryBarriers = NULL,
	//	.dependencyFlags = 0
	//	.pNext = NULL
	//};
	//static void Mcp(VkDevice Vvkdevice, VkCommandBuffer Vvkcommandbuffer)
	//{
	//	vkCmdBindPipeline(Vvkcommandbuffer, VK_PIPELINE_BIND_POINT_COMPUTE, Vvkpipeline_gp);
	//
	//	vkCmdBindDescriptorSets(Vvkcommandbuffer, VK_PIPELINE_BIND_POINT_COMPUTE, Vvkpipelinelayout_cp, 0, 1, smptr_ceaPvkdescriptorset + smpt_rd_vk_swcUframe_buffer, 0, NULL);
	//
	//	vkCmdDispatch(Vvkcommandbuffer, 1, 1, 1);
	//	vkQueueSubmit(Pinfo->Pvkqueue[smpt_rd_vkqUq_cp], 1, &Vvksubmitinfo_cp, VK_NULL_HANDLE);
	//	vkCmdPipelineBarrier2(Vvkcommandbuffer, &Vvkdependencyinfo);
	//}

	static int Mloop(void *P)
	{
		#ifdef SMPT_CM_DEBUG
			struct timespec frame_start = {0}, frame_end;
			uint32_t frame = 0;
			double frame_time = 0;
		#endif

		const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;
		VkDevice Vvkdevice = Pinfo->Vvkdevice;

		smpt_sfUstate |= SMPT_SFuS_RENDER;
		VkCommandBuffer Vvkcommandbuffer;
		while (!(smpt_sfUstate & SMPT_SFuS_EXIT))
		{
			Vvkcommandbuffer = Pinfo->Pvkcommandbuffer[smpt_rd_vk_swcUframe];

			smpt_rd_vk_swcUframe_buffer = (smpt_rd_vk_swcUframe_buffer + 1) % smpt_rd_vk_swcUimage;

			smptr_ceMloop();

			vkWaitForFences(Vvkdevice, 1, Pvkfence + smpt_rd_vk_swcUframe, VK_TRUE, UINT64_MAX);

			image_vksubmitinfo.pCommandBuffers = &Vvkcommandbuffer;

			image_vksubmitinfo.pWaitSemaphores = Pvksemaphore + smpt_rd_vk_swcUframe * 2;
			image_vksubmitinfo.pSignalSemaphores = Pvksemaphore + smpt_rd_vk_swcUframe * 2 + 1;

			vkpresentinfokhr.pWaitSemaphores = Pvksemaphore + smpt_rd_vk_swcUframe * 2 + 1;

			if (smpt_sfUstate & SMPT_SFuS_RE)
			{
				SMPT_DBmN2L("SMPT_SFuS_RE")
				Mre_sc();
				#ifdef SMPT_CM_ST_ANDROID
					uint32_t image_index;
					VkResult vkresult = vkAcquireNextImageKHR(Vvkdevice, smpt_rd_vk_swcVkhr, UINT64_MAX, Pvksemaphore[smpt_rd_vk_swcUframe * 2], VK_NULL_HANDLE, &image_index);
					smpt_rd_vk_swcUframe = (smpt_rd_vk_swcUframe + 1) % smpt_rd_vk_swcUimage;
					Mfree_semaphore(Vvkdevice);
					Mset_semaphore(Vvkdevice);
					continue;
				#endif
			}

			uint32_t image_index;
			VkResult vkresult = vkAcquireNextImageKHR(Vvkdevice, smpt_rd_vk_swcVkhr, UINT64_MAX, Pvksemaphore[smpt_rd_vk_swcUframe * 2], VK_NULL_HANDLE, &image_index);
			if (vkresult != VK_SUCCESS)
			{
				SMPT_DBmN2L("vkAcquireNextImageKHR %d", vkresult)
				Mre_sc();
				smpt_rd_vk_swcUframe = (smpt_rd_vk_swcUframe + 1) % smpt_rd_vk_swcUimage;
				Mfree_semaphore(Vvkdevice);
				Mset_semaphore(Vvkdevice);
				continue;
			}
			else
			{
				vkResetFences(Vvkdevice, 1, &Pvkfence[smpt_rd_vk_swcUframe]);
			}

			vkrenderpassbegininfo.framebuffer = smpt_rd_vk_swcPfbf[image_index];
			vkpresentinfokhr.pImageIndices = &image_index;

			vkBeginCommandBuffer(Vvkcommandbuffer, &vkcommandbufferbegininfo);

				vkCmdBeginRenderPass(Vvkcommandbuffer, &vkrenderpassbegininfo, VK_SUBPASS_CONTENTS_INLINE);

					vkCmdBindPipeline(Vvkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Vvkpipeline_gp);

					vkCmdSetViewport(Vvkcommandbuffer, 0, 1, &vkviewport);
					vkCmdSetScissor(Vvkcommandbuffer, 0, 1, &vkrect2d);

					for (uint32_t l0 = 0; l0 < smptr_cemLm; ++l0)
					{
						struct SMPTR_CEMsM Sm = smptr_cemPm[l0];

						if (Sm.Us & SMPTR_CEMuM_A)
						{
							vkCmdBindDescriptorSets(Vvkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Vvkpipelinelayout_gp, 0, 1, smptr_ceaPvkdescriptorset + smpt_rd_vk_swcUframe_buffer, 0, NULL);

							//! free size
							VkDeviceSize Loffset = 0;
							vkCmdBindVertexBuffers(Vvkcommandbuffer, 0, 1, &smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_A + Sm.Ui], &Loffset);
							//.i a to Lv
							vkCmdDraw(Vvkcommandbuffer, Sm.Ua, 1, 0, 0);
						}
						else
						{
							vkCmdBindDescriptorSets(Vvkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Vvkpipelinelayout_gp, 0, 1, smptr_cemPvkdescriptorset + Sm.Ui * smpt_rd_vk_swcUimage + smpt_rd_vk_swcUframe_buffer, 0, NULL);

							vkCmdBindVertexBuffers(Vvkcommandbuffer, 0, 1, &smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M], &SMPTR_CE_MDuA);
							vkCmdBindIndexBuffer
							(
								Vvkcommandbuffer,
								smptr_ce_mdPvkbuffer[SMPTR_CE_MDuBUFFER_M],
								smptr_ce_mdPli[Sm.Ua],
								#if SMPTRuI == 4
									VK_INDEX_TYPE_UINT32
								#elif SMPTRuI == 2
									VK_INDEX_TYPE_UINT16
								#elif SMPTRuI == 1
									VK_INDEX_TYPE_UINT8
								#endif
							);
							vkCmdDrawIndexed(Vvkcommandbuffer, smptr_ce_mdPic[Sm.Ua], 1, 0, 0, 0);
						}
					}

				vkCmdEndRenderPass(Vvkcommandbuffer);

			vkEndCommandBuffer(Vvkcommandbuffer);

			vkQueueSubmit(Pinfo->Pvkqueue[smpt_rd_vkqUq_gp], 1, &image_vksubmitinfo, Pvkfence[smpt_rd_vk_swcUframe]);
			vkQueuePresentKHR(Pinfo->Pvkqueue[smpt_rd_vkqUq_sf], &vkpresentinfokhr);

			smpt_rd_vk_swcUframe = (smpt_rd_vk_swcUframe + 1) % smpt_rd_vk_swcUimage;

			#ifdef SMPT_CM_DEBUG
				++frame;
				clock_gettime(CLOCK_MONOTONIC, &frame_end);
				frame_time = frame_end.tv_sec + (double)frame_end.tv_nsec / 1e9 - frame_start.tv_sec - (double)frame_start.tv_nsec / 1e9;
				if (frame_time >= 1.0)
				{
					frame_start = frame_end;
					SMPT_DBmN2L("time %f", frame_time)
					SMPT_DBmN2L("frame %d", frame)
					frame = 0;
				}
			#endif
		}
		smpt_sfUstate |= SMPT_SFuS_EXIT_RENDER;

		return 0;
	}

	void smpt_rd_vk_cmdMset()
	{
		const struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + SMPT_RD_VKQuGP;
		VkDevice Vvkdevice = Pinfo->Vvkdevice;

		VkShaderModule Pvkshadermodule[3];
		VkPipelineShaderStageCreateInfo Pvkpipelineshaderstagecreateinfo[3];
		smpt_rd_vk_pl_sdMgp(SMPT_RD_VKQuGP, Pvkshadermodule, Pvkpipelineshaderstagecreateinfo);
		SMPT_RD_VK_PL_LOmMAKE(SMPT_RD_VKQuGP, SMPT_RD_VKW_DSTSuGP, &Vvkpipelinelayout_gp)
		smpt_rd_vk_plMmake(SMPT_RD_VKQuGP, Pvkpipelineshaderstagecreateinfo, smpt_rd_vk_swcVrdp, Vvkpipelinelayout_gp, &Vvkpipeline_gp);

		smpt_rd_vk_pl_sdMcp(SMPT_RD_VKQuCP, Pvkshadermodule + 2, Pvkpipelineshaderstagecreateinfo + 2);
		SMPT_RD_VK_PL_LOmMAKE(SMPT_RD_VKQuCP, SMPT_RD_VKW_DSTSuCP, &Vvkpipelinelayout_cp)
		smpt_rd_vk_plMmake_comp(SMPT_RD_VKQuCP, Pvkpipelineshaderstagecreateinfo + 2, Vvkpipelinelayout_cp, &Vvkpipeline_cp);
		for (uint8_t U0 = 0; U0 < 2; ++U0)
			vkDestroyShaderModule(Vvkdevice, Pvkshadermodule[U0], NULL);
		vkDestroyShaderModule(smpt_rd_vkqPinfo[SMPT_RD_VKQuCP].Vvkdevice, Pvkshadermodule[2], NULL);

		Pvkfence = malloc(sizeof(VkFence) * smpt_rd_vk_swcUimage);
		Pvksemaphore = malloc(sizeof(VkSemaphore) * smpt_rd_vk_swcUimage * 2);
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
		{
			//! check
			//vk_cmd(Pvkcommandbuffer[l0], &vkcommandbufferbegininfo, vkqueue_graphic);

			smpt_rd_vkfMmake(SMPT_RD_VKQuGP, Pvkfence + l0);
		}
		Mset_semaphore(Vvkdevice);

		vkrenderpassbegininfo.renderPass = smpt_rd_vk_swcVrdp;
		vkrenderpassbegininfo.renderArea.extent = smpt_rd_vk_swcVet2d;

		vkviewport.width = smpt_rd_vk_swcVet2d.width;
		vkviewport.height = smpt_rd_vk_swcVet2d.height;

		vkrect2d.extent = smpt_rd_vk_swcVet2d;

		smptrMfree0();
		SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, Mloop, NULL))
	}

	void smpt_rd_vk_cmdMfree()
	{
		VkDevice Vvkdevice_gp = smpt_rd_vkqPinfo[SMPT_RD_VKQuGP].Vvkdevice;
		VkDevice Vvkdevice_cp = smpt_rd_vkqPinfo[SMPT_RD_VKQuCP].Vvkdevice;

		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
			vkDestroyFence(Vvkdevice_gp, Pvkfence[l0], NULL);
		Mfree_semaphore(Vvkdevice_gp);
		vkDestroyPipeline(Vvkdevice_gp, Vvkpipeline_gp, NULL);
		vkDestroyPipelineLayout(Vvkdevice_gp, Vvkpipelinelayout_gp, NULL);

		vkDestroyPipeline(Vvkdevice_cp, Vvkpipeline_cp, NULL);
		vkDestroyPipelineLayout(Vvkdevice_cp, Vvkpipelinelayout_cp, NULL);

		free(Pvkfence);
		free(Pvksemaphore);

		smpt_rd_vkMfree();
	}
#endif
