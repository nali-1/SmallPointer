void smptgMsend()
{
	struct timespec Stimespec_s, Stimespec_e;
	clock_gettime(CLOCK_MONOTONIC, &Stimespec_s);

	SMPT_DBmR2L("mkdir %d", mkdir(SMPTFcHOME, S_IRUSR | S_IWUSR | S_IXUSR))
	remove(SMPTFcHOME_ASSET);

	#ifdef SMPT_CM_MAIN
		smptg_mdMo_send();
	#endif
	smptg_kfMsend();
	smptg_mdMm_send();

	clock_gettime(CLOCK_MONOTONIC, &Stimespec_e);
	SMPT_DBmW2L("smptgMsend %f", (double)Stimespec_e.tv_sec + (double)Stimespec_e.tv_nsec / 1e9 - (double)Stimespec_s.tv_sec - (double)Stimespec_s.tv_nsec / 1e9)
}
