//struct SMPTG_MDsJSON
//{
//	void *Pdata;
//	uint8_t Utype;
//	struct SMPTG_MDsJSON *Pjson;
//};
//struct SMPTG_MDsJSON *Pjson;
//
//static void Mjset()
//{
//	//! test
//	//! check math
//	uint32_t Ldata;
//	uint8_t
//		*Pdata = smptfMread(Pmf[U0], &Ldata);
//	//.i skip magic
//	char
//		*Pps = strstr(Pdata + 16, "\"generator\""),
//		*Ppe;
//	//.t read string
//	SMPT_DBmN2L("Pdata %p", Pdata)
//	SMPT_DBmN2L("Ldata %d", Ldata)
//	SMPT_DBmN2L("Pps %p", Pps)
//	if (Pps)
//	{
//		Pps = strchr(Pps, ':');
//		Pps = strchr(Pps, '\"') + 1;
//		SMPT_DBmN2L("Pps %p", Pps)
//		Ppe = strchr(Pps, '\"');
//		SMPT_DBmN2L("Ppe %p", Ppe)
//		char *Ptest = malloc(Ppe - Pps + 1);
//		memcpy(Ptest, Pps, Ppe - Pps);
//		Ptest[Ppe - Pps] = 0;
//		SMPT_DBmN2L("generator %s", Ptest)
//		free(Ptest);
//	}
//	free(Pdata);
//	while (1)
//	{
//		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
//	}
//}
