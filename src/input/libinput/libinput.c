static int open_restricted(const char *path, int flags, void *user_data)
{
	int fd = open(path, flags);
	SMPT_DBmN2L("open %d", fd)
	return fd;
}

static void close_restricted(int fd, void *user_data)
{
	close(fd);
}

static struct libinput_interface Sinterface =
{
	.open_restricted = open_restricted,
	.close_restricted = close_restricted
};

static struct libinput *Plip;
static struct udev *Pudev;

static void Mfree()
{
	SMPT_DBmR2L("libinput_unref %p", libinput_unref(Plip))
	SMPT_DBmR2L("udev_unref %p", udev_unref(Pudev))
}

void smpt_ip_lipMset()
{
	SMPT_DBmR2L("udev_new %p", Pudev = udev_new())

	SMPT_DBmR2L("libinput_udev_create_context %p", Plip = libinput_udev_create_context(&Sinterface, NULL, Pudev))

	SMPT_DBmR2L("libinput_udev_assign_seat %p", libinput_udev_assign_seat(Plip, "seat0"))
}

void smpt_ip_lipMloop()
{
	struct libinput_event *Pev;

	#ifdef SMPT_CM_CLIENT
		uint8_t state_main = 0;
		while (!state_main)
		{
			libinput_dispatch(Plip);

			while ((Pev = libinput_get_event(Plip)))
			{
				if (libinput_event_get_type(Pev) == LIBINPUT_EVENT_DEVICE_ADDED)
				{
					struct libinput_device *Pdv = libinput_event_get_device(Pev);
					if (libinput_device_config_dwt_is_available(Pdv))
					{
						SMPT_DBmR2L("libinput_device_config_dwt_set_enabled %d", libinput_device_config_dwt_set_enabled(Pdv, LIBINPUT_CONFIG_DWT_DISABLED))
						state_main |= 1;
					}
				}
				libinput_event_destroy(Pev);
			}
		}
	#endif

	while (!(smpt_sfUstate & SMPT_SFuS_EXIT))
	{
		libinput_dispatch(Plip);

		struct libinput_event_pointer *Pevpt;
//		struct libinput_event_gesture *Pevgt;

//		struct libinput_event_touch *Pevt;
//		uint32_t slot;

//		int Ifinger;
		while ((Pev = libinput_get_event(Plip)))
		{
			switch (libinput_event_get_type(Pev))
			{
				case LIBINPUT_EVENT_KEYBOARD_KEY:
					struct libinput_event_keyboard *Pevkb = libinput_event_get_keyboard_event(Pev);
					uint32_t key = libinput_event_keyboard_get_key(Pevkb);
					uint32_t state = libinput_event_keyboard_get_key_state(Pevkb);
					//SMPT_DBmN2L("libinput_event_keyboard_get_key %d", key)
					if (key == KEY_ESC)
						smptrMfree1();
					#ifdef SMPT_CM_CLIENT
						if (state == LIBINPUT_KEY_STATE_PRESSED)
						{
							if (key == KEY_A)
								smpt_ceuPinput[0] |= SMPT_IPuKEY_A;
							if (key == KEY_D)
								smpt_ceuPinput[0] |= SMPT_IPuKEY_D;
							if (key == KEY_W)
								smpt_ceuPinput[0] |= SMPT_IPuKEY_W;
							if (key == KEY_S)
								smpt_ceuPinput[0] |= SMPT_IPuKEY_S;
							if (key == KEY_SPACE)
								smpt_ceuPinput[0] |= SMPT_IPuKEY_SPACE;
							if (key == KEY_LEFTSHIFT)
								smpt_ceuPinput[0] |= SMPT_IPuKEY_LEFT_SHIFT;
						}
						else
						{
							if (key == KEY_A)
								smpt_ceuPinput[0] &= 255 - SMPT_IPuKEY_A;
							if (key == KEY_D)
								smpt_ceuPinput[0] &= 255 - SMPT_IPuKEY_D;
							if (key == KEY_W)
								smpt_ceuPinput[0] &= 255 - SMPT_IPuKEY_W;
							if (key == KEY_S)
								smpt_ceuPinput[0] &= 255 - SMPT_IPuKEY_S;
							if (key == KEY_SPACE)
								smpt_ceuPinput[0] &= 255 - SMPT_IPuKEY_SPACE;
							if (key == KEY_LEFTSHIFT)
								smpt_ceuPinput[0] &= 255 - SMPT_IPuKEY_LEFT_SHIFT;
						}
					#endif
					break;

				#ifdef SMPT_CM_CLIENT
					case LIBINPUT_EVENT_POINTER_MOTION:
						Pevpt = libinput_event_get_pointer_event(Pev);
						//SMPT_DBmN2L("libinput_event_pointer_get_dx %f", dx)
						//SMPT_DBmN2L("libinput_event_pointer_get_dy %f", dy)
						smpt_ceuPpoint[0] += libinput_event_pointer_get_dx(Pevpt);
						smpt_ceuPpoint[1] += libinput_event_pointer_get_dy(Pevpt);
						break;
//					case LIBINPUT_EVENT_GESTURE_HOLD_BEGIN:
//						Pevgt = libinput_event_get_gesture_event(Pev);
//						Ifinger = libinput_event_gesture_get_finger_count(Pevgt);
//						//SMPT_DBmN2L("libinput_event_gesture_get_finger_count %d", Ifinger)
//						if (Ifinger == 1)
//						{
//							smpt_ceuPinput[0] &= 255 - SMPT_IPuPOINT_PX - SMPT_IPuPOINT_NX - SMPT_IPuPOINT_PY - SMPT_IPuPOINT_NY;
//						}
//						break;
//					case LIBINPUT_EVENT_GESTURE_HOLD_END:
//						Pevgt = libinput_event_get_gesture_event(Pev);
//						Ifinger = libinput_event_gesture_get_finger_count(Pevgt);
//						//SMPT_DBmN2L("libinput_event_gesture_get_finger_count %d", Ifinger)
//						if (Ifinger == 1)
//						{
//							smpt_ceuPinput[0] &= 255 - SMPT_IPuPOINT_PX - SMPT_IPuPOINT_NX - SMPT_IPuPOINT_PY - SMPT_IPuPOINT_NY;
//						}
//						break;
					case LIBINPUT_EVENT_POINTER_BUTTON:
						Pevpt = libinput_event_get_pointer_event(Pev);
						uint32_t button = libinput_event_pointer_get_button(Pevpt);
						//SMPT_DBmN2L("libinput_event_pointer_get_button %d", button)
//						if (button == BTN_RIGHT)
//							smptrMfree1();
						break;

//					case LIBINPUT_EVENT_TOUCH_UP:
//						Pevt = libinput_event_get_touch_event(Pev);
//						slot = libinput_event_touch_get_slot(Pevt);
//						SMPT_DBmN2L("libinput_event_touch_get_slot %d", slot)
//						break;
//					case LIBINPUT_EVENT_TOUCH_DOWN:
//						Pevt = libinput_event_get_touch_event(Pev);
//						slot = libinput_event_touch_get_slot(Pevt);
//						SMPT_DBmN2L("libinput_event_touch_get_slot %d", slot)
//						break;
//					case LIBINPUT_EVENT_TOUCH_MOTION:
//						Pevt = libinput_event_get_touch_event(Pev);
//						slot = libinput_event_touch_get_slot(Pevt);
//						SMPT_DBmN2L("libinput_event_touch_get_slot %d", slot)
//						break;
//					case LIBINPUT_EVENT_TOUCH_CANCEL:
//						Pevt = libinput_event_get_touch_event(Pev);
//						slot = libinput_event_touch_get_slot(Pevt);
//						SMPT_DBmN2L("libinput_event_touch_get_slot %d", slot)
				#endif
			}
			libinput_event_destroy(Pev);
		}
	}
	Mfree();
}
