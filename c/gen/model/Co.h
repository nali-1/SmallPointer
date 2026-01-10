#define lO_A (sizeof(float) * 3)

static void Mo_mesh(cgltf_data *Pcgltf_data, const char **Pm[], const uint8_t Pml[], uint32_t U0)
{
//	SMPT_DBmN2L("U0 %d", U0)
//	SMPT_DBmN2L("Pm %p", Pm)
//	SMPT_DBmN2L("Pml %p", Pml)
	uint16_t Ui;
	for (uint32_t U1 = 0; U1 < Pcgltf_data->nodes_count; ++U1)
	{
		cgltf_node *Pcgltf_node = Pcgltf_data->nodes + U1;
		cgltf_mesh *Pcgltf_mesh = Pcgltf_node->mesh;
		if (!Pcgltf_mesh)
			continue;

		uint8_t Pmix[sizeof(float) * 3] = {0};

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
						else
						{
							SMPT_DBmW2L("smptg_mdMsend Pcgltf_attribute->type %d", Pcgltf_attribute->type)
						}
					}

					Mh14_mesh(Pmix, Ui, lO_A);
				}
			}
		}
	}
}

static void Mo_write()
{
	FILE *Pfile = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", Pfile)
	SMPT_DBmN2L("ftell %ld", ftell(Pfile))

	for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcO; ++U0)
	{
		fwrite(Ph14_il + U0, sizeof(SMPTRtI), 1, Pfile);
		fwrite(Ph14_i[U0], sizeof(SMPTRtI), Ph14_il[U0], Pfile);
//		SMPT_DBmN2L("Ph14_il + %d %p", U0, Ph14_il + U0)
//		SMPT_DBmN2L("Ph14_il[%d] %d", U0, Ph14_il[U0])
	}

	uint8_t *Pa = malloc(lO_A * Lh14_i);
	for (uint32_t U0 = 0; U0 < lH14T; ++U0)
	{
		//SMPT_DBmN2L("Ph14_tl[%d] %d", U0, Ph14_tl[U0])
		for (uint32_t U1 = 0; U1 < Ph14_tl[U0]; ++U1)
		{
			SMPTRtI Uh14ti = Ph14_ti[U0][U1];
			memcpy(Pa + Uh14ti, Ph14_t[U0] + lO_A * U1, lO_A);
		}
	}
	fwrite(&Lh14_i, sizeof(uint32_t), 1, Pfile);
	fwrite(Pa, lO_A, Lh14_i, Pfile);
	free(Pa);

	SMPT_DBmR2L("fclose %d", fclose(Pfile))
}
