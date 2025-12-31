//! clean
#ifndef SMPThM
	#define SMPThM

//	#define SMPTMmLENGTH(number) ((number) == 0 ? 1 : log10(number) + 1)

	#define SMPTMmNORM_NF(v, m) fmodf(fmodf((v) + (m) / 2.0F, (m)) + (m), (m)) - (m) / 2.0F
//	#define SMPTMmNORM_NI(v, m) ((((v) + m / 2) % m + m) % m - m / 2)
//	#define SMPTMmNORM_PF(v, m) fmodf(fmodf(v, m) + m, m)
//	#define SMPTMmNORM_PI(v, m) (((v) % m + m) % m)

//	#define SMPTMmFIX_F(v, min, max) fmodf(v - min, max - min) + min
//	#define SMPTMmFIX_I(v, min, max) ((v - min) % (max - min)) + min
	#define SMPTMmWRAP_I(v, min, max) (min) + ((((v) - (min)) % ((max) - (min))) + ((max) - (min))) % ((max) - (min))
	#define SMPTMmWRAP_F(v, min, max) (min) + fmodf((fmodf(((v) - (min)), ((max) - (min))) + ((max) - (min))), ((max) - (min)))

	#define SMPTMmLERP(a, b, t) (a) + ((b) - (a)) * (t)

	#define SMPTMmD2R(v) ((v) * (float)M_PI / 180.0F)
	#define SMPTMmR2D(v) ((v) * 180.0F / (float)M_PI)

	//! clean
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

	//.m 4679~8940
	#define SMPTMmHV2Z(h, v) cosf(v) * cosf(h)
	#define SMPTMmV2Y(v) sinf(v)
	#define SMPTMmHV2X(h, v) cosf(v) * sinf(h)
#endif
