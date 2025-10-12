static mtx_t *Pmtx_t = &(mtx_t){};
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
	int I0 = mtx_init(Pmtx_t, mtx_plain);
	int I1 = mkdir(SMPTFcSAVE, S_IRUSR | S_IWUSR | S_IXUSR);
	int I2 = remove(SMPTFcSAVE_LOG);
	Pfile = fopen(SMPTFcSAVE_LOG, "ab");

	SMPT_DBmN2L("mtx_init %d", I0)
	SMPT_DBmN2L("mkdir %d", I1)
	SMPT_DBmN2L("remove %d", I2)
	SMPT_DBmN2L("fopen %p", Pfile)

	SMPT_DBmN2L("_SC_OPEN_MAX %ld", sysconf(_SC_OPEN_MAX))

	char Pcwd[PATH_MAX];
	SMPT_DBmN2L("getcwd %p", getcwd(Pcwd, sizeof(Pcwd)))
	SMPT_DBmN2L("cwd_p %s", Pcwd)

	SMPT_DBmN2L("__BYTE_ORDER %d", __BYTE_ORDER)
}

void smpt_dbMwrite(const char *Pformat, ...)
{
	mtx_lock(Pmtx_t);

	char Pc[1024];
	va_list Vlist;
	va_start(Vlist, Pformat);
	int I0 = vsnprintf(Pc, sizeof(Pc), Pformat, Vlist);
	va_end(Vlist);

	fwrite(Pc, 1, I0, Pfile);
	fwrite("\n", 1, 1, Pfile);

	//force write
	fflush(Pfile);
	mtx_unlock(Pmtx_t);
}

void smpt_dbMfree()
{
	mtx_destroy(Pmtx_t);
	fclose(Pfile);
}
