#ifndef SMPThSF
	#define SMPThSF

	extern uint32_t
		smpt_sfUwidth,
		smpt_sfUheight;

	#define SMPT_SFuS_EXIT 1
	#define SMPT_SFuS_RE 2
	#define SMPT_SFuS_RAW 4
	#define SMPT_SFuS_RENDER 8
	#define SMPT_SFuS_EXIT_RENDER 16
	#define SMPT_SFuS_EXIT_SERVER 32
	#define SMPT_SFuS_ANDROID_CREATE 64
	#define SMPT_SFuS_ANDROID_RE 128
	#define SMPT_SFuS_LINUX_ALSA 64
	extern uint8_t smpt_sfUstate;
#endif
