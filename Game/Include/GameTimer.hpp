#pragma once

#ifndef _GAMETIMER_
#define _GAMETIMER_

#include <chrono>

namespace Fnd
{
namespace Game
{

typedef std::chrono::high_resolution_clock Clock;

/*
	Game timer; provides methods to get the current time (since the timer started) and the dt between ticks.
*/
class GameTimer
{
	public:

		// Constructor.
		GameTimer();

		// Set the time step in milliseconds.
		void SetTimeStep( unsigned int milliseconds );

		// Start the timer.
		void Start();

		// Called at the start of every frame; thread pauses until _time_step is reached.
		void Tick();

		// Get the time of the current tick.
		float GetTime() const;

		// Get the time step.
		float GetDt() const;

		unsigned int GetTickCount() const;

	private:

		unsigned int _tick_count;

		Clock::duration _time_step;

		Clock::time_point _start;

		Clock::time_point _last_tick;
		Clock::time_point _this_tick;
};

}
}

#endif