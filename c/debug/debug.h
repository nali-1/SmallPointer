#ifndef SMPThDB
	#define SMPThDB

	#ifdef SMPT_CM_DEBUG
		#ifdef SMPT_CM_TEST
			void smpt_dbMerrno();
		#endif

		void smpt_dbMset();
		void smpt_dbMwrite(const char *Pformat, ...);
		void smpt_dbMfree();

		#define SMPT_DBmR2L(Pformat, ...) smpt_dbMwrite(Pformat, ##__VA_ARGS__);

		#define SMPT_DBmW2L(Pformat, ...) smpt_dbMwrite(Pformat, ##__VA_ARGS__);

		#define SMPT_DBmN2L(Pformat, ...) smpt_dbMwrite(Pformat, ##__VA_ARGS__);
	#else
		#define SMPT_DBmR2L(Pformat, ...) __VA_ARGS__;

		#define SMPT_DBmW2L(Pformat, ...) smpt_dbMwrite(Pformat, ##__VA_ARGS__);

		#define SMPT_DBmN2L(Pformat, ...)
	#endif
#endif
