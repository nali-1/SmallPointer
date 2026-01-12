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

//	void Mclaim(size_t L)
//	{
//		size_t Lpage = sysconf(_SC_PAGESIZE);
//		uintptr_t Uend = ((uintptr_t)L + Lpage - 1) & ~(Lpage - 1);
//		void *P = mmap(NULL, Uend, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//	}
//
//	void Mprotect(void *P, size_t L)
//	{
//		size_t Lpage = sysconf(_SC_PAGESIZE);
//
//		uintptr_t Ustart = (uintptr_t)P & ~(Lpage - 1);
//		uintptr_t Uend = ((uintptr_t)P + L + Lpage - 1) & ~(Lpage - 1);
//
//		mprotect((void *)Ustart, Uend - Ustart, PROT_READ);
//	}
//
//	void Munprotect(void *P, size_t L)
//	{
//		size_t Lpage = sysconf(_SC_PAGESIZE);
//
//		uintptr_t Ustart = (uintptr_t)P & ~(Lpage - 1);
//		uintptr_t Uend = ((uintptr_t)P + L + Lpage - 1) & ~(Lpage - 1);
//
//		mprotect((void *)Ustart, Uend - Ustart, PROT_READ | PROT_WRITE);
//	}
#endif
