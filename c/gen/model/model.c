//! check
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

//! apply macro
static const uint8_t Pg[] =
{
	1
//	#define X(v, n, b, r) 1,
//		SMPTRnM
//	#undef X
//	#define X(v, n) 0,
//		SMPTRnM1
//	#undef X
};

//! apply macro
static const char *Pc[] =
{
	SMPTFcFACTORY_MODEL "/SuperCutePomi2.glb",
//	#define X(v, n, b, r) SMPTFcFACTORY_MODEL "/" n ".glb",
//		SMPTRnM
//	#undef X
//	#define X(v, n) SMPTFcFACTORY_MODEL "/" n ".glb",
//		SMPTRnM1
//	#undef X
};

static const char *Pm[] =
{
	#define X(v, n, b) n,
		SMPTRnMA
	#undef X
};

static uint8_t Pmi[sizeof(Pm) / sizeof(Pm[0])];
static uint8_t Lmi = 0;

static uint32_t Lbone = 0;

static uint8_t *Pji;
static uint8_t Lji = 0;
static uint8_t Pj[1024];
static uint32_t Lj = 0;

static float *Prgba = 0;
static char **Pmaterial;
static uint8_t Lmaterial = 0;

static uint8_t *Pai;
static uint32_t Lai = 0;

static uint8_t *Pa_j1c1;
static uint32_t La_j1c1 = 0;
static uint8_t *Pa_c1;
static uint32_t La_c1 = 0;

static uint8_t *Pi;
static uint32_t Li = 0;
static uint8_t *Pi1;
static uint32_t Li1 = 0;

static float *Pbindpose;
static uint32_t Lbindpose = 0;

//! test
//struct SMPTG_MDsJSON
//{
//	void *Pdata;
//	uint8_t Utype;
//	struct SMPTG_MDsJSON *Pjson;
//};
//struct SMPTG_MDsJSON *Pjson;

void smptg_mdMsend()
{
	Pji = malloc(0);

	Pbindpose = malloc(0);

	Pmaterial = malloc(0);

	Pai = malloc(0);

	Pa_j1c1 = malloc(0);
	Pa_c1 = malloc(0);

	Pi = malloc(0);
	Pi1 = malloc(0);

	cgltf_options *Pcgltf_options = &(cgltf_options){};
	cgltf_data *Pcgltf_data;
	for (uint32_t l0 = 0; l0 < sizeof(Pc) / sizeof(Pc[0]); ++l0)
	{
		//! test
		//! check math
//		uint32_t Ldata;
//		uint8_t
//			*Pdata = smptfMread(Pc[l0], &Ldata);
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

		SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pc[l0], &Pcgltf_data))
		SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, Pcgltf_data, Pc[l0]))
		SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(Pcgltf_data))

		if (Pg[l0] & 1)
		{
			cgltf_skin *Pcgltf_skin = &Pcgltf_data->skins[0];

			//.i bindpose
			Pbindpose = realloc(Pbindpose, (Pcgltf_skin->joints_count - 1) * sizeof(float) * 16);
			memcpy(Pbindpose + Lbindpose * 16, Pcgltf_skin->inverse_bind_matrices->buffer_view->buffer->data + Pcgltf_skin->inverse_bind_matrices->buffer_view->offset + sizeof(float) * 16, sizeof(float) * 16 * (Pcgltf_skin->joints_count - 1));
			Lbindpose += Pcgltf_skin->joints_count - 1;

			Pji = realloc(Pji, Lji + sizeof(uint8_t));
			Pji[Lji] = Pcgltf_skin->joints_count;
			Lji += sizeof(uint8_t);

			//.i use first bone as main with default m4x4
			cgltf_node *Pbase_cgltf_node = Pcgltf_skin->joints[0];

			for (uint32_t l2 = 0; l2 < Pcgltf_skin->joints_count; ++l2)
			{
				cgltf_node *Pcgltf_node_joints = Pcgltf_skin->joints[l2];

				if (l2 == 0)
				{
					Pj[Lj] = 0;
					Lj += sizeof(uint8_t);
				}
				else
				{
					uint32_t c_0 = 0;
					while ((Pcgltf_node_joints = Pcgltf_node_joints->parent) != Pbase_cgltf_node)
					{
						for (uint32_t j_1 = 0; j_1 < Pcgltf_skin->joints_count; ++j_1)
							if (Pcgltf_node_joints == Pcgltf_skin->joints[j_1])
							{
								Pj[Lj + c_0 + 1] = j_1;
								break;
							}

						++c_0;
					}
					Pj[Lj] = c_0;
					Lj += sizeof(uint8_t) + c_0;
				}
			}

			Lbone += Pcgltf_skin->joints_count;
		}

		uint8_t Pmix[sizeof(float) * 3 + 2];
		uint32_t l_index = 0;
		uint32_t l_own_index = 0;
		uint32_t *Pindex;
		for (uint32_t l1 = 0; l1 < Pcgltf_data->meshes_count; ++l1)
		{
			cgltf_mesh *cgltf_mesh_p = &Pcgltf_data->meshes[l1];
			SMPT_DBmN2L("cgltf_mesh %s", cgltf_mesh_p->name)

			Pindex = &l_index;

			for (uint8_t l2 = 0; l2 < sizeof(Pm) / sizeof(Pm[0]); ++l2)
				if (!strcmp(Pm[l2], cgltf_mesh_p->name))
				{
					Pmi[l2] = Lmi++;
					l_own_index = 0;
					Pindex = &l_own_index;
					break;
				}

			for (uint32_t l2 = 0; l2 < cgltf_mesh_p->primitives_count; ++l2)
			{
				cgltf_primitive *Pcgltf_primitive = &cgltf_mesh_p->primitives[l2];

				Pmix[sizeof(float) * 3] = 0;
				//.i material/color
				while (Pmix[sizeof(float) * 3] < Lmaterial)
				{
					if (!strcmp(Pmaterial[Pmix[sizeof(float) * 3]], Pcgltf_primitive->material->name))
						break;
					//.i j1c1
					++Pmix[sizeof(float) * 3];
				}
				if (Pmix[sizeof(float) * 3] == Lmaterial)
				{
					cgltf_material *Pcgltf_material = Pcgltf_primitive->material;
					cgltf_float *Pbase_color_factor = Pcgltf_material->pbr_metallic_roughness.base_color_factor;
					cgltf_float *Pemissive_factor = Pcgltf_material->emissive_factor;
					if (strstr(Pcgltf_material->name, ".C0."))
						SMPT_DBmW2L("SMPTG %s", Pcgltf_material->name)

					++Lmaterial;
					Pmaterial = realloc(Pmaterial, sizeof(char *) * Lmaterial);
					Pmaterial[Pmix[sizeof(float) * 3]] = Pcgltf_material->name;
					Prgba = realloc(Prgba, sizeof(float) * 4 * Lmaterial);
					uint16_t i4 = Pmix[sizeof(float) * 3] * 4;
					Prgba[i4] = Pemissive_factor[0];
					Prgba[i4 + 1] = Pemissive_factor[1];
					Prgba[i4 + 2] = Pemissive_factor[2];
					Prgba[i4 + 3] = Pbase_color_factor[3];
				}

				uint8_t l_set = 0;
				for (uint32_t l3 = 0; l3 < Pcgltf_primitive->indices->count; ++l3)
				{
					uint16_t l3_0 = *(uint16_t *)(Pcgltf_primitive->indices->buffer_view->buffer->data + Pcgltf_primitive->indices->buffer_view->offset + l3 * sizeof(uint16_t));

					for (uint32_t l4 = 0; l4 < Pcgltf_primitive->attributes_count; ++l4)
					{
						cgltf_attribute *Pcgltf_attribute = &Pcgltf_primitive->attributes[l4];
						cgltf_accessor *Pcgltf_accessor = Pcgltf_attribute->data;

						cgltf_buffer_view *Pcgltf_buffer_view = Pcgltf_accessor->buffer_view;
						uint8_t type_bl = cgltf_component_size(Pcgltf_accessor->component_type);
						uint8_t *Pv = Pcgltf_buffer_view->buffer->data + Pcgltf_buffer_view->offset;

						uint8_t a_bl = Pcgltf_accessor->stride / type_bl;
						for (uint32_t l5 = 0; l5 < a_bl; ++l5)
						{
							if (Pcgltf_attribute->type == cgltf_attribute_type_joints)
							{
								if (l5 == 0)
								{
									uint8_t a_j = *(Pv + l3_0 * Pcgltf_accessor->stride + l5 * type_bl);
									if (a_j == 0)
									{
										SMPT_DBmW2L("SMPTG a_j0")
									}
									//.c b1
									Pmix[sizeof(float) * 3 + 1] = a_j;
								}
							}
							else if (Pcgltf_attribute->type == cgltf_attribute_type_weights)
							{
								if (l5 == 0)
								{
									if (Pcgltf_accessor->component_type == cgltf_component_type_r_32f)
									{
										float *p = (float *)(Pv + l3_0 * Pcgltf_accessor->stride + l5 * type_bl);
										if (!*p)
										{
											SMPT_DBmW2L("SMPTG w2 %f", *p)
										}
									}
									else
									{
										SMPT_DBmW2L("SMPTG Pcgltf_accessor->component_type %d", Pcgltf_accessor->component_type)
									}

									l_set = 1;
								}
								else if (l5 == 1)
								{
									if (Pcgltf_accessor->component_type == cgltf_component_type_r_32f)
									{
										float *p = (float *)(Pv + l3_0 * Pcgltf_accessor->stride + l5 * type_bl);
										if (*p)
										{
											SMPT_DBmW2L("SMPTG w2 %f", *p)
										}
									}
									else
									{
										SMPT_DBmW2L("SMPTG Pcgltf_accessor->component_type %d", Pcgltf_accessor->component_type)
									}
								}
							}
							else if (Pcgltf_attribute->type == cgltf_attribute_type_position)
							{
								memcpy(Pmix + l5 * type_bl, Pv + l3_0 * Pcgltf_accessor->stride + l5 * type_bl, type_bl);
							}
							else if (Pcgltf_attribute->type == cgltf_attribute_type_color)
							{
								//! color
							}
							else
							{
								SMPT_DBmW2L("SMPTG Pcgltf_attribute->type %d", Pcgltf_attribute->type)
							}
						}

						//.i c1
						if (Pcgltf_primitive->attributes_count == 1)
						{
							for (uint32_t l5 = 0; l5 < La_c1; l5 += sizeof(float) * 3 + 1)
							{
								if (!memcmp(Pa_c1 + l5, Pmix, sizeof(float) * 3 + 1))
								{
									if (Pindex == &l_own_index)
									{
										Pi1 = realloc(Pi1, Li1 + sizeof(uint32_t));
										*(uint32_t *)(Pi1 + Li1) = l5 / (sizeof(float) * 3 + 1);
										Li1 += sizeof(uint32_t);
									}
									else
									{
										Pi = realloc(Pi, Li + sizeof(uint32_t));
										*(uint32_t *)(Pi + Li) = l5 / (sizeof(float) * 3 + 1);
										Li += sizeof(uint32_t);
									}
									*Pindex += sizeof(uint32_t);

									l_set = 0;
									break;
								}
							}
							if (l_set == 1)
							{
								Pa_c1 = realloc(Pa_c1, La_c1 + sizeof(float) * 3 + 1);
								memcpy(Pa_c1 + La_c1, Pmix, sizeof(float) * 3 + 1);

								if (Pindex == &l_own_index)
								{
									Pi1 = realloc(Pi1, Li1 + sizeof(uint32_t));
									*(uint32_t *)(Pi1 + Li1) = La_c1 / (sizeof(float) * 3 + 1);
									Li1 += sizeof(uint32_t);
								}
								else
								{
									Pi = realloc(Pi, Li + sizeof(uint32_t));
									*(uint32_t *)(Pi + Li) = La_c1 / (sizeof(float) * 3 + 1);
									Li += sizeof(uint32_t);
								}
								*Pindex += sizeof(uint32_t);

								La_c1 += sizeof(float) * 3 + 1;

								l_set = 0;
							}
						}
						//.i j1u1v1t1
						//else if (Pcgltf_primitive->attributes_count == 4 && l4 == 3)
						//{
						//}
						//.i j1c1
						else if (l_set == 1)
						{
							for (uint32_t l5 = 0; l5 < La_j1c1; l5 += sizeof(float) * 3 + 2)
							{
								if (!memcmp(Pa_j1c1 + l5, Pmix, sizeof(float) * 3 + 2))
								{
									if (Pindex == &l_own_index)
									{
										Pi1 = realloc(Pi1, Li1 + sizeof(uint32_t));
										*(uint32_t *)(Pi1 + Li1) = l5 / (sizeof(float) * 3 + 2);
										Li1 += sizeof(uint32_t);
									}
									else
									{
										Pi = realloc(Pi, Li + sizeof(uint32_t));
										*(uint32_t *)(Pi + Li) = l5 / (sizeof(float) * 3 + 2);
										Li += sizeof(uint32_t);
									}
									*Pindex += sizeof(uint32_t);

									l_set = 0;
									break;
								}
							}
							if (l_set == 1)
							{
								Pa_j1c1 = realloc(Pa_j1c1, La_j1c1 + sizeof(float) * 3 + 2);
								memcpy(Pa_j1c1 + La_j1c1, Pmix, sizeof(float) * 3 + 2);

								if (Pindex == &l_own_index)
								{
									Pi1 = realloc(Pi1, Li1 + sizeof(uint32_t));
									*(uint32_t *)(Pi1 + Li1) = La_j1c1 / (sizeof(float) * 3 + 2);
									Li1 += sizeof(uint32_t);
								}
								else
								{
									Pi = realloc(Pi, Li + sizeof(uint32_t));
									*(uint32_t *)(Pi + Li) = La_j1c1 / (sizeof(float) * 3 + 2);
									Li += sizeof(uint32_t);
								}
								*Pindex += sizeof(uint32_t);

								La_j1c1 += sizeof(float) * 3 + 2;

								l_set = 0;
							}
						}
					}
				}
			}

			if (Pindex == &l_own_index)
			{
				Pai = realloc(Pai, Lai + sizeof(uint32_t));
				*(uint32_t *)(Pai + Lai) = l_own_index;
				Lai += sizeof(uint32_t);
			}
		}
		Pai = realloc(Pai, Lai + sizeof(uint32_t));
		*(uint32_t *)(Pai + Lai) = l_index;
		Lai += sizeof(uint32_t);

		cgltf_free(Pcgltf_data);
	}

	SMPT_DBmR2L("Lmaterial %d", Lmaterial)
	SMPT_DBmR2L("Lbone %d", Lbone)

	FILE *file = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", file)

	fwrite(&Lji, sizeof(uint8_t), 1, file);
	fwrite(Pji, sizeof(uint8_t), Lji, file);
	fwrite(Pj, sizeof(uint8_t), Lj, file);
	fwrite(Pbindpose, sizeof(float), Lbindpose * 16, file);

	fwrite(&Lai, sizeof(uint32_t), 1, file);
	for (uint8_t l0 = 0; l0 < sizeof(Pm) / sizeof(Pm[0]); ++l0)
	{
		uint8_t l0_0 = Pmi[l0];
		fwrite(Pai + l0_0 * sizeof(uint32_t), sizeof(uint32_t), 1, file);
	}
	fwrite(Pai + sizeof(Pm) / sizeof(Pm[0]) * sizeof(uint32_t), sizeof(uint32_t), 1, file);

	for (uint8_t l0 = 0; l0 < sizeof(Pm) / sizeof(Pm[0]); ++l0)
	{
		uint8_t l0_0 = Pmi[l0];

		uint32_t size = *(uint32_t *)(Pai + l0_0 * sizeof(uint32_t));
		uint32_t index = 0;

		for (uint8_t l1 = 0; l1 < l0_0; ++l1)
		{
			index += *(uint32_t *)(Pai + l1 * sizeof(uint32_t));
		}

		fwrite(Pi1 + index, sizeof(uint8_t), size, file);
	}
	fwrite(Pi, sizeof(uint8_t), Li, file);

	fwrite(&Lmaterial, sizeof(uint8_t), 1, file);
	fwrite(Prgba, sizeof(float), Lmaterial * 4, file);

	//.i uv

	//.i a c1
	fwrite((uint32_t[]){La_c1 / (sizeof(float)*3+1)}, sizeof(uint32_t), 1, file);
	fwrite(Pa_c1, sizeof(uint8_t), La_c1, file);

	//.i a j1c1
	fwrite(Pa_j1c1, sizeof(uint8_t), La_j1c1, file);

	//.i a j1t1u1v1

	//.i a t1u1v1

	fclose(file);
}

void smptg_mdMfree()
{
	free(Pji);
	free(Prgba);

	free(Pmaterial);

	free(Pai);

	free(Pa_j1c1);
	free(Pa_c1);

	free(Pi);

	free(Pi1);

	free(Pbindpose);
}
