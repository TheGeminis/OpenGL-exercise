#pragma once
#include "Module.h"
#include "MathGeoLib.h"

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
	float4x4 getProjectionMatrix();
	float4x4 getModelMatrix();
	float4x4 getViewMatrix();
	void RenderVBO(unsigned vbo, unsigned program);
	void RenderTriangle(unsigned vbo, unsigned program);
	void DestroyVBO(unsigned vbo);
	void DestroyProgram(unsigned program);
	bool CleanUp();

private:
	unsigned myTriangle = 0;
	unsigned myProgram = 0;
};