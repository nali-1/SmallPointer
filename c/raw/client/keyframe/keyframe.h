#ifndef SMPTR_CEhKF
	#define SMPTR_CEhKF

	struct SMPTR_CE_KFs
	{
		uint8_t
			Lbone,
			*Pbone;
		float
			**Ps,
			**Pr,
			**Pt;
	};

	extern struct SMPTR_CE_KFs **smptr_ce_kfP;
	extern uint8_t *smptr_ce_kfPl;

	void smptr_ce_kfMset();
	void smptr_ce_kfMfree();
#endif
