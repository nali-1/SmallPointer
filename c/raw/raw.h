#ifndef SMPTRh
	#define SMPTRh

	//.i gen/md
	//.c export
	//#define SMPTRuJW4
	//#define SMPTRuN
	#define SMPTRtRGBAL uint8_t

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

	#define SMPTRxM \
		X(POMI, 31)
	#define SMPTRxM0 \
		X(POMI_PAPI, 1, "0") \
		X(POMI_TEA_BACK, 1, "1Back") \
		X(POMI_TEA_HAT, 1, "1Hat") \
		X(POMI_TEA, 1, "1") \
		X(POMI_CAFE, 1, "2") \
		X(POMI_ICE, 1, "3") \
		X(POMI_2CORE, 1, "4") \
		X(POMI_I0, 1, "", "") \
		X(POMI_I1, 1, "", "") \
		X(POMI_FE0000_000, 1, "FE0000.000") \
		X(POMI_FE0000_001, 1, "FE0000.001") \
		X(POMI_FE0001_000, 1, "FE0001.000") \
		X(POMI_FE0001_001, 1, "FE0001.001") \
		X(POMI_FE00_000, 1, "FE00.000") \
		X(POMI_FE00_001, 1, "FE00.001") \
		X(POMI_FE01_000, 1, "FE01.000") \
		X(POMI_FE01_001, 1, "FE01.001") \
		X(POMI_FE01_002, 1, "FE01.002") \
		X(POMI_FE01_003, 1, "FE01.003") \
		X(POMI_FE0_000, 1, "FE0.000") \
		X(POMI_FE0_001, 1, "FE0.001") \
		X(POMI_FE1, 1, "FE1") \
		X(POMI_M1_000, 1, "M1.000") \
		X(POMI_M1_001, 1, "M1.001") \
		X(POMI_M0, 1, "M0") \
		X(POMI_IShovel, 1, "IShovel")
	#define SMPTRxM1 \
		X(FONT_A, 0, "A")
	enum SMPTReM
	{
		#define X(v, r) SMPTReM_##v,
			SMPTRxM
		#undef X
		SMPTRcM
	};
	enum SMPTReMA
	{
		#define X(v, b, ...) SMPTReMA_##v,
			SMPTRxM0
		#undef X
		#define X(v, b, ...) SMPTReMA_##v,
			SMPTRxM1
		#undef X
		SMPTRcMA
	};

	#define SMPTRxMK \
		X(POMI_WALK_LOOP, 0, 0, 1)
	enum SMPTReMK
	{
		#define X(v, k0, k1, k2) SMPTReMK_##v,
			SMPTRxMK
		#undef X
		SMPTRcMK
	};

	extern const SMPTRtMB smptrPmb[SMPTRcMA];
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
	#define SMPTRuRW 144

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
