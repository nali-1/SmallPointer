#ifndef SMPT_CM_ST_JAVA
#ifndef SMPT_CM_ST_JAVA_ANDROID
	#ifndef SMPTRhCEA
		#define SMPTRhCEA

		#ifdef SMPT_CM_VK
			extern VkDescriptorSet *smptr_ceaPvkdescriptorset;
			extern VkBuffer *smptr_ceaPvkbuffer;
		#endif

		struct SMPTR_CEAsA
		{
			struct SMPTRsA Sa;

			uint8_t Usync;
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
#endif
#endif
