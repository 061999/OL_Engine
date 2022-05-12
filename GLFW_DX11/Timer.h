#pragma once
#include <chrono>


class Timer
{
public:
	Timer();
	float Duration();
	float Delta();
private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point last;
};