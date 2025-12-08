//static void (*Mclear_color)(GLfloat, GLfloat, GLfloat, GLfloat);
static void (*Mget_integerv)(GLenum, GLint *);
static void (*Mget_floatv)(GLenum, GLfloat *);
static void (*Mdebug_message_callback)(GLDEBUGPROC, const void *);
static void (*Menable)(GLenum);
static void (*Mdebug_message_control)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
static void (*Muse_program)(GLuint);
static void (*Mbind_buffer)(GLenum, GLuint);
static void (*Mbuffer_data)(GLenum, GLsizeiptr, const void *, GLenum);
static void (*Mbind_buffer_base)(GLenum, GLuint, GLuint);
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
static void (*Menable_vertex_attrib_array)(GLuint);
static void (*Mdisable_vertex_attrib_array)(GLuint);
static void (*Mbind_buffer_range)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);

static GLuint Vprogram_m;
static GLuint Vshader_vert;
static GLuint Vshader_frag;

static GLuint Vvao_m;
static GLuint Pbuffer[5 + 1 + 1];

static uint32_t Pii[SMPTRcMA];
void Mbuffer_ebo()
{
	SMPT_DBmN2L("Mbuffer_ebo 0")
	Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Pbuffer[5]);
	uint32_t Li = 0;
	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
	{
		Pii[U0] = Li;
		Li += smptr_ce_mdPil[U0];
	}
	SMPT_DBmN2L("Li %d", Li);
	uint8_t *Pi = malloc(Li);
	for (SMPTRtMA U0 = 0; U0 < SMPTRcMA; ++U0)
	{
		SMPT_DBmN2L("Pii[%d] %d", U0, Pii[U0]);
		SMPT_DBmN2L("smptr_ce_mdPil[%d] %d", U0, smptr_ce_mdPil[U0]);
		memcpy(Pi + Pii[U0], smptr_ce_mdPi[U0], smptr_ce_mdPil[U0]);
	}
	Mbuffer_data(GL_ELEMENT_ARRAY_BUFFER, Li, Pi, GL_STATIC_DRAW);
	free(Pi);
	SMPT_DBmN2L("Mbuffer_ebo 1")
}
void Mbuffer_vbo()
{
	SMPT_DBmN2L("Mbuffer_vbo 0")
	Mbind_buffer(GL_ARRAY_BUFFER, Pbuffer[6]);
	Mbuffer_data(GL_ARRAY_BUFFER, smptr_ce_mdLa, smptr_ce_mdPa, GL_STATIC_DRAW);
	Menable_vertex_attrib_array(0);
	Mvertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(uint8_t) * 2, (void *)(0));
	Menable_vertex_attrib_array(1);
	Mvertex_attrib_pointer(1, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(float) * 3 + sizeof(uint8_t) * 2, (void *)(3));
	Menable_vertex_attrib_array(2);
	Mvertex_attrib_pointer(2, 1, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(float) * 3 + sizeof(uint8_t) * 2, (void *)(4));
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
static uint32_t Pbpl[SMPTRcM];
void Mbuffer()
{
	SMPT_DBmN2L("Mbuffer 0")
	GLint Vvao, Vvbo, Vebo, Vubo;
	Mget_integerv(GL_VERTEX_ARRAY_BINDING, &Vvao);
	SMPT_DBmN2L("Vvao %d", Vvao);
	Mget_integerv(GL_ARRAY_BUFFER_BINDING, &Vvbo);
	Mget_integerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &Vebo);
	Mget_integerv(GL_UNIFORM_BUFFER_BINDING, &Vubo);

	//! 1 buffer
	Mgen_buffers(5 + 1 + 1, Pbuffer);
	SMPT_DBmN2L("Pbuffer[0] %d", Pbuffer[0]);
	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[0]);
	Mbuffer_data(GL_UNIFORM_BUFFER, sizeof(float) * 16 * 2, NULL, GL_DYNAMIC_DRAW);
	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[1]);
	uint32_t Lbp = 0;
	for (SMPTRtJWL U0 = 0; U0 < SMPTRcM; ++U0)
	{
		Pbpl[U0] = Lbp;
		Lbp += smptr_ce_mdPj[U0] - 1;
		SMPT_DBmN2L("Pbpl[%d] %d", U0, Pbpl[U0]);
	}
	float *Pbp = malloc(sizeof(float) * Lbp * 16 * 2);
	for (SMPTRtJWL U0 = 0; U0 < SMPTRcM; ++U0)
	{
		SMPT_DBmN2L("smptr_ce_mdPj[%d] %d", U0, smptr_ce_mdPj[U0]);
		SMPT_DBmN2L("Pbpl[%d] %d", U0, Pbpl[U0]);
		memcpy(Pbp + Pbpl[U0] * 16 * 2, smptr_ce_mdPbp[U0], sizeof(float) * 16 * 2 * (smptr_ce_mdPj[U0] - 1));
	}
	Mbuffer_data(GL_UNIFORM_BUFFER, sizeof(float) * 16 * 2 * Lbp, Pbp, GL_STATIC_DRAW);
	free(Pbp);
	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[2]);
	Mbuffer_data(GL_UNIFORM_BUFFER, sizeof(float) * 4 * 3 * SMPTR_CE_MDlBONE, NULL, GL_DYNAMIC_DRAW);
	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[3]);
	Mbuffer_data(GL_UNIFORM_BUFFER, smptr_ce_mdLrgba, smptr_ce_mdPrgba, GL_STATIC_DRAW);
	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[4]);
	Mbuffer_data(GL_UNIFORM_BUFFER, sizeof(uint32_t), NULL, GL_DYNAMIC_DRAW);

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

	Mshader_source(Vs, 1, (const GLchar *const *)&Pd, NULL);
	SMPT_DBmN2L("T0");
	Mcompile_shader(Vs);
	SMPT_DBmN2L("T1");

	GLint Vss;
	Mget_shaderiv(Vs, GL_COMPILE_STATUS, &Vss);
	SMPT_DBmN2L("T2");
	if (!Vss)
	{
		char Pcf[512];
		Mget_shader_info_log(Vs, 512, NULL, Pcf);
		SMPT_DBmN2L("Mget_shader_info_log %s", Pcf)
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

void Mdebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	SMPT_DBmN2L("gl source %d", source)
	SMPT_DBmN2L("gl type %d", type)
	SMPT_DBmN2L("gl id %d", id)
	SMPT_DBmN2L("gl severity %d", severity)
	SMPT_DBmN2L("gl length %d", length)
	SMPT_DBmN2L("gl message %s", message)
	SMPT_DBmN2L("gl userParam %p", userParam)
}

JNIEXPORT void JNICALL Java_com_nali_C_Mgl(JNIEnv *Pjnienv, jclass Vjclass)
{
	smpt_dbMset();

	smptm_v4Mset();

	smptrMset();
	#ifdef SMPT_CM_CLIENT
		smptr_ceMset();
	#endif

	//Mclear_color = (void (*)(GLfloat, GLfloat, GLfloat, GLfloat))glXGetProcAddress((const GLubyte*)"glClearColor");
	Mget_integerv = (void (*)(GLenum, GLint *))glXGetProcAddress((const GLubyte *)"glGetIntegerv");
	Mget_floatv = (void (*)(GLenum, GLfloat *))glXGetProcAddress((const GLubyte *)"glGetFloatv");
	Mdebug_message_callback = (void (*)(GLDEBUGPROC, const void *))glXGetProcAddress((const GLubyte *)"glDebugMessageCallback");
	Menable = (void (*)(GLenum))glXGetProcAddress((const GLubyte *)"glEnable");
	Mdebug_message_control = (void (*)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean))glXGetProcAddress((const GLubyte *)"glDebugMessageControl");
	Muse_program = (void (*)(GLuint))glXGetProcAddress((const GLubyte *)"glUseProgram");
	Mbind_buffer = (void (*)(GLenum, GLuint))glXGetProcAddress((const GLubyte *)"glBindBuffer");
	Mbuffer_data = (void (*)(GLenum, GLsizeiptr, const void *, GLenum))glXGetProcAddress((const GLubyte *)"glBufferData");
	Mbind_buffer_base = (void (*)(GLenum, GLuint, GLuint))glXGetProcAddress((const GLubyte *)"glBindBufferBase");
	Mmap_buffer_range = (void *(*)(GLenum, GLintptr, GLsizeiptr, GLbitfield))glXGetProcAddress((const GLubyte *)"glMapBufferRange");
	Munmap_buffer = (GLboolean (*)(GLenum))glXGetProcAddress((const GLubyte *)"glUnmapBuffer");
	Mshader_source = (void (*)(GLuint, GLsizei, const GLchar *const *, const GLint *))glXGetProcAddress((const GLubyte *)"glShaderSource");
	Mcompile_shader = (void (*)(GLuint))glXGetProcAddress((const GLubyte *)"glCompileShader");
	Mget_shaderiv = (void (*)(GLuint, GLenum, GLint *))glXGetProcAddress((const GLubyte *)"glGetShaderiv");
	Mget_shader_info_log = (void (*)(GLuint, GLsizei, GLsizei *, GLchar *))glXGetProcAddress((const GLubyte *)"glGetShaderInfoLog");
	Mcreate_program = (GLuint (*)(void))glXGetProcAddress((const GLubyte *)"glCreateProgram");
	Mcreate_shader = (GLuint (*)(GLenum))glXGetProcAddress((const GLubyte *)"glCreateShader");
	Mattach_shader = (void (*)(GLuint, GLuint))glXGetProcAddress((const GLubyte *)"glAttachShader");
	Mlink_program = (void (*)(GLuint))glXGetProcAddress((const GLubyte *)"glLinkProgram");
	Mdetach_shader = (void (*)(GLuint, GLuint))glXGetProcAddress((const GLubyte *)"glDetachShader");
	//Mdelete_program = (void (*)(GLenum))glXGetProcAddress((const GLubyte *)"glDeleteProgram");
	Mdelete_shader = (void (*)(GLenum))glXGetProcAddress((const GLubyte *)"glDeleteShader");
	Mgen_buffers = (void (*)(GLsizei, GLuint *))glXGetProcAddress((const GLubyte *)"glGenBuffers");
	Mdraw_elements = (void (*)(GLenum, GLsizei, GLenum, const void *))glXGetProcAddress((const GLubyte *)"glDrawElements");
	Mgen_vertex_arrays = (void (*)(GLsizei, GLuint *))glXGetProcAddress((const GLubyte *)"glGenVertexArrays");
	Mbind_vertex_array = (void (*)(GLuint))glXGetProcAddress((const GLubyte *)"glBindVertexArray");
	Mvertex_attrib_pointer = (void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))glXGetProcAddress((const GLubyte *)"glVertexAttribPointer");
	Menable_vertex_attrib_array = (void (*)(GLuint))glXGetProcAddress((const GLubyte *)"glEnableVertexAttribArray");
	Mdisable_vertex_attrib_array = (void (*)(GLuint))glXGetProcAddress((const GLubyte *)"glDisableVertexAttribArray");
	Mbind_buffer_range = (void (*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr))glXGetProcAddress((const GLubyte *)"glBindBufferRange");

	Menable(GL_DEBUG_OUTPUT);
	Menable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	Mdebug_message_callback(Mdebug, NULL);
	Mdebug_message_control(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, NULL, GL_TRUE);

	Mbuffer();
	Mshader();
}

JNIEXPORT void JNICALL Java_com_nali_C_Mdraw(JNIEnv *Pjnienv, jclass Vjclass)
{
	const uint8_t Uj = SMPTReM_POMI;
	const uint8_t Lma = 7;
	const uint8_t Pma[] =
	{
		SMPTReMA_POMI_2CORE,
		SMPTReMA_POMI_MF0000,
		SMPTReMA_POMI_MF00,
		SMPTReMA_POMI_MF0,
		SMPTReMA_POMI_MM1,
		SMPTReMA_POMI_M,
		SMPTReMA_POMI_IShovel
	};
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

	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[0]);
	void *Pu = Mmap_buffer_range(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16 * 2, GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	GLfloat Pf[16*2];
	Mget_floatv(GL_MODELVIEW_MATRIX, Pf);
	Mget_floatv(GL_PROJECTION_MATRIX, Pf + 16);
	memcpy(Pu, Pf, sizeof(float) * 16 * 2);
	Munmap_buffer(GL_UNIFORM_BUFFER);

	Mbind_buffer_range(GL_UNIFORM_BUFFER, 1, Pbuffer[1], Pbpl[Uj] * sizeof(float) * 16 * 2, (smptr_ce_mdPj[Uj] - 1) * sizeof(float) * 16 * 2);

	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[2]);
	Pu = Mmap_buffer_range(GL_UNIFORM_BUFFER, 0, (sizeof(float) * 4 * 3 * SMPTR_CE_MDlBONE), GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	for (SMPTRtJW U0 = 0; U0 < smptr_ce_mdPj[Uj]; ++U0)
		memcpy(Pu + sizeof(smptm_v4Psrt) * U0, smptm_v4Psrt, sizeof(smptm_v4Psrt));
	Munmap_buffer(GL_UNIFORM_BUFFER);

	Mbind_buffer_base(GL_UNIFORM_BUFFER, 3, Pbuffer[3]);

	Mbind_buffer(GL_UNIFORM_BUFFER, Pbuffer[4]);
	Pu = Mmap_buffer_range(GL_UNIFORM_BUFFER, 0, sizeof(uint32_t), GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	Mget_floatv(GL_CURRENT_COLOR, Pf);
	float Fr = Pf[0];
	float Fg = Pf[1];
	float Fb = Pf[2];
	float Fa = Pf[3];
	//! apply lightmap
	((uint32_t *)Pu)[0] = 0xFFFFFFFF;
	Munmap_buffer(GL_UNIFORM_BUFFER);

	for (SMPTRtJWL U0 = 0; U0 < Lma; ++U0)
	{
		Mdraw_elements(GL_TRIANGLES, Pii[Pma[U0]] / sizeof(uint32_t), GL_UNSIGNED_INT, (void*)((uintptr_t)Pii[Pma[U0]]));
	}

	Mbind_vertex_array(Vvao);
	Muse_program(Vprogram);
	Mbind_buffer(GL_ARRAY_BUFFER, Vvbo);
	Mbind_buffer(GL_ELEMENT_ARRAY_BUFFER, Vebo);
	Mbind_buffer(GL_UNIFORM_BUFFER, Vubo);

	Mdisable_vertex_attrib_array(0);
	Mdisable_vertex_attrib_array(1);
	Mdisable_vertex_attrib_array(2);
}

//JNIEXPORT void JNICALL Java_com_nali_C_Mfree(JNIEnv *Pjnienv, jclass Vjclass)
//{
//	smptr_ceMfree();
//	smpt_dbMfree();
//}
