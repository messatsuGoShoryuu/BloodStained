#include "bs_Clock.h"

#ifdef _WIN32 || _WIN64
#include <Windows.h>

static real	currentTime(i64 cyclesPerMinute)
{
	LARGE_INTEGER performanceCounter;
	QueryPerformanceCounter(&performanceCounter);
	return (real)((f64)performanceCounter.QuadPart / (f64)cyclesPerMinute);
}

static i64	cyclesPerSecond()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	return li.QuadPart;
}

#endif

namespace bs
{
	//declare static members
	i64 Clock::sm_CPU_cyclesPerSecond;
	f64 Clock::sm_CPU_frequency;

	//Constrcutors / destructor:

	Clock::Clock()
		:m_lastTime(0.0f),
		m_rate(1.0f),
		m_startTime(0.0f),
		m_endTime(-1.0f)
	{

	}

	Clock::Clock(const Clock& c)
		:m_lastTime(c.m_lastTime),
		m_rate(c.m_rate),
		m_startTime(c.m_startTime),
		m_endTime(c.m_endTime)
	{

	}

	Clock::~Clock()
	{

	}

	//Static functions:

	bool Clock::initialize()
	{
		sm_CPU_cyclesPerSecond = cyclesPerSecond();
		sm_CPU_frequency = 1.0 / (f64)sm_CPU_cyclesPerSecond;
		return true;
	}

	real Clock::now()
	{
		return currentTime(sm_CPU_cyclesPerSecond);
	}

	//Clock tick.
	bool	Clock::tick()
	{
		//Check if clock is finished
		if (m_endTime > 0.0)
		{
			if (m_lastTime >= m_endTime) return false;
		}

		//Calculate current time, period and elapsed time.
		real currentTime = now();
		real period = 1.0 / m_rate;
		real elapsedTime = currentTime - m_lastTime;

		//If enough time has elapsed, update m_lastTime and return true.
		if (elapsedTime >= period)
		{
			m_lastTime = currentTime;
			return true;
		}

		//Not at ticking time yet.
		return false;
	}

	//Start with infinite duration.
	void	Clock::start()
	{
		real currentTime = now();
		m_lastTime = currentTime;
		m_startTime = currentTime;
		m_endTime = -1.0f;
	}

	//Start with fixed duration
	void	Clock::start(real duration)
	{
		real currentTime = now();
		m_lastTime = currentTime;
		m_startTime = currentTime;
		m_endTime = currentTime + duration;
	}
}



