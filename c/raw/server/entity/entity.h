#ifndef SMPTR_SVhETT
	#define SMPTR_SVhETT

	struct SMPTR_SV_ETTs
	{
		uint8_t Uwork;
		float Fmove[3];
		uint8_t Umove;
		uint8_t Ueye;
		uint8_t Umouth;
		//uint8_t Ulooku;
		//float Ptr[SMPTRMlTR];
		//uint8_t Ptime[2];
	};
	extern struct SMPTR_SV_ETTs *smptr_sv_ettP;

	void smptr_sv_ettMset();
	void smptr_sv_ettMloop();
	void smptr_sv_ettMfree();
#endif
