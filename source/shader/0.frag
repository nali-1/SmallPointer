#version 420

//#define lTEXTURE 1
//layout(set = 0, binding = 5) uniform sampler2D Ss[lTEXTURE];

layout(location = 0) in vec4 Nc;
//layout(location = 1) in vec2 Nt;

layout(std140, set = 0, binding = 4) uniform bC
{
	vec4 Vc;
} Bc;

layout(location = 0) out vec4 Oc;

void main()
{
//	if (!Nt[1])
//		Oc = texture(Ss[Nc.x], Nt);
//	else
		Oc = Nc * Bc.Vc;
}
