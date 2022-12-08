#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include <GL\glew.h>
#include "MathGeoLib.h"
#include "DirectXTex.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	// loads a triangle into a VBO
	LOG("Loading Triangle into a VBO");
	myTriangle = CreateTriangleVBO();

	// creates a program with Hello World vertex and fragment shaders
	LOG("Creating a program with Hello World vertex and fragment shaders");
	myProgram = 
		App->program->CreateProgram
		(
			App->program->CompileShader(GL_VERTEX_SHADER, App->program->LoadShaderSource("../default_vertex.glsl")), 
			App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->LoadShaderSource("../default_fragment.glsl"))
		);
	if (!InitTexture()) return false;
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
		-0.5f, 1.0f, 0.0f,
		 0.5f, 1.0f, 0.0f,
		-0.5f, 2.0f, 0.0f,
		 0.5f, 2.0f, 0.0f
	};
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW); //******ALGO PETA AQUI!!!****** <--- ___No es un error greu___
	//<Source:API> <Type:Other> <Severity:notification> <ID:131185> <Message:Buffer detailed info: Buffer object 1 (bound to GL_ARRAY_BUFFER_ARB, usage hint is GL_STATIC_DRAW) will use VIDEO memory as the source for buffer object operations.>

	return vbo;
}

bool ModuleRenderExercise::InitTexture()
{
	static const wchar_t* filename = L"../assets/textures/BaboonTexture.png";
	TexMetadata md;
	ScratchImage img, imgFR;
	int internal_format, format, type;

	if (!App->texture->LoadTexture(filename, &md, img))
	{
		LOG("Texture Failed To Load");
		return false;
	}

	glGenTextures(1, &gl_texture);
	glBindTexture(GL_TEXTURE_2D, gl_texture);
	
	switch (md.format) {
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internal_format = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internal_format = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internal_format = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}

	FlipRotate(img.GetImages(), img.GetImageCount(), img.GetMetadata(), TEX_FR_FLIP_VERTICAL, imgFR);
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, md.width, md.height, 0, format, type, imgFR.GetImage(0, 0, 0)->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return true;
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
	
	//Bind Texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 4));
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, gl_texture);
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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