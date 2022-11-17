#include "ModuleTimer.h"
#include "SDL.h"


ModuleTimer::ModuleTimer()
{}

// Destructor
ModuleTimer::~ModuleTimer()
{}

// Called before render is available
bool ModuleTimer::Init()
{
    lastTime = 0;
    return true;
}

// Called every draw update
update_status ModuleTimer::Update()
{
    return UPDATE_CONTINUE;
}

void ModuleTimer::StartMilliseconds()
{
    lastTime = SDL_GetTicks();
}

void ModuleTimer::StartMicroseconds()
{
    lastTime = SDL_GetPerformanceCounter() + SDL_GetPerformanceFrequency();
}

void ModuleTimer::ReadMilliseconds()
{
    currentTime = SDL_GetTicks();
}

void ModuleTimer::ReadMicroseconds()
{
    currentTime = SDL_GetPerformanceCounter() + SDL_GetPerformanceFrequency();;
}

unsigned int ModuleTimer::EndMilliseconds()
{
    return currentTime - lastTime;
}

unsigned int ModuleTimer::EndMicroseconds()
{
    return currentTime - lastTime;
}

// Called before quitting
bool ModuleTimer::CleanUp()
{
    return true;
}