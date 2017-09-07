#ifndef _BS_CLOCK_H_
#define _BS_CLOCK_H_

#include <Utilities/bs_types.h>

namespace bs
{
	class Clock
	{
	public:
		static void update(f32 dt, f32 now);
		static f32	now() { return m_now; }

	private:
		static f32	m_now;
		static f32	m_dt;
	};
}

#endif // !_BS_CLOCK_H