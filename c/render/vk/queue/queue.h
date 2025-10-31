#ifndef SMPT_RD_VKhQ
	#define SMPT_RD_VKhQ

	#define SMPT_RD_VKQuGP 0
	#define SMPT_RD_VKQuCP 1

	#define SMPT_RD_VKQmOFFSET(Udevice, U) (U) & ~(smpt_rd_vkqPinfo[Udevice].Unon_coherent_atom_size - 1)
	#define SMPT_RD_VKQmSIZE(Udevice, U) ((U) + smpt_rd_vkqPinfo[Udevice].Unon_coherent_atom_size - 1) & ~(smpt_rd_vkqPinfo[Udevice].Unon_coherent_atom_size - 1)

	struct SMPT_RD_VKQsINFO
	{
		VkCommandBuffer *Pvkcommandbuffer;
		VkCommandPool *Pvkcommandpool;

		float Fmax_sampler_anisotropy;
		uint8_t
			Unon_coherent_atom_size,
			Usample_count;
		uint32_t *Pfamily;
		VkQueue *Pvkqueue;
		VkDevice Vvkdevice;
		VkPhysicalDevice Vvkphysicaldevice;
	};
	extern struct SMPT_RD_VKQsINFO *smpt_rd_vkqPinfo;
	extern uint32_t smpt_rd_vkqLinfo;

	extern uint8_t
		smpt_rd_vkqUq_gp,
		smpt_rd_vkqUq_sf,
		smpt_rd_vkqUq_cp,
		smpt_rd_vkqUdv_cp;

	void smpt_rd_vkqMset();
	void smpt_rd_vkqMfree();
#endif
