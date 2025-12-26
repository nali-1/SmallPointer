#ifndef SMPThADO
	#define SMPThADO

	#define SMPT_ADOfSAMPLE_RATE 48000.0F
	#define SMPT_ADOuCHANNEL_COUNT 2
	#define SMPT_ADOuFRAME 256
	void smpt_adoMgen(float *Pdata, int32_t Iframe);
#endif
