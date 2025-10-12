#version 420

#define lCOLOR 8

//#define lTEXTURE 1
//layout(location = 1) in flat uint f_t;
//layout(set = 0, binding = 5) uniform sampler2D ubo_s[lTEXTURE];
//layout(std140, set = 0, binding = 6) uniform UBOT
//{
//	vec4 uv[lTEXTURE];
//} uboc;

layout(location = 0) in flat uint f_c;

layout(std140, set = 0, binding = 3) uniform UBOC
{
	vec4 c[lCOLOR];
} uboc;

layout(std140, set = 0, binding = 4) uniform UBOSC
{
	vec4 c;
} ubosc;

layout(location = 0) out vec4 o_c;

void main()
{
//	if (!f_t)
//		o_c = texture(ubo_s[f_c], uv[f_t].xy);
//	else
		o_c = uboc.c[f_c] * ubosc.c;
}
