#include "ModuleProgram.h"

ModuleProgram::ModuleProgram()
{
}

// Destructor
ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
}

update_status ModuleProgram::PreUpdate() 
{
}

update_status ModuleProgram::Update()
{
}

update_status ModuleProgram::PostUpdate()
{
}

bool ModuleProgram::CleanUp()
{
}

/*
unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vtx_shader);
	glAttachShader(program_id, frg_shader);
	glLinkProgram(program_id);
	int res;
	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program, len, &written, info);
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return program_id;
}
*/