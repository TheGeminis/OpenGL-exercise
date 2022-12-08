#pragma once
#include "Module.h"
#include "MathGeoLib.h"
#include "DirectXTex.h"
#include "Globals.h"
#include <GL\glew.h>

class ModuleRenderExercise : public Module
{

public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	unsigned CreateTriangleVBO();
	bool InitTexture();
	void RenderVBO(unsigned vbo, unsigned program);
	void RenderTriangle(unsigned vbo, unsigned program);
	void DestroyVBO(unsigned vbo);
	void DestroyProgram(unsigned program);
	bool CleanUp();

private:
	unsigned myTriangle;
	unsigned myProgram;
	GLuint gl_texture;
};