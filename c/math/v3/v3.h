#ifndef SMPTMhV3
	#define SMPTMhV3

	//.i a * b
	#define SMPTM_V3mDOT(xa, ya, za, xb, yb, zb) (xa) * (xb) + (ya) * (yb) + (za) * (zb)

	#define SMPTM_V3mLENGTH(x, y, z) (x) * (x) + (y) * (y) + (z) * (z)
	#define SMPTM_V3mNORM(x, y, z, l) \
		x /= l; \
		y /= l; \
		z /= l;

//	extern const int8_t smptm_v3Ppath[3];

//	void smptm_v3Mq2m(const float q[3], float w[16]);
//	uint8_t smptm_v3Mray(float Pa[3], float Pb[3], float Pc[3]);
#endif
