#ifndef SMPTMhV4
	#define SMPTMhV4

	extern const float smptm_v4Psrt[4 + 4 + 4];

	void smptm_v4Mq(float x, float y, float z, float w[4]);
	void smptm_v4Mq2m(const float q[4], float w[16]);
	void smptm_v4Mm(const float a[4], const float b[4], float w[4]);
	void smptm_v4Mm4(const float a[16], const float b[4], float w[4]);

	#define SMPTM_V4mQI(p, n) \
		p[n] = -p[n]; \
		p[n + 1] = -p[n + 1]; \
		p[n + 2] = -p[n + 2];
#endif
