#ifndef SMPTRhSVM
	#define SMPTRhSVM

	extern struct SMPTRsM *smptr_svmPm;
	extern SMPTRtMI smptr_svmLm;

	extern uint8_t smptr_svmPsync[SMPTRlMI];

	void smptr_svmMset();
	void smptr_svmMloop();
	void smptr_svmMsend(SMPT_NWtU u);
	void smptr_svmMfread();
	void smptr_svmMfsend();
	void smptr_svmMfree();
#endif
