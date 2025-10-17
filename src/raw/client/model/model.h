#ifndef SMPTR_CEhMD
	#define SMPTR_CEhMD

	//c1j1
	//c1j0
	//t1j1u1v1
	//t1j0u1v1
	#define SMPTR_CE_MDlA 2

	//! check again to move to raw / server
	extern uint8_t
		*smptr_ce_mdPj,
		smptr_ce_mdLj,
		**smptr_ce_mdPb;

	#ifdef SMPT_CM_VK
		#define SMPTR_CE_MDuBUFFER_M 0
		#define SMPTR_CE_MDuBUFFER_D (SMPTR_CE_MDuBUFFER_M + 1)
		#define SMPTR_CE_MDuBUFFER_VP_P (SMPTR_CE_MDuBUFFER_D + 1)
		#define SMPTR_CE_MDuBUFFER_VP_N (SMPTR_CE_MDuBUFFER_VP_P + smpt_rd_vk_swcUimage)
		#define SMPTR_CE_MDuBUFFER_A (SMPTR_CE_MDuBUFFER_VP_N + smpt_rd_vk_swcUimage)

		extern uint32_t
			*smptr_ce_mdPil,
			smptr_ce_mdLrgba;

		extern VkDeviceSize smptr_ce_mdPai[SMPTR_CE_MDlA];
		extern VkDeviceSize *smptr_ce_mdPli;

		extern VkBuffer *smptr_ce_mdPvkbuffer;
		extern VkDeviceMemory *smptr_ce_mdPvkdevicememory;
		extern void **smptr_ce_mdPbuffer_map;
		extern VkDeviceSize *smptr_ce_mdPvkdevicesize;
	#endif

	void smptr_ce_mdMset();
	#ifdef SMPT_CM_VK
		void smptr_ce_mdMvk();
	#endif
	void smptr_ce_mdMfree();
#endif
