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
	void DestroyVBO(unsigned vbo);
	void RenderVBO(unsigned vbo);
	bool CleanUp();
};