#define lH14T (1024*8)

static uint8_t *Ph14_t[lH14T];
static SMPTRtI *Ph14_ti[lH14T];
static uint32_t Ph14_tl[lH14T];
static uint32_t Lh14_i;

static SMPTRtI **Ph14_i;
static SMPTRtI *Ph14_il;

//.i https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
static uint64_t Mh14(uint8_t *P, uint8_t L)
{
	uint64_t h = 1469598103934665603ULL;
	for (uint8_t U0 = 0; U0 < L; U0++)
	{
		h ^= P[U0];
		//.i FNV prime 64bit
		h *= 1099511628211ULL;
	}
	return h;
}

static void Mh14_mesh(uint8_t *Pmix, uint16_t Ui, uint8_t Lm)
{
//	while (1)
//		SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))

//	SMPT_DBmN2L("Ui %d", Ui)
//	SMPT_DBmN2L("Ph14_il %p", Ph14_il)
//	SMPT_DBmN2L("Ph14_i %p", Ph14_i)
//	SMPT_DBmN2L("Ph14_il[%d] %d", Ui, Ph14_il[Ui])
//	SMPT_DBmN2L("Ph14_i[%d] %p", Ui, Ph14_i[Ui])
//	SMPT_DBmN2L("Ph14_i[%d] + Ph14_il[%d] %d", Ui, Ui, Ph14_i[Ui] + Ph14_il[Ui])

//	SMPT_DBmN2L("V0 %f", *(float *)Pmix)
//	SMPT_DBmN2L("V1 %f", *(float *)(Pmix + sizeof(float)))
//	SMPT_DBmN2L("V2 %f", *(float *)(Pmix + sizeof(float) * 2))
//	SMPT_DBmN2L("C %d", Pmix[sizeof(float) * 3])
//	SMPT_DBmN2L("J %d", Pmix[sizeof(float) * 3 + 1])

	uint16_t Uh14 = Mh14(Pmix, Lm) % lH14T;
	for (uint32_t U0 = 0; U0 < Ph14_tl[Uh14]; ++U0)
	{
		if (!memcmp(Ph14_t[Uh14] + Lm * U0, Pmix, Lm))
		{
			Ph14_i[Ui] = realloc(Ph14_i[Ui], sizeof(SMPTRtI) * (Ph14_il[Ui] + 1));
			Ph14_i[Ui][Ph14_il[Ui]] = Ph14_ti[Uh14][U0];
			++Ph14_il[Ui];
			return;
		}
	}

	//SMPT_DBmN2L("Ph14_il[%d] * sizeof(SMPTRtI) + sizeof(SMPTRtI) %d", Ui, Ph14_il[Ui] * sizeof(SMPTRtI) + sizeof(SMPTRtI))
	Ph14_i[Ui] = realloc(Ph14_i[Ui], sizeof(SMPTRtI) * (Ph14_il[Ui] + 1));
	Ph14_i[Ui][Ph14_il[Ui]] = Lh14_i;
	++Ph14_il[Ui];

	Ph14_ti[Uh14] = realloc(Ph14_ti[Uh14], sizeof(SMPTRtI) * (Ph14_tl[Uh14] + 1));
	Ph14_ti[Uh14][Ph14_tl[Uh14]] = Lh14_i;

	Ph14_t[Uh14] = realloc(Ph14_t[Uh14], Lm * (Ph14_tl[Uh14] + 1));
	memcpy(Ph14_t[Uh14] + Lm * Ph14_tl[Uh14], Pmix, Lm);
	//SMPT_DBmN2L("Ph14_t[Uh14] + Lm * Ph14_tl[Uh14] %p", Ph14_t[Uh14] + Lm * Ph14_tl[Uh14])
//	SMPT_DBmN2L("Lm %d", Lm)
//	for (uint8_t U0 = 0; U0 < 3; ++U0)
//		SMPT_DBmN2L("Pmix %d %f", U0, Pmix + U0 * sizeof(float))
	++Ph14_tl[Uh14];

	++Lh14_i;
}

static void Mh14_set(uint8_t L)
{
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		Ph14_t[U0] = malloc(sizeof(uint8_t));
		Ph14_ti[U0] = malloc(sizeof(SMPTRtI));
	}
	memset(Ph14_tl, 0, sizeof(uint32_t) * lH14T);
	Lh14_i = 0;

	Ph14_i = malloc(sizeof(SMPTRtI *) * L);
	SMPT_DBmN2L("Ph14_i %p", Ph14_i)
	for (uint8_t U0 = 0; U0 < L; ++U0)
	{
		Ph14_i[U0] = malloc(sizeof(SMPTRtI));
		SMPT_DBmN2L("Ph14_i[%d] %p", U0, Ph14_i[U0])
	}

	Ph14_il = malloc(sizeof(SMPTRtI) * L);
	memset(Ph14_il, 0, sizeof(SMPTRtI) * L);
}

static void Mh14_free(uint8_t L)
{
	for (uint8_t U0 = 0; U0 < L; ++U0)
		free(Ph14_i[U0]);
	free(Ph14_i);
	free(Ph14_il);

	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		free(Ph14_t[U0]);
		free(Ph14_ti[U0]);
	}
}
