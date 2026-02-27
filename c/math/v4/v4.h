#ifndef SMPTMhV4
	#define SMPTMhV4

	extern float smptm_v4Psrt[4 + 4 + 4];

	void smptm_v4Mset();

	void smptm_v4Mq(float Fx, float Fy, float Fz, float Pq[4]);
	void smptm_v4Mqi(float Pq[4]);
	void smptm_v4Mq2m(const float Pq[4], float Pm[16]);
	void smptm_v4Mm(const float Pa[4], const float Pb[4], float Pq[4]);
	void smptm_v4Mm4(const float Pa[16], const float Pb[4], float Pq[4]);

	float smptm_v4Md(const float Pa[4], const float Pb[4]);
	void smptm_v4Mn(float Pq[4]);
	//.i Nlerp
	void smptm_v4Mna2b(const float Pa[4], const float Pb[4], float Ft, float Pq[4]);
#endif
