const float smptm_v4Psrt[4 + 4 + 4] =
{
	1, 1, 1, 0,
	0, 0, 0, 1,
	0, 0, 0, 0
};

void smptm_v4Mq(float x, float y, float z, float w[4])
{
	float c1 = cosf(x / 2);
	float s1 = sinf(x / 2);
	float c2 = cosf(y / 2);
	float s2 = sinf(y / 2);
	float c3 = cosf(z / 2);
	float s3 = sinf(z / 2);

	//.i ZYX
	w[0] = s1 * c2 * c3 + c1 * s2 * s3;
	w[1] = c1 * s2 * c3 - s1 * c2 * s3;
	w[2] = c1 * c2 * s3 + s1 * s2 * c3;
	w[3] = c1 * c2 * c3 - s1 * s2 * s3;
	//.i XYZ
//	w[0] = s1 * c2 * c3 - c1 * s2 * s3;
//	w[1] = c1 * s2 * c3 + s1 * c2 * s3;
//	w[2] = c1 * c2 * s3 - s1 * s2 * c3;
//	w[3] = c1 * c2 * c3 + s1 * s2 * s3;
}

//! test
//void smptm_v4Mq2xyz(float *rx, float *ry, float *rz, float q[4])
//{
//	float n = sqrtf(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
//	q[0] /= n;
//	q[1] /= n;
//	q[2] /= n;
//	q[3] /= n;
//
//	float sinr = 2.0F * (q[3] * q[0] + q[1] * q[2]);
//	float cosr = 1.0F - 2.0F * (q[0] * q[0] + q[1] * q[1]);
//	*rx = atan2f(sinr, cosr);
//
//	float sinp = 2.0F * (q[3] * q[1] - q[2] * q[0]);
//	if (fabsf(sinp) >= 1)
//		*ry = copysignf(M_PI / 2, sinp);
//	else
//		*ry = asinf(sinp);
//
//	float siny = 2.0F * (q[3] * q[2] + q[0] * q[1]);
//	float cosy = 1.0F - 2.0F * (q[1] * q[1] + q[2] * q[2]);
//	*rz = atan2f(siny, cosy);
//}
//
//void smptm_v4Mq2zyx(float *rx, float *ry, float *rz, float q[4])
//{
//	float n = sqrtf(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
//	q[0] /= n;
//	q[1] /= n;
//	q[2] /= n;
//	q[3] /= n;
//
//	float siny = 2.0F * (q[3] * q[2] + q[0] * q[1]);
//	float cosy = 1.0F - 2.0F * (q[1] * q[1] + q[2] * q[2]);
//	*rz = atan2f(siny, cosy);
//
//	float sinp = 2.0F * (q[3] * q[1] - q[2] * q[0]);
//	if (fabsf(sinp) >= 1)
//		*ry = copysignf(M_PI / 2, sinp);
//	else
//		*ry = asinf(sinp);
//
//	float sinr = 2.0F * (q[3] * q[0] + q[1] * q[2]);
//	float cosr = 1.0F - 2.0F * (q[0] * q[0] + q[1] * q[1]);
//	*rx = atan2f(sinr, cosr);
//}

void smptm_v4Mq2m(const float q[4], float w[16])
{
	float xy = q[0] * q[1];
	float xz = q[0] * q[2];
	float xw = q[0] * q[3];
	float yz = q[1] * q[2];
	float yw = q[1] * q[3];
	float zw = q[2] * q[3];
	float x_squared = q[0] * q[0];
	float y_squared = q[1] * q[1];
	float z_squared = q[2] * q[2];

	w[0] = 1 - 2 * (y_squared + z_squared);
	w[1] = 2 * (xy - zw);
	w[2] = 2 * (xz + yw);
	w[4] = 2 * (xy + zw);
	w[5] = 1 - 2 * (x_squared + z_squared);
	w[6] = 2 * (yz - xw);
	w[8] = 2 * (xz - yw);
	w[9] = 2 * (yz + xw);
	w[10] = 1 - 2 * (x_squared + y_squared);
}

void smptm_v4Mm(const float a[4], const float b[4], float w[4])
{
	w[0] = a[3] * b[0] + a[0] * b[3] + a[1] * b[2] - a[2] * b[1];
	w[1] = a[3] * b[1] - a[0] * b[2] + a[1] * b[3] + a[2] * b[0];
	w[2] = a[3] * b[2] + a[0] * b[1] - a[1] * b[0] + a[2] * b[3];
	w[3] = a[3] * b[3] - a[0] * b[0] - a[1] * b[1] - a[2] * b[2];
}

void smptm_v4Mm4(const float a[16], const float b[4], float w[4])
{
	for (uint8_t row = 0; row < 4; ++row)
	{
		w[row] = 0.0F;
		for (int col = 0; col < 4; ++col)
		{
			w[row] += a[col * 4 + row] * b[col];
		}
	}
}
