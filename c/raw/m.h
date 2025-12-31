#ifndef SMPTRhM
	#define SMPTRhM

	#define SMPTRMuX 0
	#define SMPTRMuY 1
	#define SMPTRMuZ 2
	#define SMPTRMuBX 3
	#define SMPTRMuBY 4
	#define SMPTRMuHX 5
	#define SMPTRMuHY 6
	#define SMPTRMlTR (3 + 2 + 2)

	//.i Forward +Z
	//.i Up -Y
	//.i RIGHT +X
	#define SMPTRMmXZ2H(x, z) atan2f(-(x), z)
	#define SMPTRMmXYZ2V(x, y, z) atan2f(y, sqrtf((x) * (x) + (z) * (z)))

	struct SMPTRsM0
	{
		float Ptr[SMPTRMlTR];
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
		struct SMPTRsM0 Sm0;
	};
#endif
