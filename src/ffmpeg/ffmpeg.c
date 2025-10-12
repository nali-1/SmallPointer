static AVFormatContext *avformatcontext_p = NULL;
static AVCodecContext *avcodeccontext_p = NULL;
static AVFrame *avframe_p = NULL;
static AVPacket avpacket;
// static struct SwsContext *swscontext = NULL;
//static int video_stream_index = -1;

void ffmpeg_read(const char *filename)
{
	SMPT_DBmR2L("avformat_network_init %d", avformat_network_init())

	#ifdef SMPT_CM_ST_ANDROID
		uint32_t data_bl;
		uint8_t *data_p = smptfMread(filename, &data_bl);
		FILE *file_p = fopen(SMPTFcREAD_CACHE, "wb");
		fwrite(data_p, data_bl, 1, file_p);
		fclose(file_p);
		free(data_p);
		SMPT_DBmR2L("avformat_open_input %d", avformat_open_input(&avformatcontext_p, SMPTFcREAD_CACHE, NULL, NULL))
	#else
		SMPT_DBmR2L("avformat_open_input %d", avformat_open_input(&avformatcontext_p, filename, NULL, NULL))
	#endif

	#ifdef SMPT_CM_ST_ANDROID
		remove(SMPTFcREAD_CACHE);
	#endif

	SMPT_DBmR2L("avformat_find_stream_info %d", avformat_find_stream_info(avformatcontext_p, NULL))

	SMPT_DBmR2L("av_frame_alloc %p", avframe_p = av_frame_alloc())
}

uint8_t *ffmpeg_png(uint32_t *width_p, uint32_t *height_p)
{
	int video_stream_index;
	const AVCodec *avcodec_p;
	SMPT_DBmR2L("av_find_best_stream %d", video_stream_index = av_find_best_stream(avformatcontext_p, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0))

	SMPT_DBmR2L("avcodec_find_decoder %p", avcodec_p = avcodec_find_decoder(avformatcontext_p->streams[video_stream_index]->codecpar->codec_id))

	SMPT_DBmR2L("avcodec_alloc_context3 %p", avcodeccontext_p = avcodec_alloc_context3(avcodec_p))

	SMPT_DBmR2L("avcodec_parameters_to_context %d", avcodec_parameters_to_context(avcodeccontext_p, avformatcontext_p->streams[video_stream_index]->codecpar))

	SMPT_DBmR2L("avcodec_open2 %d", avcodec_open2(avcodeccontext_p, avcodec_p, NULL))


	SMPT_DBmR2L("av_read_frame %d", av_read_frame(avformatcontext_p, &avpacket))

	SMPT_DBmR2L("avcodec_send_packet %d", avcodec_send_packet(avcodeccontext_p, &avpacket))

	SMPT_DBmR2L("avcodec_receive_frame %d", avcodec_receive_frame(avcodeccontext_p, avframe_p))

	*width_p = avframe_p->width;
	*height_p = avframe_p->height;

	// uint8_t *data_p = (uint8_t *)malloc(avframe_p->width * avframe_p->height * 4);

	int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, avframe_p->width, avframe_p->height, 1);
	uint8_t *data_p = (uint8_t *)malloc(num_bytes);
	SMPT_DBmR2L("av_image_copy_to_buffer %d", av_image_copy_to_buffer(data_p, num_bytes, (const uint8_t * const *)avframe_p->data, avframe_p->linesize, AV_PIX_FMT_RGBA, avframe_p->width, avframe_p->height, 1))

	// data_p[0] = 255;
	// data_p[1] = 0;
	// data_p[2] = 0;
	// data_p[3] = 255;

	av_packet_unref(&avpacket);

	return data_p;
}

uint8_t *ffmpeg_ogg(int *sample_rate_p, int *nb_channels_p, uint32_t *data_bl)
{
	int stream_index;
	const AVCodec *avcodec_p = NULL;
	SMPT_DBmR2L("av_find_best_stream %d", stream_index = av_find_best_stream(avformatcontext_p, AVMEDIA_TYPE_AUDIO, -1, -1, &avcodec_p, 0))

	avcodeccontext_p = avcodec_alloc_context3(avcodec_p);
	avcodec_parameters_to_context(avcodeccontext_p, avformatcontext_p->streams[stream_index]->codecpar);
	avcodec_open2(avcodeccontext_p, avcodec_p, NULL);

	uint8_t *data_p = NULL;
	*data_bl = 0;
	while (av_read_frame(avformatcontext_p, &avpacket) >= 0)
	{
		if (avpacket.stream_index == stream_index)
			if (avcodec_send_packet(avcodeccontext_p, &avpacket) == 0)
				while (avcodec_receive_frame(avcodeccontext_p, avframe_p) == 0)
				{
					SwrContext *swrcontext_p = NULL;

					swr_alloc_set_opts2
					(
						&swrcontext_p,
						&avcodeccontext_p->ch_layout, AV_SAMPLE_FMT_S16, avcodeccontext_p->sample_rate,
						&avframe_p->ch_layout, AV_SAMPLE_FMT_FLTP, avcodeccontext_p->sample_rate,
						0, NULL
					);
					swr_init(swrcontext_p);

					int out_samples = av_rescale_rnd
					(
						swr_get_delay(swrcontext_p, avcodeccontext_p->sample_rate) + avframe_p->nb_samples,
						avcodeccontext_p->sample_rate,
						avcodeccontext_p->sample_rate,
						AV_ROUND_UP
					);

					uint8_t *out_data = NULL;
					int out_linesize = 0;

					av_samples_alloc
					(
						&out_data, &out_linesize,
						avcodeccontext_p->ch_layout.nb_channels,
						out_samples,
						AV_SAMPLE_FMT_S16, 0
					);

					int converted = swr_convert
					(
						swrcontext_p,
						&out_data, out_samples,
						(const uint8_t **)avframe_p->extended_data,
						avframe_p->nb_samples
					);

					int out_data_size = av_samples_get_buffer_size
					(
						NULL, avcodeccontext_p->ch_layout.nb_channels,
						converted,
						AV_SAMPLE_FMT_S16, 1
					);

					data_p = realloc(data_p, *data_bl + out_data_size);
					memcpy(data_p + *data_bl, out_data, out_data_size);
					*data_bl += out_data_size;

					av_freep(&out_data);

					*sample_rate_p = avframe_p->sample_rate;
					*nb_channels_p = avframe_p->ch_layout.nb_channels;

					swr_free(&swrcontext_p);
					break;
				}
		av_packet_unref(&avpacket);
	}
	return data_p;
}


void ffmpeg_free()
{
	av_frame_free(&avframe_p);
	avframe_p = NULL;
	avcodec_free_context(&avcodeccontext_p);
	avcodeccontext_p = NULL;
	avformat_close_input(&avformatcontext_p);
	avformatcontext_p = NULL;
}

// void decode()
// {
// 	if (av_read_frame(avformatcontext, &avpacket) < 0)
// 	{
// 		error("av_read_frame")
// 	}

// 	if (avpacket.stream_index == video_stream_index)
// 	{
// 		if (avcodec_send_packet(avcodeccontext, &avpacket) < 0)
// 		{
// 			error("avcodec_send_packet")
// 		}

// 		if (!avcodec_receive_frame(avcodeccontext, avframe))
// 		{
// 			swscontext = sws_getContext
// 			(
// 				avframe->width, avframe->height, avcodeccontext->pix_fmt,
// 				avframe->width, avframe->height, AV_PIX_FMT_RGBA,
// 				SWS_BICUBIC, NULL, NULL, NULL
// 			);

// 			AVFrame *rgbaFrame = av_frame_alloc();
// 			rgbaFrame->width = avframe->width;
// 			rgbaFrame->height = avframe->height;
// 			rgbaFrame->format = AV_PIX_FMT_RGBA;

// 			av_frame_get_buffer(rgbaFrame, 32);
// 			sws_scale(swscontext, (const uint8_t *const *)avframe->data, avframe->linesize, 0, avframe->height, rgbaFrame->data, rgbaFrame->linesize);
// 		}
// 	}

// 	av_packet_unref(&avpacket);
// }
