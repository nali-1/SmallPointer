struct SMPTRsA *smptr_svaPa;
SMPTRtA smptr_svaLa = 0;

static uint8_t Psync[SMPTRlA] = {0};

void smptr_svaMset()
{
	//! test
	++smptr_svaLa;
	smptr_svaPa = malloc(sizeof(struct SMPTRsA) * smptr_svaLa);
	smptr_svaPa[0].Ua = 0;
	smptr_svaPa[0].Lv = 3 + 3;
	smptr_svaPa[0].Pv = malloc(sizeof(float) * 3 * smptr_svaPa[0].Lv);
	smptr_svaPa[0].Pc = malloc(sizeof(uint8_t) * smptr_svaPa[0].Lv);

	//.i up
	smptr_svaPa[0].Pv[0] = 0.0F;
	smptr_svaPa[0].Pv[1] = -2.0F;
	smptr_svaPa[0].Pv[2] = 2.0F;

	//.i left
	smptr_svaPa[0].Pv[3] = -1.0F;
	smptr_svaPa[0].Pv[4] = 0.0F;
	smptr_svaPa[0].Pv[5] = 2.0F;

	//.i right
	smptr_svaPa[0].Pv[6] = 1.0F;
	smptr_svaPa[0].Pv[7] = 0.0F;
	smptr_svaPa[0].Pv[8] = 2.0F;

	//.i up
	smptr_svaPa[0].Pv[9] = 0.0F;
	smptr_svaPa[0].Pv[10] = -0.1F;
	smptr_svaPa[0].Pv[11] = 2.0F;
	//.i left
	smptr_svaPa[0].Pv[12] = -0.1F;
	smptr_svaPa[0].Pv[13] = 0.1F;
	smptr_svaPa[0].Pv[14] = 2.0F;
	//.i right
	smptr_svaPa[0].Pv[15] = 0.1F;
	smptr_svaPa[0].Pv[16] = 0.1F;
	smptr_svaPa[0].Pv[17] = 2.0F;

	memset(smptr_svaPa[0].Pc, 0, sizeof(uint8_t) * smptr_svaPa[0].Lv);
	smptr_svaPa[0].Pc[0] = 15;
	smptr_svaPa[0].Pc[1] = 43;
	smptr_svaPa[0].Pc[2] = 0;

	Psync[0] = Psync[0] % 255 + 1;
	smptr_svaPa[0].Usync = Psync[0];
}

void smptr_svaMloop()
{
	//.i up
	smptr_svaPa[0].Pv[9] = -smptr_svuSu[0].Ptr[0] + 0.0F;
	smptr_svaPa[0].Pv[10] = -smptr_svuSu[0].Ptr[1] + -0.1F * 1.0F;
	smptr_svaPa[0].Pv[11] = -smptr_svuSu[0].Ptr[2] + 4.0F;
	//.i left
	smptr_svaPa[0].Pv[12] = -smptr_svuSu[0].Ptr[0] + -0.1F * 1.0F;
	smptr_svaPa[0].Pv[13] = -smptr_svuSu[0].Ptr[1] + 0.1F * 1.0F;
	smptr_svaPa[0].Pv[14] = -smptr_svuSu[0].Ptr[2] + 4.0F;
	//.i right
	smptr_svaPa[0].Pv[15] = -smptr_svuSu[0].Ptr[0] + 0.1F * 1.0F;
	smptr_svaPa[0].Pv[16] = -smptr_svuSu[0].Ptr[1] + 0.1F * 1.0F;
	smptr_svaPa[0].Pv[17] = -smptr_svuSu[0].Ptr[2] + 4.0F;

	smptr_svaPa[0].Pv[1] -= 0.1F / SMPTRuRW;

	Psync[0] = Psync[0] % 255 + 1;
	smptr_svaPa[0].Usync = Psync[0];
}

void smptr_svaMsend(SMPT_NWtU u)
{
	//SMPT_DBmN2L("smptr_svaLa %d", smptr_svaLa)
	*(SMPTRtA *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = smptr_svaLa;
	//*(SMPTRtA *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = 0;
	smptr_svPnet[u].Lnet += sizeof(SMPTRtA);

	for (SMPTRtA l0 = 0; l0 < smptr_svaLa; ++l0)
	{
		struct SMPTRsA Sa = smptr_svaPa[l0];

		//! cull
		//! to m
		if (1)
		{
			*(SMPTRtA *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sa.Ua;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtA);

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sa.Lv;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, Sa.Pv, sizeof(float) * 3 * Sa.Lv);
			smptr_svPnet[u].Lnet += (SMPTRtNET)(sizeof(float) * 3 * Sa.Lv);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, Sa.Pc, sizeof(uint8_t) * Sa.Lv);
			smptr_svPnet[u].Lnet += sizeof(uint8_t) * Sa.Lv;

			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = Sa.Usync;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);
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
