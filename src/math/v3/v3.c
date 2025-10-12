//const int8_t smptm_v3Ppath[3] =
//{
//	-1,
//	0,
//	1
//};

//void smptm_v3Mq2m(const float q[3], float w[16])
//{
//	float xy = q[0] * q[1];
//	float xz = q[0] * q[2];
//	float x = q[0];
//	float yz = q[1] * q[2];
//	float y = q[1];
//	float z = q[2];
//	float x_squared = q[0] * q[0];
//	float y_squared = q[1] * q[1];
//	float z_squared = q[2] * q[2];
//
//	w[0] = 1 - 2 * (y_squared + z_squared);
//	w[1] = 2 * (xy - z);
//	w[2] = 2 * (xz + y);
//	w[4] = 2 * (xy + z);
//	w[5] = 1 - 2 * (x_squared + z_squared);
//	w[6] = 2 * (yz - x);
//	w[8] = 2 * (xz - y);
//	w[9] = 2 * (yz + x);
//	w[10] = 1 - 2 * (x_squared + y_squared);
//}

//uint8_t smptm_v3Mray(float Pa[3], float Pb[3], float Pc[3])
//{
//	float b2a_x = Pa[0] - Pb[0];
//	float b2a_y = Pa[1] - Pb[1];
//	float b2a_z = Pa[2] - Pb[2];

//	float b2a_l = sqrtf(SMPTM_V3mLENGTH(b2a_x, b2a_y, b2a_z));
//	float c_l = sqrtf(SMPTM_V3mLENGTH(Pc[0], Pc[1], Pc[2]));

//	float s = b2a_l - c_l;

//	float x = Pa[0] - (Pb[0] + Pc[0] * s);
//	float y = Pa[1] - (Pb[1] + Pc[1] * s);
//	float z = Pa[2] - (Pb[2] + Pc[2] * s);

//	return
//		x >= -1 && x <= 1 &&
//		y >= -1 && y <= 1 &&
//		z >= -1 && z <= 1;
//}
