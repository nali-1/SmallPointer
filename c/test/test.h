#ifndef SMPThT
	#define SMPThT

	#ifdef SMPT_CM_TEST
		#define SMPTTmP(d_bl, l_bl) \
			if ((d_bl) >= (l_bl)) \
			{ \
				exit(EXIT_FAILURE); \
			}

		#define SMPTTmE smpt_dbMerrno();
	#else
		#define SMPTTmP(d_bl, l_bl)

		#define SMPTTmE
	#endif
#endif
