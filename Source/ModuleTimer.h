#pragma once
#include "Module.h"

class ModuleTimer : public Module
{
public:

	ModuleTimer();
	~ModuleTimer();

	bool Init();
	update_status Update();
	void StartMilliseconds();
	void StartMicroseconds();
	void ReadMilliseconds();
	void ReadMicroseconds();
	unsigned int EndMilliseconds();
	unsigned int EndMicroseconds();
	bool CleanUp();

private:
	unsigned int lastTime;
	unsigned int currentTime;
}; 
#pragma once
