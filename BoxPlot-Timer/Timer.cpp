#include "Timer.hpp"
double Timer::elapsed_minutes()
{
	return std::chrono::duration_cast<std::chrono::duration<double, minutes>>(stop - beg).count();
}

double Timer::elapsed_seconds()
{
	return std::chrono::duration_cast<std::chrono::duration<double, seconds>>(stop - beg).count();
}

double Timer::elapsed_milliseconds()
{
	return std::chrono::duration_cast<std::chrono::duration<double, millis>>(stop - beg).count();
}

double Timer::elapsed_microseconds()
{
	return std::chrono::duration_cast<std::chrono::duration<double, micros>>(stop - beg).count();
}

double Timer::elapsed_nanoseconds()
{
	return std::chrono::duration_cast<std::chrono::duration<double, nanos>>(stop - beg).count();
}

Timer::Timer(){
	reset();
}

void Timer::reset()
{
	beg = h_clock::now();
	stop = beg;
}

void Timer::timestamp(){
	stop = h_clock::now();
}
