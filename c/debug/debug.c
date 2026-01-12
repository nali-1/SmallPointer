static mtx_t Vmtx_t;
static FILE *Pfile;

#ifdef SMPT_CM_TEST
	//.i check in one thread only
	static int Ierrno = 0;
	void smpt_dbMerrno()
	{
		if (errno != Ierrno)
		{
			SMPT_DBmN2L("errno %s", strerror(errno))
			Ierrno = errno;
		}
	}
#endif

void smpt_dbMset()
{
	int I0 = mtx_init(&Vmtx_t, mtx_plain);
	int I1 = mkdir(SMPTFcSAVE, S_IRUSR | S_IWUSR | S_IXUSR);
	int I2 = remove(SMPTFcSAVE_LOG);
	Pfile = fopen(SMPTFcSAVE_LOG, "ab");

	SMPT_DBmN2L("mtx_init %d", I0)
	SMPT_DBmN2L("mkdir %d", I1)
	SMPT_DBmN2L("remove %d", I2)
	SMPT_DBmN2L("fopen %p", Pfile)

	SMPT_DBmN2L("_SC_OPEN_MAX %ld", sysconf(_SC_OPEN_MAX))

	#ifdef SMPT_CM_DEBUG
		char *Pcwd;
		SMPT_DBmN2L("PATH_MAX %d", PATH_MAX)
		SMPT_DBmN2L("getcwd %p", Pcwd = getcwd(NULL, PATH_MAX))
		SMPT_DBmN2L("cwd_p %s", Pcwd)
		free(Pcwd);
	#endif

	SMPT_DBmN2L("__BYTE_ORDER %d", __BYTE_ORDER)
}

static char Pc[1024 * 10];
void smpt_dbMwrite(const char *Pformat, ...)
{
	mtx_lock(&Vmtx_t);

	va_list Vlist;
	va_start(Vlist, Pformat);
	uint64_t I0 = (uint64_t)vsnprintf(Pc, sizeof(Pc), Pformat, Vlist);
	va_end(Vlist);

	fwrite(Pc, 1, I0, Pfile);
	fwrite("\n", 1, 1, Pfile);

	//force write
	fflush(Pfile);
	mtx_unlock(&Vmtx_t);
}

void smpt_dbMfree()
{
	mtx_destroy(&Vmtx_t);
	fclose(Pfile);
}
