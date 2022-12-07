#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleRenderExercise;
class ModuleCamera;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	void RequestBrowser();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* renderExercise = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleTexture* texture = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
