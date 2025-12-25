ANativeWindow *smpt_sf_awdPnative_window = NULL;

void smpt_sf_awdMcreated(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("onNativeWindowCreated")
	SMPT_DBmN2L("window %p", window)
	smpt_sfUwidth = ANativeWindow_getWidth(window);
	smpt_sfUheight = ANativeWindow_getHeight(window);
	SMPT_DBmN2L("smpt_sfUwidth %d", smpt_sfUwidth)
	SMPT_DBmN2L("smpt_sfUheight %d", smpt_sfUheight)
	smpt_sf_awdPnative_window = window;
	smpt_sfUstate |= SMPT_SFuS_RE;
}

void smpt_sf_awdMresized(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("onNativeWindowResized")
	SMPT_DBmN2L("window %p", window)
	smpt_sfUwidth = ANativeWindow_getWidth(window);
	smpt_sfUheight = ANativeWindow_getHeight(window);
	SMPT_DBmN2L("smpt_sfUwidth %d", smpt_sfUwidth)
	SMPT_DBmN2L("smpt_sfUheight %d", smpt_sfUheight)
	smpt_sf_awdPnative_window = window;
	smpt_sfUstate |= SMPT_SFuS_RE;
}

void smpt_sf_awdMdestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("onNativeWindowDestroyed")
	SMPT_DBmN2L("window %p", window)
	smpt_sf_awdPnative_window = NULL;
	smpt_sfUstate |= SMPT_SFuS_RE;
}
