#ifndef SMPThKF
	#define SMPThKF

	enum SMPTReMK
	{
		#define X(v, k0, k1, k2) SMPTReMK_##v,
			SMPTR_MDxMK
		#undef X
		SMPTRcMK
	};

	extern const SMPTRtMK smptrPmk[SMPTRcMK][3];
#endif
