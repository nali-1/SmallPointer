#ifndef SMPTRhCEM
	#define SMPTRhCEM

	#ifdef SMPT_CM_VK
		extern VkDescriptorSet *smptr_cemPvkdescriptorset;
		extern VkBuffer *smptr_cemPvkbuffer;
	#endif

	struct SMPTR_CEMsM
	{
		SMPTRtMI Ui;
		SMPTRtMA Ua;
		SMPTRtMB Ub;
		float Fd;
	};
	extern struct SMPTR_CEMsM *smptr_cemPm;
	extern uint32_t smptr_cemLm;

	void smptr_cemMset();
	void smptr_cemMread();
	void smptr_cemMloop();
	void smptr_cemMfree();
#endif
