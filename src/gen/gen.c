void smptgMsend()
{
	SMPT_DBmR2L("mkdir %d", mkdir(SMPTFcHOME, S_IRUSR | S_IWUSR | S_IXUSR))
	remove(SMPTFcHOME_ASSET);

	smptg_kfMsend();

	smptg_mdMsend();
	smptg_mdMfree();
}
