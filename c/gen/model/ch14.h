#define lH14T (1024*8)

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
