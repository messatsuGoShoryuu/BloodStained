#include "bs_FunctionTimer.h"
#include "../Utilities/bs_Clock.h"

namespace bs
{
	FunctionTimer::FunctionTimer()
		:m_taskIsDone(-1.0f),
		m_accumulator(0.0f)
	{
		m_startTime = Clock::now();
	}

	FunctionTimer::FunctionTimer(const FunctionTimer& f)
		:m_taskIsDone(f.m_taskIsDone),
		m_startTime(f.m_startTime),
		m_accumulator(f.m_accumulator)
	{

	}

	FunctionTimer::~FunctionTimer()
	{

	}

	bool FunctionTimer::elapsed(real seconds)
	{
		//Calculate elapsed time
		real elapsedTime = Clock::now() - m_startTime;
		
		//If enough time has passed
		if (elapsedTime >= seconds)
		{
			//If the last task timestamp isn't hit
			if (m_startTime + seconds > m_taskIsDone)
			{
				//Update last timestamp and return true.
				m_taskIsDone = m_startTime + seconds;
				return true;
			}
		}
		return false;
	}

	void FunctionTimer::beginScope()
	{
		//Reset the accumulator.
		m_accumulator = 0.0f;
	}

	bool FunctionTimer::wait(real seconds)
	{
		//Accumulate seconds.
		m_accumulator += seconds;

		//Calculate elapsed time
		real elapsedTime = Clock::now() - m_startTime;

		//If enough time has passed
		if (elapsedTime >= m_accumulator)
		{
			//If the last task timestamp isn't hit
			if (m_startTime + m_accumulator > m_taskIsDone)
			{
				//Update last timestamp and return true.
				m_taskIsDone = m_startTime + m_accumulator;
				return true;
			}
		}
		return false;
	}

	void FunctionTimer::start()
	{
		m_startTime = Clock::now();
		m_taskIsDone = -1.0f;
	}

	real FunctionTimer::getElapsedSeconds()
	{
		return Clock::now() - m_startTime;
	}
}