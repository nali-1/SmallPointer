#ifndef SMPTRhA
	#define SMPTRhA

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
#endif
