#ifndef SMPTRhSV
	#define SMPTRhSV

	struct SMPTR_SVtNET
	{
		uint8_t Pnet[SMPTRlNET];
		SMPTRtNET Lnet;
	};
	extern struct SMPTR_SVtNET smptr_svPnet[SMPT_NWlU];

	extern FILE *smptr_svPfile;
	extern uint8_t smptr_svUrw;

	void smptr_svMset();
	void smptr_svMsend(SMPT_NWtU u);
	void smptr_svMread(SMPT_NWtU u);
	int smptr_svMloop(void *P);
	void smptr_svMfread();
	void smptr_svMfsend();
	void smptr_svMfree();
#endif
