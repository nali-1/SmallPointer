#ifndef SMPThAR
	#define SMPThAR

	extern ANativeWindow *smpt_arPnative_window;
	extern ANativeActivity *smpt_arPnative_activity;
	extern AInputQueue *smpt_arPinput_queue;

	void smpt_arMwait();
#endif
