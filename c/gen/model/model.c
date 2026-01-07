//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "Cx.h"
#include "Ch14.h"
#include "Co.h"
#include "Cm.h"

static void Mcgltf(cgltf_options *Pcgltf_options, cgltf_data *Pcgltf_data, const char *Pn)
{
	SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pn, &Pcgltf_data))
	SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, Pcgltf_data, Pn))
	SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(Pcgltf_data))
}

static void Mo()
{
	cgltf_options *Pcgltf_options = &(cgltf_options){};
	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lOF; ++U0)
	{
		Mcgltf(Pcgltf_options, Pcgltf_data, Pof[U0]);
		Mo_mesh(Pcgltf_data, Pon, Ponl, U0);
		cgltf_free(Pcgltf_data);
	}
}
static void Mm()
{
	cgltf_options *Pcgltf_options = &(cgltf_options){};
	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lMF; ++U0)
	{
		Mcgltf(Pcgltf_options, Pcgltf_data, Pmf[U0]);
		Mm_rgba(Pcgltf_data);
		Mm_bone(Pcgltf_data);
		Mm_mesh(Pcgltf_data, Pmn, Pmnl, U0);
		cgltf_free(Pcgltf_data);
	}
}
void smptg_mdMsend()
{
	SMPT_DBmN2L("SMPTR_MDcM %d", SMPTR_MDcM)

	Mm_set();
	Mh14_set();

	Mo();
	Mo_write();
	Mh14_clean();
	Mm();
	Mm_write();
}

void smptg_mdMfree()
{
	Mm_free();
	Mh14_free();
}
