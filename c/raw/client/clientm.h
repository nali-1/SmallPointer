#ifndef SMPT_CM_ST_JAVA
	#ifndef SMPTRhCEM
		#define SMPTRhCEM

		#ifdef SMPT_CM_VK
			extern VkDescriptorSet *smptr_cemPvkdescriptorset;
			extern VkBuffer *smptr_cemPvkbuffer;
		#endif

		#define SMPTR_CEMuM_N 0
		#define SMPTR_CEMuM_A 1
		struct SMPTR_CEMsM
		{
			uint8_t Us;
			SMPTRtMI Ui;
			SMPTRtMA Ua;
			float Fd;
		};
		extern struct SMPTR_CEMsM *smptr_cemPm;
		extern uint32_t smptr_cemLm;

		void smptr_cemMset();
		void smptr_cemMread();
		void smptr_cemMloop();
		void smptr_cemMfree();
	#endif
#endif
