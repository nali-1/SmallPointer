#ifndef SMPTRhG
	#define SMPTRhG

	//#define SMPTRuJW4
	//.c normal
	#define SMPTRuN
	//.c fix normal
	#define SMPTRuNF
	#define SMPTRtI uint32_t
	#define SMPTRuI 4
//	#define SMPTRtI uint8_t
//	#define SMPTRuI 1
	#define SMPTRtRGBAL uint8_t
	#define SMPTRtJWL uint8_t

	#ifdef SMPTRuJW4
		#define SMPTRtJW uint32_t
	#else
		#define SMPTRtJW uint8_t
	#endif

	#ifdef SMPTRuN
		#ifdef SMPTRuNF
			#define SMPTRlVN 0
		#endif
		#ifndef SMPTRuNF
			#define SMPTRlVN (sizeof(float) * 3)
		#endif
	#endif
	#ifndef SMPTRuN
		#define SMPTRlVN 0
	#endif

	#define SMPTRlV (sizeof(float) * 3 + SMPTRlVN + 2)

	#define SMPTRtM uint8_t
	#define SMPTRvM 0xFFu
	#define SMPTRtMA uint8_t
	#define SMPTRtMB uint8_t
	#define SMPTRtMI uint16_t
	#define SMPTRlMI (0xFFFFu - 1)
	#define SMPTRtMK uint8_t
	#define SMPTRtMT uint16_t
#endif
