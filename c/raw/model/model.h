#ifndef SMPThMD
	#define SMPThMD

	#define SMPTRxM \
		X(POMI, 31) \
		X(UI, 27) \
		X(CROAKIE, 0)
	#define SMPTRxM0 \
		X(POMI_PAPI, "0") \
		X(POMI_TEA_BACK, "1Back") \
		X(POMI_TEA_HAT, "1Hat") \
		X(POMI_TEA, "1") \
		X(POMI_CAFE, "2") \
		X(POMI_ICE, "3") \
		X(POMI_2CORE, "4") \
		X(POMI_MF0000, "MF0000") \
		X(POMI_MF0001, "MF0001") \
		X(POMI_MF00, "MF00") \
		X(POMI_MF01, "MF01") \
		X(POMI_MF0, "MF0") \
		X(POMI_MF1, "MF1") \
		X(POMI_MM0, "MM0") \
		X(POMI_MM1, "MM1") \
		X(POMI_M, "M") \
		X(POMI_I0, "IIceL") \
		X(POMI_I1, "IIceR") \
		X(POMI_IShovel, "IShovel")
	//! mix to a
	#define SMPTRxM1 \
		X(FONT_A, "A")
	#define SMPTRxM2 \
		X(UI_000, "000") \
		X(UI_001, "001") \
		X(UI_RAIN, "0") \
		X(UI_MF00, "MF00") \
		X(UI_MF01, "MF01") \
		X(UI_MF02, "MF02") \
		X(UI_MF0, "MF0") \
		X(UI_MF1, "MF1") \
		X(UI_MM0, "MM0") \
		X(UI_MM1, "MM1") \
		X(UI_M, "M") \
		X(UI_IClover, "IClover")
	#define SMPTRxM3 \
		X(CROAKIE_C0, "C0") \
		X(CROAKIE_C1, "C1") \
		X(CROAKIE_RAIN, "C")
	enum SMPTReM
	{
		#define X(v, r) SMPTReM_##v,
			SMPTRxM
		#undef X
		SMPTRcM
	};
	enum SMPTReMA
	{
		#define X(v, n) SMPTReMA_##v,
			SMPTRxM0
		#undef X
		#define X(v, n) SMPTReMA_##v,
			SMPTRxM1
		#undef X
		#define X(v, n) SMPTReMA_##v,
			SMPTRxM2
		#undef X
		#define X(v, n) SMPTReMA_##v,
			SMPTRxM3
		#undef X
		SMPTRcMA
	};

	extern const SMPTRtMA smptrPmr[SMPTRcM];
//	extern const float smptrPmd[SMPTRcMA][3];
#endif
