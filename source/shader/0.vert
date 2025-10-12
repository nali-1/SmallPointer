#version 420

#define lBONE 52

layout(location = 0) in vec3 a_v;
layout(location = 1) in uint a_c1j1;

layout(std140, set = 0, binding = 0) uniform UBOS
{
	mat4 v;
	mat4 p;
} ubos;

struct PB
{
	mat4 i_bindpose;
	mat4 bindpose;
};
layout(std140, set = 0, binding = 1) uniform UBOB
{
	PB pb[lBONE];
} ubob;

struct PA
{
	vec4 s;//w1-2_start w3-4_end
	vec4 r;
	vec4 t;//w1-4_b
};
layout(std140, set = 0, binding = 2) uniform UBOA
{
	PA pa[lBONE];
} uboa;

layout(location = 0) out uint f_c;
//layout(location = 1) out uint f_t;

mat4 s2mat4(vec3 s)
{
	return mat4
	(
		s.x, 0.0, 0.0, 0.0,
		0.0, s.y, 0.0, 0.0,
		0.0, 0.0, s.z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

mat4 r2mat4(vec4 q)
{
	float x = q.x;
	float y = q.y;
	float z = q.z;
	float w = q.w;

	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	return mat4
	(
		1.0 - 2.0 * (yy + zz),	2.0 * (xy - wz),	2.0 * (xz + wy),	0.0,

		2.0 * (xy + wz),	1.0 - 2.0 * (xx + zz),	2.0 * (yz - wx),	0.0,

		2.0 * (xz - wy),	2.0 * (yz + wx),	1.0 - 2.0 * (xx + yy),	0.0,

		0.0,			0.0,			0.0,			1.0
	);
}

mat4 t2mat4(vec3 t)
{
	return mat4
	(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		t.x, t.y, t.z, 1.0
	);
}

void main()
{
	vec4 l_v = vec4(a_v, 1);
	uint l_j = (a_c1j1 >> 8) & 0xFFu;
	uint l_b = floatBitsToUint(uboa.pa[l_j].s.w);
	uint l_bs = l_b & 0xFFFFu;
	if (l_bs != 0xFFFFu)
	{
		l_v = ubob.pb[l_j].bindpose * t2mat4(uboa.pa[l_j].t.xyz) * r2mat4(uboa.pa[l_j].r) * s2mat4(uboa.pa[l_j].s.xyz) * ubob.pb[l_j].i_bindpose * l_v;
		uint l_be = (l_b >> (8+8)) & 0xFFFFu;
		for (uint l_0 = l_bs; l_0 < l_be; ++l_0)
		{
			uint l_0_0 = (floatBitsToUint(uboa.pa[l_0 / 4].t.w) >> l_0 % 4 * 8) & 0xFFu;

			l_v = ubob.pb[l_0_0].bindpose * t2mat4(uboa.pa[l_0_0].t.xyz) * r2mat4(uboa.pa[l_0_0].r) * s2mat4(uboa.pa[l_0_0].s.xyz) * ubob.pb[l_0_0].i_bindpose * l_v;
		}
	}
	l_v = t2mat4(uboa.pa[0].t.xyz) * r2mat4(uboa.pa[0].r) * s2mat4(uboa.pa[0].s.xyz) * l_v;

	gl_Position = ubos.p * ubos.v * l_v;

	f_c = a_c1j1 & 0xFFu;
//	f_t = (a_c1j1 >> 16) & 0xFFFFu;
}
