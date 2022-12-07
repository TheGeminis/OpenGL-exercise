#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include <GL\glew.h>
#include "MathGeoLib.h"

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
	LOG("Loading Triangle into a VBO with vertices: (-1, -1, 0) (1, -1, 0) (0, 1, 0)");
	myTriangle = CreateTriangleVBO();

	// creates a program with Hello World vertex and fragment shaders
	LOG("Creating a program with Hello World vertex and fragment shaders");
	myProgram = 
		App->program->CreateProgram
		(
			App->program->CompileShader(GL_VERTEX_SHADER, App->program->LoadShaderSource("../default_vertex.glsl")), 
			App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->LoadShaderSource("../default_fragment.glsl"))
		);

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	RenderTriangle(myTriangle, myProgram);
	//RenderVBO(myTriangle, myProgram);
	
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// This function must be called one time at creation of vertex buffer
unsigned ModuleRenderExercise::CreateTriangleVBO()
{
	float vtx_data[] = 
	{
		-1.0f, -1.0f, 0.5f, 
		1.0f, -1.0f, 0.5f,
		0.0f, 1.0f, 0.5f
	};
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW); //******ALGO PETA AQUI!!!****** <--- ___No es un error greu___
	//<Source:API> <Type:Other> <Severity:notification> <ID:131185> <Message:Buffer detailed info: Buffer object 1 (bound to GL_ARRAY_BUFFER_ARB, usage hint is GL_STATIC_DRAW) will use VIDEO memory as the source for buffer object operations.>

	return vbo;
}

// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ModuleRenderExercise::RenderTriangle(unsigned vbo, unsigned program)
{
	float4x4 proj, view, model;

	// TODO: retrieve projection, view and model
	proj = App->camera->getProjectionMatrix();
	view = App->camera->getViewMatrix();
	model = App->camera->getModelMatrix();

	//model.Transpose();

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &proj[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);

	// TODO: bind buffer and vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

// This function must be called one time at destruction of vertex buffer
void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}

// This function must be called one time at destruction of program
void ModuleRenderExercise::DestroyProgram(unsigned program)
{
	glDeleteProgram(program);
}

bool ModuleRenderExercise::CleanUp()
{
	DestroyVBO(myTriangle);
	DestroyProgram(myProgram);
	return true;
}