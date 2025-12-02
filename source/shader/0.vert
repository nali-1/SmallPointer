#version 420

#define lBONE 52
#define lCOLOR 36/4

//! support more byte
//#define SMPTRtJW4
//#define SMPTRtRGBAL4

layout(location = 0) in vec3 Av;
layout(location = 1) in uint Ac;
layout(location = 2) in uint Aj;

layout(std140, set = 0, binding = 0) uniform bS
{
	mat4 Tv;
	mat4 Tp;
} Bs;

struct sB
{
	mat4 Tbindpose_i;
	mat4 Tbindpose_o;
};
layout(std140, set = 0, binding = 1) uniform bB
{
	sB Pb[lBONE];
} Bb;

struct sA
{
	vec4 Vs;//w1-2_start w3-4_end
	vec4 Vr;
	vec4 Vt;//w1-4_b
};
layout(std140, set = 0, binding = 2) uniform bA
{
	sA Pa[lBONE];
} Ba;

layout(std140, set = 0, binding = 3) uniform bC
{
	uvec4 Vc[lCOLOR];
} Bc;
layout(std140, set = 0, binding = 4) uniform bC1
{
	vec4 Vc;
} Bc1;

layout(location = 0) out vec4 Oc;
//layout(location = 1) out vec2 Ot;

mat4 Ms2mat4(vec3 Vs)
{
	return mat4
	(
		Vs.x, 0.0, 0.0, 0.0,
		0.0, Vs.y, 0.0, 0.0,
		0.0, 0.0, Vs.z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);
}

mat4 Mr2mat4(vec4 Vq)
{
	float Fx = Vq.x;
	float Fy = Vq.y;
	float Fz = Vq.z;
	float Fw = Vq.w;

	float Fxx = Fx * Fx;
	float Fyy = Fy * Fy;
	float Fzz = Fz * Fz;
	float Fxy = Fx * Fy;
	float Fxz = Fx * Fz;
	float Fyz = Fy * Fz;
	float Fwx = Fw * Fx;
	float Fwy = Fw * Fy;
	float Fwz = Fw * Fz;

	return mat4
	(
		1.0 - 2.0 * (Fyy + Fzz), 2.0 * (Fxy - Fwz), 2.0 * (Fxz + Fwy), 0.0,

		2.0 * (Fxy + Fwz), 1.0 - 2.0 * (Fxx + Fzz), 2.0 * (Fyz - Fwx), 0.0,

		2.0 * (Fxz - Fwy), 2.0 * (Fyz + Fwx), 1.0 - 2.0 * (Fxx + Fyy), 0.0,

		0.0, 0.0, 0.0, 1.0
	);
}

mat4 Mt2mat4(vec3 Vt)
{
	return mat4
	(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		Vt.x, Vt.y, Vt.z, 1.0
	);
}

void main()
{
	vec4 Vv = vec4(Av, 1);
	uint Ub = floatBitsToUint(Ba.Pa[Aj].Vs.w);
	uint Ubs = Ub & 0xFFFFu;
	if (Ubs != 0xFFFFu)
	{
		Vv = Bb.Pb[Aj].Tbindpose_o * Mt2mat4(Ba.Pa[Aj].Vt.xyz) * Mr2mat4(Ba.Pa[Aj].Vr) * Ms2mat4(Ba.Pa[Aj].Vs.xyz) * Bb.Pb[Aj].Tbindpose_i * Vv;
		uint Ube = (Ub >> (8+8)) & 0xFFFFu;
		for (uint l0 = Ubs; l0 < Ube; ++l0)
		{
			uint Ubi = (floatBitsToUint(Ba.Pa[l0 / 4].Vt.w) >> l0 % 4 * 8) & 255;
			Vv = Bb.Pb[Ubi].Tbindpose_o * Mt2mat4(Ba.Pa[Ubi].Vt.xyz) * Mr2mat4(Ba.Pa[Ubi].Vr) * Ms2mat4(Ba.Pa[Ubi].Vs.xyz) * Bb.Pb[Ubi].Tbindpose_i * Vv;
		}
	}
	Vv = Mt2mat4(Ba.Pa[0].Vt.xyz) * Mr2mat4(Ba.Pa[0].Vr) * Ms2mat4(Ba.Pa[0].Vs.xyz) * Vv;

	gl_Position = Bs.Tp * Bs.Tv * Vv;

	uvec4 Vrgba = Bc.Vc[Ac / 4];
	uint Urgba = Vrgba[Ac % 4];
	Oc = vec4(Urgba >> (8+8+8), (Urgba >> (8+8)) & 255, (Urgba >> 8) & 255, Urgba & 255) / 255.0 * Bc1.Vc;
//	Ot = [Ac];
//	Oc[0] = ;
}
