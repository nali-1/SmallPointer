static void Mset_mesho(cgltf_data *Pcgltf_data, const char **Pm[], const uint8_t Pml[], uint32_t U0)
{
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

					//! mesh to
					//Ma(Pmix, Ui);
//					void Ma(*Pi, *Pil, Ls, *Ph14t, *Ph14ti, *Ph14tl, *Lh14i)
//					{
//						uint16_t Uh14 = Mh14(Pmix, sizeof(struct )) % lH14T;
//						for (uint32_t U0 = 0; U0 < Ph14tl[Uh14]; ++U0)
//						{
//							if (!memcmp(Ph14t[Uh14][U0].P, Pmix, lO))
//							{
//								Pi[Ui] = realloc(Pi[Ui], Pil[Ui] * sizeof(SMPTRtI) + sizeof(SMPTRtI));
//								*(Pi[Ui] + Pil[Ui]) = Ph14ti[Uh14][U0];
//								++Pil[Ui];
//								return;
//							}
//						}
//
//						Pi[Ui] = realloc(Pi[Ui], Pil[Ui] * sizeof(SMPTRtI) + sizeof(SMPTRtI));
//						*(Pi[Ui] + Pil[Ui]) = Lh14i;
//						++Pil[Ui];
//
//						Ph14ti[Uh14] = realloc(Ph14ti[Uh14], sizeof(SMPTRtI) * Ph14tl[Uh14] + sizeof(SMPTRtI));
//						Ph14ti[Uh14][Ph14tl[Uh14]] = Lh14i;
//
//						Ph14t[Uh14] = realloc(Ph14t[Uh14], lO * Ph14tl[Uh14] + lO);
//						memcpy(Ph14t[Uh14][Ph14tl[Uh14]].P, Pmix, lO);
//						++Ph14tl[Uh14];
//
//						++Lh14i;
//					}
				}
			}
		}
	}
}
