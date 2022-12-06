#pragma once

class Timer
{
public:

	Timer();
	~Timer();

	bool Init();
	void StartMilliseconds();
	void StartMicroseconds();
	float ReadMilliseconds();
	float ReadMicroseconds();
	bool CleanUp();

private:
	float current_time_milliseconds;
	float current_time_microseconds;
}; 
#pragma once
