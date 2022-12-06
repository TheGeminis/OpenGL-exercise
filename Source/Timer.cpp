#include "Timer.h"
#include "SDL.h"


Timer::Timer()
{}

// Destructor
Timer::~Timer()
{}

// Called before render is available
bool Timer::Init()
{
    return true;
}

void Timer::StartMilliseconds()
{
    current_time_milliseconds = SDL_GetTicks();
}

void Timer::StartMicroseconds()
{
    current_time_microseconds = SDL_GetPerformanceCounter() + SDL_GetPerformanceFrequency();
}

float Timer::ReadMilliseconds()
{
    float reading = (float)SDL_GetTicks() - current_time_milliseconds;
    if (reading < 1.0f) return 1.0f;
    return reading;
}

float Timer::ReadMicroseconds()
{
    float reading = (float)(SDL_GetPerformanceCounter() + SDL_GetPerformanceFrequency()) - current_time_microseconds;
    if (reading < 1.0f) return 1.0f;
    return reading;
}

// Called before quitting
bool Timer::CleanUp()
{
    return true;
}