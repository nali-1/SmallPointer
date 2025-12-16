static float
	x00 = 0, y00 = 0,
	x01 = 0, y01 = 0;

static int Mset(void *p)
{
	smptm_v4Mset();

	smptrMset();
	#if SMPT_CM_SERVER
		smptr_svMset();
	#endif
	#ifdef SMPT_CM_CLIENT
		smptr_ceMset();

		smpt_rd_vkMset();
	//! audio android
//		al_set();
	#endif

	while (1)
	{
		AInputEvent *ainputevent_p = NULL;
		while (smpt_arPinput_queue != NULL && AInputQueue_getEvent(smpt_arPinput_queue, &ainputevent_p) >= 0)
		{
			if (AInputQueue_preDispatchEvent(smpt_arPinput_queue, ainputevent_p))
			{
				continue;
			}
			if (AInputEvent_getType(ainputevent_p) == AINPUT_EVENT_TYPE_MOTION)
			{
				size_t pointer_count = AMotionEvent_getPointerCount(ainputevent_p);
//				if (pointer_count == 1)
//				{
//					SMPT_DBmN2L("AINPUT_EVENT_TYPE_MOTION")
				int32_t action = AMotionEvent_getAction(ainputevent_p);
				int32_t actionType = action & AMOTION_EVENT_ACTION_MASK;

				float l_x = AMotionEvent_getX(ainputevent_p, 0);
				float l_y = AMotionEvent_getY(ainputevent_p, 0);

				if (actionType == AMOTION_EVENT_ACTION_MOVE)
				{
					//! config
					smpt_ceuPpoint[0] += (l_x - x00) / 4.0F;
					smpt_ceuPpoint[1] += (l_y - y00) / 4.0F;
				}
//					else if (/*actionType == AMOTION_EVENT_ACTION_DOWN || */actionType == AMOTION_EVENT_ACTION_UP)
//					{
//					}
				x00 = l_x;
				y00 = l_y;
//				}

				if (pointer_count == 2)
				{
					l_x = AMotionEvent_getX(ainputevent_p, 1);
					l_y = AMotionEvent_getY(ainputevent_p, 1);

					if (actionType == AMOTION_EVENT_ACTION_MOVE)
					{
						float l_x01 = l_x - x01;
						float l_y01 = l_y - y01;

						//! use m3x3
						smpt_ceuPinput[0] |= l_y01 < -2.0F ? SMPT_IPuKEY_W :
							l_y01 > 2.0F ? SMPT_IPuKEY_S : 0;
						smpt_ceuPinput[0] &= l_y01 < -2.0F ? 0xFFu - SMPT_IPuKEY_S :
							l_y01 > 2.0F ? 0xFFu - SMPT_IPuKEY_W : 0xFFu;

						smpt_ceuPinput[0] |= l_x01 < -2.0F ? SMPT_IPuKEY_A :
							l_x01 > 2.0F ? SMPT_IPuKEY_D : 0;
						smpt_ceuPinput[0] &= l_x01 < -2.0F ? 0xFFu - SMPT_IPuKEY_D :
							l_x01 > 2.0F ? 0xFFu - SMPT_IPuKEY_A : 0xFFu;
					}
					else
					{
						smpt_ceuPinput[0] &= 255 - (SMPT_IPuKEY_S | SMPT_IPuKEY_W | SMPT_IPuKEY_A | SMPT_IPuKEY_D);
					}

					x01 = l_x;
					y01 = l_y;
				}
			}
			AInputQueue_finishEvent(smpt_arPinput_queue, ainputevent_p, 1);
		}
	}
	return 0;
}

ANativeWindow *smpt_arPnative_window = NULL;
ANativeActivity *smpt_arPnative_activity;
AInputQueue *smpt_arPinput_queue = NULL;

static uint8_t a_state = 0;
#define A_STATE_WAIT 1
#define A_STATE_READY 2

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("onNativeWindowCreated")
	SMPT_DBmN2L("window %p", window)
	smpt_sfUwidth = ANativeWindow_getWidth(window);
	smpt_sfUheight = ANativeWindow_getHeight(window);
	SMPT_DBmN2L("smpt_sfUwidth %d", smpt_sfUwidth)
	SMPT_DBmN2L("smpt_sfUheight %d", smpt_sfUheight)
	smpt_arPnative_window = window;
	smpt_sfUstate |= SMPT_SFuS_RE;
}

static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("onNativeWindowResized")
	SMPT_DBmN2L("window %p", window)
	smpt_sfUwidth = ANativeWindow_getWidth(window);
	smpt_sfUheight = ANativeWindow_getHeight(window);
	SMPT_DBmN2L("smpt_sfUwidth %d", smpt_sfUwidth)
	SMPT_DBmN2L("smpt_sfUheight %d", smpt_sfUheight)
	smpt_arPnative_window = window;
	smpt_sfUstate |= SMPT_SFuS_RE;
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("onNativeWindowDestroyed")
	SMPT_DBmN2L("window %p", window)
	smpt_arPnative_window = NULL;
	smpt_sfUstate |= SMPT_SFuS_RE;
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
	SMPT_DBmN2L("onInputQueueCreated")
	smpt_arPinput_queue = queue;
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
	SMPT_DBmN2L("onInputQueueDestroyed")
	smpt_arPinput_queue = NULL;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	#ifdef SMPT_CM_DEBUG
		smpt_dbMset();
	#endif

	SMPT_DBmN2L("ANativeActivity_onCreate")
	if (!(a_state & A_STATE_READY))
	{
		a_state |= A_STATE_READY;
		SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, Mset, NULL))
	}
	activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
	activity->callbacks->onNativeWindowResized = onNativeWindowResized;
	activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
	activity->callbacks->onInputQueueCreated = onInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
	smpt_arPnative_activity = activity;
}

void smpt_arMwait()
{
	SMPT_DBmN2L("smpt_arMwait 0")
	while (!smpt_arPnative_window)
	{
		a_state |= A_STATE_WAIT;
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	if (a_state & A_STATE_WAIT)
	{
		smpt_rd_vk_sfMfree();
		smpt_rd_vk_sfMmake();

		smpt_sfUstate |= SMPT_SFuS_RE;
		a_state &= 0xFFu - A_STATE_WAIT;
	}
	SMPT_DBmN2L("smpt_arMwait 1")
}
