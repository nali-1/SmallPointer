#ifndef SMPTR_CEhMD
	#define SMPTR_CEhMD

	//! check again to move to raw / server
	extern SMPTRtJW *smptr_ce_mdPj;
	extern uint8_t **smptr_ce_mdPb;

	#define SMPTR_CE_MDlBONE 52
	extern SMPTRtRGBAL smptr_ce_mdLrgba;

	#ifdef SMPT_CM_VK
		#define SMPTR_CE_MDuBUFFER_M 0
		#define SMPTR_CE_MDuBUFFER_D (SMPTR_CE_MDuBUFFER_M + 1)
		#define SMPTR_CE_MDuBUFFER_VP_P (SMPTR_CE_MDuBUFFER_D + 1)
		#define SMPTR_CE_MDuBUFFER_VP_N (SMPTR_CE_MDuBUFFER_VP_P + smpt_rd_vk_swcUimage)
		#define SMPTR_CE_MDuBUFFER_A (SMPTR_CE_MDuBUFFER_VP_N + smpt_rd_vk_swcUimage)

		#define SMPTR_CE_MDuRGBA 0
		#define SMPTR_CE_MDuA smptr_ce_mdPli[SMPTR_MDcM]

		extern VkDeviceSize smptr_ce_mdPli[SMPTR_MDcM + 1];
		extern uint32_t smptr_ce_mdPic[SMPTR_MDcM];

		extern VkBuffer *smptr_ce_mdPvkbuffer;
		extern VkDeviceMemory *smptr_ce_mdPvkdevicememory;
		extern void **smptr_ce_mdPbuffer_map;
		extern VkDeviceSize *smptr_ce_mdPvkdevicesize;
	#endif
	extern SMPTRtI *smptr_ce_mdPi[SMPTR_MDcM];
	extern SMPTRtI smptr_ce_mdPil[SMPTR_MDcM];
	extern uint8_t *smptr_ce_mdPa;
	extern uint32_t smptr_ce_mdLa;
	extern float **smptr_ce_mdPbp;
	extern uint32_t *smptr_ce_mdPrgba;

	void smptr_ce_mdMset();
	#ifdef SMPT_CM_VK
		void smptr_ce_mdMvk();
	#endif
	void smptr_ce_mdMfree();
#endif
