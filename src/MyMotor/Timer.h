#pragma once
#include <chrono>

class Timer
{
public:
	std::chrono::steady_clock::time_point _start;
	bool _isCounting = false;

public:
	Timer();
	void Start();
	std::chrono::duration<double> GetTime();
	double Get_Deltatime();
	std::chrono::duration<double> Restart();
	void Stop();
};

