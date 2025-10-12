#ifndef SMPTRhCEM
	#define SMPTRhCEM

	#ifdef SMPT_CM_VK
		extern VkDescriptorSet *smptr_cemPvkdescriptorset;

		extern VkBuffer *smptr_cemPvkbuffer;
	#endif

	struct SMPTR_CEMsM1
	{
		SMPTRtMI Ui;
		SMPTRtMA Ua;
		SMPTRtMB Ub;
		float Fd;
	};
	extern struct SMPTR_CEMsM1 *smptr_cemPm1;
	extern uint32_t smptr_cemLm1;

	void smptr_cemMset();
	void smptr_cemMread();
	void smptr_cemMloop();
	void smptr_cemMfree();
#endif
