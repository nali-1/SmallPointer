#define xO \
	X("Font") \
	X("Space")
#define lOF (sizeof(Pof) / sizeof(Pof[0]))
static const char *Pof[] =
{
	#define X(N) SMPTFcFACTORY_MODEL "/" N ".glb",
		xO
	#undef X
};
#ifdef SMPTR_MDxO0
	static const char *Pon0[] =
	{
		#define X(V, N) N,
			SMPTR_MDxO0
		#undef X
	};
#endif
#ifdef SMPTR_MDxO1
	static const char *Pon1[] =
	{
		#define X(V, N) N,
			SMPTR_MDxO1
		#undef X
	};
#endif
static const char **Pon[] =
{
	#ifdef SMPTR_MDxO0
		Pon0,
	#endif
	#ifdef SMPTR_MDxO1
		Pon1,
	#endif
};
static const uint8_t Ponl[] =
{
	#ifdef SMPTR_MDxO0
		sizeof(Pon0) / sizeof(Pon0[0]),
	#endif
	#ifdef SMPTR_MDxO1
		sizeof(Pon1) / sizeof(Pon1[0]),
	#endif
};

#define xM \
	X("SuperCutePomi", 1, "ArmatureSuperCutePomi") \
	X("Ui", 2, "ArmatureUi", "ArmatureCroakie")
#define lMF (sizeof(Pmf) / sizeof(Pmf[0]))
static const char *Pmf[] =
{
	#define X(N, La, ...) SMPTFcFACTORY_MODEL "/" N ".glb",
		xM
	#undef X
};
static const char *Pma[] =
{
	#define X(N, La, ...) __VA_ARGS__,
		xM
	#undef X
};
static const uint8_t Pmal[] =
{
	#define X(N, La, ...) La,
		xM
	#undef X
};

#ifdef SMPTR_MDxM0
	static const char *Pmn0[] =
	{
		#define X(V, N) N,
			SMPTR_MDxM0
		#undef X
	};
#endif
#ifdef SMPTR_MDxM1
	static const char *Pmn1[] =
	{
		#define X(V, N) N,
			SMPTR_MDxM1
		#undef X
	};
#endif
static const char **Pmn[] =
{
	#ifdef SMPTR_MDxM0
		Pmn0,
	#endif
	#ifdef SMPTR_MDxM1
		Pmn1,
	#endif
};
static const uint8_t Pmnl[] =
{
	#ifdef SMPTR_MDxM0
		sizeof(Pmn0) / sizeof(Pmn0[0]),
	#endif
	#ifdef SMPTR_MDxM1
		sizeof(Pmn1) / sizeof(Pmn1[0]),
	#endif
};
