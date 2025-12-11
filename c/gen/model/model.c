//! a without i
//! uv
#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

//! fix
#define xM \
	X("Ui", 1) \
	X("Croakie", 1)
//	X("SuperCutePomi", 1) \
//	X("Font", 0)
#define lM (sizeof(Pg) / sizeof(Pg[0]))
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

//! fix
//static const char *Pm0[] =
//{
//	#define X(v, n) n,
//		SMPTRxM0
//	#undef X
//};
//static const char *Pm1[] =
//{
//	#define X(v, n) n,
//		SMPTRxM1
//	#undef X
//};
static const char *Pm2[] =
{
	#define X(v, n) n,
		SMPTRxM2
	#undef X
};
static const char *Pm3[] =
{
	#define X(v, n) n,
		SMPTRxM3
	#undef X
};
static const char **Pm[] =
{
//	Pm0,
//	Pm1,
	Pm2,
	Pm3
};
static const uint8_t Pml[] =
{
//	sizeof(Pm0) / sizeof(Pm0[0]),
//	sizeof(Pm1) / sizeof(Pm1[0]),
	sizeof(Pm2) / sizeof(Pm2[0]),
	sizeof(Pm3) / sizeof(Pm3[0])
};

//! bp later
static SMPTRtJW *Pji;
static SMPTRtJWL Lji = 0;
//! clean
static SMPTRtJW **Pj;
static uint8_t *Pjl;

static uint32_t *Prgba;
static SMPTRtRGBAL Lrgba = 0;

//! clean
//static uint8_t *Pa;
//static uint32_t La = 0;

//! clean
static SMPTRtI *Pi[SMPTRcMA];
static SMPTRtI Pil[SMPTRcMA] = {0};

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

	//.i bindpose
	Pbindpose = realloc(Pbindpose, (Lbindpose + Pcgltf_skin->joints_count - 1) * sizeof(float) * 16);
	memcpy(Pbindpose + Lbindpose * 16, Pcgltf_skin->inverse_bind_matrices->buffer_view->buffer->data + Pcgltf_skin->inverse_bind_matrices->buffer_view->offset + sizeof(float) * 16, sizeof(float) * 16 * (Pcgltf_skin->joints_count - 1));
	Lbindpose += Pcgltf_skin->joints_count - 1;

	//.i use first bone as main with default m4x4
	cgltf_node *Pbase_cgltf_node = Pcgltf_skin->joints[0];

	Pj[Lji] = malloc(sizeof(SMPTRtJW) * 512);
	Pj[Lji][0] = 0;
	Pjl[Lji] = sizeof(uint8_t);
	SMPT_DBmN2L("joints_count %d", Pcgltf_skin->joints_count)
	//SMPT_DBmN2L("Pcgltf_node_joint %d %s", Pcgltf_skin->joints_count, Pcgltf_skin->joints[Pcgltf_skin->joints_count]->name)
	for (uint8_t U0 = 1; U0 < Pcgltf_skin->joints_count; ++U0)
	{
		cgltf_node *Pcgltf_node_joint = Pcgltf_skin->joints[U0];
		//SMPT_DBmN2L("Pcgltf_node_joint %d %s", U0, Pcgltf_node_joint->name)

		//.i ik rig -> fix animate
		uint16_t U00 = 0;
		if (Pcgltf_node_joint->parent && Pcgltf_node_joint->parent->parent)
		{
			while ((Pcgltf_node_joint = Pcgltf_node_joint->parent) != Pbase_cgltf_node)
			{
				for (uint8_t U1 = 1; U1 < Pcgltf_skin->joints_count; ++U1)
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
	Pji[Lji] = Pcgltf_skin->joints_count;
	++Lji;
}

struct Sh14
{
//	float Fx, Fy, Fz;
//	SMPTRtRGBAL Uc;
//	#ifdef SMPTRuJW4
//	#else
//		SMPTRtJWL Uj;
//	#endif
//	#ifdef SMPTRuN
//	#endif
	uint8_t P[sizeof(float) * 3 + 2];
};
#define lH14T (1024*8)
static struct Sh14 *Ph14t[lH14T];
static SMPTRtI *Ph14ti[lH14T];
static uint32_t Ph14tl[lH14T] = {0};
static uint32_t Lh14i = 0;

static void Mwrite()
{
	SMPT_DBmN2L("Lrgba %d", Lrgba)

	FILE *file = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", file)

	fwrite(&Lji, sizeof(SMPTRtJWL), 1, file);
	fwrite(Pji, sizeof(SMPTRtJW), Lji, file);
	for (SMPTRtJWL U0 = 0; U0 < Lji; ++U0)
		fwrite(Pj[U0], sizeof(SMPTRtJW), Pjl[U0], file);
	fwrite(Pbindpose, sizeof(float), Lbindpose * 16, file);

	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
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

	struct Sh14 Pa[Lh14i];
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		for (uint32_t U1 = 0; U1 < Ph14tl[U0]; ++U1)
		{
			SMPTRtI Uh14ti = Ph14ti[U0][U1];
			memcpy(Pa + Uh14ti, Ph14t[U0][U1].P, sizeof(struct Sh14));
		}
	}
	fwrite(Pa, sizeof(struct Sh14), Lh14i, file);
	//fwrite(Pa, sizeof(uint8_t), La, file);

	fclose(file);
}

//.i https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
static uint64_t Mh14(uint8_t *P14)
{
	uint64_t h = 1469598103934665603ULL;
	for (uint8_t i = 0; i < sizeof(struct Sh14); i++)
	{
		h ^= P14[i];
		h *= 1099511628211ULL;
	}
	return h;
}
static void Ma(uint8_t *Pmix, uint16_t Ui)
{
	//! hash 14b
//	SMPT_DBmN2L("V0 %f", *(float *)Pmix)
//	SMPT_DBmN2L("V1 %f", *(float *)(Pmix + sizeof(float)))
//	SMPT_DBmN2L("V2 %f", *(float *)(Pmix + sizeof(float) * 2))
//	SMPT_DBmN2L("C %d", Pmix[sizeof(float) * 3])
//	SMPT_DBmN2L("J %d", Pmix[sizeof(float) * 3 + 1])

	//for (uint32_t U0 = 0; U0 < La; U0 += sizeof(float) * 3 + 2)
	uint16_t Uh14 = Mh14(Pmix) % lH14T;
	//for (uint32_t U0 = 0; U0 < La; U0 += sizeof(float) * 3 + 2)
	for (uint32_t U0 = 0; U0 < Ph14tl[Uh14]; ++U0)
	{
		//if (!memcmp(Pa + U0, Pmix, sizeof(float) * 3 + 2))
		if (!memcmp(Ph14t[Uh14][U0].P, Pmix, sizeof(struct Sh14)))
		{
			Pi[Ui] = realloc(Pi[Ui], Pil[Ui] * sizeof(SMPTRtI) + sizeof(SMPTRtI));
			//*(Pi[Ui] + Pil[Ui]) = U0 / (sizeof(float) * 3 + 2);
			*(Pi[Ui] + Pil[Ui]) = Ph14ti[Uh14][U0];
			++Pil[Ui];
			return;
		}
	}

	Pi[Ui] = realloc(Pi[Ui], Pil[Ui] * sizeof(SMPTRtI) + sizeof(SMPTRtI));
	//*(Pi[Ui] + Pil[Ui]) = La / (sizeof(float) * 3 + 2);
	*(Pi[Ui] + Pil[Ui]) = Lh14i;
	++Pil[Ui];

//	Pa = realloc(Pa, La + sizeof(float) * 3 + 2);
//	memcpy(Pa + La, Pmix, sizeof(float) * 3 + 2);
//	La += sizeof(float) * 3 + 2;
	Ph14ti[Uh14] = realloc(Ph14ti[Uh14], sizeof(SMPTRtI) * Ph14tl[Uh14] + sizeof(SMPTRtI));
	Ph14ti[Uh14][Ph14tl[Uh14]] = Lh14i;

	Ph14t[Uh14] = realloc(Ph14t[Uh14], sizeof(struct Sh14) * Ph14tl[Uh14] + sizeof(struct Sh14));
	memcpy(Ph14t[Uh14][Ph14tl[Uh14]].P, Pmix, sizeof(struct Sh14));
	++Ph14tl[Uh14];

	++Lh14i;
}
void smptg_mdMsend()
{
	SMPT_DBmN2L("SMPTRcMA %d", SMPTRcMA)

	Pj = malloc(0);
	Pjl = malloc(0);

	Pji = malloc(0);

	Pbindpose = malloc(0);

	Prgba = malloc(0);

	//Pa = malloc(0);
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		Ph14t[U0] = malloc(0);
		Ph14ti[U0] = malloc(0);
	}

	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
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
			Mset_bone(Pcgltf_data);

		uint16_t Ui;
		for (uint32_t U1 = 0; U1 < Pcgltf_data->nodes_count; ++U1)
		{
			cgltf_node *Pcgltf_node = Pcgltf_data->nodes + U1;
			cgltf_mesh *Pcgltf_mesh = Pcgltf_node->mesh;
			if (!Pcgltf_mesh)
				continue;

			uint8_t
				#ifdef SMPTRuJW4
					#ifdef SMPTRuN
					#endif
				#else
					Pmix[sizeof(float) * 3 + 2] = {0};
				#endif

			SMPT_DBmN2L("Pcgltf_node %s", Pcgltf_node->name)
			Ui = 0xFFFF;
			for (uint8_t U2 = 0; U2 < Pml[U0]; ++U2)
			{
				SMPT_DBmN2L("T0 %s", Pcgltf_node->name)
				SMPT_DBmN2L("T1 %s", Pm[U0][U2])
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
				for (uint8_t U2 = 0; U2 < U0; ++U2)
				{
					Ui += Pml[U2];
				}
				//SMPT_DBmN2L("Ui %d", Ui)

				for (uint32_t U2 = 0; U2 < Pcgltf_mesh->primitives_count; ++U2)
				{
					cgltf_primitive *Pcgltf_primitive = Pcgltf_mesh->primitives + U2;

					cgltf_material *Pcgltf_material = Pcgltf_primitive->material;
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
							Pmix[sizeof(float) * 3] = Min_rgba((uint8_t)(Pemissive_factor[0] * 255) << (8+8+8) | (uint8_t)(Pemissive_factor[1] * 255) << (8+8) | (uint8_t)(Pemissive_factor[2] * 255) << 8 | (uint8_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255));
							//SMPT_DBmN2L("Pmix C0 %d", Pmix[sizeof(float) * 3])
						}
					}
					else
					{
					}

					cgltf_accessor *Pcgltf_accessor_index = Pcgltf_primitive->indices;
					for (uint32_t U3 = 0; U3 < Pcgltf_accessor_index->count; ++U3)
					{
						cgltf_size Udi = cgltf_accessor_read_index(Pcgltf_accessor_index, U3);

						//! fix
						for (uint32_t U4 = 0; U4 < Pcgltf_primitive->attributes_count; ++U4)
						{
							float Pda[4];
							cgltf_attribute *Pcgltf_attribute = Pcgltf_primitive->attributes + U4;
							cgltf_accessor_read_float(Pcgltf_attribute->data, Udi, Pda, 4);

							if (Pcgltf_attribute->type == cgltf_attribute_type_joints)
							{
								#ifdef SMPTRuJW4
								#else
									Pmix[sizeof(float) * 3 + 1] = Pda[0];
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
							else if (Pcgltf_attribute->type == cgltf_attribute_type_position)
							{
								memcpy(Pmix, Pda, sizeof(float) * 3);
							}
							else if
							(
								sizeof(SMPTRtRGBAL) == sizeof(uint8_t) &&
								!strcmp(Pcgltf_material->name, "VRGBA") &&
								Pcgltf_attribute->type == cgltf_attribute_type_color
							)
							{
								Pmix[sizeof(float) * 3] = Min_rgba((uint8_t)(Pda[0] * 255) << (8+8+8) | (uint8_t)(Pda[1] * 255) << (8+8) | (uint8_t)(Pda[2] * 255) << 8 | (uint8_t)(Pda[3] * 255));
								if (Pmix[sizeof(float) * 3] == 255)
									SMPT_DBmW2L("smptg_mdMsend VC")
							}
							else
							{
								SMPT_DBmW2L("smptg_mdMsend Pcgltf_attribute->type %d", Pcgltf_attribute->type)
							}
						}

						Ma(Pmix, Ui);
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
	for (SMPTRtJWL U0 = 0; U0 < Lji; ++U0)
		free(Pj[U0]);
	free(Pj);
	free(Pjl);

	free(Pji);
	free(Prgba);

	//free(Pa);
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		free(Ph14t[U0]);
		free(Ph14ti[U0]);
	}

	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
		free(Pi[U0]);

	free(Pbindpose);
}
