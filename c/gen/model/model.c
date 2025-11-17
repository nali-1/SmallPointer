//! a without i
//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#define xM \
	X("SuperCutePomi", 1) \
	X("Font", 0)
#define lM (sizeof(Pg) / sizeof(Pg[0]))
#define lMA SMPTRcMA
static const uint8_t Pg[] =
{
	#define X(v, a) a,
		xM
	#undef X
};
static const char *Pc[] =
{
	#define X(n, a) SMPTFcFACTORY_MODEL "/" n ".glb",
		xM
	#undef X
};

#define mCOUNT0(_1, _2, N, ...) N
#define mCOUNT(...) \
	mCOUNT0(__VA_ARGS__, 2, 1, 0)
#define X(v, b, ...) static const char *Pm0_##v[] = { __VA_ARGS__ };
	SMPTRxM0
#undef X
#define X(v, b, ...) static const char *Pm1_##v[] = { __VA_ARGS__ };
	SMPTRxM1
#undef X
static const char **Pm[] =
{
	#define X(v, b, ...) Pm0_##v,
		SMPTRxM0
	#undef X
	#define X(v, b, ...) Pm1_##v,
		SMPTRxM1
	#undef X
};
static const uint8_t Pml[] =
{
	#define X(v, b, ...) mCOUNT(__VA_ARGS__),
		SMPTRxM0
	#undef X
	#define X(v, b, ...) mCOUNT(__VA_ARGS__),
		SMPTRxM1
	#undef X
};

static uint32_t Lbone = 0;

//! bp later
static uint8_t *Pji;
static uint8_t Lji = 0;
static uint8_t Pj[1024];
static uint32_t Lj = 0;

static uint32_t *Prgba;
static SMPTRtRGBAL Lrgba = 0;

static uint8_t *Pa;
static uint8_t La = 0;

//! clean
static uint8_t *Pi[lMA];
static uint32_t Pil[lMA] = {0};

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

static uint8_t Min_rgba(uint32_t Urgba)
{
	for (uint8_t U0 = 0; U0 < Lrgba; ++U0)
		if (!memcmp(Prgba + U0, &Urgba, sizeof(uint32_t)))
			return U0;
	return 0;
}
static void Mset_rgba(cgltf_data *Pcgltf_data)
{
	cgltf_material *Pcgltf_material = Pcgltf_data->materials;
	for (uint8_t U0 = 0; U0 < Pcgltf_data->materials_count; ++U0)
	{
		if (strcmp(Pcgltf_material->name, "VRGBA"))
			continue;

		cgltf_float *Pemissive_factor = Pcgltf_material->emissive_factor;
		uint32_t Urgba = (uint8_t)(Pemissive_factor[0] * 255) << (8+8+8) | (uint8_t)(Pemissive_factor[1] * 255) << (8+8) | (uint8_t)(Pemissive_factor[2] * 255) << 8 | (uint8_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255);
		if (Min_rgba(Urgba))
			continue;

		++Lrgba;
		Prgba = realloc(Prgba, sizeof(uint32_t) * Lrgba);
		Prgba[Lrgba - 1] = Urgba;
	}
}

static void Mset_bone(cgltf_data *Pcgltf_data)
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

	for (uint32_t U0 = 0; U0 < Pcgltf_skin->joints_count; ++U0)
	{
		cgltf_node *Pcgltf_node_joints = Pcgltf_skin->joints[U0];

		if (U0 == 0)
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

static void Mwrite()
{
	SMPT_DBmN2L("Lrgba %d", Lrgba)
	SMPT_DBmN2L("Lbone %d", Lbone)

	FILE *file = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", file)

	fwrite(&Lji, sizeof(uint8_t), 1, file);
	fwrite(Pji, sizeof(uint8_t), Lji, file);
	fwrite(Pj, sizeof(uint8_t), Lj, file);
	fwrite(Pbindpose, sizeof(float), Lbindpose * 16, file);

	for (uint8_t U0 = 0; U0 < lMA; ++U0)
	{
		fwrite(Pil + U0, sizeof(uint32_t), 1, file);
		fwrite(Pi[U0], sizeof(uint8_t), Pil[U0], file);
	}

	fwrite(&Lrgba, sizeof(SMPTRtRGBAL), 1, file);
	fwrite(Prgba, sizeof(uint32_t), Lrgba * 4, file);

	fwrite(Pa, sizeof(uint8_t), La, file);

	fclose(file);
}

static void Ma(uint8_t *Pmix, uint8_t Ui)
{
	for (uint32_t U0 = 0; U0 < La; U0 += sizeof(float) * 3 + 2)
	{
		if (!memcmp(Pa + U0, Pmix, sizeof(float) * 3 + 2))
		{
			Pi[Ui] = realloc(Pi[Ui], Pil[Ui] + sizeof(uint32_t));
			*(uint32_t *)(Pi[Ui] + Pil[Ui]) = U0 / (sizeof(float) * 3 + 2);
			Pil[Ui] += sizeof(uint32_t);
			return;
		}
	}
	Pa = realloc(Pa, La + sizeof(float) * 3 + 2);
	memcpy(Pa + La, Pmix, sizeof(float) * 3 + 2);

	Pi[Ui] = realloc(Pi[Ui], Pil[Ui] + sizeof(uint32_t));
	*(uint32_t *)(Pi[Ui] + Pil[Ui]) = La / (sizeof(float) * 3 + 2);
	Pil[Ui] += sizeof(uint32_t);

	La += sizeof(float) * 3 + 2;
}
void smptg_mdMsend()
{
	Pji = malloc(0);

	Pbindpose = malloc(0);

	Prgba = malloc(0);

	Pa = malloc(0);

	for (uint32_t U0 = 0; U0 < lMA; ++U0)
		Pi[U0] = malloc(0);

	cgltf_options *Pcgltf_options = &(cgltf_options){};
	cgltf_data *Pcgltf_data;
	for (uint32_t U0 = 0; U0 < lM; ++U0)
	{
		//! test
		//! check math
//		uint32_t Ldata;
//		uint8_t
//			*Pdata = smptfMread(Pc[U0], &Ldata);
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

		SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(Pcgltf_options, Pc[U0], &Pcgltf_data))
		SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(Pcgltf_options, Pcgltf_data, Pc[U0]))
		SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(Pcgltf_data))

		Mset_rgba(Pcgltf_data);
		if (Pg[U0] & 1)
		{
			Mset_bone(Pcgltf_data);
		}

		for (uint32_t U1 = 0; U1 < Pcgltf_data->meshes_count; ++U1)
		{
			uint8_t
				#ifdef SMPTRuJW4
					#ifdef SMPTRuN
					#endif
				#else
					Pmix[sizeof(float) * 3 + 2] = {0},
				#endif
				Ui = 255;

			cgltf_mesh *cgltf_mesh_p = &Pcgltf_data->meshes[U1];
			SMPT_DBmN2L("cgltf_mesh %s", cgltf_mesh_p->name)

			for (uint8_t U2 = 0; U2 < lMA; ++U2)
			{
				if
				(
					(!cgltf_mesh_p->name[1] && cgltf_mesh_p->name[0] == Pm[U0][U2][0]) ||
					(cgltf_mesh_p->name[1] && strstr(cgltf_mesh_p->name, Pm[U0][U2]))
				)
				{
					Ui = U2;
					break;
				}
			}

			if (Ui != 255)
			{
				for (uint32_t U2 = 0; U2 < cgltf_mesh_p->primitives_count; ++U2)
				{
					cgltf_primitive *Pcgltf_primitive = &cgltf_mesh_p->primitives[U2];

					cgltf_material *Pcgltf_material = Pcgltf_primitive->material;
					if (strcmp(Pcgltf_material->name, "VRGBA"))
					{
						cgltf_float *Pemissive_factor = Pcgltf_material->emissive_factor;
						Pmix[sizeof(float) * 3] = Min_rgba((uint8_t)(Pemissive_factor[0] * 255) << (8+8+8) | (uint8_t)(Pemissive_factor[1] * 255) << (8+8) | (uint8_t)(Pemissive_factor[2] * 255) << 8 | (uint8_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255));
					}
					else
						Pmix[sizeof(float) * 3] = Lrgba;

					for (uint32_t U3 = 0; U3 < Pcgltf_primitive->indices->count; ++U3)
					{
						uint16_t Pd = *(uint16_t *)(Pcgltf_primitive->indices->buffer_view->buffer->data + Pcgltf_primitive->indices->buffer_view->offset + U3 * sizeof(uint16_t));

						for (uint32_t U4 = 0; U4 < Pcgltf_primitive->attributes_count; ++U4)
						{
							cgltf_attribute *Pcgltf_attribute = &Pcgltf_primitive->attributes[U4];
							cgltf_accessor *Pcgltf_accessor = Pcgltf_attribute->data;

							cgltf_buffer_view *Pcgltf_buffer_view = Pcgltf_accessor->buffer_view;
							uint8_t *Pv = Pcgltf_buffer_view->buffer->data + Pcgltf_buffer_view->offset;
							float *Pvf = (float *)(Pv + Pd * Pcgltf_accessor->stride);
							if (Pcgltf_attribute->type == cgltf_attribute_type_joints)
							{
								#ifdef SMPTRuJW4
								#else
									Pmix[sizeof(float) * 3 + 1] = *(uint8_t *)Pvf;
								#endif
							}
							else if (Pcgltf_attribute->type == cgltf_attribute_type_weights)
							{
								#ifdef SMPTRuJW4
								#else
									if (!*Pvf)
									{
										SMPT_DBmW2L("smptg_mdMsend w0")
									}
									if (Pvf[1])
									{
										SMPT_DBmW2L("smptg_mdMsend w1 %f", Pvf[1])
									}
								#endif
							}
							else if (Pcgltf_attribute->type == cgltf_attribute_type_position)
							{
								memcpy(Pmix, Pvf, Pcgltf_accessor->stride);
							}
							else if
							(
								Pmix[sizeof(float) * 3] == Lrgba &&
								Pcgltf_attribute->type == cgltf_attribute_type_color
							)
							{
								Pmix[sizeof(float) * 3] = Min_rgba((uint8_t)(Pvf[0] * 255) << (8+8+8) | (uint8_t)(Pvf[1] * 255) << (8+8) | (uint8_t)(Pvf[2] * 255) << 8 | (uint8_t)(Pvf[3] * 255));
							}
							else
							{
								SMPT_DBmW2L("smptg_mdMsend Pcgltf_attribute->type %d", Pcgltf_attribute->type)
							}

							Ma(Pmix, Ui);
						}
					}
				}
			}
		}

		cgltf_free(Pcgltf_data);
	}

	Mwrite();
}

void smptg_mdMfree()
{
	free(Pji);
	free(Prgba);

	free(Pa);

	for (uint32_t U0 = 0; U0 < lMA; ++U0)
		free(Pi[U0]);

	free(Pbindpose);
}
