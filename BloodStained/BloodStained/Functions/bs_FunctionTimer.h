#ifndef BS_FUNCTIONTIMER_H
#define BS_FUNCTIONTIMER_H


#include "../Utilities/bs_types.h"
namespace bs
{
	//A class to fire events in functions in different times.
	class FunctionTimer
	{
	public:
		//Constructor:
		FunctionTimer();

		//Copy constructor:
		FunctionTimer(const FunctionTimer& f);

		//Destructor:
		~FunctionTimer();

		//Mark the beginning of the scope.
		void beginScope();

		//Time elapsed since the beginning of the function. Does not need beginScope()
		//@param seconds seconds elapsed since beginning of the function.
		bool	elapsed(real seconds);

		//Get the time elapsed since the beginning of the function.
		real	getElapsedSeconds();

		//Wait for seconds. If true, execute stuff.
		//@param seconds seconds to wait.
		bool	wait(real seconds);


		//Explicitly start the timer. 
		void	start();

	private:
		//Start time of the timer.
		real	m_startTime;

		//Timestamp of the last completed task.
		real	m_taskIsDone;

		//Accumulate seconds.
		real	m_accumulator;
	};
}
#endif // !BS_FUNCTIONTIMER_H
