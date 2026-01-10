//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "Cx.h"
#include "Ch14.h"
#include "Co.h"
#include "Cm.h"

static void Mcgltf(cgltf_data **Pcgltf_data, const char *Pn)
{
	cgltf_options *Pcgltf_options = &(cgltf_options){};
	SMPT_DBmN2L("Pn %s", Pn)
	SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pn, Pcgltf_data))
	SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, *Pcgltf_data, Pn))
	SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(*Pcgltf_data))
}

static void Mo()
{
	SMPT_DBmN2L("SMPTR_MDcO %d", SMPTR_MDcO)
	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lOF; ++U0)
	{
		Mcgltf(&Pcgltf_data, Pof[U0]);
		Mo_mesh(Pcgltf_data, Pon, Ponl, U0);
		cgltf_free(Pcgltf_data);
	}
}
static void Mm()
{
	SMPT_DBmN2L("SMPTR_MDcM %d", SMPTR_MDcM)
	#ifdef SMPT_CM_DEBUG
		uint32_t Utest = 0;
		for (uint32_t U0 = 0; U0 < lMF; ++U0)
			for (uint32_t U1 = 0; U1 < Pmal[U0]; ++U1)
			{
				SMPT_DBmN2L("Pma[%d] %s", Utest, Pma[Utest])
				++Utest;
			}
	#endif

	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lMF; ++U0)
	{
		Mcgltf(&Pcgltf_data, Pmf[U0]);
		Mm_rgba(Pcgltf_data);
		Mm_bone(Pcgltf_data, U0);
		Mm_mesh(Pcgltf_data, Pmn, Pmnl, U0);
		cgltf_free(Pcgltf_data);
	}
}
void smptg_mdMo_send()
{
	Mh14_set(SMPTR_MDcO);
	Mo();
	Mo_write();
	Mh14_free(SMPTR_MDcO);
}
void smptg_mdMm_send()
{
	Mm_set();
	Mh14_set(SMPTR_MDcM);
	Mm();
	Mm_write();
	Mh14_free(SMPTR_MDcM);
	Mm_free();
}
