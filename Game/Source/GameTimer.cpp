#include "../Include/GameTimer.hpp"

#include <thread>

#define DURATION_TO_SECONDS(duration) 0.000001f * (float)std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

using namespace Fnd::Game;

GameTimer::GameTimer():
	_tick_count(0),
	_time_step(std::chrono::duration_cast<Clock::duration>( std::chrono::microseconds(0))),
	_start(),
	_last_tick()
{
}

void GameTimer::SetTimeStep( unsigned int milliseconds )
{
	_time_step = std::chrono::duration_cast<Clock::duration>( std::chrono::microseconds(milliseconds*1000) );
}

void GameTimer::Start()
{
	_start = Clock::now();
	_last_tick = _start;
	std::this_thread::sleep_for( _time_step );
	_this_tick = Clock::now();
}

void GameTimer::Tick()
{
	_last_tick = _this_tick;

	std::this_thread::sleep_until( _last_tick + _time_step );
	_this_tick = Clock::now();
	++_tick_count;
}

float GameTimer::GetTime() const
{
	return DURATION_TO_SECONDS( _this_tick - _start );
}

float GameTimer::GetDt() const
{
	return DURATION_TO_SECONDS( _this_tick - _last_tick );
}

unsigned int GameTimer::GetTickCount() const
{
	return _tick_count;
}