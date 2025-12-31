//! clean this folder
#ifndef SMPThR
	#define SMPThR

	//.i package
	#define SMPTRtNET uint16_t
	#define SMPTRlNET 0xFFFFu

	struct SMPTRsCACHE
	{
		#ifdef SMPT_CM_CLIENT
			uint16_t
				**bs_p,
				**be_p;
		#endif
		#ifdef SMPT_CM_SERVER
		#endif
		uint8_t *d_p;
		uint32_t *d_bl_p;
	};
	extern struct SMPTRsCACHE *smptrPcache;

	void smptrMset();
	void smptrMfree0();
	void smptrMfree1();
#endif
