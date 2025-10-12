#ifndef SMPTRhSVU
	#define SMPTRhSVU

	extern struct SMPTRsU smptr_svuSu[SMPT_NWlU];
	extern uint8_t *smptr_svuPm[SMPT_NWlU];

	void smptr_svuMset();
	void smptr_svuMloop();
	void smptr_svuMsend(SMPT_NWtU u);
	void smptr_svuMread(SMPT_NWtU u);
	void smptr_svuMfread();
	void smptr_svuMfsend();
	void smptr_svuMfree();
#endif
