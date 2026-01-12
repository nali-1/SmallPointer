void smptr_sv_ett_uiMwork(SMPTRtMI Umi)
{
	struct SMPTRsM *Sm = smptr_svmPm + Umi;
	Sm->Sm0.Ptr[SMPTRMuBY] += 1.0F / SMPTRuRW;
}
