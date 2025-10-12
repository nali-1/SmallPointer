#ifndef SMPThNW
	#define SMPThNW

	//.c max connect
	#define SMPT_NWlU 1
	//.c max connect type
	#define SMPT_NWtU uint8_t

	#if __BYTE_ORDER == __LITTLE_ENDIAN
		#define SMPT_NWmIP(a, b, c, d) \
			(((a << 24 | b << 16 | c << 8 | d) & 0x000000FF) << 24) | \
			(((a << 24 | b << 16 | c << 8 | d) & 0x0000FF00) << 8) | \
			(((a << 24 | b << 16 | c << 8 | d) & 0x00FF0000) >> 8) | \
			(((a << 24 | b << 16 | c << 8 | d) & 0xFF000000) >> 24)
		#define SMPT_NWmPORT(a) \
			(((a) & 0x00FF) << 8) | \
			(((a) & 0xFF00) >> 8)
	#else
		#define SMPT_NWmIP(a, b, c, d) a << 24 | b << 16 | c << 8 | d
		#define SMPT_NWmPORT(a) a
	#endif

	#ifdef SMPT_CM_CLIENT
		//.c connect ip
		#define SMPT_NWuIP SMPT_NWmIP(127, 0, 0, 1)
	#endif

	//.c port
	#define SMPT_NWuPORT 11111

	#ifdef SMPT_CM_SERVER
		extern const uint32_t smpt_nwPu[SMPT_NWlU];
	#endif
#endif
