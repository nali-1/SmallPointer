#ifndef SMPTRhCE
	#define SMPTRhCE

	extern uint8_t smptr_cePnet[SMPTRlNET];
	extern SMPTRtNET smptr_ceLnet;

	extern double smptr_ceDdelta;

	void smptr_ceMset();
	void smptr_ceMsend();
	void smptr_ceMread();
	void smptr_ceMloop();
	void smptr_ceMfree();
#endif
