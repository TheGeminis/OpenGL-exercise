#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

};