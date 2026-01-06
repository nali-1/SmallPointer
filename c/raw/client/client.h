#ifndef SMPTRhCE
	#define SMPTRhCE

	void smptr_ceMset();
	#ifdef SMPT_CM_UDP
		extern uint8_t smptr_cePnet[SMPTRlNET];
		extern SMPTRtNET smptr_ceLnet;
	#endif

	extern float smptr_ceDpartial_tick;
	extern double
		smptr_ceDdelta;
		//smptr_ceDalpha;
	extern uint8_t smptr_ceUstate;

	void smptr_ceMsend();
	void smptr_ceMread();
	void smptr_ceMloop();

	void smptr_ceMfree();
#endif
