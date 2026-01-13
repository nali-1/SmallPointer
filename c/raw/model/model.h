#ifndef SMPThMD
	#define SMPThMD

	#ifdef SMPT_CM_MAIN
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
	#endif
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

	#ifdef SMPTR_MDxM0
		#define SMPTR_MDxM0F X(1, "SuperCutePomi")
		#define SMPTR_MDxM0FV \
			X(POMI, "SuperCutePomi")
		#define SMPTR_MDxM0FR X(31)
		#define SMPTR_MDxM0FK \
			X(POMI_IDLE, SMPTR_MDePOMI, 15, 17) \
			X(POMI_WALK_START, SMPTR_MDePOMI, 0, 13) \
			X(POMI_WALK_MID, SMPTR_MDePOMI, 5, 10) \
			X(POMI_WALK_END, SMPTR_MDePOMI, 0, 13) \
			X(POMI_JUMP, SMPTR_MDePOMI, 13, 15)
		#define SMPTR_MDxM0FW \
			X(POMI, smptr_sv_ett_pmMwork)
	#else
		#define SMPTR_MDxM0F
		#define SMPTR_MDxM0FV
		#define SMPTR_MDxM0FK
		#define SMPTR_MDxM0FW
	#endif
	#ifdef SMPTR_MDxM1
		#define SMPTR_MDxM1F X(2, "Ui")
		#define SMPTR_MDxM1FV \
			X(UI, "Ui") \
			X(CROAKIE, "Croakie")
		#define SMPTR_MDxM1FR X(27, 0)
		#define SMPTR_MDxM1FK \
			X(UI_IDLE, SMPTR_MDeUI, 0, 2) \
			X(UI_IDLE1, SMPTR_MDeUI, 2, 4) \
			X(UI_ATTACK, SMPTR_MDeUI, 4, 6) \
			X(UI_WALK, SMPTR_MDeUI, 6, 8) \
			X(CROAKIE_IDLE, SMPTR_MDeCROAKIE, 0, 2) \
			X(CROAKIE_WALK, SMPTR_MDeCROAKIE, 2, 4)
		#define SMPTR_MDxM1FW \
			X(UI, smptr_sv_ett_uiMwork)
	#else
		#define SMPTR_MDxM1F
		#define SMPTR_MDxM1FV
		#define SMPTR_MDxM1FK
		#define SMPTR_MDxM1FW
	#endif

	#define SMPTR_MDxMF \
		SMPTR_MDxM0F \
		SMPTR_MDxM1F
	#define SMPTR_MDxMV \
		SMPTR_MDxM0FV \
		SMPTR_MDxM1FV
	#define SMPTR_MDxMK \
		SMPTR_MDxM0FK \
		SMPTR_MDxM1FK
	#define SMPTR_MDxMW \
		SMPTR_MDxM0FW \
		SMPTR_MDxM1FW
	enum SMPTR_MDe
	{
		#ifdef SMPTR_MDxM0
			#define X(V, N) SMPTR_MDe##V,
				SMPTR_MDxM0FV
			#undef X
		#endif
		#ifdef SMPTR_MDxM1
			#define X(V, N) SMPTR_MDe##V,
				SMPTR_MDxM1FV
			#undef X
		#endif
		SMPTR_MDc
	};
	enum SMPTR_MDeM
	{
		#ifdef SMPTR_MDxM0
			#define X(V, N) SMPTR_MDeM_##V,
				SMPTR_MDxM0
			#undef X
		#endif
		#ifdef SMPTR_MDxM1
			#define X(V, N) SMPTR_MDeM_##V,
				SMPTR_MDxM1
			#undef X
		#endif
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
	enum SMPTR_MDeO
	{
		#ifdef SMPTR_MDxO0
			#define X(v, n) SMPTR_MDeO_##v,
				SMPTR_MDxO0
			#undef X
		#endif
		#ifdef SMPTR_MDxO1
			#define X(v, n) SMPTR_MDeO_##v,
				SMPTR_MDxO1
			#undef X
		#endif
		SMPTR_MDcO
	};

	#ifdef SMPTR_MDxO0
		#define SMPTR_MDxO0F X("Font")
	#else
		#define SMPTR_MDxO0F
	#endif
	#ifdef SMPTR_MDxO1
		#define SMPTR_MDxO1F X("Space")
	#else
		#define SMPTR_MDxO1F
	#endif

	#define SMPTR_MDxO \
		SMPTR_MDxO0F \
		SMPTR_MDxO1F

	extern const SMPTRtMA smptrPmr[SMPTR_MDc];
//	extern const float smptrPmd[SMPTR_MDcM][3];

	#ifdef SMPT_CM_MAIN
		extern SMPTRtI *smptr_mdPi[SMPTR_MDcO];
		extern SMPTRtI smptr_mdPil[SMPTR_MDcO];
		extern uint8_t *smptr_mdPa;
		extern uint32_t smptr_mdLa;

		void smptr_mdMset();
		void smptr_mdMfree();
	#endif
#endif
