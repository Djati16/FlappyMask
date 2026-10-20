#include "Timer.h"
#include <iostream>
#include <thread>
Timer::Timer()
{
	_start = std::chrono::steady_clock::now();
}

void Timer::Start()
{
	_isCounting = true;
	_start = std::chrono::steady_clock::now();
}

double Timer::Get_Deltatime()
{
	static auto lastTime = std::chrono::steady_clock::now();
	auto currentTime = std::chrono::steady_clock::now();

	double delta = std::chrono::duration<double>(currentTime - lastTime).count();
	lastTime = currentTime;
	
	return delta;
}

std::chrono::duration<double> Timer::Restart()
{

	auto _tempTime = std::chrono::steady_clock::now();
	auto _elapsedTime = _tempTime - _start;
	_start = _tempTime;
	//std::cout << _elapsedTime.count() << "\n";

	return _elapsedTime;
}

/*std::_miniTimer::duration<double> Timer::GetTime()
{
	std::cout << _elapsedTime.count() << "\n";
	return _elapsedTime;

}*/

void Timer::Stop()
{
	if (_isCounting == true)
	{
		_isCounting = false;
		_start = std::chrono::steady_clock::now();
	}
}