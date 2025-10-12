static int Isv;
static struct sockaddr_in Ssv = {0};
static socklen_t Lsv = sizeof(Ssv);

void smpt_nw_udp_ceMset()
{
//	SMPTTmE

	SMPT_DBmR2L("socket %d", Isv = socket(AF_INET, SOCK_DGRAM, 0))
//	SMPTTmE

	SMPT_DBmR2L("fcntl %d", fcntl(Isv, F_SETFL, fcntl(Isv, F_GETFL, 0) | O_NONBLOCK))
//	SMPTTmE

	Ssv.sin_family = AF_INET;
	Ssv.sin_addr.s_addr = SMPT_NWuIP;
	Ssv.sin_port = SMPT_NWuPORT;
//	SMPTTmE
}

void smpt_nw_udp_ceMsend()
{
	sendto(Isv, smptr_cePnet, smptr_ceLnet, 0, (struct sockaddr *)&Ssv, Lsv);
//	SMPTTmE
}

void smpt_nw_udp_ceMread()
{
	if (recvfrom(Isv, smptr_cePnet, SMPTRlNET, 0, (struct sockaddr*)&Ssv, &Lsv) > 0)
	{
		smptr_ceMread();
	}
}

void smpt_nw_udp_ceMfree()
{
	close(Isv);
}
