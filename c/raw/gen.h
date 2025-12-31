#ifndef SMPTRhG
	#define SMPTRhG

	//#define SMPTRuJW4
	//#define SMPTRuN
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

	#define SMPTRtM uint8_t
	#define SMPTRvM 0xFFu
	#define SMPTRtMA uint8_t
	#define SMPTRtMB uint8_t
	#define SMPTRtMI uint16_t
	#define SMPTRlMI (0xFFFFu - 1)
	#define SMPTRtMK uint8_t
	#define SMPTRtMT uint16_t
#endif
