//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#include "Cx.h"
#include "Ch14.h"
#ifdef SMPT_CM_MAIN
	#include "Co.h"
#endif
#include "Cm.h"

static void Mcgltf(cgltf_options *Pcgltf_options, cgltf_data **Pcgltf_data, const char *Pn)
{
	SMPT_DBmN2L("Pn %s", Pn)
	SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pn, Pcgltf_data))
	SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, *Pcgltf_data, Pn))
	SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(*Pcgltf_data))
}

#define uMODE_O 0
#define uMODE_M 1
static void Mmesh(uint8_t Umode, cgltf_data *Pcgltf_data, const char **Pm[], const uint8_t Pml[], uint16_t U0)
{
	uint16_t Ui;
	for (uint32_t U1 = 0; U1 < Pcgltf_data->nodes_count; ++U1)
	{
		cgltf_node *Pcgltf_node = Pcgltf_data->nodes + U1;
		cgltf_mesh *Pcgltf_mesh = Pcgltf_node->mesh;
		if (!Pcgltf_mesh)
			continue;

		uint8_t Lmix;
		if (Umode == uMODE_O)
		{
			Lmix = lO_A;
		}
		else if (Umode == uMODE_M)
		{
			Lmix = SMPTRlV;
		}
		uint8_t Pmix[Lmix];
		memset(Pmix, 0, sizeof(uint8_t) * Lmix);

		SMPT_DBmN2L("Pcgltf_node %s", Pcgltf_node->name)
		Ui = 0xFFFF;
		for (uint8_t U2 = 0; U2 < Pml[U0]; ++U2)
		{
//			SMPT_DBmN2L("T0 %s", Pcgltf_node->name)
//			SMPT_DBmN2L("T1 %s", Pm[U0][U2])
			if
			(
				(!Pcgltf_node->name[1] && Pcgltf_node->name[0] == Pm[U0][U2][0]) ||
				(Pcgltf_node->name[1] && strstr(Pcgltf_node->name, Pm[U0][U2]) == Pcgltf_node->name)
			)
			{
				SMPT_DBmN2L("cgltf_mesh %s %s", Pm[U0][U2], Pcgltf_node->name)
				Ui = U2;
				break;
			}
		}

		if (Ui != 0xFFFF)
		{
			for (uint16_t U2 = 0; U2 < U0; ++U2)
			{
				Ui += Pml[U2];
			}
			//SMPT_DBmN2L("Ui %d", Ui)

			for (uint32_t U2 = 0; U2 < Pcgltf_mesh->primitives_count; ++U2)
			{
				cgltf_primitive *Pcgltf_primitive = Pcgltf_mesh->primitives + U2;

				cgltf_material *Pcgltf_material = Pcgltf_primitive->material;
				if (Umode == uMODE_M)
				{
					//! mix to a
					if (sizeof(SMPTRtRGBAL) == sizeof(uint8_t))
					{
						if (!Pcgltf_material)
						{
							SMPT_DBmN2L("smptg_mdMsend M0")
							Pmix[sizeof(float) * 3] = 0;
						}
						else if (strcmp(Pcgltf_material->name, "VRGBA"))
						{
							cgltf_float *Pemissive_factor = Pcgltf_material->emissive_factor;
							Pmix[sizeof(float) * 3] = Mm_in_rgba((uint32_t)(Pemissive_factor[0] * 255.0F) << (8+8+8) | (uint32_t)(Pemissive_factor[1] * 255.0F) << (8+8) | (uint32_t)(Pemissive_factor[2] * 255.0F) << 8 | (uint32_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255.0F));
							//SMPT_DBmN2L("Pmix C0 %d", Pmix[sizeof(float) * 3])
						}
					}
					else
					{
					}
				}

				cgltf_accessor *Pcgltf_accessor_index = Pcgltf_primitive->indices;
				for (uint32_t U3 = 0; U3 < Pcgltf_accessor_index->count; ++U3)
				{
					cgltf_size Udi = cgltf_accessor_read_index(Pcgltf_accessor_index, U3);

					for (uint32_t U4 = 0; U4 < Pcgltf_primitive->attributes_count; ++U4)
					{
						float Pda[4];
						cgltf_attribute *Pcgltf_attribute = Pcgltf_primitive->attributes + U4;
						cgltf_accessor_read_float(Pcgltf_attribute->data, Udi, Pda, 4);

						if (Pcgltf_attribute->type == cgltf_attribute_type_position)
						{
							memcpy(Pmix, Pda, sizeof(float) * 3);
						}
						else if (Umode == uMODE_M)
						{
							if (Pcgltf_attribute->type == cgltf_attribute_type_joints)
							{
								#ifdef SMPTRuJW4
								#else
									Pmix[sizeof(float) * 3 + 1] = Pda[0];
									//SMPT_DBmW2L("j0 %f", Pda[0])
								#endif
							}
							else if (Pcgltf_attribute->type == cgltf_attribute_type_weights)
							{
								#ifdef SMPTRuJW4
								#else
									if (!*Pda)
									{
										SMPT_DBmW2L("smptg_mdMsend w0")
									}
									if (Pda[1])
									{
										SMPT_DBmW2L("smptg_mdMsend w1 %f", Pda[1])
									}
								#endif
							}
							else if
							(
								sizeof(SMPTRtRGBAL) == sizeof(uint8_t) &&
								!strcmp(Pcgltf_material->name, "VRGBA") &&
								Pcgltf_attribute->type == cgltf_attribute_type_color
							)
							{
								Pmix[sizeof(float) * 3] = Mm_in_rgba((uint32_t)(Pda[0] * 255.0F) << (8+8+8) | (uint32_t)(Pda[1] * 255.0F) << (8+8) | (uint32_t)(Pda[2] * 255.0F) << 8 | (uint32_t)(Pda[3] * 255.0F));
								if (Pmix[sizeof(float) * 3] == 255)
									SMPT_DBmW2L("smptg_mdMsend VC")
							}
							#ifdef SMPTRuN
								#ifndef SMPTRuNF
									else if (Pcgltf_attribute->type == cgltf_attribute_type_normal)
									{
										memcpy(Pmix + sizeof(float) * 3 + 2, Pda, sizeof(float) * 3);
										for (uint8_t U0 = 0; U0 < 3; ++U0)
											SMPT_DBmN2L("Pda %d %f", U0, *(float *)(Pda + U0 * sizeof(float)))
									}
								#endif
							#endif
						}
//						SMPT_DBmW2L("smptg_mdMsend Pcgltf_attribute->type %d", Pcgltf_attribute->type)
					}

					Mh14_mesh(Pmix, Ui, Lmix);
				}
			}
		}
	}
}

#ifdef SMPT_CM_MAIN
	void smptg_mdMo_send()
	{
		Mh14_set(SMPTR_MDcO);

		SMPT_DBmN2L("SMPTR_MDcO %d", SMPTR_MDcO)

		cgltf_data *Pcgltf_data = NULL;
		cgltf_options Vcgltf_options = {0};
		for (uint16_t U0 = 0; U0 < lOF; ++U0)
		{
			Mcgltf(&Vcgltf_options, &Pcgltf_data, Pof[U0]);

			Mmesh(uMODE_O, Pcgltf_data, Pon, Ponl, U0);

			cgltf_free(Pcgltf_data);
		}

		Mo_write();

		Mh14_free(SMPTR_MDcO);
	}
#endif
void smptg_mdMm_send()
{
	Mm_set();

	Mh14_set(SMPTR_MDcM);

	SMPT_DBmN2L("SMPTR_MDcM %d", SMPTR_MDcM)
//	#ifdef SMPT_CM_DEBUG
//		uint32_t Utest = 0;
//		for (uint32_t U0 = 0; U0 < lMF; ++U0)
//			for (uint32_t U1 = 0; U1 < Pmal[U0]; ++U1)
//			{
//				SMPT_DBmN2L("Pma[%d] %s", Utest, Pma[Utest])
//				++Utest;
//			}
//	#endif

	cgltf_data *Pcgltf_data = NULL;
	cgltf_options Vcgltf_options = {0};
	for (uint16_t U0 = 0; U0 < lMF; ++U0)
	{
		Mcgltf(&Vcgltf_options, &Pcgltf_data, Pmf[U0]);
		Mm_rgba(Pcgltf_data);
		Mm_bone(Pcgltf_data, U0);
		Mmesh(uMODE_M, Pcgltf_data, Pmn, Pmnl, U0);
		cgltf_free(Pcgltf_data);
	}

	Mm_write();

	Mh14_free(SMPTR_MDcM);

	Mm_free();
}
