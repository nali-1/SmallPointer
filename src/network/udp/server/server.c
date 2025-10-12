struct sCE
{
	struct sockaddr_in Sce;
	socklen_t Lce;
};
static struct sCE Pce[SMPT_NWlU];

static int Isv;
void smpt_nw_udp_svMset()
{
//	SMPTTmE

	SMPT_DBmR2L("socket %d", Isv = socket(AF_INET, SOCK_DGRAM, 0))
//	SMPTTmE

	SMPT_DBmR2L("fcntl %d", fcntl(Isv, F_SETFL, fcntl(Isv, F_GETFL, 0) | O_NONBLOCK))
//	SMPTTmE

	struct sockaddr_in Ssv = {0};
	Ssv.sin_family = AF_INET;
	Ssv.sin_addr.s_addr = INADDR_ANY;
	Ssv.sin_port = SMPT_NWuPORT;
	SMPT_DBmR2L("bind %d", bind(Isv, (struct sockaddr*)&Ssv, sizeof(Ssv)))
//	SMPTTmE
}

void smpt_nw_udp_svMsend(SMPT_NWtU u)
{
	sendto(Isv, smptr_svPnet[u].Pnet, smptr_svPnet[u].Lnet, 0, (struct sockaddr *)&Pce[u].Sce, Pce[u].Lce);
//	SMPTTmE
}

static struct sockaddr_in Sce;
static socklen_t Lce = sizeof(Sce);
void smpt_nw_udp_svMread()
{
	while (recvfrom(Isv, smptr_svPnet[0].Pnet, SMPTRlNET, 0, (struct sockaddr*)&Sce, &Lce) > 0)
	{
		//SMPT_DBmN2L("S smptr_svPnet[0].Lnet %d", smptr_svPnet[0].Lnet)
		//SMPT_DBmN2L("Sce.sin_addr.s_addr %d", Sce.sin_addr.s_addr)
		//SMPT_DBmN2L("Sce.sin_port %d", Sce.sin_port)
		for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
		{
			//SMPT_DBmN2L("smpt_nwPu[l0] %d", smpt_nwPu[l0])
			if (Sce.sin_addr.s_addr == smpt_nwPu[l0])
			{
				Pce[l0].Sce = Sce;
				Pce[l0].Lce = Lce;
				smptr_svMread(l0);
				break;
			}
		}
	}
//	SMPTTmE
}

void smpt_nw_udp_svMfree()
{
	close(Isv);
}
