#ifndef SMPTRhCEU
	#define SMPTRhCEU

	extern struct SMPTRsU smptr_ceuSu;
	extern uint8_t smpt_ceuPinput[SMPT_IPlL];
	extern float smpt_ceuPpoint[2];

	void smptr_ceuMset();
	void smptr_ceuMsend();
	void smptr_ceuMread();
	void smptr_ceuMloop();
	void smptr_ceuMfree();
#endif
