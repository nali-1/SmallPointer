//! clean
#ifndef SMPThM
	#define SMPThM

//	#define SMPTMmLENGTH(number) ((number) == 0 ? 1 : log10(number) + 1)

	float smptmMnr(float Fr, float F1);
//	#define SMPTMmNORM_NI(v, m) ((((v) + m / 2) % m + m) % m - m / 2)
//	#define SMPTMmNORM_PF(v, m) fmodf(fmodf(v, m) + m, m)
//	#define SMPTMmNORM_PI(v, m) (((v) % m + m) % m)

//	#define SMPTMmFIX_F(v, min, max) fmodf(v - min, max - min) + min
//	#define SMPTMmFIX_I(v, min, max) ((v - min) % (max - min)) + min
	uint32_t smptmMnu(uint32_t Uv, uint32_t U0, uint32_t U1);
	float smptmMnf(float Fv, float F0, float F1);

	float smptmMa2b(float Fa, float Fb, float Ft);

	float smptmMd2r(float Fd);
	//#define SMPTMmR2D(v) ((v) * 180.0F / (float)M_PI)

//	//hash
//	#define SMPTMmH3(x, y, z, m) x * m * m + y * m + z
//	#define SMPTMmH3X(hi, m) hi / (m * m)
//	#define SMPTMmH3Y(hi, m) (hi / m) % m
//	#define SMPTMmH3Z(hi, m) hi % m

//	#define SMPTMmSpi(name, a, b, pi) \
//		float name = fmodf((a - b + pi), 2 * pi); \
//		if (name < 0) \
//		{ \
//			name += 2 * pi; \
//		} \
//		name -= pi; \

//	//.m 4679~8940
//	#define SMPTMmHV2Z(h, v) cosf(v) * cosf(h)
//	#define SMPTMmV2Y(v) sinf(v)
//	#define SMPTMmHV2X(h, v) cosf(v) * sinf(h)
#endif
