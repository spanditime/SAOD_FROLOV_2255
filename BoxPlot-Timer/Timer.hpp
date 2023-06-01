#pragma once
#include <chrono>

using minutes = std::ratio<60, 1>;
using seconds = std::ratio<1>;
using millis = std::ratio<1, 1000>;
using micros = std::ratio<1, 1000000>;
using nanos = std::ratio<1, 1000000000>;

class Timer
{
private:
	typedef std::chrono::high_resolution_clock h_clock;
	std::chrono::time_point<std::chrono::high_resolution_clock> beg;
	std::chrono::time_point<std::chrono::high_resolution_clock> stop;
public:
	Timer();
	void reset();
	void timestamp();
	double elapsed_minutes();
	double elapsed_seconds();
	double elapsed_milliseconds();
	double elapsed_microseconds();
	double elapsed_nanoseconds();
};

