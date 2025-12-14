#ifndef SMPTRh
	#define SMPTRh

	//.i gen/md
	//.c export
	//#define SMPTRuJW4
	//#define SMPTRuN
	#define SMPTRtI uint32_t
	#define SMPTRtRGBAL uint8_t
	#define SMPTRtJWL uint8_t

	#ifdef SMPTRuJW4
		#define SMPTRtJW uint32_t
	#else
		#define SMPTRtJW uint8_t
	#endif

	//.i model
	#define SMPTRtM uint8_t
	#define SMPTRvM 0xFFu
	#define SMPTRtMA uint8_t
	#define SMPTRtMB uint8_t
	#define SMPTRtMI uint16_t
	#define SMPTRlMI (0xFFFFu - 1)
	#define SMPTRtMK uint8_t
	#define SMPTRtMT uint16_t

	//! fix
	#define SMPTRxM \
		X(UI, 27) \
		X(CROAKIE, 0)
		//X(POMI, 31)
//	#define SMPTRxM0 \
//		X(POMI_PAPI, "0") \
//		X(POMI_TEA_BACK, "1Back") \
//		X(POMI_TEA_HAT, "1Hat") \
//		X(POMI_TEA, "1") \
//		X(POMI_CAFE, "2") \
//		X(POMI_ICE, "3") \
//		X(POMI_2CORE, "4") \
//		X(POMI_MF0000, "MF0000") \
//		X(POMI_MF0001, "MF0001") \
//		X(POMI_MF00, "MF00") \
//		X(POMI_MF01, "MF01") \
//		X(POMI_MF0, "MF0") \
//		X(POMI_MF1, "MF1") \
//		X(POMI_MM0, "MM0") \
//		X(POMI_MM1, "MM1") \
//		X(POMI_M, "M") \
//		X(POMI_I0, "IIceL") \
//		X(POMI_I1, "IIceR") \
//		X(POMI_IShovel, "IShovel")
//	//! mix to a
//	#define SMPTRxM1 \
//		X(FONT_A, "A")
	#define SMPTRxM2 \
		X(UI_000, "000") \
		X(UI_001, "001") \
		X(UI_RAIN, "0") \
		X(UI_MF00, "MF00") \
		X(UI_MF01, "MF01") \
		X(UI_MF0, "MF0") \
		X(UI_MF1, "MF1") \
		X(UI_MF, "MF") \
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
//		#define X(v, n) SMPTReMA_##v,
//			SMPTRxM0
//		#undef X
//		#define X(v, n) SMPTReMA_##v,
//			SMPTRxM1
//		#undef X
		#define X(v, n) SMPTReMA_##v,
			SMPTRxM2
		#undef X
		#define X(v, n) SMPTReMA_##v,
			SMPTRxM3
		#undef X
		SMPTRcMA
	};

	//! fix
	#define SMPTRxMK \
		X(UI_IDLE, 0, 0, 2) \
		X(CROAKIE_IDLE, 1, 0, 2)
		//X(POMI_WALK_LOOP, 0, 0, 1)
	enum SMPTReMK
	{
		#define X(v, k0, k1, k2) SMPTReMK_##v,
			SMPTRxMK
		#undef X
		SMPTRcMK
	};

	extern const SMPTRtMK smptrPmk[SMPTRcMK][3];

	extern const SMPTRtMA smptrPmr[SMPTRcM];
//	extern const float smptrPmd[SMPTRcMA][3];

	struct SMPTRsM0
	{
		uint8_t Ltr;
		float *Ptr;
		uint8_t Usync;
	};
	struct SMPTRsM
	{
		//.i client always get same size as server
		//.i server can return norender to client
		//.i i
		SMPTRtM Um;
		//.i a
		SMPTRtMK Uk;
		SMPTRtMT Ut;
		//.i r
		uint8_t La;
		SMPTRtMA *Pa;
		struct SMPTRsM0 Sm0;
	};

	struct SMPTRsU
	{
		float Ptr[3 + 2];
		//uint8_t Us;
	};

	//.i a
	#define SMPTRtA uint16_t
	#define SMPTRlA 0xFFFFu
	struct SMPTRsA
	{
		SMPTRtA Ua;
		float
			//.i 3
			*Pv;
		uint8_t
			*Pc,
			Lv;
		uint8_t Usync;
	};

	//.c server read/write
	#define SMPTRuRW 20

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
