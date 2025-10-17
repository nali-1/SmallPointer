struct SMPTRsA *smptr_svaPa;
SMPTRtA smptr_svaLa = 0;

void smptr_svaMset()
{
	//! test
	++smptr_svaLa;
	smptr_svaPa = malloc(sizeof(struct SMPTRsA) * smptr_svaLa);
	smptr_svaPa[0].Ua = 0;
	smptr_svaPa[0].Lv = 3;
	smptr_svaPa[0].Pv = malloc(sizeof(float) * 3 * smptr_svaPa[0].Lv);
	smptr_svaPa[0].Pc = malloc(sizeof(uint8_t) * smptr_svaPa[0].Lv);
	smptr_svaPa[0].Pv[0] = 0;
	smptr_svaPa[0].Pv[1] = -1;
	smptr_svaPa[0].Pv[2] = 0;

	smptr_svaPa[0].Pv[3] = 1;
	smptr_svaPa[0].Pv[4] = 1;
	smptr_svaPa[0].Pv[5] = 0;

	smptr_svaPa[0].Pv[6] = -1;
	smptr_svaPa[0].Pv[7] = 1;
	smptr_svaPa[0].Pv[8] = 0;

	memset(smptr_svaPa[0].Pc, 0, sizeof(uint8_t) * smptr_svaPa[0].Lv);
}

void smptr_svaMloop()
{
}

void smptr_svaMsend(SMPT_NWtU u)
{
	//SMPT_DBmN2L("smptr_svaLa %d", smptr_svaLa)
	*(SMPTRtA *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = smptr_svaLa;
	smptr_svPnet[u].Lnet += sizeof(SMPTRtA);

	for (SMPTRtA l0 = 0; l0 < smptr_svaLa; ++l0)
	{
		struct SMPTRsA a = smptr_svaPa[l0];

		//! cull
		if (1)
		{
			*(SMPTRtA *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = a.Ua;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtA);

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = a.Lv;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, a.Pv, sizeof(float) * 3 * a.Lv);
			smptr_svPnet[u].Lnet += sizeof(float) * 3 * a.Lv;

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, a.Pc, sizeof(uint8_t) * a.Lv);
			smptr_svPnet[u].Lnet += sizeof(uint8_t) * a.Lv;
		}
		else
		{
			*(SMPTRtA *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = l0 + 1;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtA);
		}
	}
}

void smptr_svaMread(SMPT_NWtU u)
{
}

void smptr_svaMfread()
{
}

void smptr_svaMfsend()
{
}

void smptr_svaMfree()
{
	for (SMPTRtA l0 = 0; l0 < smptr_svaLa; ++l0)
	{
		free(smptr_svaPa[l0].Pv);
		free(smptr_svaPa[l0].Pc);
	}
	free(smptr_svaPa);
}
