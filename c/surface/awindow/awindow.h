#ifndef SMPT_SFhAWD
	#define SMPT_SFhAWD

	extern ANativeWindow *smpt_sf_awdPnative_window;

	void smpt_sf_awdMcreated(ANativeActivity* activity, ANativeWindow* window);
	void smpt_sf_awdMresized(ANativeActivity* activity, ANativeWindow* window);
	void smpt_sf_awdMdestroyed(ANativeActivity* activity, ANativeWindow* window);
#endif
