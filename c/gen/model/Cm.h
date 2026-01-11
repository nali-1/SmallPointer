#define lM_A (sizeof(float) * 3 + 2)

static SMPTRtJW *Pm_ji;
static SMPTRtJWL Lm_ji = 0;

static SMPTRtJW **Pm_j;
static uint8_t *Pm_jl;

static uint32_t *Pm_rgba;
static SMPTRtRGBAL Lm_rgba = 0;

static float *Pm_bindpose;
static uint32_t Lm_bindpose = 0;

static SMPTRtRGBAL Mm_in_rgba(uint32_t Urgba)
{
	for (SMPTRtRGBAL U0 = 0; U0 < Lm_rgba; ++U0)
		if (!memcmp(Pm_rgba + U0, &Urgba, sizeof(uint32_t)))
			return U0;
	return 255;
}
static void Mm_rgba(cgltf_data *Pcgltf_data)
{
	for (uint8_t U0 = 0; U0 < Pcgltf_data->materials_count; ++U0)
	{
		cgltf_material *Pcgltf_material = Pcgltf_data->materials + U0;

		SMPT_DBmN2L("Pcgltf_material %s", Pcgltf_material->name)

		if (!strcmp(Pcgltf_material->name, "VRGBA"))
			continue;

		cgltf_float *Pemissive_factor = Pcgltf_material->emissive_factor;

		uint32_t Urgba = (uint32_t)(Pemissive_factor[0] * 255.0F) << (8+8+8) | (uint32_t)(Pemissive_factor[1] * 255.0F) << (8+8) | (uint32_t)(Pemissive_factor[2] * 255.0F) << 8 | (uint32_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255.0F);
		if (Mm_in_rgba(Urgba) != 255)
			continue;

//		SMPT_DBmN2L("rf %f", Pemissive_factor[0])
//		SMPT_DBmN2L("gf %f", Pemissive_factor[1])
//		SMPT_DBmN2L("bf %f", Pemissive_factor[2])
//		SMPT_DBmN2L("af %f", Pcgltf_material->pbr_metallic_roughness.base_color_factor[3])

//		SMPT_DBmN2L("rd %d", Urgba >> (8+8+8))
//		SMPT_DBmN2L("gd %d", (Urgba >> (8+8)) & 255)
//		SMPT_DBmN2L("bd %d", (Urgba >> 8) & 255)
//		SMPT_DBmN2L("ad %d", Urgba & 255)

		Pm_rgba = realloc(Pm_rgba, sizeof(uint32_t) * Lm_rgba + sizeof(uint32_t));
		Pm_rgba[Lm_rgba] = Urgba;
		++Lm_rgba;
	}
}

static void Mm_bone(cgltf_data *Pcgltf_data, uint8_t U0)
{
	for (uint8_t U1 = 0; U1 < Pmal[U0]; ++U1)
	{
		for (uint8_t U2 = 0; U2 < Pcgltf_data->skins_count; ++U2)
		{
			cgltf_skin *Pcgltf_skin = Pcgltf_data->skins + U2;
			if (!strcmp(Pcgltf_skin->name, Pma[U0]))
			{
				SMPT_DBmN2L("joints_count %d", Pcgltf_skin->joints_count)
				SMPTRtJWL joints_count = Pcgltf_skin->joints_count;
				for (SMPTRtJWL U3 = 1; U3 < Pcgltf_skin->joints_count; ++U3)
				{
					cgltf_node *Pcgltf_node_joint = Pcgltf_skin->joints[U3];

					uint16_t U00 = 0;
					if (!Pcgltf_node_joint->parent || !Pcgltf_node_joint->parent->parent)
					{
						--joints_count;
						SMPT_DBmW2L("Mmbone F %d %s", U3, Pcgltf_node_joint->name)
						continue;
					}
				}
				SMPT_DBmN2L("joints_count F %d", joints_count)

				//.i bindpose
				Pm_bindpose = realloc(Pm_bindpose, (Lm_bindpose + joints_count - 1) * sizeof(float) * 16);
				memcpy(Pm_bindpose + Lm_bindpose * 16, Pcgltf_skin->inverse_bind_matrices->buffer_view->buffer->data + Pcgltf_skin->inverse_bind_matrices->buffer_view->offset + sizeof(float) * 16, sizeof(float) * 16 * (joints_count - 1));
				Lm_bindpose += joints_count - 1;

				//.i use first bone as main with default m4x4
				cgltf_node *Pbase_cgltf_node = Pcgltf_skin->joints[0];

				Pm_j = realloc(Pm_j, sizeof(SMPTRtJW *) * (Lm_ji + 1));
				Pm_j[Lm_ji] = malloc(sizeof(SMPTRtJW) * 512);
				Pm_j[Lm_ji][0] = 0;
				Pm_jl = realloc(Pm_jl, sizeof(uint8_t) * (Lm_ji + 1));
				Pm_jl[Lm_ji] = sizeof(uint8_t);
				//SMPT_DBmN2L("Pcgltf_node_joint %d %s", joints_count, Pcgltf_skin->joints[joints_count]->name)
				for (uint8_t U3 = 1; U3 < joints_count; ++U3)
				{
					cgltf_node *Pcgltf_node_joint = Pcgltf_skin->joints[U3];
					//SMPT_DBmN2L("Pcgltf_node_joint %d %s", U3, Pcgltf_node_joint->name)

					//.i ik rig -> fix animate
					uint16_t U00 = 0;
					if (Pcgltf_node_joint->parent && Pcgltf_node_joint->parent->parent)
					{
						while ((Pcgltf_node_joint = Pcgltf_node_joint->parent) != Pbase_cgltf_node)
						{
							for (uint8_t U1 = 1; U1 < joints_count; ++U1)
								if (Pcgltf_node_joint == Pcgltf_skin->joints[U1])
								{
									Pm_j[Lm_ji][Pm_jl[Lm_ji] + U00 + 1] = U1;
									break;
								}

							++U00;
						}
					}
					else
					{
						SMPT_DBmW2L("Mmbone %d %s", U3, Pcgltf_node_joint->name)
						continue;
					}
					Pm_j[Lm_ji][Pm_jl[Lm_ji]] = U00;
					Pm_jl[Lm_ji] += sizeof(uint8_t) + U00;
				}

				Pm_ji = realloc(Pm_ji, Lm_ji + 1 * sizeof(SMPTRtJWL));
				Pm_ji[Lm_ji] = joints_count;
				++Lm_ji;
			}
		}
	}
}

static void Mm_mesh(cgltf_data *Pcgltf_data, const char **Pm[], const uint8_t Pml[], uint32_t U0)
{
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
						Pmix[sizeof(float) * 3] = Mm_in_rgba((uint32_t)(Pemissive_factor[0] * 255.0F) << (8+8+8) | (uint32_t)(Pemissive_factor[1] * 255.0F) << (8+8) | (uint32_t)(Pemissive_factor[2] * 255.0F) << 8 | (uint32_t)(Pcgltf_material->pbr_metallic_roughness.base_color_factor[3] * 255.0F));
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

//						for (uint8_t U0 = 0; U0 < 4; ++U0)
//							SMPT_DBmN2L("%d Pda %d %f", U4, U0, Pda + U0 * sizeof(float))

						if (Pcgltf_attribute->type == cgltf_attribute_type_joints)
						{
							#ifdef SMPTRuJW4
							#else
								Pmix[sizeof(float) * 3 + 1] = Pda[0];
//								if (Pda[0] > 52)
//									SMPT_DBmW2L("smptg_mdMsend j0 %d", Pda[0])
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
							Pmix[sizeof(float) * 3] = Mm_in_rgba((uint32_t)(Pda[0] * 255.0F) << (8+8+8) | (uint32_t)(Pda[1] * 255.0F) << (8+8) | (uint32_t)(Pda[2] * 255.0F) << 8 | (uint32_t)(Pda[3] * 255.0F));
							if (Pmix[sizeof(float) * 3] == 255)
								SMPT_DBmW2L("smptg_mdMsend VC")
						}
						else
						{
							SMPT_DBmW2L("smptg_mdMsend Pcgltf_attribute->type %d", Pcgltf_attribute->type)
						}
					}

					Mh14_mesh(Pmix, Ui, lM_A);
				}
			}
		}
	}
}

static void Mm_write()
{
	SMPT_DBmN2L("Lm_rgba %d", Lm_rgba)

	FILE *Pfile = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", Pfile)
	SMPT_DBmN2L("ftell %ld", ftell(Pfile))

	fwrite(Pm_ji, sizeof(SMPTRtJW), Lm_ji, Pfile);
	for (SMPTRtJWL U0 = 0; U0 < Lm_ji; ++U0)
		fwrite(Pm_j[U0], sizeof(SMPTRtJW), Pm_jl[U0], Pfile);
	fwrite(Pm_bindpose, sizeof(float), Lm_bindpose * 16, Pfile);

//	for (uint32_t l0 = 0; l0 < Lm_rgba; ++l0)
//	{
//		SMPT_DBmN2L("Uc %d", l0)
//		SMPT_DBmN2L("rf %f", (Pm_rgba[l0] >> (8+8+8)) / 255.0F)
//		SMPT_DBmN2L("gf %f", ((Pm_rgba[l0] >> (8+8)) & 255) / 255.0F)
//		SMPT_DBmN2L("bf %f", ((Pm_rgba[l0] >> 8) & 255) / 255.0F)
//		SMPT_DBmN2L("af %f", (Pm_rgba[l0] & 255) / 255.0F)
//	}
	fwrite(&Lm_rgba, sizeof(SMPTRtRGBAL), 1, Pfile);
	fwrite(Pm_rgba, sizeof(uint32_t), Lm_rgba, Pfile);

	for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
	{
		SMPT_DBmN2L("Ph14_il[%d] %d", U0, Ph14_il[U0])
		fwrite(Ph14_il + U0, sizeof(SMPTRtI), 1, Pfile);
		fwrite(Ph14_i[U0], sizeof(SMPTRtI), Ph14_il[U0], Pfile);
	}

	uint8_t *Pa = malloc(lM_A * Lh14_i);
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		for (uint32_t U1 = 0; U1 < Ph14_tl[U0]; ++U1)
		{
			SMPTRtI Uh14ti = Ph14_ti[U0][U1];
			memcpy(Pa + Uh14ti, Ph14_t[U0] + lM_A * U1, lM_A);
		}
	}
	fwrite(Pa, lM_A, Lh14_i, Pfile);
	free(Pa);

	SMPT_DBmR2L("fclose %d", fclose(Pfile))
}

static void Mm_set()
{
	Pm_j = malloc(0);
	Pm_jl = malloc(0);

	Pm_ji = malloc(0);

	Pm_bindpose = malloc(0);

	Pm_rgba = malloc(0);
}

static void Mm_free()
{
	for (SMPTRtJWL U0 = 0; U0 < Lm_ji; ++U0)
		free(Pm_j[U0]);
	free(Pm_j);
	free(Pm_jl);

	free(Pm_ji);
	free(Pm_rgba);

	free(Pm_bindpose);
}
