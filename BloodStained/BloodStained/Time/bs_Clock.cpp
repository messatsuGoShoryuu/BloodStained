#include "bs_Clock.h"

namespace bs
{
	f32 Clock::m_now;
	f32 Clock::m_dt;

	void Clock::update(f32 dt, f32 now)
	{
		m_dt = dt;
		m_now = now;
	}
}