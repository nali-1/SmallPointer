#ifndef SMPTRhU
	#define SMPTRhU

	//.i Forward -Z
	//.i Up +Y
	//.i RIGHT -X
	#define SMPTRUmXZ2H(x, z) atan2f(x, -(z))
	#define SMPTRUmXYZ2V(x, y, z) -atan2f(y, sqrtf((x) * (x) + (z) * (z)))

	#define SMPTRlUTR (3 + 2)
	struct SMPTRsU
	{
		float Ptr[SMPTRlUTR];
		//uint8_t Us;
	};
#endif
