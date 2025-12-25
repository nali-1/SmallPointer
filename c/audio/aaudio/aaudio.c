static AAudioStreamBuilder *Paaudiostreambuilder;

static aaudio_data_callback_result_t Maaudiostream_datacallback(AAudioStream* _Nonnull stream, void* _Nullable userData, void* _Nonnull audioData, int32_t numFrames)
{
	smpt_adoMgen((float *)audioData, numFrames);
	return AAUDIO_CALLBACK_RESULT_CONTINUE;
}

static AAudioStream *Paaudiostream;
void smpt_ado_aadoMset()
{
	AAudio_createStreamBuilder(&Paaudiostreambuilder);
	AAudioStreamBuilder_setDirection(Paaudiostreambuilder, AAUDIO_DIRECTION_OUTPUT);
	AAudioStreamBuilder_setPerformanceMode(Paaudiostreambuilder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);
	AAudioStreamBuilder_setSharingMode(Paaudiostreambuilder, AAUDIO_SHARING_MODE_EXCLUSIVE);
	AAudioStreamBuilder_setFormat(Paaudiostreambuilder, AAUDIO_FORMAT_PCM_FLOAT);
	AAudioStreamBuilder_setChannelCount(Paaudiostreambuilder, SMPT_ADOuCHANNEL_COUNT);
	AAudioStreamBuilder_setSampleRate(Paaudiostreambuilder, SMPT_ADOfSAMPLE_RATE);
	AAudioStreamBuilder_setDataCallback(Paaudiostreambuilder, Maaudiostream_datacallback, NULL);
	AAudioStreamBuilder_openStream(Paaudiostreambuilder, &Paaudiostream);
	AAudioStreamBuilder_delete(Paaudiostreambuilder);
	AAudioStream_requestStart(Paaudiostream);
}

void smpt_ado_aadoMfree()
{
	AAudioStream_requestStop(Paaudiostream);
	AAudioStream_close(Paaudiostream);
}
