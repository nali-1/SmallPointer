#ifndef SMPTRhCE
	#define SMPTRhCE

	void smptr_ceMset();
	#ifndef SMPT_CM_ST_JAVA
		#ifdef SMPT_CM_UDP
			extern uint8_t smptr_cePnet[SMPTRlNET];
			extern SMPTRtNET smptr_ceLnet;
		#endif

		extern double
			smptr_ceDdelta,
			smptr_ceDalpha;
		extern uint8_t smptr_ceUstate;

		void smptr_ceMsend();
		void smptr_ceMread();
		void smptr_ceMloop();
	#endif
	void smptr_ceMfree();
#endif
