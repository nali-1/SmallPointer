//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "Cx.h"
#include "Ch14.h"
#include "Co.h"
#include "Cm.h"

void Mprotect(void *P, size_t L)
{
	size_t Lpage = sysconf(_SC_PAGESIZE);

	uintptr_t Ustart = (uintptr_t)P & ~(Lpage - 1);
	uintptr_t Uend = ((uintptr_t)P + L + Lpage - 1) & ~(Lpage - 1);

	mprotect((void *)Ustart, Uend - Ustart, PROT_READ);
}

void Munprotect(void *P, size_t L)
{
	size_t Lpage = sysconf(_SC_PAGESIZE);

	uintptr_t Ustart = (uintptr_t)P & ~(Lpage - 1);
	uintptr_t Uend = ((uintptr_t)P + L + Lpage - 1) & ~(Lpage - 1);

	mprotect((void *)Ustart, Uend - Ustart, PROT_READ | PROT_WRITE);
}

static void Mcgltf(cgltf_options *Pcgltf_options, cgltf_data **Pcgltf_data, const char *Pn)
{
	SMPT_DBmN2L("Pn %s", Pn)
	SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pn, Pcgltf_data))
	SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, *Pcgltf_data, Pn))
	SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(*Pcgltf_data))
}

void smptg_mdMo_send()
{
	Mh14_set(SMPTR_MDcO);

	SMPT_DBmN2L("SMPTR_MDcO %d", SMPTR_MDcO)

	cgltf_data *Pcgltf_data = NULL;
	cgltf_options Vcgltf_options = {0};
	for (uint32_t U0 = 0; U0 < lOF; ++U0)
	{
		Mcgltf(&Vcgltf_options, &Pcgltf_data, Pof[U0]);

		for (size_t L1 = 0; L1 < Pcgltf_data->buffers_count; L1++)
		{
			cgltf_buffer *Pcgltf_buffer = &Pcgltf_data->buffers[L1];
			if (!Pcgltf_buffer->data || Pcgltf_buffer->size == 0)
				continue;

			SMPT_DBmN2L("Pcgltf_buffer->data %p", Pcgltf_buffer->data)
			SMPT_DBmN2L("Pcgltf_buffer->size %ld", Pcgltf_buffer->size)
			SMPT_DBmN2L("data + size %p", (void *)(Pcgltf_buffer->data + Pcgltf_buffer->size))

			//Mprotect(Pcgltf_buffer->data, Pcgltf_buffer->size);
			//((uint8_t *)Pcgltf_buffer->data)[0] = 0;
		}

		Mo_mesh(Pcgltf_data, Pon, Ponl, U0);

		for (size_t L1 = 0; L1 < Pcgltf_data->buffers_count; L1++)
		{
			cgltf_buffer *Pcgltf_buffer = &Pcgltf_data->buffers[L1];
			if (!Pcgltf_buffer->data || Pcgltf_buffer->size == 0)
				continue;

			//Munprotect(Pcgltf_buffer->data, Pcgltf_buffer->size);
			//((uint8_t *)Pcgltf_buffer->data)[0] = 0;
		}

		cgltf_free(Pcgltf_data);
	}

	Mo_write();

	Mh14_free(SMPTR_MDcO);
}
void smptg_mdMm_send()
{
	Mm_set();

	Mh14_set(SMPTR_MDcM);

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

	cgltf_data *Pcgltf_data = NULL;
	cgltf_options Vcgltf_options = {0};
	for (uint32_t U0 = 0; U0 < lMF; ++U0)
	{
		Mcgltf(&Vcgltf_options, &Pcgltf_data, Pmf[U0]);
		Mm_rgba(Pcgltf_data);
		Mm_bone(Pcgltf_data, U0);
		Mm_mesh(Pcgltf_data, Pmn, Pmnl, U0);
		cgltf_free(Pcgltf_data);
	}

	Mm_write();

	Mh14_free(SMPTR_MDcM);

	Mm_free();
}
