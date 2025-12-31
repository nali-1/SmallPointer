#ifndef SMPTRhU
	#define SMPTRhU

	//.i Forward -Z
	//.i Up +Y
	//.i RIGHT -X
	#define SMPTRUmXZ2H(x, z) atan2f(x, -(z))
	#define SMPTRUmXYZ2V(x, y, z) -atan2f(y, sqrtf((x) * (x) + (z) * (z)))

	struct SMPTRsU
	{
		float Ptr[3 + 2];
		//uint8_t Us;
	};
#endif
