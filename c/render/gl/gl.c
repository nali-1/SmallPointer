#ifdef SMPT_CM_ST_JAVA
	#define mGET_PROC_ADDRESS(P) glXGetProcAddress(P);
#endif
#ifdef SMPT_CM_ST_JAVA_ANDROID
	#define mGET_PROC_ADDRESS(P) eglGetProcAddress(P);
#endif

#define mOFFSET_UBO(U) (((U) % Vuniform_buffer_offset_alignment != 0) ? (U) + (Vuniform_buffer_offset_alignment - ((U) % Vuniform_buffer_offset_alignment)) : (U))
#define mSIZE_UBO(U) (((U) + Vuniform_buffer_offset_alignment - 1) & ~(Vuniform_buffer_offset_alignment - 1))
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
#define lUBO 512
#define tUBO uint16_t
static GLuint Pbuffer_m[1 + lUBO];

static uint32_t Pii[SMPTRcMA];
static uint32_t Li = 0;
static uint32_t Lbp_fix = 0;
void Mbuffer_ebo()
{
	SMPT_DBmN2L("Mbuffer_ebo 0")
	Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Pbuffer_m[0]);
	uint8_t *Pi = malloc(Li);
	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
	{
		SMPT_DBmN2L("Pii[%d] %d", U0, Pii[U0]);
		SMPT_DBmN2L("smptr_ce_mdPil_l[%d] %d", U0, smptr_ce_mdPil_l[U0]);
		memcpy(Pi + Pii[U0], smptr_ce_mdPi[U0], smptr_ce_mdPil_l[U0]);
	}
	void *Pu = Mmap_buffer_range(GL_ELEMENT_ARRAY_BUFFER, mSIZE_UBO(smptr_ce_mdLa), mSIZE_UBO(Li), GL_MAP_WRITE_BIT);
	memcpy(Pu, Pi, Li);
	Munmap_buffer(GL_ELEMENT_ARRAY_BUFFER);
	free(Pi);
	SMPT_DBmN2L("Mbuffer_ebo 1")
}
void Mbuffer_vbo()
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
void Mbuffer_vao()
{
	SMPT_DBmN2L("Mbuffer_vao 0")
	Mgen_vertex_arrays(1, &Vvao_m);
	Mbind_vertex_array(Vvao_m);
	Mbuffer_ebo();
	Mbuffer_vbo();
	SMPT_DBmN2L("Mbuffer_vao 1")
}
static uint32_t Pbpl_fix[SMPTRcM];
void Mbuffer()
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
	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
	{
		Pii[U0] = Li;
		Li += smptr_ce_mdPil_l[U0];
	}
	SMPT_DBmN2L("Li %d", Li);
	for (SMPTRtJWL U0 = 0; U0 < SMPTRcM; ++U0)
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
	for (SMPTRtJWL U0 = 0; U0 < SMPTRcM; ++U0)
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

void Mshader_gen(GLuint Vs, const char *Pc)
{
	SMPT_DBmN2L("Mshader_gen 0")
	uint32_t Ld;
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
void Mshader()
{
	SMPT_DBmN2L("Mshader 0")
	Vprogram_m = Mcreate_program();
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
	#ifdef SMPT_CM_CLIENT
		smptr_ceMset();
	#endif

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

//! clean
//static const uint8_t Uj = SMPTReM_POMI;
//static const uint8_t Lma = 7;
//static const uint8_t Pma[] =
//{
//	SMPTReMA_POMI_2CORE,
//	SMPTReMA_POMI_MF0000,
//	SMPTReMA_POMI_MF00,
//	SMPTReMA_POMI_MF0,
//	SMPTReMA_POMI_MM1,
//	SMPTReMA_POMI_M,
//	SMPTReMA_POMI_IShovel
//};
//! set
//enum eKF
//{
//	UI_IDLE,
//	UI_RUN,
//	UI_ATTACK
//};
struct sM
{
	SMPTRtM Uj;
	uint8_t Lma;
	SMPTRtMA *Pma;
};
static SMPTRtMA Pma_ui_rain0[] =
{
	SMPTReMA_UI_RAIN,
	SMPTReMA_UI_001,
	SMPTReMA_UI_M,
	SMPTReMA_UI_IClover,
	SMPTReMA_UI_MF,
	SMPTReMA_UI_MF0,
	SMPTReMA_UI_MF01,
	SMPTReMA_UI_MM0
};
static const struct sM Sm_ui_rain0 =
{
	.Uj = SMPTReM_UI,
	.Lma = sizeof(Pma_ui_rain0) / sizeof(Pma_ui_rain0[0]),
	.Pma = Pma_ui_rain0
};
static SMPTRtMA Pma_ui_rain1[] =
{
	SMPTReMA_UI_RAIN,
	SMPTReMA_UI_001,
	SMPTReMA_UI_M,
	SMPTReMA_UI_IClover,
	SMPTReMA_UI_MF,
	SMPTReMA_UI_MF1,
	SMPTReMA_UI_MM0
};
static const struct sM Sm_ui_rain1 =
{
	.Uj = SMPTReM_UI,
	.Lma = sizeof(Pma_ui_rain1) / sizeof(Pma_ui_rain1[0]),
	.Pma = Pma_ui_rain1
};

static SMPTRtMA Pma_croakie_rain0[] =
{
	SMPTReMA_CROAKIE_RAIN,
	SMPTReMA_CROAKIE_C0
};
static const struct sM Sm_croakie_rain0 =
{
	.Uj = SMPTReM_CROAKIE,
	.Lma = sizeof(Pma_croakie_rain0) / sizeof(Pma_croakie_rain0[0]),
	.Pma = Pma_croakie_rain0
};
static SMPTRtMA Pma_croakie_rain1[] =
{
	SMPTReMA_CROAKIE_RAIN,
	SMPTReMA_CROAKIE_C1
};
static const struct sM Sm_croakie_rain1 =
{
	.Uj = SMPTReM_CROAKIE,
	.Lma = sizeof(Pma_croakie_rain1) / sizeof(Pma_croakie_rain1[0]),
	.Pma = Pma_croakie_rain1
};
static const struct sM Pm[] =
{
	Sm_ui_rain0,
	Sm_croakie_rain0,
	Sm_ui_rain1,
	Sm_croakie_rain1
};
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
	struct sM Sm = Pm[Um];
	//GLint Pvp[4];
	//.i left bottom width height
	//Mget_integerv(GL_VIEWPORT, Pvp);
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
	const SMPTRtMK *Pk = smptrPmk[Uk];
	SMPTRtMK Uks = SMPTMmWRAP_F(Vkf, Pk[1], Pk[2]);
	float Ff = fabsf(SMPTMmWRAP_F(Vkf, Pk[1], Pk[2]) - Uks);
	SMPTRtMK Uke = SMPTMmWRAP_I(Uks + 1, Pk[1], Pk[2]);
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
	Skf = smptr_ce_kfP[Pk[0]][Uke];
	for (uint8_t l_0 = 0; l_0 < Skf.Lbone; ++l_0)
	{
		//.t unclean
//		if (Skf.Pbone[l_0] >= smptr_ce_mdPj[Sm.Uj])
//			continue;

		for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
		{
			(Pbone_cache + Skf.Pbone[l_0] * 4 * 3)[l_3] = SMPTMmLERP((Pbone_cache + Skf.Pbone[l_0] * 4 * 3)[l_3], Skf.Ps[l_0][l_3], Ff);
			(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4 * 2)[l_3] = SMPTMmLERP((Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4 * 2)[l_3], Skf.Pt[l_0][l_3], Ff);
		}

		for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
		{
			(Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4)[l_3] = SMPTMmLERP((Pbone_cache + Skf.Pbone[l_0] * 4 * 3 + 4)[l_3], Skf.Pr[l_0][l_3], Ff);
		}
	}
	memcpy(Pu + mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)), Pbone_cache, smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 4 * 3);
	Munmap_buffer(GL_UNIFORM_BUFFER);
	Mbind_buffer_range(GL_UNIFORM_BUFFER, 0, Vbuffer_m, 0, sizeof(float) * 16 * 2);
	//! bp need mSIZE_UBO
	Mbind_buffer_range(GL_UNIFORM_BUFFER, 1, Pbuffer_m[0], mSIZE_UBO(smptr_ce_mdLa) + mSIZE_UBO(Li) + Pbpl_fix[Sm.Uj], smptr_ce_mdPj[Sm.Uj] * sizeof(float) * 16 * 2);
	Mbind_buffer_range(GL_UNIFORM_BUFFER, 2, Vbuffer_m, mSIZE_UBO(sizeof(float) * 16 * 2) + mSIZE_UBO(sizeof(uint32_t)), (sizeof(float) * 4 * 3 * smptr_ce_mdPj[Sm.Uj]));
	Mbind_buffer_range(GL_UNIFORM_BUFFER, 3, Pbuffer_m[0], mSIZE_UBO(smptr_ce_mdLa) + mSIZE_UBO(Li) + mSIZE_UBO(Lbp_fix), smptr_ce_mdLrgba);
	Mbind_buffer_range(GL_UNIFORM_BUFFER, 4, Vbuffer_m, mSIZE_UBO(sizeof(float) * 16 * 2), sizeof(uint32_t));

	for (SMPTRtJWL U0 = 0; U0 < Sm.Lma; ++U0)
	{
		Mdraw_elements(GL_TRIANGLES, smptr_ce_mdPil_l[Sm.Pma[U0]] / sizeof(uint32_t), GL_UNSIGNED_INT, (void *)((uintptr_t)(mSIZE_UBO(smptr_ce_mdLa) + Pii[Sm.Pma[U0]])));
	}

	Mbind_vertex_array(Vvao);
	Muse_program(Vprogram);
	Mbind_buffer(GL_ARRAY_BUFFER, Vvbo);
	Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Vebo);
	Mbind_buffer(GL_UNIFORM_BUFFER, Vubo);

	Mdisable_vertex_attrib_array(0);
	Mdisable_vertex_attrib_array(1);
	Mdisable_vertex_attrib_array(2);

	Uubo = (Uubo + 1) % lUBO;
}

//JNIEXPORT void JNICALL Java_com_nali_C_Mfree(JNIEnv *Pjnienv, jclass Vjclass)
//{
//	smptr_ceMfree();
//	smpt_dbMfree();
//}
