#ifndef SMPTRhCEA
	#define SMPTRhCEA

	#ifdef SMPT_CM_VK
		extern VkDescriptorSet *smptr_ceaPvkdescriptorset;
		extern VkBuffer *smptr_ceaPvkbuffer;
	#endif

	struct SMPTR_CEAsA
	{
		struct SMPTRsA Sa;
//		float *Pv;
//		float *Pc;
//		uint8_t Lv;
//		uint8_t Uframe_buffer;
	};
	extern struct SMPTR_CEAsA *smptr_ceaPa;
	extern uint32_t smptr_ceaLa;

	void smptr_ceaMset();
	#ifdef SMPT_CM_VK
		void smptr_ceaMvk();
	#endif
	void smptr_ceaMread();
	void smptr_ceaMloop();
	void smptr_ceaMfree();
#endif
