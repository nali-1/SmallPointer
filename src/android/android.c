static float
	x00 = 0, y00 = 0,
	x01 = 0, y01 = 0;

static int s1_set(void *p)
{
	smptrMset();
	#if SMPT_CM_SERVER
		ls_set();
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
					lcu_xy_p[0] = l_x - x00;
					lcu_xy_p[1] = l_y - y00;
				}
				else
				{
					lcu_xy_p[0] = 0;
					lcu_xy_p[1] = 0;
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

						lcu_k |= l_y01 < -2.0F ? SMPTRB_K_W :
							l_y01 > 2.0F ? SMPTRB_K_S : 0;
						lcu_k &= l_y01 < -2.0F ? 0xFFu - SMPTRB_K_S :
							l_y01 > 2.0F ? 0xFFu - SMPTRB_K_W : 0xFFu;

						lcu_k |= l_x01 < -2.0F ? SMPTRB_K_A :
							l_x01 > 2.0F ? SMPTRB_K_D : 0;
						lcu_k &= l_x01 < -2.0F ? 0xFFu - SMPTRB_K_D :
							l_x01 > 2.0F ? 0xFFu - SMPTRB_K_A : 0xFFu;
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
	SMPT_DBmN2L("window %p", window)
	smpt_sfUwidth = ANativeWindow_getWidth(window);
	smpt_sfUheight = ANativeWindow_getHeight(window);
	smpt_arPnative_window = window;
}

static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("window resize")
	smpt_sfUwidth = ANativeWindow_getWidth(window);
	smpt_sfUheight = ANativeWindow_getHeight(window);
	smpt_sfUstate |= SMPT_SFuS_RE;
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	SMPT_DBmN2L("window 0")
	smpt_arPnative_window = NULL;
	smpt_sfUstate |= SMPT_SFuS_RE;
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
	smpt_arPinput_queue = queue;
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
	smpt_arPinput_queue = NULL;
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	#ifdef SMPT_CM_DEBUG
		smpt_db_set();
	#endif

	SMPT_DBmN2L("ANativeActivity_onCreate")
	if (!(a_state & A_STATE_READY))
	{
		a_state |= A_STATE_READY;
		SMPT_DBmN2L("scene")
		SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, s1_set, NULL))
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
}
