#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include <GL\glew.h>

ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	// loads a triangle into a VBO with vertices: (-1, -1, 0) (1, -1, 0) (0, 1, 0)
	unsigned myTriangle = CreateTriangleVBO();
	RenderVBO(myTriangle);

	// creates a program with Hello World vertex and fragment shaders
	App->program->CreateProgram(
		App->program->CompileShader(GL_VERTEX_SHADER, App->program->LoadShaderSource("./../Source/default_vertex.hlsl")), 
		App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->LoadShaderSource("./../Source/default_fragment.hlsl")));
	
	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// This function must be called one time at creation of vertex buffer
unsigned ModuleRenderExercise::CreateTriangleVBO()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return vbo;
}

// This function must be called one time at destruction of vertex buffer
void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}

// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO(unsigned vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool ModuleRenderExercise::CleanUp()
{
	return true;
}