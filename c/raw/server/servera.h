#ifndef SMPTRhSVA
	#define SMPTRhSVA

	extern struct SMPTRsA *smptr_svaPa;
	extern SMPTRtA smptr_svaLa;

	void smptr_svaMset();
	void smptr_svaMloop();
	void smptr_svaMsend(SMPT_NWtU u);
	void smptr_svaMread(SMPT_NWtU u);
	void smptr_svaMfread();
	void smptr_svaMfsend();
	void smptr_svaMfree();
#endif
