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
	#define uCOMP_SHADER

	#define mOFFSET_UBO(U) (((uint32_t)(U) % (uint32_t)Vuniform_buffer_offset_alignment != 0u) ? (uint32_t)(U) + ((uint32_t)Vuniform_buffer_offset_alignment - ((uint32_t)(U) % (uint32_t)Vuniform_buffer_offset_alignment)) : (uint32_t)(U))
	#define mSIZE_UBO(U) (((uint32_t)(U) + (uint32_t)Vuniform_buffer_offset_alignment - 1u) & ~((uint32_t)Vuniform_buffer_offset_alignment - 1u))
	static GLint Vuniform_buffer_offset_alignment;

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
	static void (*Mdraw_elements)(GLenum, GLsizei, GLenum, const void *);
	static void (*Mgen_vertex_arrays)(GLsizei, GLuint *);
	static void (*Mbind_vertex_array)(GLuint);
	static void (*Mvertex_attrib_pointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
	static void (*Mvertex_attrib_ipointer)(GLuint, GLint, GLenum, GLsizei, const void *);
	static void (*Menable_vertex_attrib_array)(GLuint);
	static void (*Mdisable_vertex_attrib_array)(GLuint);
	static void (*Mbind_buffer_range)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);

	static GLuint Vprogram_m;
	static GLuint Vshader_vert;
	static GLuint Vshader_frag;

	static GLuint Vvao_m;
	//.c ubo cache
	#ifdef uCOMP_SHADER
		static uint32_t Lpa = 0;
		#define lUBO (512u * Lpa)
	#endif
	#ifndef uCOMP_SHADER
		#define lUBO 512u
	#endif
	#define tUBO uint16_t
	static GLuint Pbuffer_m[1 + lUBO];

	static uint32_t Pii[SMPTR_MDcM];
	static uint32_t Li = 0;
	static uint32_t Lbp_fix = 0;
	static void Mbuffer_ebo()
	{
		SMPT_DBmN2L("Mbuffer_ebo 0")
		Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Pbuffer_m[0]);
		uint8_t *Pi = malloc(Li);
		for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
		{
			SMPT_DBmN2L("Pii[%d] %d", U0, Pii[U0]);
			SMPT_DBmN2L("smptr_ce_mdPil[%d] %d", U0, smptr_ce_mdPil[U0]);
			memcpy(Pi + Pii[U0], smptr_ce_mdPi[U0], smptr_ce_mdPil[U0]);
		}
		void *Pu = Mmap_buffer_range(GL_ELEMENT_ARRAY_BUFFER, mSIZE_UBO(smptr_ce_mdLa), mSIZE_UBO(Li), GL_MAP_WRITE_BIT);
		memcpy(Pu, Pi, Li);
		Munmap_buffer(GL_ELEMENT_ARRAY_BUFFER);
		free(Pi);
		SMPT_DBmN2L("Mbuffer_ebo 1")
	}
	static void Mbuffer_vbo()
	{
		SMPT_DBmN2L("Mbuffer_vbo 0")
		void *Pu = Mmap_buffer_range(GL_ARRAY_BUFFER, 0, mSIZE_UBO(smptr_ce_mdLa), GL_MAP_WRITE_BIT);
		memcpy(Pu, smptr_ce_mdPa, smptr_ce_mdLa);
		Munmap_buffer(GL_ARRAY_BUFFER);
		Menable_vertex_attrib_array(0);
		Mvertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(uint8_t) * 2, (void *)(0));
		Menable_vertex_attrib_array(1);
		Mvertex_attrib_ipointer(1, 1, GL_UNSIGNED_BYTE, sizeof(float) * 3 + sizeof(uint8_t) * 2, (void *)(12));
		Menable_vertex_attrib_array(2);
		Mvertex_attrib_ipointer(2, 1, GL_UNSIGNED_BYTE, sizeof(float) * 3 + sizeof(uint8_t) * 2, (void *)(13));
		SMPT_DBmN2L("Mbuffer_vbo 1")
	}
	static void Mbuffer_vao()
	{
		SMPT_DBmN2L("Mbuffer_vao 0")
		Mgen_vertex_arrays(1, &Vvao_m);
		Mbind_vertex_array(Vvao_m);
		Mbuffer_ebo();
		Mbuffer_vbo();
		SMPT_DBmN2L("Mbuffer_vao 1")
	}
	static uint32_t Pbpl_fix[SMPTR_MDc];
	static void Mbuffer()
	{
		SMPT_DBmN2L("Mbuffer 0")
		GLint Vvao, Vvbo, Vebo, Vubo;
		Mget_integerv(GL_VERTEX_ARRAY_BINDING, &Vvao);
		SMPT_DBmN2L("Vvao %d", Vvao);
		Mget_integerv(GL_ARRAY_BUFFER_BINDING, &Vvbo);
		Mget_integerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &Vebo);
		Mget_integerv(GL_UNIFORM_BUFFER_BINDING, &Vubo);

		Mgen_buffers(1 + lUBO, Pbuffer_m);
		SMPT_DBmN2L("Pbuffer_m[0] %d", Pbuffer_m[0]);
		Mbind_buffer(GL_ARRAY_BUFFER, Pbuffer_m[0]);
		for (SMPTRtMA U0 = 0; U0 < SMPTR_MDcM; ++U0)
		{
			Pii[U0] = Li;
			#ifdef uCOMP_SHADER
				Li += smptr_ce_mdPil[U0] + 2;
			#endif
			#ifndef uCOMP_SHADER
				Li += smptr_ce_mdPil[U0];
			#endif
		}
		SMPT_DBmN2L("Li %d", Li);
		for (SMPTRtJWL U0 = 0; U0 < SMPTR_MDc; ++U0)
		{
			Pbpl_fix[U0] = Lbp_fix;
			Lbp_fix += mSIZE_UBO(sizeof(float) * 16 * 2 * smptr_ce_mdPj[U0]);
			SMPT_DBmN2L("Pbpl_fix[%d] %d", U0, Pbpl_fix[U0]);
		}
		Mbuffer_data(GL_ARRAY_BUFFER, mSIZE_UBO(smptr_ce_mdLa) + mSIZE_UBO(Li) + mSIZE_UBO(Lbp_fix) + smptr_ce_mdLrgba, NULL, GL_DYNAMIC_DRAW);
		for (tUBO U0 = 1; U0 < 1 + lUBO; ++U0)
		{
			Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer_m[U0]);
			Mbuffer_data(GL_UNIFORM_BUFFER, mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)) + (sizeof(float) * 4 * 3 * SMPTR_CE_MDlBONE), NULL, GL_DYNAMIC_DRAW);
		}
		uint8_t *Pbp = malloc(Lbp_fix);
		for (SMPTRtJWL U0 = 0; U0 < SMPTR_MDc; ++U0)
		{
			//SMPT_DBmN2L("smptr_ce_mdPj[%d] %d", U0, smptr_ce_mdPj[U0]);
			//SMPT_DBmN2L("Pbpl_fix[%d] %d", U0, Pbpl_fix[U0]);
			memcpy(Pbp + Pbpl_fix[U0] + sizeof(float) * 16 * 2, smptr_ce_mdPbp[U0], sizeof(float) * 16 * 2 * (smptr_ce_mdPj[U0] - 1));
		}
		Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer_m[0]);
		void *Pu = Mmap_buffer_range(GL_UNIFORM_BUFFER, mSIZE_UBO(smptr_ce_mdLa) + mSIZE_UBO(Li), mSIZE_UBO(Lbp_fix) + smptr_ce_mdLrgba, GL_MAP_WRITE_BIT);
		memcpy(Pu, Pbp, Lbp_fix);
		memcpy(Pu + mSIZE_UBO(Lbp_fix), smptr_ce_mdPrgba, smptr_ce_mdLrgba);
		Munmap_buffer(GL_UNIFORM_BUFFER);
		free(Pbp);

		Mbuffer_vao();

		Mbind_vertex_array(Vvao);
		Mbind_buffer(GL_ARRAY_BUFFER, Vvbo);
		Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Vebo);
		Mbind_buffer(GL_UNIFORM_BUFFER, Vubo);

		Mdisable_vertex_attrib_array(0);
		Mdisable_vertex_attrib_array(1);
		Mdisable_vertex_attrib_array(2);
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

			Mdetach_shader(Vprogram_m, Vshader_vert);
			Mdetach_shader(Vprogram_m, Vshader_frag);
			Mdelete_shader(Vshader_vert);
			Mdelete_shader(Vshader_frag);
		#endif
		SMPT_DBmN2L("Mshader 1")
	}

	#ifdef SMPT_CM_GL_DEBUG
		void Mdebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
		{
			SMPT_DBmW2L("gl_debug")
			SMPT_DBmW2L("source %d", source)
			SMPT_DBmW2L("type %d", type)
			SMPT_DBmW2L("id %d", id)
			SMPT_DBmW2L("severity %d", severity)
			SMPT_DBmW2L("length %d", length)
			SMPT_DBmW2L("message %s", message)
			SMPT_DBmW2L("userParam %p", userParam)
		}
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
		Mdraw_elements = (void (*)(GLenum, GLsizei, GLenum, const void *))mGET_PROC_ADDRESS("glDrawElements");
		Mgen_vertex_arrays = (void (*)(GLsizei, GLuint *))mGET_PROC_ADDRESS("glGenVertexArrays");
		Mbind_vertex_array = (void (*)(GLuint))mGET_PROC_ADDRESS("glBindVertexArray");
		Mvertex_attrib_pointer = (void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))mGET_PROC_ADDRESS("glVertexAttribPointer");
		Mvertex_attrib_ipointer = (void (*)(GLuint, GLint, GLenum, GLsizei, const void *))mGET_PROC_ADDRESS("glVertexAttribIPointer");
		Menable_vertex_attrib_array = (void (*)(GLuint))mGET_PROC_ADDRESS("glEnableVertexAttribArray");
		Mdisable_vertex_attrib_array = (void (*)(GLuint))mGET_PROC_ADDRESS("glDisableVertexAttribArray");
		Mbind_buffer_range = (void (*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr))mGET_PROC_ADDRESS("glBindBufferRange");

		#ifdef uCOMP_SHADER
		#endif

		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &Vuniform_buffer_offset_alignment);
		SMPT_DBmN2L("Vuniform_buffer_offset_alignment %d", Vuniform_buffer_offset_alignment)

		#ifdef SMPT_CM_GL_DEBUG
			Menable(GL_DEBUG_OUTPUT);
			Menable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			Mdebug_message_callback(Mdebug, NULL);
			Mdebug_message_control(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, NULL, GL_TRUE);
		#endif

		Mbuffer();
		Mshader();
	}

	static tUBO Uubo = 0;
	float Pbone_cache[SMPTR_CE_MDlBONE * 4 * 3];
	JNIEXPORT void JNICALL Java_com_nali_C_Mdraw(JNIEnv *Pjnienv, jclass Vjclass, jbyte Vm, jbyte Vk, jfloat Vkf, jint Vlight)
	{
		//! check
		uint32_t Ulight = (uint32_t)Vlight;
		uint8_t Um = (uint8_t)Vm;
		uint8_t Uk = (uint8_t)Vk;
	//	SMPT_DBmN2L("Vkf %d", Vkf)
	//	SMPT_DBmN2L("Um %d", Um)
	//	SMPT_DBmN2L("Uk %d", Uk)
	//	SMPT_DBmN2L("Ulight %08X", Ulight)
		struct SMPTR_CE_ETTsM Sm = smptr_ce_ettPm[Um];
		//GLint Pvp[4];
		//.i left bottom width height
		//Mget_integerv(GL_VIEWPORT, Pvp);
		#ifdef uCOMP_SHADER
			//! no vao
			//! ubo ssbo
			Muse_program(Vprogram_m);
			glDispatchCompute(1, 1, 1);

			GLsync Vcompute_fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

			glClientWaitSync(Vcompute_fence, GL_SYNC_FLUSH_COMMANDS_BIT, GL_TIMEOUT_IGNORED);
			glDeleteSync(Vcompute_fence);
			//! draw
			GLboolean Vva = glIsEnabledClientState(GL_VERTEX_ARRAY);
			GLboolean Vca = glIsEnabledClientState(GL_COLOR_ARRAY);
			GLboolean Vna = glIsEnabledClientState(GL_NORMAL_ARRAY);
			GLboolean Vtca = glIsEnabledClientState(GL_TEXTURE_COORD_ARRAY);
			GLboolean Via = glIsEnabledClientState(GL_INDEX_ARRAY);
			GLboolean Vefa = glIsEnabledClientState(GL_EDGE_FLAG_ARRAY);

			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_INDEX_ARRAY);
			glDisableClientState(GL_EDGE_FLAG_ARRAY);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)0);

			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

			glDrawArrays(GL_POINTS, 0, numVertices);

			if (Vva)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
			}
			else
			{
				glDisableClientState(GL_VERTEX_ARRAY);
			}
			if (Vca)
			{
				glEnableClientState(GL_COLOR_ARRAY);
			}
			else
			{
				glDisableClientState(GL_COLOR_ARRAY);
			}
			if (Vna)
			{
				glEnableClientState(GL_NORMAL_ARRAY);
			}
			else
			{
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			if (Vtca)
			{
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			else
			{
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			if (Via)
			{
				glEnableClientState(GL_INDEX_ARRAY);
			}
			else
			{
				glDisableClientState(GL_INDEX_ARRAY);
			}
			if (Vefa)
			{
				glEnableClientState(GL_EDGE_FLAG_ARRAY);
			}
			else
			{
				glDisableClientState(GL_EDGE_FLAG_ARRAY);
			}
		#endif
		#ifndef uCOMP_SHADER
		#endif
		GLint Vprogram, Vvao, Vvbo, Vebo, Vubo;
		Mget_integerv(GL_CURRENT_PROGRAM, &Vprogram);
		Mget_integerv(GL_VERTEX_ARRAY_BINDING, &Vvao);
		Mget_integerv(GL_ARRAY_BUFFER_BINDING, &Vvbo);
		Mget_integerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &Vebo);
		Mget_integerv(GL_UNIFORM_BUFFER_BINDING, &Vubo);

		Muse_program(Vprogram_m);
		Mbind_vertex_array(Vvao_m);

		GLuint Vbuffer_m = Pbuffer_m[1 + Uubo];
		Mbind_buffer(GL_UNIFORM_BUFFER, Vbuffer_m);
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
		memcpy(Pu + mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)), Pbone_cache, smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 4 * 3);
		Munmap_buffer(GL_UNIFORM_BUFFER);
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 0, Vbuffer_m, 0, sizeof(float) * 16 * 2);
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 1, Pbuffer_m[0], mSIZE_UBO(smptr_ce_mdLa) + mSIZE_UBO(Li) + Pbpl_fix[Sm.Uj], smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 16 * 2);
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 2, Vbuffer_m, mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)), (sizeof(float) * 4 * 3 * smptr_ce_mdPj[Sm.Uj]));
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 3, Pbuffer_m[0], mSIZE_UBO(smptr_ce_mdLa) + mSIZE_UBO(Li) + mSIZE_UBO(Lbp_fix), smptr_ce_mdLrgba);
		Mbind_buffer_range(GL_UNIFORM_BUFFER, 4, Vbuffer_m, mSIZE_UBO(sizeof(float) * 16 * 2), sizeof(uint32_t));

		for (SMPTRtJWL U0 = 0; U0 < Sm.Lma; ++U0)
		{
			Mdraw_elements(GL_TRIANGLES, smptr_ce_mdPil[Sm.Pma[U0]] / sizeof(uint32_t), GL_UNSIGNED_INT, (void *)((uintptr_t)(mSIZE_UBO(smptr_ce_mdLa) + Pii[Sm.Pma[U0]])));
		}

		Mbind_vertex_array((GLuint)Vvao);
		//SMPT_DBmN2L("Vprogram %d", Vprogram)
		Muse_program((GLuint)Vprogram);
		Mbind_buffer(GL_ARRAY_BUFFER, (GLuint)Vvbo);
		Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)Vebo);
		Mbind_buffer(GL_UNIFORM_BUFFER, (GLuint)Vubo);

		Mdisable_vertex_attrib_array(0);
		Mdisable_vertex_attrib_array(1);
		Mdisable_vertex_attrib_array(2);

		Uubo = (Uubo + 1u) % lUBO;
	}

	//JNIEXPORT void JNICALL Java_com_nali_C_Mfree(JNIEnv *Pjnienv, jclass Vjclass)
	//{
	//	smptr_ceMfree();
	//	smpt_dbMfree();
#endif
