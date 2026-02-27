#ifndef SMPTMhM4X4
	#define SMPTMhM4X4

	extern const float smptm_m4x4P[16];

	void smptm_m4x4Mi(float Pm[16]);
	void smptm_m4x4Mm(const float Pa[16], const float Pb[16], float Pm[16]);

	//.c fov
	#define SMPTM_M4X4fFOV 30.0F
	#define SMPTM_M4X4fZ_NEAR 0.1F
	#define SMPTM_M4X4fZ_FAR 100.0F
	void smptm_m4x4Mp(float Pm[16]);
#endif
