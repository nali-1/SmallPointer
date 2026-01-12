struct SMPTR_SV_ETTs *smptr_sv_ettP;

static void (*Pwork[])(SMPTRtMI) =
{
	#define X(V, M) M,
		SMPTR_ETTx
	#undef X
};

void smptr_sv_ettMset()
{
	smptr_sv_ettP = malloc(sizeof(struct SMPTR_SV_ETTs));
	smptr_sv_ett_pmMset();
}

void smptr_sv_ettMloop()
{
	for (SMPTRtMI U0 = 0; U0 < smptr_svmLm; ++U0)
	{
		Pwork[smptr_sv_ettP[U0].Uwork](U0);
	}
}

void smptr_sv_ettMfree()
{
	smptr_sv_ett_pmMfree();
	free(smptr_sv_ettP);
}
