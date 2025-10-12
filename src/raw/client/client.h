#ifndef SMPTRhCE
	#define SMPTRhCE

	//.c refresh rate
	#define SMPTR_CEuFPS 144
	#define SMPTR_CEuDELTA (1.0F / SMPTR_CEuFPS)

	extern uint8_t smptr_cePnet[SMPTRlNET];
	extern SMPTRtNET smptr_ceLnet;

	extern double smptr_ceDdelta;

	void smptr_ceMset();
	void smptr_ceMsend();
	void smptr_ceMread();
	void smptr_ceMloop();
	void smptr_ceMfree();
#endif
