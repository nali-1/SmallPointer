#ifdef SMPT_CM_ST_ANDROID
	ANativeActivity *smptPanative_activity;

	static int Mset(void *p)
	{
		smptm_v4Mset();

		smptrMset();
		#ifdef SMPT_CM_CLIENT
			smpt_rd_vkMset();
			//! audio math
			//smpt_adoMset();
		#endif
		smpt_ip_aipMloop();
		return 0;
	}

	void ANativeActivity_onCreate(ANativeActivity *Panativeactivity, void *Psaved_state, size_t Lsaved_state)
	{
		if (!(smpt_sfUstate & SMPT_SFuS_ANDROID_CREATE))
		{
			#ifdef SMPT_CM_DEBUG
				smpt_dbMset();
			#endif

			smpt_sfUstate |= SMPT_SFuS_ANDROID_CREATE;
			SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, Mset, NULL))

			Panativeactivity->callbacks->onNativeWindowCreated = smpt_sf_awdMcreated;
			Panativeactivity->callbacks->onNativeWindowResized = smpt_sf_awdMresized;
			Panativeactivity->callbacks->onNativeWindowDestroyed = smpt_sf_awdMdestroyed;
			Panativeactivity->callbacks->onInputQueueCreated = smpt_ip_aipMcreated;
			Panativeactivity->callbacks->onInputQueueDestroyed = smpt_ip_aipMdestroyed;
			smptPanative_activity = Panativeactivity;
		}
		SMPT_DBmN2L("ANativeActivity_onCreate")
	}
#endif

#ifdef SMPT_CM_ST_LINUX
	int main()
	{
		smpt_dbMset();
		#ifdef SMPT_CM_CLIENT
			SMPT_DBmR2L("signal %d", signal(SIGINT, SIG_IGN))
		#endif

		smptm_v4Mset();

		#ifdef SMPT_CM_GEN
			smptgMsend();
		#endif
		smptrMset();
		#ifdef SMPT_CM_CLIENT
			#ifdef SMPT_CM_LIBINPUT
				smpt_ip_lipMset();
			#endif

			#ifdef SMPT_CM_WL
				smpt_sf_wl_ceMset();
			#else
				#ifdef SMPT_CM_VK
					smpt_rd_vkMset();
				#endif
			#endif

			//! audio math
			//smpt_adoMset();
			//! switch to pipewire
			// al_set();
			//! test with wl
			#ifdef SMPT_CM_LIBINPUT
				smpt_ip_lipMloop();
			#endif
		#endif
		SMPT_DBmR2L("tcflush %d", tcflush(STDIN_FILENO, TCIFLUSH))
		smpt_dbMfree();
	}
#endif

#ifdef SMPT_CM_ST_UI
//	#ifdef
		#define mGET_PROC_ADDRESS(P) glXGetProcAddress(P);
//	#endif
//	#ifdef
//		#define mGET_PROC_ADDRESS(P) eglGetProcAddress(P);
//	#endif
	//.c compute shader
	//#define uCOMP_SHADER

	#define mOFFSET_UBO(U) (((uint32_t)(U) % (uint32_t)Vuniform_buffer_offset_alignment != 0u) ? (uint32_t)(U) + ((uint32_t)Vuniform_buffer_offset_alignment - ((uint32_t)(U) % (uint32_t)Vuniform_buffer_offset_alignment)) : (uint32_t)(U))
	#define mSIZE_UBO(U) (((uint32_t)(U) + (uint32_t)Vuniform_buffer_offset_alignment - 1u) & ~((uint32_t)Vuniform_buffer_offset_alignment - 1u))
	static GLint Vuniform_buffer_offset_alignment;
	static GLint Vshader_storage_buffer_offset_alignment;

	//static void (*Mclear_color)(GLfloat, GLfloat, GLfloat, GLfloat);
	static void (*Mget_integerv)(GLenum, GLint *);
	static void (*Mget_floatv)(GLenum, GLfloat *);
	#ifdef SMPT_CM_GL_DEBUG
		static void (*Mdebug_message_callback)(GLDEBUGPROC, const void *);
		static void (*Menable)(GLenum);
		static void (*Mdebug_message_control)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
	#endif
	static void (*Muse_program)(GLuint);
	static void (*Mbind_buffer)(GLenum, GLuint);
	static void (*Mbuffer_data)(GLenum, GLsizeiptr, const void *, GLenum);
	//static void (*Mbind_buffer_base)(GLenum, GLuint, GLuint);
	static void *(*Mmap_buffer_range)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
	static GLboolean (*Munmap_buffer)(GLenum);
	static void (*Mshader_source)(GLuint, GLsizei, const GLchar *const *, const GLint *);
	static void (*Mcompile_shader)(GLuint);
	static void (*Mget_shaderiv)(GLuint, GLenum, GLint *);
	static void (*Mget_shader_info_log)(GLuint, GLsizei, GLsizei *, GLchar *);
	static GLuint (*Mcreate_program)(void);
	static GLuint (*Mcreate_shader)(GLenum);
	static void (*Mattach_shader)(GLuint, GLuint);
	static void (*Mlink_program)(GLuint);
	static void (*Mdetach_shader)(GLuint, GLuint);
	//static void (*Mdelete_program)(GLuint);
	static void (*Mdelete_shader)(GLuint);
	static void (*Mgen_buffers)(GLsizei, GLuint *);
	#ifndef uCOMP_SHADER
		static void (*Mdraw_elements)(GLenum, GLsizei, GLenum, const void *);
		static void (*Mgen_vertex_arrays)(GLsizei, GLuint *);
		static void (*Mbind_vertex_array)(GLuint);
		static void (*Mget_vertex_attribiv)(GLuint, GLenum, GLint *);
		static void (*Mget_vertex_attrib_pointerv)(GLuint, GLenum, void **);
	#endif
	static void (*Mvertex_attrib_pointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
	static void (*Mvertex_attrib_ipointer)(GLuint, GLint, GLenum, GLsizei, const void *);
	static void (*Menable_vertex_attrib_array)(GLuint);
	static void (*Mdisable_vertex_attrib_array)(GLuint);
	static void (*Mbind_buffer_range)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
	#ifdef uCOMP_SHADER
		static void (*Mdispatch_compute)(GLuint, GLuint, GLuint);
//		static GLsync (*Mfence_sync)(GLenum, GLbitfield);
//		static GLenum (*Mclient_wait_sync)(GLsync, GLbitfield, GLuint64);
//		static void (*Mdelete_sync)(GLsync);
		static void (*Mget_booleanv)(GLenum, GLboolean *);
		static void (*Mdisable_client_state)(GLenum);
		static void (*Menable_client_state)(GLenum);
		static void (*Mvertex_pointer)(GLint, GLenum, GLsizei, const GLvoid *);
		static void (*Mcolor_pointer)(GLint, GLenum, GLsizei, const GLvoid *);
		static void (*Mdraw_arrays)(GLenum, GLint, GLsizei);
		static void (*Mmemory_barrier)(GLbitfield);
		#ifndef SMPT_CM_GL_DEBUG
			static void (*Menable)(GLenum);
		#endif
		static void (*Mdisable)(GLenum);
		static GLint (*Mget_uniform_location)(GLuint, const GLchar *);
		static void (*Muniform1i)(GLint, GLint);
		static void (*Mget_uniformiv)(GLuint, GLint, GLint *);
		static void (*Mactive_texture)(GLenum);
		static void (*Mgen_textures)(GLsizei, GLuint *);
		static void (*Mbind_texture)(GLenum, GLuint);
		static void (*Mtex_parameteri)(GLenum, GLenum, GLint);
		static void (*Mtex_image2d)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *);
		//static void (*Mshade_model)(GLenum);
	#endif
	static void (*Mget_programiv)(GLuint, GLenum, GLint *);
	static void (*Mget_program_info_log)(GLuint, GLsizei, GLsizei *, GLchar *);

	static GLuint Vprogram_m;
	#ifdef uCOMP_SHADER
		static GLuint Vshader_comp;
	#endif
	#ifndef uCOMP_SHADER
		static GLuint Vshader_vert;
		static GLuint Vshader_frag;
	#endif

	#ifndef uCOMP_SHADER
		#define uLA_UBO mSIZE_UBO(smptr_ce_mdLa)
		#define uLCOLOR_UBO smptr_ce_mdLrgba
		static GLuint Vvao_m;
		#define uLI_UBO mSIZE_UBO(Li)
	#endif
	//.c ubo cache
	#define lUBO 512u
	#define tUBO uint16_t
	#ifdef uCOMP_SHADER
		static uint8_t *Pa_fix;
		static uint32_t La_fix;
		#define uLA_UBO mSIZE_UBO(La_fix)
		#define uLCOLOR_UBO mSIZE_UBO(smptr_ce_mdLrgba)
		//.c fix vec4*2 vc
		#ifdef uCOMP_SHADER
			static const uint32_t Lal_fix = sizeof(float) * 4 * 3 * 3 * 30000;
		#endif
		#ifndef uCOMP_SHADER
			static const uint32_t Lal_fix = sizeof(float) * 4 * 2 * 3 * 30000;
		#endif
		uint32_t Pcomp_ssbo[SMPTR_MDcM];
		uint32_t Lcomp_ssbo = 0;
		uint32_t Pi_fix[SMPTR_MDcM];
		uint32_t Li_fix = 0;
		#define uLI_UBO mSIZE_UBO(Li_fix)
	#endif
	#define lBUFFER_M (1 + lUBO)
	static GLuint Pbuffer_m[lBUFFER_M];

	static uint32_t Pii[SMPTR_MDcM];
	static uint32_t Li = 0;
	static uint32_t Lbp_fix = 0;
	static uint32_t Pbpl_fix[SMPTR_MDc];
	static void Mbuffer_write(uint8_t *Pbp, uint8_t *Pi)
	{
		Mbind_buffer(GL_ARRAY_BUFFER, Pbuffer_m[0]);
		#ifdef uCOMP_SHADER
			Mbuffer_data(GL_ARRAY_BUFFER, uLA_UBO + uLI_UBO + mSIZE_UBO(Lbp_fix) + uLCOLOR_UBO + Lcomp_ssbo, NULL, GL_DYNAMIC_DRAW);
		#endif
		#ifndef uCOMP_SHADER
			Mbuffer_data(GL_ARRAY_BUFFER, uLA_UBO + uLI_UBO + mSIZE_UBO(Lbp_fix) + uLCOLOR_UBO, NULL, GL_DYNAMIC_DRAW);
		#endif
		void *Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, uLA_UBO + uLI_UBO, mSIZE_UBO(Lbp_fix) + smptr_ce_mdLrgba, GL_MAP_WRITE_BIT);
		memcpy(Pu, Pbp, Lbp_fix);
		memcpy(Pu + mSIZE_UBO(Lbp_fix), smptr_ce_mdPrgba, smptr_ce_mdLrgba);
		Munmap_buffer(GL_ARRAY_BUFFER);

		#ifdef uCOMP_SHADER
			Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, uLA_UBO, Li_fix, GL_MAP_WRITE_BIT);
			for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
			{
				memcpy(Pu + Pi_fix[U0], Pi + Pii[U0], smptr_ce_mdPil[U0]);
			}
		#endif
		#ifndef uCOMP_SHADER
			Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, uLA_UBO, Li, GL_MAP_WRITE_BIT);
			memcpy(Pu, Pi, Li);
		#endif
		Munmap_buffer(GL_ARRAY_BUFFER);

		#ifdef uCOMP_SHADER
			Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, 0, La_fix, GL_MAP_WRITE_BIT);
			memcpy(Pu, Pa_fix, La_fix);
		#endif
		#ifndef uCOMP_SHADER
			Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, 0, smptr_ce_mdLa, GL_MAP_WRITE_BIT);
			memcpy(Pu, smptr_ce_mdPa, smptr_ce_mdLa);
		#endif
		Munmap_buffer(GL_ARRAY_BUFFER);
		#ifdef uCOMP_SHADER
			//.i fix buffer offset
			for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
				smptr_ce_mdPil[U0] /= sizeof(SMPTRtI);

//			for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
//				SMPT_DBmN2L("smptr_ce_mdPil[%d] %d", U0, smptr_ce_mdPil[U0])
			Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, uLA_UBO + uLI_UBO + mSIZE_UBO(Lbp_fix) + uLCOLOR_UBO, Lcomp_ssbo, GL_MAP_WRITE_BIT);
			for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
			{
				memcpy(Pu + Pcomp_ssbo[U0], smptr_ce_mdPil + U0, sizeof(SMPTRtI));
			}
			Munmap_buffer(GL_ARRAY_BUFFER);

			for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
				smptr_ce_mdPil[U0] *= sizeof(SMPTRtI);
		#endif
	}
	static void Mbuffer()
	{
		SMPT_DBmN2L("Mbuffer 0")

		for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
		{
			Pii[U0] = Li;
			Li += smptr_ce_mdPil[U0];
		}
		SMPT_DBmN2L("Li %d", Li);
		for (SMPTRtJWL U0 = 0; U0 < SMPTR_MDc; ++U0)
		{
			Pbpl_fix[U0] = Lbp_fix;
			Lbp_fix += mSIZE_UBO(sizeof(float) * 16 * 2 * smptr_ce_mdPj[U0]);
			SMPT_DBmN2L("Pbpl_fix[%d] %d", U0, Pbpl_fix[U0]);
		}
		uint8_t *Pbp = malloc(Lbp_fix);
		for (SMPTRtJWL U0 = 0; U0 < SMPTR_MDc; ++U0)
		{
			//SMPT_DBmN2L("smptr_ce_mdPj[%d] %d", U0, smptr_ce_mdPj[U0]);
			//SMPT_DBmN2L("Pbpl_fix[%d] %d", U0, Pbpl_fix[U0]);
			memcpy(Pbp + Pbpl_fix[U0] + sizeof(float) * 16 * 2, smptr_ce_mdPbp[U0], sizeof(float) * 16 * 2 * (smptr_ce_mdPj[U0] - 1));
		}
		uint8_t *Pi = malloc(Li);
		for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
		{
			SMPT_DBmN2L("Pii[%d] %d", U0, Pii[U0]);
			SMPT_DBmN2L("smptr_ce_mdPil[%d] %d", U0, smptr_ce_mdPil[U0]);
			memcpy(Pi + Pii[U0], smptr_ce_mdPi[U0], smptr_ce_mdPil[U0]);
		}
		#ifdef uCOMP_SHADER
			SMPT_DBmN2L("Lal_fix %ld", Lal_fix);
			#ifdef SMPTRuN
				#ifdef SMPTRuNF
					uint32_t Lv = sizeof(float) * 4;
				#endif
				#ifndef SMPTRuNF
					uint32_t Lv = sizeof(float) * (4 + 4);
				#endif
			#endif
			#ifndef SMPTRuN
				uint32_t Lv = sizeof(float) * 4;
			#endif
			Pa_fix = malloc(smptr_ce_mdLa / SMPTRlV * Lv);
			for (uint32_t U0 = 0; U0 < smptr_ce_mdLa / SMPTRlV; ++U0)
			{
				memcpy(Pa_fix + Lv * U0, smptr_ce_mdPa + SMPTRlV * U0, sizeof(float) * 3);
				memcpy(Pa_fix + Lv * U0 + sizeof(float) * 3 + 2, smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float) * 3, 2);
				//memset(Pa_fix + Lv * U0 + sizeof(float) * 3 + 2, 0, 2);
				#ifdef SMPTRuN
					#ifndef SMPTRuNF
						memcpy(Pa_fix + Lv * U0 + sizeof(float) * 4, smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float) * 3 + 2, sizeof(float) * 3);
						//memset(Pa_fix + Lv * U0 + sizeof(float) * (4 + 3), 0, sizeof(float));
					#endif
				#endif
//				SMPT_DBmN2L("Pv %d %f %f %f", U0, *(float *)(smptr_ce_mdPa + SMPTRlV * U0), *(float *)(smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float)), *(float *)(smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float) * 2))
//				SMPT_DBmN2L("Pn %d %f %f %f", U0, *(float *)(smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float) * 3 + 2), *(float *)(smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float) * 3 + 2 + sizeof(float)), *(float *)(smptr_ce_mdPa + SMPTRlV * U0 + sizeof(float) * 3 + 2 + sizeof(float) * 2))
			}
			La_fix = smptr_ce_mdLa / SMPTRlV * Lv;

			for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
			{
				Pcomp_ssbo[U0] = Lcomp_ssbo;
				Lcomp_ssbo += mSIZE_UBO(sizeof(SMPTRtI));
				Pi_fix[U0] = Li_fix;
				Li_fix += mSIZE_UBO(smptr_ce_mdPil[U0]);
			}
		#endif

		GLint Vvbo;
		Mgen_buffers(lBUFFER_M, Pbuffer_m);
		SMPT_DBmN2L("Pbuffer_m[0] %d", Pbuffer_m[0]);
		Mget_integerv(GL_ARRAY_BUFFER_BINDING, &Vvbo);
		#ifdef uCOMP_SHADER
			for (tUBO U0 = 1; U0 < 1 + lUBO; ++U0)
			{
				Mbind_buffer(GL_ARRAY_BUFFER, Pbuffer_m[U0]);
				Mbuffer_data(GL_ARRAY_BUFFER, mSIZE_UBO(Lal_fix) + mSIZE_UBO(sizeof(float) * 4 * 3 * SMPTR_CE_MDlBONE), NULL, GL_DYNAMIC_DRAW);
			}
			Mbuffer_write(Pbp, Pi);
		#endif
		#ifndef uCOMP_SHADER
			GLint Vvaa_enabled[3], Vvaa_size[3], Vvaa_stride[3], Vvaa_type[3], Vvaa_normalized[3];
			void *Vvaa_pointer[3];
			for (uint8_t U0 = 0; U0 < 3; ++U0)
			{
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &Vvaa_enabled[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &Vvaa_size[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &Vvaa_stride[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &Vvaa_type[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &Vvaa_normalized[U0]);
				Mget_vertex_attrib_pointerv(U0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &Vvaa_pointer[U0]);
			}

			GLint Vvao, Vebo;
			Mget_integerv(GL_VERTEX_ARRAY_BINDING, &Vvao);
			SMPT_DBmN2L("Vvao %d", Vvao);
			Mget_integerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &Vebo);

			for (tUBO U0 = 1; U0 < 1 + lUBO; ++U0)
			{
				Mbind_buffer(GL_ARRAY_BUFFER, Pbuffer_m[U0]);
				Mbuffer_data(GL_ARRAY_BUFFER, mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)) + (sizeof(float) * 4 * 3 * SMPTR_CE_MDlBONE), NULL, GL_DYNAMIC_DRAW);
			}
			Mbuffer_write(Pbp, Pi);

			Mgen_vertex_arrays(1, &Vvao_m);
			Mbind_vertex_array(Vvao_m);

			Mbind_buffer(GL_ARRAY_BUFFER, Pbuffer_m[0]);
			Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Pbuffer_m[0]);

			Menable_vertex_attrib_array(0);
			Mvertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, SMPTRlV, (void *)(0));
			Menable_vertex_attrib_array(1);
			Mvertex_attrib_ipointer(1, 1, GL_UNSIGNED_BYTE, SMPTRlV, (void *)(sizeof(float) * 3));
			Menable_vertex_attrib_array(2);
			Mvertex_attrib_ipointer(2, 1, GL_UNSIGNED_BYTE, SMPTRlV, (void *)(sizeof(float) * 3 + 1));

			Mbind_vertex_array(Vvao);
			Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Vebo);

			for (uint8_t U0 = 0; U0 < 3; ++U0)
			{
				if (Vvaa_enabled[U0])
				{
					Menable_vertex_attrib_array(U0);
				}
				else
				{
					Mdisable_vertex_attrib_array(U0);
				}

				Mvertex_attrib_pointer((GLuint)U0, Vvaa_size[U0], Vvaa_type[U0], Vvaa_normalized[U0], Vvaa_stride[U0], Vvaa_pointer[U0]);
			}
		#endif

		Mbind_buffer(GL_ARRAY_BUFFER, Vvbo);

		free(Pbp);
		free(Pi);

		#ifdef uCOMP_SHADER
			//! clean
			free(Pa_fix);
		#endif

		SMPT_DBmN2L("Mbuffer 1")
	}

	static void Mshader_gen(GLuint Vs, const char *Pc)
	{
		SMPT_DBmN2L("Mshader_gen 0")
		uint64_t Ld;
		void *Pd = smptfMread(Pc, &Ld);
		Pd = realloc(Pd, Ld + sizeof(char));
		((char *)Pd)[Ld] = '\0';
		Mshader_source(Vs, 1, (const GLchar *const *)&Pd, NULL);
		//SMPT_DBmN2L("Ld %d", Ld);
		//SMPT_DBmN2L("Pd %s", Pd);
		Mcompile_shader(Vs);

		GLint Vss;
		Mget_shaderiv(Vs, GL_COMPILE_STATUS, &Vss);
		if (!Vss)
		{
			char *Pcf = malloc(1024*4);
			Mget_shader_info_log(Vs, 1024*4, NULL, Pcf);
			SMPT_DBmN2L("Mget_shader_info_log %s", Pcf)
			free(Pcf);
		}

		free(Pd);
		SMPT_DBmN2L("Mshader_gen 1")
	}
	static void Mshader()
	{
		SMPT_DBmN2L("Mshader 0")
		Vprogram_m = Mcreate_program();
		#ifdef uCOMP_SHADER
			Vshader_comp = Mcreate_shader(GL_COMPUTE_SHADER);
			Mshader_gen(Vshader_comp, "0.comp");
			Mattach_shader(Vprogram_m, Vshader_comp);
			Mlink_program(Vprogram_m);

			GLint Vlink_status = 0;
			Mget_programiv(Vprogram_m, GL_LINK_STATUS, &Vlink_status);
			if (!Vlink_status)
			{
				GLint Lc = 0;
				Mget_programiv(Vprogram_m, GL_INFO_LOG_LENGTH, &Lc);
				char *Pc = malloc(Lc);
				Mget_program_info_log(Vprogram_m, Lc, NULL, Pc);
				SMPT_DBmW2L("glGetProgramInfoLog %s", Pc);
				free(Pc);
			}

			Mdetach_shader(Vprogram_m, Vshader_comp);
			Mdelete_shader(Vshader_comp);
		#endif
		#ifndef uCOMP_SHADER
			Vshader_vert = Mcreate_shader(GL_VERTEX_SHADER);
			Vshader_frag = Mcreate_shader(GL_FRAGMENT_SHADER);
			Mshader_gen(Vshader_vert, "0.vert");
			Mshader_gen(Vshader_frag, "0.frag");
			Mattach_shader(Vprogram_m, Vshader_vert);
			Mattach_shader(Vprogram_m, Vshader_frag);
			Mlink_program(Vprogram_m);

			GLint Vlink_status = 0;
			Mget_programiv(Vprogram_m, GL_LINK_STATUS, &Vlink_status);
			if (!Vlink_status)
			{
				GLint Lc = 0;
				Mget_programiv(Vprogram_m, GL_INFO_LOG_LENGTH, &Lc);
				char *Pc = malloc(Lc);
				Mget_program_info_log(Vprogram_m, Lc, NULL, Pc);
				SMPT_DBmW2L("glGetProgramInfoLog %s", Pc);
				free(Pc);
			}

			Mdetach_shader(Vprogram_m, Vshader_vert);
			Mdetach_shader(Vprogram_m, Vshader_frag);
			Mdelete_shader(Vshader_vert);
			Mdelete_shader(Vshader_frag);
		#endif
		SMPT_DBmN2L("Mshader 1")
	}

	#ifdef SMPT_CM_GL_DEBUG
		static uint8_t Ulimit = 0;
		void Mdebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
		{
			if (Ulimit < 255u)
			{
				SMPT_DBmW2L("gl_debug")
				SMPT_DBmW2L("source %d", source)
				SMPT_DBmW2L("type %d", type)
				SMPT_DBmW2L("id %d", id)
				SMPT_DBmW2L("severity %d", severity)
				SMPT_DBmW2L("length %d", length)
				SMPT_DBmW2L("message %s", message)
				SMPT_DBmW2L("userParam %p", userParam)
				++Ulimit;
			}
		}
	#endif

	#ifdef uCOMP_SHADER
		GLuint Vtexture_m = 0;
	#endif
	JNIEXPORT void JNICALL Java_com_nali_C_Mgl(JNIEnv *Pjnienv, jclass Vjclass)
	{
		smpt_dbMset();

		smptm_v4Mset();

		smptrMset();

		//Mclear_color = (void (*)(GLfloat, GLfloat, GLfloat, GLfloat))mGET_PROC_ADDRESS("glClearColor");
		Mget_integerv = (void (*)(GLenum, GLint *))mGET_PROC_ADDRESS("glGetIntegerv");
		Mget_floatv = (void (*)(GLenum, GLfloat *))mGET_PROC_ADDRESS("glGetFloatv");
		#ifdef SMPT_CM_GL_DEBUG
			Mdebug_message_callback = (void (*)(GLDEBUGPROC, const void *))mGET_PROC_ADDRESS("glDebugMessageCallback");
			Menable = (void (*)(GLenum))mGET_PROC_ADDRESS("glEnable");
			Mdebug_message_control = (void (*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean))mGET_PROC_ADDRESS("glDebugMessageControl");
		#endif
		Muse_program = (void (*)(GLuint))mGET_PROC_ADDRESS("glUseProgram");
		Mbind_buffer = (void (*)(GLenum, GLuint))mGET_PROC_ADDRESS("glBindBuffer");
		Mbuffer_data = (void (*)(GLenum, GLsizeiptr, const void *, GLenum))mGET_PROC_ADDRESS("glBufferData");
		//Mbind_buffer_base = (void (*)(GLenum, GLuint, GLuint))mGET_PROC_ADDRESS("glBindBufferBase");
		Mmap_buffer_range = (void *(*)(GLenum, GLintptr, GLsizeiptr, GLbitfield))mGET_PROC_ADDRESS("glMapBufferRange");
		Munmap_buffer = (GLboolean (*)(GLenum))mGET_PROC_ADDRESS("glUnmapBuffer");
		Mshader_source = (void (*)(GLuint, GLsizei, const GLchar *const *, const GLint *))mGET_PROC_ADDRESS("glShaderSource");
		Mcompile_shader = (void (*)(GLuint))mGET_PROC_ADDRESS("glCompileShader");
		Mget_shaderiv = (void (*)(GLuint, GLenum, GLint *))mGET_PROC_ADDRESS("glGetShaderiv");
		Mget_shader_info_log = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *))mGET_PROC_ADDRESS("glGetShaderInfoLog");
		Mcreate_program = (GLuint (*)(void))mGET_PROC_ADDRESS("glCreateProgram");
		Mcreate_shader = (GLuint (*)(GLenum))mGET_PROC_ADDRESS("glCreateShader");
		Mattach_shader = (void (*)(GLuint, GLuint))mGET_PROC_ADDRESS("glAttachShader");
		Mlink_program = (void (*)(GLuint))mGET_PROC_ADDRESS("glLinkProgram");
		Mdetach_shader = (void (*)(GLuint, GLuint))mGET_PROC_ADDRESS("glDetachShader");
		//Mdelete_program = (void (*)(GLenum))mGET_PROC_ADDRESS("glDeleteProgram");
		Mdelete_shader = (void (*)(GLenum))mGET_PROC_ADDRESS("glDeleteShader");
		Mgen_buffers = (void (*)(GLsizei, GLuint *))mGET_PROC_ADDRESS("glGenBuffers");
		#ifndef uCOMP_SHADER
			Mdraw_elements = (void (*)(GLenum, GLsizei, GLenum, const void *))mGET_PROC_ADDRESS("glDrawElements");
			Mgen_vertex_arrays = (void (*)(GLsizei, GLuint *))mGET_PROC_ADDRESS("glGenVertexArrays");
			Mbind_vertex_array = (void (*)(GLuint))mGET_PROC_ADDRESS("glBindVertexArray");
			Mget_vertex_attribiv = (void (*)(GLuint, GLenum, GLint *))mGET_PROC_ADDRESS("glGetVertexAttribiv");
			Mget_vertex_attrib_pointerv = (void (*)(GLuint, GLenum, void **))mGET_PROC_ADDRESS("glGetVertexAttribPointerv");
		#endif
		Mvertex_attrib_pointer = (void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))mGET_PROC_ADDRESS("glVertexAttribPointer");
		Mvertex_attrib_ipointer = (void (*)(GLuint, GLint, GLenum, GLsizei, const void *))mGET_PROC_ADDRESS("glVertexAttribIPointer");
		Menable_vertex_attrib_array = (void (*)(GLuint))mGET_PROC_ADDRESS("glEnableVertexAttribArray");
		Mdisable_vertex_attrib_array = (void (*)(GLuint))mGET_PROC_ADDRESS("glDisableVertexAttribArray");
		Mbind_buffer_range = (void (*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr))mGET_PROC_ADDRESS("glBindBufferRange");
		#ifdef uCOMP_SHADER
			Mdispatch_compute = (void (*)(GLuint, GLuint, GLuint))mGET_PROC_ADDRESS("glDispatchCompute");
//			Mfence_sync = (GLsync (*)(GLenum, GLbitfield))mGET_PROC_ADDRESS("glFenceSync");
//			Mclient_wait_sync = (GLenum (*)(GLsync, GLbitfield, GLuint64))mGET_PROC_ADDRESS("glClientWaitSync");
//			Mdelete_sync = (void (*)(GLsync))mGET_PROC_ADDRESS("glDeleteSync");
			Mget_booleanv = (void (*)(GLenum, GLboolean *))mGET_PROC_ADDRESS("glGetBooleanv");
			Mdisable_client_state = (void (*)(GLenum))mGET_PROC_ADDRESS("glDisableClientState");
			Menable_client_state = (void (*)(GLenum))mGET_PROC_ADDRESS("glEnableClientState");
			Mvertex_pointer = (void (*)(GLint, GLenum, GLsizei, const GLvoid *))mGET_PROC_ADDRESS("glVertexPointer");
			Mcolor_pointer = (void (*)(GLint, GLenum, GLsizei, const GLvoid *))mGET_PROC_ADDRESS("glColorPointer");
			Mdraw_arrays = (void (*)(GLenum, GLint, GLsizei))mGET_PROC_ADDRESS("glDrawArrays");
			Mmemory_barrier = (void (*)(GLbitfield))mGET_PROC_ADDRESS("glMemoryBarrier");
			#ifndef SMPT_CM_GL_DEBUG
				Menable = (void (*)(GLenum))mGET_PROC_ADDRESS("glEnable");
			#endif

			Mdisable = (void (*)(GLenum))mGET_PROC_ADDRESS("glDisable");
			Mget_uniform_location = (GLint (*)(GLuint, const GLchar *))mGET_PROC_ADDRESS("glGetUniformLocation");
			Muniform1i = (void (*)(GLint, GLint))mGET_PROC_ADDRESS("glUniform1i");
			Mget_uniformiv = (void (*)(GLuint, GLint, GLint *))mGET_PROC_ADDRESS("glGetUniformiv");
			Mactive_texture = (void (*)(GLenum))mGET_PROC_ADDRESS("glActiveTexture");
			Mgen_textures = (void (*)(GLsizei, GLuint *))mGET_PROC_ADDRESS("glGenTextures");
			Mbind_texture = (void (*)(GLenum, GLuint))mGET_PROC_ADDRESS("glBindTexture");
			Mtex_parameteri = (void (*)(GLenum, GLenum, GLint))mGET_PROC_ADDRESS("glTexParameteri");
			Mtex_image2d = (void (*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *))mGET_PROC_ADDRESS("glTexImage2D");
			//Mshade_model = (void (*)(GLenum))mGET_PROC_ADDRESS("glShadeModel");
		#endif
		Mget_programiv = (void (*)(GLuint, GLenum, GLint *))mGET_PROC_ADDRESS("glGetProgramiv");
		Mget_program_info_log = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *))mGET_PROC_ADDRESS("glGetProgramInfoLog");

		Mget_integerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &Vuniform_buffer_offset_alignment);
		SMPT_DBmN2L("Vuniform_buffer_offset_alignment %d", Vuniform_buffer_offset_alignment)

		Mget_integerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &Vshader_storage_buffer_offset_alignment);
		SMPT_DBmN2L("Vshader_storage_buffer_offset_alignment %d", Vshader_storage_buffer_offset_alignment)

		#ifdef SMPT_CM_GL_DEBUG
			Menable(GL_DEBUG_OUTPUT);
			Menable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			Mdebug_message_callback(Mdebug, NULL);
			Mdebug_message_control(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, NULL, GL_TRUE);
		#endif
		#ifdef uCOMP_SHADER
			GLint Vat = 0;
			Mget_integerv(GL_ACTIVE_TEXTURE, &Vat);

			Mactive_texture(GL_TEXTURE16);
			Mgen_textures(1, &Vtexture_m);
			Mbind_texture(GL_TEXTURE_2D, Vtexture_m);

			Mtex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			Mtex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			Mtex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			Mtex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			Mtex_image2d
			(
				GL_TEXTURE_2D,
				0,
				GL_RGBA8,
				1, 1,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				(uint8_t[4]){255, 255, 255, 255}
			);

			Mactive_texture(Vat);
		#endif

		Mbuffer();
		Mshader();
	}

	static tUBO Uubo = 0;
	static float Pbone_cache[SMPTR_CE_MDlBONE * 4 * 3];
	#ifdef uCOMP_SHADER
		static uint32_t Udraw_array;
	#endif
	static void Mdraw(GLuint Vbuffer_m, uint32_t Ulight, uint8_t Um, uint8_t Uk, float Vkf)
	{
	//	SMPT_DBmN2L("Vkf %d", Vkf)
	//	SMPT_DBmN2L("Um %d", Um)
	//	SMPT_DBmN2L("Uk %d", Uk)
	//	SMPT_DBmN2L("Ulight %08X", Ulight)
		struct SMPTR_CE_ETTsM Sm = smptr_ce_ettPm[Um];
		//GLint Pvp[4];
		//.i left bottom width height
		//Mget_integerv(GL_VIEWPORT, Pvp);

		Muse_program(Vprogram_m);
		Mbind_buffer(GL_UNIFORM_BUFFER, Vbuffer_m);
		#ifdef uCOMP_SHADER
			void *Pu = Mmap_buffer_range(GL_UNIFORM_BUFFER, mSIZE_UBO(Lal_fix), (sizeof(float) * 4 * 3 * smptr_ce_mdPj[Sm.Uj]), GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
		#endif
		#ifndef uCOMP_SHADER
			Mbind_vertex_array(Vvao_m);

			void *Pu = Mmap_buffer_range(GL_UNIFORM_BUFFER, 0, mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)) + (sizeof(float) * 4 * 3 * smptr_ce_mdPj[Sm.Uj]), GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
			Mget_floatv(GL_MODELVIEW_MATRIX, Pu);
			Mget_floatv(GL_PROJECTION_MATRIX, Pu + 16 * sizeof(float));
			float Pc[4];
			Mget_floatv(GL_CURRENT_COLOR, Pc);
			Pc[0] *= (Ulight >> (8+8) & 255) / 255.0F;
			Pc[1] *= (Ulight >> (8) & 255) / 255.0F;
			Pc[2] *= (Ulight & 255) / 255.0F;
			Pc[3] *= (Ulight >> (8+8+8)) / 255.0F;
			((uint32_t *)(Pu + mSIZE_UBO(sizeof(float) * 16 * 2)))[0] = (uint8_t)(Pc[0] * 255) << (8+8+8) | (uint8_t)(Pc[1] * 255) << (8+8) | (uint8_t)(Pc[2] * 255) << 8 | (uint8_t)(Pc[3] * 255);
		#endif
		memcpy(Pbone_cache, smptr_ce_mdPb[Sm.Uj], smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 4 * 3);
		//.i animate
		//.t keyframe
	//	Uk = SMPTReMK_UI_ATTACK;
	//	Vkf = 5.5F;
		const SMPTRtMK *Pk = smptrPmk[Uk];
		SMPTRtMK Uks = SMPTMmWRAP_F(Vkf, Pk[1], Pk[2]);
		float Ff = fabsf(SMPTMmWRAP_F(Vkf, Pk[1], Pk[2]) - Uks);
		SMPTRtMK Uke = SMPTMmWRAP_I(Uks + 1, Pk[1], Pk[2]);
	//	SMPT_DBmN2L("Vkf %f", Vkf)
	//	SMPT_DBmN2L("Uks %d", Uks)
	//	SMPT_DBmN2L("Ff %f", Ff)
	//	SMPT_DBmN2L("Uke %d", Uke)
		struct SMPTR_CE_KFs Skf = smptr_ce_kfP[Pk[0]][Uks];
		for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
		{
			//.t unclean
	//		if (Skf.Pbone[l_0] >= smptr_ce_mdPj[Sm.Uj])
	//			continue;
			//SMPT_DBmN2L("Skf.Pbone[%d] %d", l_0, Skf.Pbone[l_0])
			memcpy(Pbone_cache + Skf.Pbone[l_0] * 4 * 3, Skf.Ps[l_0], sizeof(float) * 3);
			memcpy(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4, Skf.Pr[l_0], sizeof(float) * 4);
			memcpy(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4 * 2, Skf.Pt[l_0], sizeof(float) * 3);
		}
	//	SMPT_DBmN2L("Pk[0] %d", Pk[0])
	//	SMPT_DBmN2L("Uke %d", Uke)
		Skf = smptr_ce_kfP[Pk[0]][Uke];
		//SMPT_DBmN2L("Skf.Lbone %d", Skf.Lbone)
		for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
		{
			//SMPT_DBmN2L("Skf.Pbone[%d] %d", l_0, Skf.Pbone[l_0])
			//.t unclean
	//		if (Skf.Pbone[l_0] >= smptr_ce_mdPj[Sm.Uj])
	//			continue;

			for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
			{
				(Pbone_cache + Skf.Pbone[l_0] * 4 * 3)[l_3] = SMPTMmLERP((Pbone_cache + Skf.Pbone[l_0] * 4 * 3)[l_3], Skf.Ps[l_0][l_3], Ff);
				(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4 * 2)[l_3] = SMPTMmLERP((Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4 * 2)[l_3], Skf.Pt[l_0][l_3], Ff);
			}

	//		for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
	//		{
	//			(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4)[l_3] = SMPTMmLERP((Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4)[l_3], Skf.Pr[l_0][l_3], Ff);
	//		}
			smptm_v4Mnlerp(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4, Skf.Pr[l_0], Ff, Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4);

			//.t step
	//		memcpy(Pbone_cache + Skf.Pbone[l_0] * 4 * 3, Skf.Ps[l_0], sizeof(float) * 3);
	//		memcpy(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4, Skf.Pr[l_0], sizeof(float) * 4);
	//		memcpy(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4 * 2, Skf.Pt[l_0], sizeof(float) * 3);
		}
		#ifdef uCOMP_SHADER
			memcpy(Pu, Pbone_cache, smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 4 * 3);
		#endif
		#ifndef uCOMP_SHADER
			memcpy(Pu + mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)), Pbone_cache, smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 4 * 3);
		#endif
		Munmap_buffer(GL_UNIFORM_BUFFER);
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 1, Pbuffer_m[0], uLA_UBO + uLI_UBO + Pbpl_fix[Sm.Uj], smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 16 * 2);
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 3, Pbuffer_m[0], uLA_UBO + uLI_UBO + mSIZE_UBO(Lbp_fix), smptr_ce_mdLrgba);

		#ifdef uCOMP_SHADER
			Mbind_buffer_range(GL_UNIFORM_BUFFER, 2, Vbuffer_m, mSIZE_UBO(Lal_fix), (sizeof(float) * 4 * 3 * smptr_ce_mdPj[Sm.Uj]));
			Mbind_buffer_range(GL_SHADER_STORAGE_BUFFER, 6, Pbuffer_m[0], 0, La_fix);

			Udraw_array = 0;
			for (uint8_t U0 = 0; U0 < Sm.Lma; ++U0)
			//for (uint8_t U0 = 0; U0 < 1; ++U0)
			{
				#ifdef SMPTRuN
					uint32_t Lssbo = 2 * 5;
				#endif
				#ifndef SMPTRuN
					uint32_t Lssbo = 4 * 2;
				#endif
				Mbind_buffer_range(GL_SHADER_STORAGE_BUFFER, 5, Vbuffer_m, Udraw_array * Lssbo, smptr_ce_mdPil[Sm.Pma[U0]] * Lssbo);
				Mbind_buffer_range(GL_SHADER_STORAGE_BUFFER, 0, Pbuffer_m[0], uLA_UBO + Pi_fix[Sm.Pma[U0]], smptr_ce_mdPil[Sm.Pma[U0]]);
				Mbind_buffer_range(GL_UNIFORM_BUFFER, 4, Pbuffer_m[0], uLA_UBO + uLI_UBO + mSIZE_UBO(Lbp_fix) + uLCOLOR_UBO + Pcomp_ssbo[Sm.Pma[U0]], sizeof(uint32_t));
				Mdispatch_compute((uint16_t)ceilf(smptr_ce_mdPil[Sm.Pma[U0]] / sizeof(uint32_t) / 512.0F), 1, 1);
				Udraw_array += smptr_ce_mdPil[Sm.Pma[U0]];
			}
			Udraw_array /= sizeof(uint32_t);
			//SMPT_DBmN2L("Udraw_array %d", Udraw_array);
//			GLsync Vcompute_fence = Mfence_sync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
//			Mclient_wait_sync(Vcompute_fence, GL_SYNC_FLUSH_COMMANDS_BIT, GL_TIMEOUT_IGNORED);
//			Mdelete_sync(Vcompute_fence);
			Mmemory_barrier
			(
				GL_SHADER_STORAGE_BARRIER_BIT |
				GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT
			);
		#endif
		#ifndef uCOMP_SHADER
			Mbind_buffer_range(GL_UNIFORM_BUFFER, 0, Vbuffer_m, 0, sizeof(float) * 16 * 2);
			Mbind_buffer_range(GL_UNIFORM_BUFFER, 2, Vbuffer_m, mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)), (sizeof(float) * 4 * 3 * smptr_ce_mdPj[Sm.Uj]));
			Mbind_buffer_range(GL_UNIFORM_BUFFER, 4, Vbuffer_m, mSIZE_UBO(sizeof(float) * 16 * 2), sizeof(uint32_t));
			for (uint8_t U0 = 0; U0 < Sm.Lma; ++U0)
				Mdraw_elements(GL_TRIANGLES, smptr_ce_mdPil[Sm.Pma[U0]] / sizeof(uint32_t), GL_UNSIGNED_INT, (void *)((uintptr_t)(uLA_UBO + Pii[Sm.Pma[U0]])));
		#endif
	}

	static void Mcurrent(GLuint Vprogram, GLuint Vvbo, GLuint Vebo, GLuint Vubo)
	{
		//SMPT_DBmN2L("Vprogram %d", Vprogram)
		Muse_program(Vprogram);
		Mbind_buffer(GL_ARRAY_BUFFER, Vvbo);
		Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Vebo);
		Mbind_buffer(GL_UNIFORM_BUFFER, Vubo);
	}

	JNIEXPORT void JNICALL Java_com_nali_C_Mdraw(JNIEnv *Pjnienv, jclass Vjclass, jbyte Vm, jbyte Vk, jfloat Vkf, jint Vlight)
	{
		GLuint Vbuffer_m = Pbuffer_m[1 + Uubo];

		GLint Vprogram, Vvbo, Vebo, Vubo;
		Mget_integerv(GL_CURRENT_PROGRAM, &Vprogram);
		Mget_integerv(GL_ARRAY_BUFFER_BINDING, &Vvbo);
		Mget_integerv(GL_UNIFORM_BUFFER_BINDING, &Vubo);
		#ifdef uCOMP_SHADER
			Mdraw(Vbuffer_m, (uint32_t)Vlight, (uint8_t)Vm, (uint8_t)Vk, (float)Vkf);

			GLboolean Vva, Vca, Vna, Vtca, Via, Vefa;
			Mget_booleanv(GL_VERTEX_ARRAY, &Vva);
			Mget_booleanv(GL_COLOR_ARRAY, &Vca);
			Mget_booleanv(GL_NORMAL_ARRAY, &Vna);
			Mget_booleanv(GL_TEXTURE_COORD_ARRAY, &Vtca);
			Mget_booleanv(GL_INDEX_ARRAY, &Via);
			Mget_booleanv(GL_EDGE_FLAG_ARRAY, &Vefa);

			#ifndef SMPTRuN
				Mdisable_client_state(GL_NORMAL_ARRAY);
			#endif
			Mdisable_client_state(GL_TEXTURE_COORD_ARRAY);
			Mdisable_client_state(GL_INDEX_ARRAY);
			Mdisable_client_state(GL_EDGE_FLAG_ARRAY);

			Mcurrent((GLuint)Vprogram, (GLuint)Vvbo, (GLuint)Vebo, (GLuint)Vubo);
			Mbind_buffer(GL_ARRAY_BUFFER, Vbuffer_m);

			GLint Vul_tex, Vul_tex_at;
			if (Vprogram)
			{
				Vul_tex = Mget_uniform_location((GLuint)Vprogram, "tex");
				if (Vul_tex != -1)
				{
					Mget_uniformiv((GLuint)Vprogram, Vul_tex, &Vul_tex_at);
					Muniform1i(Vul_tex, 16);
				}
			}

			#ifdef SMPTRuN
				uint32_t Lv = sizeof(float) * (3 + 4 + 3);
			#endif
			#ifndef SMPTRuN
				uint32_t Lv = sizeof(float) * (4 + 4);
			#endif

			Menable_client_state(GL_VERTEX_ARRAY);
			#ifdef SMPTRuN
				Mvertex_pointer(3, GL_FLOAT, Lv, (void*)0);
			#endif
			#ifndef SMPTRuN
				Mvertex_pointer(4, GL_FLOAT, Lv, (void*)0);
			#endif

			Menable_client_state(GL_COLOR_ARRAY);
			#ifdef SMPTRuN
				Mcolor_pointer(4, GL_FLOAT, Lv, (void*)(sizeof(float) * 3));
			#endif
			#ifndef SMPTRuN
				Mcolor_pointer(4, GL_FLOAT, Lv, (void*)(sizeof(float) * 4));
			#endif

			#ifdef SMPTRuN
				Menable_client_state(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, Lv, (void*)(sizeof(float) * (3 + 4)));
			#endif

			GLboolean Vtexture_2d;
			Mget_booleanv(GL_TEXTURE_2D, &Vtexture_2d);
			Mdisable(GL_TEXTURE_2D);

			//GLint Vshade_model;
			//Mget_integerv(GL_SHADE_MODEL, &Vshade_model);
			//Mshade_model(GL_SMOOTH);

			GLboolean Vlighting;
			Mget_booleanv(GL_LIGHTING, &Vlighting);
			Mdisable(GL_LIGHTING);

			Mdraw_arrays(GL_TRIANGLES, 0, Udraw_array);
			Mcurrent((GLuint)Vprogram, (GLuint)Vvbo, (GLuint)Vebo, (GLuint)Vubo);

			//Mshade_model(Vshade_model);

			if (Vprogram)
			{
				if (Vul_tex != -1)
				{
					Muniform1i(Vul_tex, Vul_tex_at);
				}
			}

			if (Vlighting)
			{
				Menable(GL_LIGHTING);
			}
			else
			{
				Mdisable(GL_LIGHTING);
			}

			if (Vtexture_2d)
			{
				Menable(GL_TEXTURE_2D);
			}
			else
			{
				Mdisable(GL_TEXTURE_2D);
			}

			if (Vva)
			{
				Menable_client_state(GL_VERTEX_ARRAY);
			}
			else
			{
				Mdisable_client_state(GL_VERTEX_ARRAY);
			}
			if (Vca)
			{
				Menable_client_state(GL_COLOR_ARRAY);
			}
			else
			{
				Mdisable_client_state(GL_COLOR_ARRAY);
			}
			if (Vna)
			{
				Menable_client_state(GL_NORMAL_ARRAY);
			}
			else
			{
				Mdisable_client_state(GL_NORMAL_ARRAY);
			}
			if (Vtca)
			{
				Menable_client_state(GL_TEXTURE_COORD_ARRAY);
			}
			else
			{
				Mdisable_client_state(GL_TEXTURE_COORD_ARRAY);
			}
			if (Via)
			{
				Menable_client_state(GL_INDEX_ARRAY);
			}
			else
			{
				Mdisable_client_state(GL_INDEX_ARRAY);
			}
			if (Vefa)
			{
				Menable_client_state(GL_EDGE_FLAG_ARRAY);
			}
			else
			{
				Mdisable_client_state(GL_EDGE_FLAG_ARRAY);
			}
		#endif
		#ifndef uCOMP_SHADER
			GLint Vvao;
			Mget_integerv(GL_VERTEX_ARRAY_BINDING, &Vvao);
			Mget_integerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &Vebo);

			GLint Vvaa_enabled[3], Vvaa_size[3], Vvaa_stride[3], Vvaa_type[3], Vvaa_normalized[3];
			void *Vvaa_pointer[3];
			for (uint8_t U0 = 0; U0 < 3; ++U0)
			{
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &Vvaa_enabled[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_SIZE, &Vvaa_size[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &Vvaa_stride[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_TYPE, &Vvaa_type[U0]);
				Mget_vertex_attribiv(U0, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &Vvaa_normalized[U0]);
				Mget_vertex_attrib_pointerv(U0, GL_VERTEX_ATTRIB_ARRAY_POINTER, &Vvaa_pointer[U0]);
			}

			Mdraw(Vbuffer_m, (uint32_t)Vlight, (uint8_t)Vm, (uint8_t)Vk, (float)Vkf);
			Mbind_vertex_array((GLuint)Vvao);
			Mcurrent((GLuint)Vprogram, (GLuint)Vvbo, (GLuint)Vebo, (GLuint)Vubo);

			for (uint8_t U0 = 0; U0 < 3; ++U0)
			{
				if (Vvaa_enabled[U0])
				{
					Menable_vertex_attrib_array(U0);
				}
				else
				{
					Mdisable_vertex_attrib_array(U0);
				}

				Mvertex_attrib_pointer((GLuint)U0, Vvaa_size[U0], Vvaa_type[U0], Vvaa_normalized[U0], Vvaa_stride[U0], Vvaa_pointer[U0]);
			}
		#endif

		Uubo = (Uubo + 1u) % lUBO;
	}

	//JNIEXPORT void JNICALL Java_com_nali_C_Mfree(JNIEnv *Pjnienv, jclass Vjclass)
	//{
	//	smptr_ceMfree();
	//	smpt_dbMfree();
#endif
