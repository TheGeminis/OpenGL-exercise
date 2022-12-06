#pragma once
#include "Module.h"
#include "Globals.h"
#include "Timer.h"

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void ConsoleWindow();
	void ConfigurationWindow();
	bool CleanUp();

private:
	float* fps_log = nullptr;
	float* ms_log = nullptr;
	int fps_offset;
	Timer timer;
};