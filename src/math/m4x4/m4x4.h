#ifndef SMPTMhM4X4
	#define SMPTMhM4X4

	extern const float smptm_m4x4P[16];

	void smptm_m4x4Mi(float Pm[16]);
	void smptm_m4x4Mm(const float Pa[16], const float Pb[16], float Pw[16]);

	//.c fov
	#define SMPTM_M4X4fFOV 30.0F
	#define SMPTM_M4X4fFOV_F (1.0F / tanf(SMPTMmD2R(SMPTM_M4X4fFOV * 0.5F)))
	#define SMPTM_M4X4fZ_NEAR 0.1F
	#define SMPTM_M4X4fZ_FAR 100.0F
	#define SMPTM_M4X4fASPECT ((float)smpt_sfUwidth / (float)smpt_sfUheight)

	#define SMPTM_M4X4mP(Pm4x4) \
		(Pm4x4)[0] = SMPTM_M4X4fFOV_F / SMPTM_M4X4fASPECT; \
		(Pm4x4)[5] = SMPTM_M4X4fFOV_F; \
		(Pm4x4)[10] = SMPTM_M4X4fZ_FAR / (SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR); \
		(Pm4x4)[11] = 1.0F; \
		(Pm4x4)[14] = -(SMPTM_M4X4fZ_FAR * SMPTM_M4X4fZ_NEAR) / (SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR);
#endif
