static AInputQueue *Pinput_queue = NULL;

void smpt_ip_aipMcreated(ANativeActivity* activity, AInputQueue* queue)
{
	SMPT_DBmN2L("onInputQueueCreated")
	Pinput_queue = queue;
}

void smpt_ip_aipMdestroyed(ANativeActivity* activity, AInputQueue* queue)
{
	SMPT_DBmN2L("onInputQueueDestroyed")
	Pinput_queue = NULL;
}

void smpt_ip_aipMloop()
{
	#ifdef SMPT_CM_CLIENT
		float
			Fx00 = 0, Fy00 = 0,
			Fx10 = 0, Fy10 = 0,
			Fx20 = 0, Fy20 = 0;
	#endif
	while (1)
	{
		AInputEvent *Painputevent = NULL;
		while (Pinput_queue != NULL && AInputQueue_getEvent(Pinput_queue, &Painputevent) >= 0)
		{
			if (AInputQueue_preDispatchEvent(Pinput_queue, Painputevent))
			{
				continue;
			}
			#ifdef SMPT_CM_CLIENT
				if (AInputEvent_getType(Painputevent) == AINPUT_EVENT_TYPE_MOTION)
				{
					size_t Upointer_count = AMotionEvent_getPointerCount(Painputevent);
					int32_t Uaction = AMotionEvent_getAction(Painputevent);
					int32_t Uaction_type = Uaction & AMOTION_EVENT_ACTION_MASK;

					float Fx0 = AMotionEvent_getX(Painputevent, 0);
					float Fy0 = AMotionEvent_getY(Painputevent, 0);

					if (Uaction_type == AMOTION_EVENT_ACTION_MOVE)
					{
						//! config
						smpt_ceuPpoint[0] += (Fx0 - Fx00) / 4.0F;
						smpt_ceuPpoint[1] += (Fy0 - Fy00) / 4.0F;
					}
					Fx00 = Fx0;
					Fy00 = Fy0;

					if (Upointer_count >= 2)
					{
						float Fx1 = AMotionEvent_getX(Painputevent, 1);
						float Fy1 = AMotionEvent_getY(Painputevent, 1);

						if (Uaction_type == AMOTION_EVENT_ACTION_MOVE)
						{
							float Fx01 = Fx1 - Fx10;
							float Fy01 = Fy1 - Fy10;

							smpt_ceuPinput[0] |= Fy01 < -2.0F ? SMPT_IPuKEY_W : 0;
							smpt_ceuPinput[0] &= Fy01 < -2.0F ? 255 : 255 - SMPT_IPuKEY_W;
							smpt_ceuPinput[0] |= Fy01 > 2.0F ? SMPT_IPuKEY_S : 0;
							smpt_ceuPinput[0] &= Fy01 > 2.0F ? 255 : 255 - SMPT_IPuKEY_S;
							smpt_ceuPinput[0] |= Fx01 > 2.0F ? SMPT_IPuKEY_D : 0;
							smpt_ceuPinput[0] &= Fx01 > 2.0F ? 255 : 255 - SMPT_IPuKEY_D;
							smpt_ceuPinput[0] |= Fx01 < -2.0F ? SMPT_IPuKEY_A : 0;
							smpt_ceuPinput[0] &= Fx01 < -2.0F ? 255 : 255 - SMPT_IPuKEY_A;
						}
						else
						{
							smpt_ceuPinput[0] &= 255 - (SMPT_IPuKEY_S | SMPT_IPuKEY_W | SMPT_IPuKEY_A | SMPT_IPuKEY_D);
						}

						Fx10 = Fx1;
						Fy10 = Fy1;
					}
					if (Upointer_count == 3)
					{
						float Fx2 = AMotionEvent_getX(Painputevent, 2);
						float Fy2 = AMotionEvent_getY(Painputevent, 2);

						float Fx02 = Fx2 - Fx20;
						float Fy02 = Fy2 - Fy20;

						smpt_ceuPinput[0] |= Fy02 < -2.0F ? SMPT_IPuKEY_SPACE : 0;
						smpt_ceuPinput[0] &= Fy02 < -2.0F ? 255 : 255 - SMPT_IPuKEY_SPACE;
						smpt_ceuPinput[0] |= Fy02 > 2.0F ? SMPT_IPuKEY_LEFT_SHIFT : 0;
						smpt_ceuPinput[0] &= Fy02 > 2.0F ? 255 : 255 - SMPT_IPuKEY_LEFT_SHIFT;

						Fx20 = Fx2;
						Fy20 = Fy2;
					}
				}
			#endif
			AInputQueue_finishEvent(Pinput_queue, Painputevent, 1);
		}
	}
}
