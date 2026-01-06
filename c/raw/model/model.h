#ifndef SMPThMD
	#define SMPThMD

	#define SMPTR_MDx \
		X(POMI, 31) \
		X(UI, 27) \
		X(CROAKIE, 0)
	#define SMPTR_MDxM0 \
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
	#define SMPTR_MDxM1 \
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
		X(UI_IClover, "IClover") \
		X(CROAKIE_C0, "C0") \
		X(CROAKIE_C1, "C1") \
		X(CROAKIE_RAIN, "C")
	enum SMPTR_MDe
	{
		#define X(v, r) SMPTR_MDe##v,
			SMPTR_MDx
		#undef X
		SMPTR_MDc
	};
	enum SMPTR_MDeM
	{
		#define X(v, n) SMPTReMA_##v,
			SMPTR_MDxM0
		#undef X
		#define X(v, n) SMPTReMA_##v,
			SMPTR_MDxM1
		#undef X
		SMPTR_MDcM
	};

	#define SMPTR_MDxO0 \
		X(FONT_A, "A") \
		X(FONT_B, "B") \
		X(FONT_C, "C") \
		X(FONT_D, "D") \
		X(FONT_E, "E") \
		X(FONT_F, "F") \
		X(FONT_G, "G") \
		X(FONT_H, "H") \
		X(FONT_I, "I") \
		X(FONT_J, "J") \
		X(FONT_K, "K") \
		X(FONT_L, "L") \
		X(FONT_M, "M") \
		X(FONT_N, "N") \
		X(FONT_O, "O") \
		X(FONT_P, "P") \
		X(FONT_Q, "Q") \
		X(FONT_R, "R") \
		X(FONT_S, "S") \
		X(FONT_T, "T") \
		X(FONT_U, "U") \
		X(FONT_V, "V") \
		X(FONT_W, "W") \
		X(FONT_X, "X") \
		X(FONT_Y, "Y") \
		X(FONT_Z, "Z") \
		X(FONT_1, "1") \
		X(FONT_3, "3") \
		X(FONT_4, "4") \
		X(FONT_5, "5") \
		X(FONT_6, "6") \
		X(FONT_7, "7") \
		X(FONT_8, "8") \
		X(FONT_9, "9")
	#define SMPTR_MDxO1 \
		X(SPACE_CUBE, "Cube") \
		X(SPACE_SPHERE, "Sphere")

	extern const SMPTRtMA smptrPmr[SMPTR_MDc];
//	extern const float smptrPmd[SMPTR_MDcM][3];

	void smptr_mdMset();
	void smptr_mdMfree();
#endif
