float smptm_v4Psrt[4 + 4 + 4] =
{
	1, 1, 1, 0,
	0, 0, 0, 1,
	0, 0, 0, 0
};

void smptm_v4Mset()
{
	*(uint32_t *)(smptm_v4Psrt + 3) = 0xFFFFu;
}

void smptm_v4Mq(float Fx, float Fy, float Fz, float Pq[4])
{
	float c1 = cosf(Fx / 2);
	float s1 = sinf(Fx / 2);
	float c2 = cosf(Fy / 2);
	float s2 = sinf(Fy / 2);
	float c3 = cosf(Fz / 2);
	float s3 = sinf(Fz / 2);

	//.i ZYX
	Pq[0] = s1 * c2 * c3 + c1 * s2 * s3;
	Pq[1] = c1 * s2 * c3 - s1 * c2 * s3;
	Pq[2] = c1 * c2 * s3 + s1 * s2 * c3;
	Pq[3] = c1 * c2 * c3 - s1 * s2 * s3;
	//.i XYZ
//	Pq[0] = s1 * c2 * c3 - c1 * s2 * s3;
//	Pq[1] = c1 * s2 * c3 + s1 * c2 * s3;
//	Pq[2] = c1 * c2 * s3 - s1 * s2 * c3;
//	Pq[3] = c1 * c2 * c3 + s1 * s2 * s3;
}

void smptm_v4Mqi(float Pq[4])
{
	Pq[0] = -Pq[0];
	Pq[1] = -Pq[1];
	Pq[2] = -Pq[2];
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

void smptm_v4Mq2m(const float Pq[4], float Pm[16])
{
	float xy = Pq[0] * Pq[1];
	float xz = Pq[0] * Pq[2];
	float xw = Pq[0] * Pq[3];
	float yz = Pq[1] * Pq[2];
	float yw = Pq[1] * Pq[3];
	float zw = Pq[2] * Pq[3];
	float x_squared = Pq[0] * Pq[0];
	float y_squared = Pq[1] * Pq[1];
	float z_squared = Pq[2] * Pq[2];

	Pm[0] = 1 - 2 * (y_squared + z_squared);
	Pm[1] = 2 * (xy - zw);
	Pm[2] = 2 * (xz + yw);
	Pm[4] = 2 * (xy + zw);
	Pm[5] = 1 - 2 * (x_squared + z_squared);
	Pm[6] = 2 * (yz - xw);
	Pm[8] = 2 * (xz - yw);
	Pm[9] = 2 * (yz + xw);
	Pm[10] = 1 - 2 * (x_squared + y_squared);
}

void smptm_v4Mm(const float Pa[4], const float Pb[4], float Pq[4])
{
	Pq[0] = Pa[3] * Pb[0] + Pa[0] * Pb[3] + Pa[1] * Pb[2] - Pa[2] * Pb[1];
	Pq[1] = Pa[3] * Pb[1] - Pa[0] * Pb[2] + Pa[1] * Pb[3] + Pa[2] * Pb[0];
	Pq[2] = Pa[3] * Pb[2] + Pa[0] * Pb[1] - Pa[1] * Pb[0] + Pa[2] * Pb[3];
	Pq[3] = Pa[3] * Pb[3] - Pa[0] * Pb[0] - Pa[1] * Pb[1] - Pa[2] * Pb[2];
}

void smptm_v4Mm4(const float Pa[16], const float Pb[4], float Pq[4])
{
	for (uint8_t U0 = 0; U0 < 4; ++U0) Pq[U0] = 0.0F;

	for (uint8_t U0 = 0; U0 < 4; ++U0)
		for (uint8_t U1 = 0; U1 < 4; ++U1)
			Pq[U0] += Pa[U1 * 4 + U0] * Pb[U1];
}

float smptm_v4Md(const float Pa[4], const float Pb[4])
{
	return Pa[0] * Pb[0] + Pa[1] * Pb[1] + Pa[2] * Pb[2] + Pa[3] * Pb[3];
}

void smptm_v4Mn(float Pq[4])
{
	float Fl = sqrtf(Pq[0] * Pq[0] + Pq[1] * Pq[1] + Pq[2] * Pq[2] + Pq[3] * Pq[3]);

	if (Fl == 0.0F)
	{
		Pq[0] = 0;
		Pq[1] = 0;
		Pq[2] = 0;
		Pq[3] = 1;
		return;
	}

	float Fn = 1.0F / Fl;
	Pq[0] *= Fn;
	Pq[1] *= Fn;
	Pq[2] *= Fn;
	Pq[3] *= Fn;
}

void smptm_v4Mna2b(const float Pa[4], const float Pb[4], float Ft, float Pq[4])
{
	float Pb0[4];
	if (smptm_v4Md(Pa, Pb) < 0.0F)
	{
		Pb0[0] = -Pb[0];
		Pb0[1] = -Pb[1];
		Pb0[2] = -Pb[2];
		Pb0[3] = -Pb[3];
	}
	else
	{
		memcpy(Pb0, Pb, sizeof(float) * 4);
	}

	Pq[0] = Pa[0] + (Pb0[0] - Pa[0]) * Ft;
	Pq[1] = Pa[1] + (Pb0[1] - Pa[1]) * Ft;
	Pq[2] = Pa[2] + (Pb0[2] - Pa[2]) * Ft;
	Pq[3] = Pa[3] + (Pb0[3] - Pa[3]) * Ft;

	smptm_v4Mn(Pq);
}
