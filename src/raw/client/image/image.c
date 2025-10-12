// // static const uint16_t nali_g_index_uint16_t_array[] =
// // {
// // 	// 0, 1, 2
// // 	0, 1, 2,
// // 	2, 3, 0
// // };

// // static const float nali_g_data_float_array[] =
// // {
// // 	-1.0F, -1.0F, 0.0F, 0.0F,//bottom left
// // 	1.0F, -1.0F, 1.0F, 0.0F,//bottom right
// // 	1.0F,  1.0F, 1.0F, 1.0F,//top right
// // 	-1.0F,  1.0F, 0.0F, 1.0F//top left
// // };

// // void smptr_ceMsetVkVertexInputBindingDescription(VkVertexInputBindingDescription *vkvertexinputbindingdescription_p)
// // {
// // 	vkvertexinputbindingdescription_p[0] = (VkVertexInputBindingDescription)
// // 	{
// // 		.binding = 0,
// // 		.stride = sizeof(float) * 2 + sizeof(float) * 2,
// // 		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
// // 	};
// // }
// // void smptr_ceMsetVkVertexInputAttributeDescription(VkVertexInputAttributeDescription *vkvertexinputattributedescription_p)
// // {
// // 	//VK_FORMAT_R8_UINT
// // 	vkvertexinputattributedescription_p[0] = (VkVertexInputAttributeDescription)
// // 	{
// // 		.binding = 0,
// // 		.location = 0,
// // 		.format = VK_FORMAT_R32G32_SFLOAT,
// // 		.offset = 0
// // 	};
// // 	vkvertexinputattributedescription_p[1] = (VkVertexInputAttributeDescription)
// // 	{
// // 		.binding = 0,
// // 		.location = 1,
// // 		// .format = VK_FORMAT_R32G32B32_SFLOAT,
// // 		.format = VK_FORMAT_R32G32_SFLOAT,
// // 		// .format = VK_FORMAT_R16G16_SINT,
// // 		.offset = sizeof(float) * 2
// // 	};
// // }

// // void smptr_ceMsetVkDescriptorSetLayout(VkDescriptorSetLayout *vkdescriptorsetlayout_p)
// // {
// // 	vk_makeDescriptorSetLayout
// // 	(
// // 		smpt_rd_vkUdevice,
// // 		(VkDescriptorSetLayoutBinding[])
// // 		{
// // 			{
// // 				.binding = 0,
// // 				.descriptorCount = 1,
// // 				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC
// // 				.pImmutableSamplers = VK_NULL_HANDLE,
// // 				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT//VK_SHADER_STAGE_VERTEX_BIT VK_SHADER_STAGE_FRAGMENT_BIT
// // 			},
// // 			{
// // 				.binding = 1,
// // 				.descriptorCount = 1,
// // 				//sampler VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
// // 				//image2d VK_DESCRIPTOR_TYPE_STORAGE_IMAGE
// // 				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
// // 				.pImmutableSamplers = VK_NULL_HANDLE,
// // 				.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
// // 			}
// // 		},
// // 		2,
// // 		vkdescriptorsetlayout_p
// // 	);
// // }
// // void smptr_ceMsetVkDescriptorPoolSize(VkDescriptorPoolSize *vkdescriptorpoolsize_p)
// // {
// // 	//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC
// // 	vkdescriptorpoolsize_p[0] = (VkDescriptorPoolSize)
// // 	{
// // 		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
// // 		.descriptorCount = 1
// // 	};
// // 	vkdescriptorpoolsize_p[1] = (VkDescriptorPoolSize)
// // 	{
// // 		//image2d
// // 		// .type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
// // 		//sampler
// // 		.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
// // 		.descriptorCount = 1
// // 	};
// // }
// // void smptr_ceMsetVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p)
// // {
// // 	*vkdescriptorbufferinfo_p = (VkDescriptorBufferInfo)
// // 	{
// // 		.buffer = m_nali_g_ubo_vkbuffer_p[0],
// // 		.offset = 0,
// // 		// .range = m_nali_g_ubo_vkdevicesize_p[0]
// // 		.range = sizeof(nali_v_uniform_float_array)
// // 	};
// // 	vk_setVkWriteDescriptorSet(smpt_rd_vkUdevice, 0, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);
// // 	*vkdescriptorimageinfo_p = (VkDescriptorImageInfo)
// // 	{
// // 		//sampler VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
// // 		//image2d VK_IMAGE_LAYOUT_GENERAL
// // 		.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
// // 		.imageView = m_nali_g_image_vkimageview_p[0],
// // 		.sampler = m_nali_g_image_vksampler_p[0]
// // 		// .sampler = VK_NULL_HANDLE
// // 	};
// // 	vk_setVkWriteDescriptorSet(smpt_rd_vkUdevice, 1, vkdescriptorimageinfo_p, VK_NULL_HANDLE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, vkdescriptorset, vkwritedescriptorset_p + 1);
// // 	// *vkdescriptorbufferinfo_p = (VkDescriptorBufferInfo)
// // 	// {
// // 	// 	.buffer = ,
// // 	// 	.offset = 0,
// // 	// 	.range = 
// // 	// };
// // 	// vk_setVkWriteDescriptorSet(smpt_rd_vkUdevice, 2, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);
// // }

// uint16_t m_nali_g_max_image;
// long m_nali_g_max_image_state;
// uint8_t *m_nali_g_image_state_uint8_t_p;
// uint8_t **m_nali_g_image_uint8_t_p;
// uint32_t *m_nali_g_image_wh_uint32_t_p;
// VkImage *m_nali_g_image_vkimage_p;
// VkImageView *m_nali_g_image_vkimageview_p;
// VkSampler *m_nali_g_image_vksampler_p;
// VkDeviceMemory *m_nali_g_image_vkimage_vkdevicememory_p;

// VkBuffer *m_nali_g_image_vkbuffer_p;
// VkDeviceMemory *m_nali_g_image_vkbuffer_vkdevicememory_p;

// static void init()
// {
// 	//s0-image
// 	m_nali_g_image_state_uint8_t_p = smptfMread(SMPTFcHOME "image.bin", &m_nali_g_max_image_state);
// 	m_nali_g_image_uint8_t_p = malloc(0);
// 	m_nali_g_image_wh_uint32_t_p = malloc(0);

// 	struct dirent *dirent_p;

// 	const char image_type[] = ".png";
// 	const char image_path[] = SMPTFcHOME_IMAGE;
// 	DIR *dir_p = opendir(image_path);
// 	SMPT_DBmN2L("opendir %p", dir_p)

// 	size_t name_index = sizeof(image_path)-1 + 1 + 1;
// 	char *image_file = malloc(name_index);
// 	strcpy(image_file, image_path);
// 	strcat(image_file, "/");

// 	// png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
// 	// png_infop info = png_create_info_struct(png);

// 	int16_t index;
// 	int16_t size = -1;
// 	uint32_t wh_index;
// 	uint8_t name_index_size;
// 	while ((dirent_p = readdir(dir_p)) != NULL)
// 	{
// 		if (dirent_p->d_type == DT_REG)
// 		{
// 			sscanf(dirent_p->d_name, "%hd", &index);
// 			if (size < index)
// 			{
// 				size = index;

// 				m_nali_g_max_image = size + 1;
// 				m_nali_g_image_uint8_t_p = realloc(m_nali_g_image_uint8_t_p, sizeof(uint8_t *) * m_nali_g_max_image);
// 				m_nali_g_image_wh_uint32_t_p = realloc(m_nali_g_image_wh_uint32_t_p, sizeof(uint32_t) * m_nali_g_max_image * 2);
// 			}
// 			name_index_size = name_index + M_LENGTH(index);
// 			image_file = realloc(image_file, name_index_size + sizeof(image_type)-1);
// 			sprintf(image_file + name_index - 1, "%u", index);
// 			image_file[name_index_size - 1] = '\0';
// 			strcat(image_file, image_type);

// 			wh_index = index * 2;

// 			// FILE *file_p = fopen(image_file, "rb");
// 			// SMPT_DBmN2L("file_p %p", file_p)
// 			// png_init_io(png, file_p);
// 			// png_read_info(png, info);

// 			// m_nali_g_image_wh_uint32_t_p[wh_index] = png_get_image_width(png, info);
// 			// png_uint_32 height = m_nali_g_image_wh_uint32_t_p[wh_index + 1] = png_get_image_height(png, info);
// 			// // png_byte color_type = png_get_color_type(png, info);
// 			// // png_byte bit_depth = png_get_bit_depth(png, info);

// 			// png_read_update_info(png, info);
// 			// png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
// 			// for (int y = 0; y < height; y++)
// 			// {
// 			// 	row_pointers[y] = malloc(png_get_rowbytes(png, info));
// 			// }

// 			// png_read_image(png, row_pointers);

// 			ffmpeg_read(image_file);
// 			m_nali_g_image_uint8_t_p[index] = ffmpeg_png(&m_nali_g_image_wh_uint32_t_p[wh_index], &m_nali_g_image_wh_uint32_t_p[wh_index + 1]);
// 			ffmpeg_clean();
// 		}
// 	}
// 	free(image_file);
// 	//e0-image
// }

// static void vk()
// {
// 	VkDeviceSize vkdevicesize;
// 	VkMemoryRequirements vkmemoryrequirements;
// 	void *data_p;
// 	//s0-image
// 	m_nali_g_image_vkimage_p = malloc(sizeof(VkImage) * m_nali_g_max_image);
// 	m_nali_g_image_vkimageview_p = malloc(sizeof(VkImageView) * m_nali_g_max_image);
// 	m_nali_g_image_vksampler_p = malloc(sizeof(VkSampler) * m_nali_g_max_image);
// 	m_nali_g_image_vkimage_vkdevicememory_p = malloc(sizeof(VkDeviceMemory) * m_nali_g_max_image);

// 	m_nali_g_image_vkbuffer_p = malloc(sizeof(VkBuffer) * m_nali_g_max_image);
// 	m_nali_g_image_vkbuffer_vkdevicememory_p = malloc(sizeof(VkDeviceMemory) * m_nali_g_max_image);

// 	uint32_t u2;
// 	uint32_t u2_1;
// 	uint8_t line;
// 	int vkimageusageflagbits = 0;
// 	for (uint16_t u = 0; u < m_nali_g_max_image; ++u)
// 	{
// 		u2 = u * 2;
// 		u2_1 = u2 + 1;

// 		uint8_t mipmap = 1;
// 		if (m_nali_g_image_state_uint8_t_p[u / (8/2)] & 1 << (u % (8/2)) * 2)
// 		{
// 			mipmap = M_MIPMAP(m_nali_g_image_wh_uint32_t_p[u2], m_nali_g_image_wh_uint32_t_p[u2_1]);
// 			vkimageusageflagbits = VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
// 		}
// 		line = m_nali_g_image_state_uint8_t_p[u / (8/2)] & 2 << (u % (8/2)) * 2;

// 		SMPT_RD_VK_IMmMAKE
// 		(
// 			smpt_rd_vkUdevice,
// 			SMPT_RD_VK_COLOR_FORMAT,
// 			((VkExtent3D)
// 			{
// 				.width = m_nali_g_image_wh_uint32_t_p[u2],
// 				.height = m_nali_g_image_wh_uint32_t_p[u2_1],
// 				.depth = 1
// 			}),
// 			mipmap,
// 			line ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL,
// 			//sampler
// 			vkimageusageflagbits | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
// 			//image2d
// 			// VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_STORAGE_BIT,
// 			VK_IMAGE_LAYOUT_UNDEFINED,
// 			VK_SAMPLE_COUNT_1_BIT,
// 			&m_nali_g_image_vkimage_p[u]
// 		)
// 		SMPT_RD_VK_IMmGEN(smpt_rd_vkUdevice, m_nali_g_image_vkimage_p[u], VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &m_nali_g_image_vkimage_vkdevicememory_p[u], vkmemoryrequirements)
// 		vkdevicesize = m_nali_g_image_wh_uint32_t_p[u2] * m_nali_g_image_wh_uint32_t_p[u2_1] * 4;
// 		// SMPT_RD_VK_BFmMAP(smpt_rd_vkUdevice, vkdevicesize, 0, m_nali_g_image_uint8_t_p[0], &m_nali_g_image_vkimage_vkdevicememory_p[0]);

// 		SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, vkdevicesize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_image_vkbuffer_p[u], m_nali_g_image_vkbuffer_vkdevicememory_p[u], vkmemoryrequirements)
// 		SMPT_RD_VK_BFmMAP(smpt_rd_vkUdevice, vkdevicesize, m_nali_g_image_uint8_t_p[u], &m_nali_g_image_vkbuffer_vkdevicememory_p[u], data_p)

// 		SMPT_RD_VK_IMVmMAKE(smpt_rd_vkUdevice, m_nali_g_image_vkimage_p[u], SMPT_RD_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, mipmap, &m_nali_g_image_vkimageview_p[u])
// 		SMPT_RD_VK_SPmMAKE(smpt_rd_vkUdevice, mipmap, line, &m_nali_g_image_vksampler_p[u])

// 		// info("&m_nali_g_image_vkbuffer_p[0] %p", &m_nali_g_image_vkbuffer_p[0]);
// 		// info("&m_nali_g_image_vkbuffer_vkdevicememory_p[0] %p", &m_nali_g_image_vkbuffer_vkdevicememory_p[0]);
// 	}
// 	//e0-image
// }

// static void clear(uint32_t device)
// {
// 	VkDevice vkdevice = smpt_rd_vkq_dvP[device];

// 	//s0-image
// 	for (uint32_t i = 0; i < m_nali_g_max_image; ++i)
// 	{
// 		vkDestroySampler(vkdevice, m_nali_g_image_vksampler_p[i], VK_NULL_HANDLE);
// 		vkDestroyImageView(vkdevice, m_nali_g_image_vkimageview_p[i], VK_NULL_HANDLE);
// 		vkDestroyImage(vkdevice, m_nali_g_image_vkimage_p[i], VK_NULL_HANDLE);
// 		vkFreeMemory(vkdevice, m_nali_g_image_vkimage_vkdevicememory_p[i], VK_NULL_HANDLE);

// 		// vkDestroyBuffer(vkdevice, m_nali_g_image_vkbuffer_p[i], VK_NULL_HANDLE);
// 		// vkFreeMemory(vkdevice, m_nali_g_image_vkbuffer_vkdevicememory_p[i], VK_NULL_HANDLE);

// 		// free(m_nali_g_image_uint8_t_p[i]);
// 	}
// 	free(m_nali_g_image_state_uint8_t_p);
// 	// free(m_nali_g_image_uint8_t_p);
// 	free(m_nali_g_image_wh_uint32_t_p);
// 	free(m_nali_g_image_vkimage_p);
// 	free(m_nali_g_image_vkimageview_p);
// 	free(m_nali_g_image_vksampler_p);
// 	free(m_nali_g_image_vkimage_vkdevicememory_p);

// 	// free(m_nali_g_image_vkbuffer_p);
// 	// free(m_nali_g_image_vkbuffer_vkdevicememory_p);
// 	//e0-image
// }
