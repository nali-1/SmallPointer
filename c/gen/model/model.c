//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "cx.h"

static SMPTRtJW *Pji;
static SMPTRtJWL Lji = 0;

static SMPTRtJW **Pj;
static uint8_t *Pjl;

static uint32_t *Prgba;
static SMPTRtRGBAL Lrgba = 0;

static SMPTRtI *Pi[SMPTR_MDcM];
static SMPTRtI Pil[SMPTR_MDcM] = {0};

static float *Pbindpose;
static uint32_t Lbindpose = 0;

#include "ch14.h"
#include "ch14_m.h"
#include "ch14_o.h"

//! test
//struct SMPTG_MDsJSON
//{
//	void *Pdata;
//	uint8_t Utype;
//	struct SMPTG_MDsJSON *Pjson;
//};
//struct SMPTG_MDsJSON *Pjson;

static void Mcgltf(cgltf_options *Pcgltf_options, cgltf_data *Pcgltf_data, const char *Pn)
{
	SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pn, &Pcgltf_data))
	SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, Pcgltf_data, Pn))
	SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(Pcgltf_data))
}

static SMPTRtRGBAL Min_rgba(uint32_t Urgba)
{
	for (SMPTRtRGBAL U0 = 0; U0 < Lrgba; ++U0)
		if (!memcmp(Prgba + U0, &Urgba, sizeof(uint32_t)))
			return U0;
	return 255;
}
static void Mset_rgba(cgltf_data *Pcgltf_data)
{
	for (uint8_t U0 = 0; U0 < Pcgltf_data->materials_count; ++U0)
	{
		cgltf_material *Pcgltf_material = Pcgltf_data->materials + U0;

		SMPT_DBmN2L("Pcgltf_material %s", Pcgltf_material->name)

		if (!strcmp(Pcgltf_material->name, "VRGBA"))
			continue;

		cgltf_float *Pemissive_factor = Pcgltf_material->emissive_factor;

		uint32_t Urgba = (uint8_t)(Pemissive_factor[0] * 255) << (8+8+8) | (uint8_t)(Pemissive_factor[1] * 255) << (8+8) | (uint8_t)(Pemissive_factor[2] * 255) << 8 | (uint8_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255);
		if (Min_rgba(Urgba) != 255)
			continue;

		SMPT_DBmN2L("rf %f", Pemissive_factor[0])
		SMPT_DBmN2L("gf %f", Pemissive_factor[1])
		SMPT_DBmN2L("bf %f", Pemissive_factor[2])
		SMPT_DBmN2L("af %f", Pcgltf_material->pbr_metallic_roughness.base_color_factor[3])
//		SMPT_DBmN2L("rd %d", Urgba >> (8+8+8))
//		SMPT_DBmN2L("gd %d", (Urgba >> (8+8)) & 255)
//		SMPT_DBmN2L("bd %d", (Urgba >> 8) & 255)
//		SMPT_DBmN2L("ad %d", Urgba & 255)

		Prgba = realloc(Prgba, sizeof(uint32_t) * Lrgba + sizeof(uint32_t));
		Prgba[Lrgba] = Urgba;
		++Lrgba;
	}
}

static void Mset_bone(cgltf_data *Pcgltf_data)
{
	cgltf_skin *Pcgltf_skin = Pcgltf_data->skins;

	SMPT_DBmN2L("joints_count %d", Pcgltf_skin->joints_count)
	SMPTRtJWL joints_count = Pcgltf_skin->joints_count;
	for (SMPTRtJWL U0 = 1; U0 < Pcgltf_skin->joints_count; ++U0)
	{
		cgltf_node *Pcgltf_node_joint = Pcgltf_skin->joints[U0];

		uint16_t U00 = 0;
		if (!Pcgltf_node_joint->parent || !Pcgltf_node_joint->parent->parent)
		{
			--joints_count;
			SMPT_DBmW2L("Mset_bone F %d %s", U0, Pcgltf_node_joint->name)
			continue;
		}
	}
	SMPT_DBmN2L("joints_count F %d", joints_count)

	//.i bindpose
	Pbindpose = realloc(Pbindpose, (Lbindpose + joints_count - 1) * sizeof(float) * 16);
	memcpy(Pbindpose + Lbindpose * 16, Pcgltf_skin->inverse_bind_matrices->buffer_view->buffer->data + Pcgltf_skin->inverse_bind_matrices->buffer_view->offset + sizeof(float) * 16, sizeof(float) * 16 * (joints_count - 1));
	Lbindpose += joints_count - 1;

	//.i use first bone as main with default m4x4
	cgltf_node *Pbase_cgltf_node = Pcgltf_skin->joints[0];

	Pj[Lji] = malloc(sizeof(SMPTRtJW) * 512);
	Pj[Lji][0] = 0;
	Pjl[Lji] = sizeof(uint8_t);
	//SMPT_DBmN2L("Pcgltf_node_joint %d %s", joints_count, Pcgltf_skin->joints[joints_count]->name)
	for (uint8_t U0 = 1; U0 < joints_count; ++U0)
	{
		cgltf_node *Pcgltf_node_joint = Pcgltf_skin->joints[U0];
		//SMPT_DBmN2L("Pcgltf_node_joint %d %s", U0, Pcgltf_node_joint->name)

		//.i ik rig -> fix animate
		uint16_t U00 = 0;
		if (Pcgltf_node_joint->parent && Pcgltf_node_joint->parent->parent)
		{
			while ((Pcgltf_node_joint = Pcgltf_node_joint->parent) != Pbase_cgltf_node)
			{
				for (uint8_t U1 = 1; U1 < joints_count; ++U1)
					if (Pcgltf_node_joint == Pcgltf_skin->joints[U1])
					{
						Pj[Lji][Pjl[Lji] + U00 + 1] = U1;
						break;
					}

				++U00;
			}
		}
		else
		{
			SMPT_DBmW2L("Mset_bone %d %s", U0, Pcgltf_node_joint->name)
			continue;
		}
		Pj[Lji][Pjl[Lji]] = U00;
		Pjl[Lji] += sizeof(uint8_t) + U00;
	}

	Pji = realloc(Pji, Lji + 1 * sizeof(SMPTRtJWL));
	Pji[Lji] = joints_count;
	++Lji;
}

#define lM (sizeof(float) * 3 + 2)
#define lO (sizeof(float) * 3)

static void Mwriteo()
{
	FILE *file = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", file)

	uint8_t Pa[Lh14i];
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		for (uint32_t U1 = 0; U1 < Ph14tl[U0]; ++U1)
		{
			SMPTRtI Uh14ti = Ph14ti[U0][U1];
			memcpy(Pa + Uh14ti, Ph14t[U0][U1].P, lO);
		}
	}
	fwrite(&Lh14i, sizeof(uint32_t), 1, file);
	fwrite(Pa, lO, Lh14i, file);

	fclose(file);
}
static void Mwritem()
{
	SMPT_DBmN2L("Lrgba %d", Lrgba)

	FILE *file = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", file)

	fwrite(Pji, sizeof(SMPTRtJW), Lji, file);
	for (SMPTRtJWL U0 = 0; U0 < Lji; ++U0)
		fwrite(Pj[U0], sizeof(SMPTRtJW), Pjl[U0], file);
	fwrite(Pbindpose, sizeof(float), Lbindpose * 16, file);

	for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
	{
		fwrite(Pil + U0, sizeof(SMPTRtI), 1, file);
		fwrite(Pi[U0], sizeof(SMPTRtI), Pil[U0], file);
	}

	for (uint32_t l0 = 0; l0 < Lrgba; ++l0)
	{
		SMPT_DBmN2L("Uc %d", l0)
		SMPT_DBmN2L("rf %f", (Prgba[l0] >> (8+8+8)) / 255.0F)
		SMPT_DBmN2L("gf %f", ((Prgba[l0] >> (8+8)) & 255) / 255.0F)
		SMPT_DBmN2L("bf %f", ((Prgba[l0] >> 8) & 255) / 255.0F)
		SMPT_DBmN2L("af %f", (Prgba[l0] & 255) / 255.0F)
	}
	fwrite(&Lrgba, sizeof(SMPTRtRGBAL), 1, file);
	fwrite(Prgba, sizeof(uint32_t), Lrgba, file);

	uint8_t Pa[Lh14i];
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		for (uint32_t U1 = 0; U1 < Ph14tl[U0]; ++U1)
		{
			SMPTRtI Uh14ti = Ph14ti[U0][U1];
			memcpy(Pa + Uh14ti, Ph14t[U0][U1].P, lM);
		}
	}
	fwrite(Pa, lM, Lh14i, file);

	fclose(file);
}

static void Mo()
{
	cgltf_options *Pcgltf_options = &(cgltf_options){};
	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lOF; ++U0)
	{
		Mcgltf(Pcgltf_options, Pcgltf_data, Pof[U0]);
		//Mset_mesh(Pcgltf_data, Pon, Ponl, U0);
		Mset_mesho(Pcgltf_data, Pon, Ponl, U0);
		cgltf_free(Pcgltf_data);
	}
}
static void Mm()
{
	cgltf_options *Pcgltf_options = &(cgltf_options){};
	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lMF; ++U0)
	{
		//! test
		//! check math
//		uint32_t Ldata;
//		uint8_t
//			*Pdata = smptfMread(Pmf[U0], &Ldata);
//		//.i skip magic
//		char
//			*Pps = strstr(Pdata + 16, "\"generator\""),
//			*Ppe;
//		//.t read string
//		SMPT_DBmN2L("Pdata %p", Pdata)
//		SMPT_DBmN2L("Ldata %d", Ldata)
//		SMPT_DBmN2L("Pps %p", Pps)
//		if (Pps)
//		{
//			Pps = strchr(Pps, ':');
//			Pps = strchr(Pps, '\"') + 1;
//			SMPT_DBmN2L("Pps %p", Pps)
//			Ppe = strchr(Pps, '\"');
//			SMPT_DBmN2L("Ppe %p", Ppe)
//			char *Ptest = malloc(Ppe - Pps + 1);
//			memcpy(Ptest, Pps, Ppe - Pps);
//			Ptest[Ppe - Pps] = 0;
//			SMPT_DBmN2L("generator %s", Ptest)
//			free(Ptest);
//		}
//		free(Pdata);
//		while (1)
//		{
//			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
//		}
		Mcgltf(Pcgltf_options, Pcgltf_data, Pmf[U0]);
		Mset_rgba(Pcgltf_data);
		Mset_bone(Pcgltf_data);
		Mset_meshm(Pcgltf_data, Pmn, Pmnl, U0);
		cgltf_free(Pcgltf_data);
	}
}
void smptg_mdMsend()
{
	SMPT_DBmN2L("SMPTR_MDcM %d", SMPTR_MDcM)

	Pj = malloc(0);
	Pjl = malloc(0);

	Pji = malloc(0);

	Pbindpose = malloc(0);

	Prgba = malloc(0);

	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		Ph14t[U0] = malloc(0);
		Ph14ti[U0] = malloc(0);
	}

	for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
		Pi[U0] = malloc(0);

	Mo();
	Mm();
	Mwrite();
}

void smptg_mdMfree()
{
	for (SMPTRtJWL U0 = 0; U0 < Lji; ++U0)
		free(Pj[U0]);
	free(Pj);
	free(Pjl);

	free(Pji);
	free(Prgba);

	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		free(Ph14t[U0]);
		free(Ph14ti[U0]);
	}

	for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
		free(Pi[U0]);

	free(Pbindpose);
}
