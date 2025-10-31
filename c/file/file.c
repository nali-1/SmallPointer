void *smptfMread(const char *Pc, uint32_t *Pl)
{
	#ifdef SMPT_CM_ST_ANDROID
		AAssetManager *Paassetmanager = smpt_arPnative_activity->assetManager;
		AAsset *Paasset = AAssetManager_open(Paassetmanager, Pc, AASSET_MODE_BUFFER);
		*Pl = AAsset_getLength(Paasset);
		const void *Pdata = AAsset_getBuffer(Paasset);

		void *P = malloc(*Pl);
		memcpy(P, Pdata, *Pl);

		AAsset_close(Paasset);

		return P;
	#else
		FILE *Pfile = fopen(Pc, "rb");
		SMPT_DBmN2L("fopen %p", Pfile)
		return smptfMread1(Pfile, Pl);
	#endif
}

void *smptfMread1(FILE *Pfile, uint32_t *Pl)
{
	SMPT_DBmR2L("fseek %d", fseek(Pfile, 0, SEEK_END))
	SMPT_DBmR2L("ftell %d", *Pl = ftell(Pfile))
	SMPT_DBmR2L("fseek %d", fseek(Pfile, 0, SEEK_SET))

	void *P = malloc(*Pl);
	SMPT_DBmR2L("fread %ld", fread(P, *Pl, 1, Pfile))

	SMPT_DBmR2L("fclose %d", fclose(Pfile))

	return P;
}
