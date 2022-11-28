#pragma once
#include "Module.h"

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
	void RenderVBO(unsigned vbo, unsigned program);
	void RenderTriangle();
	void DestroyVBO(unsigned vbo);
	void DestroyProgram(unsigned program);
	bool CleanUp();

private:
	unsigned myTriangle = 0;
	unsigned myProgram = 0;
};