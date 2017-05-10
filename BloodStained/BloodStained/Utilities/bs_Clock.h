#ifndef BS_CLOCK_H
#define BS_CLOCK_H

#include "bs_types.h"

namespace bs
{
	class Clock
	{
	public:
		//Default constructor.
		Clock();

		//Copy constructor.
		Clock(const Clock& c);

		//Default destructor.
		~Clock();

	public:
		//Initialization of static members.
		static bool		initialize();

	public:
		//Setters and getters:
		inline	void	setRate(real rate){ m_rate = rate; }
		inline	real	rate(){ return m_rate; }

		inline	void	setEndTime(real endTime){ m_endTime = endTime; }
		inline  void	addTime(real time){ m_endTime += time; }
		inline  real	endTime(){ return m_endTime; }

		inline bool		isTicking(){ return (m_endTime < 0 || now() < m_endTime); }

	public:
		//Clock tick.
		bool	tick();

		//Start with infinite duration.
		void	start();

		//Start with fixed duration
		void	start(real duration);

	private:
		//Static members:

		//CPU frequency (calculated in initialization).
		static	f64		sm_CPU_frequency;
		//CPU cycles per second (retrieved from OS in initialization).
		static	i64		sm_CPU_cyclesPerSecond;

	public:
		//Accessors of static members:
		static	f64	CPU_frequency(){ return sm_CPU_frequency; }
		static	i64	CPU_cyclesPerSecond(){ return sm_CPU_cyclesPerSecond; }

		//Current timestamp:
		static	real now();

	private:
		//Private members:

		//Start time.
		real	m_startTime;

		//Timestamp of last frame
		real	m_lastTime;

		//Tick per second.
		real	m_rate;

		//Time to stop clock. Set to -1 for infinite tick.
		real	m_endTime;
	};
}

#endif // !BS_CLOCK_H
