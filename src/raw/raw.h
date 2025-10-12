#ifndef SMPTRh
	#define SMPTRh

	//.i model
	#define SMPTRtM uint8_t
	#define SMPTRvM 0xFFu
	#define SMPTRtMA uint8_t
	#define SMPTRtMB uint8_t
	#define SMPTRtMI uint16_t
	#define SMPTRlMI (0xFFFFu - 1)
	#define SMPTRtMK uint8_t
	#define SMPTRtMT uint16_t
	#define SMPTRnMA \
		X(FE0000_000, "FE0000.000", 1) \
		X(FE0000_001, "FE0000.001", 1) \
		X(FE0001_000, "FE0001.000", 1) \
		X(FE0001_001, "FE0001.001", 1) \
		X(FE00_000, "FE00.000", 1) \
		X(FE00_001, "FE00.001", 1) \
		X(FE01_000, "FE01.000", 1) \
		X(FE01_001, "FE01.001", 1) \
		X(FE01_002, "FE01.002", 1) \
		X(FE01_003, "FE01.003", 1) \
		X(FE0_000, "FE0.000", 1) \
		X(FE0_001, "FE0.001", 1) \
		X(FE1, "FE1", 1) \
		X(M1_000, "M1.000", 1) \
		X(M1_001, "M1.001", 1) \
		X(M0, "M0", 1) \
		X(IShovel, "IShovel", 1)

	#define SMPTRnM \
		X(POMI_PAPI, "SuperCutePomi2", 1, 31) \
		X(POMI_TEA, "SuperCutePomi1", 1, 31) \
		X(POMI_CAFE, "SuperCutePomi0", 1, 31)

	#define SMPTRnM1 \
		X(FONT, "Font", 0)

	#define SMPTRnMK \
		X(POMI_WALK_LOOP, 0, 3, 5)

	enum SMPTReMA
	{
		#define X(v, n, b) SMPTReMA_##v,
			SMPTRnMA
		#undef X
		SMPTReMAc
	};

	enum SMPTReM
	{
		#define X(v, n, b, r) SMPTReM_##v,
			SMPTRnM
		#undef X
		SMPTReMc
	};

	enum SMPTReM1
	{
		#define X(v, n, b) SMPTReM1_##v,
			SMPTRnM1
		#undef X
		SMPTReM1c
	};

	enum SMPTReMK
	{
		#define X(v, k0, k1, k2) SMPTReMK_##v,
			SMPTRnMK
		#undef X
		SMPTReMKc
	};

	extern const SMPTRtMB smptrPmb[SMPTReMAc + SMPTReMc + SMPTReM1c];
	extern const SMPTRtMK smptrPmk[SMPTReMKc][3];

	extern const SMPTRtMA smptrPmr[SMPTReMc];
//	extern const float smptrPmd[SMPTReMAc + SMPTReMc][3];

	struct SMPTRsM0
	{
		uint8_t Ltr;
		float *Ptr;
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
	struct SMPTRsA
	{
		SMPTRtA Ua;
		float
			//.i 3
			*Pv;
		uint8_t
			*Pc,
			Lv;
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
