#include <Utilities\bs_Clock.h>
#include <Globals\bs_globals.h>
#include <Functions\bs_FunctionTimer.h>

#include <iostream>
#include "controlTests.h"

#ifdef TEST_CLOCK
int main()
{

	if(!bs::initialize()) std::cout<<"initialization failed"<<std::endl;

	ui32 secondsElapsed = 0;

	real startTime = bs::Clock::now();

	bs::FunctionTimer waitTimer;
	bs::FunctionTimer elapsedTimer;

	bs::Clock clock;

	clock.start(60.0f);
	clock.setRate(1.0f);

	while (clock.isTicking())
	{

		waitTimer.beginScope();
		if (clock.tick())
		{
			std::cout << "Seconds elapsed = " << secondsElapsed << std::endl;
			secondsElapsed++;
		}

		if (waitTimer.wait(2.0f))
		{
			std::cout << "2 seconds have elapsed (wait)" << std::endl;
		}
		if (elapsedTimer.elapsed(2.1f))
		{
			std::cout << "2.1 seconds have elapsed (elapsed)" << std::endl;
		}

		if (waitTimer.wait(4.0f))
		{
			std::cout << "6 seconds have elapsed (wait)" << std::endl;
		}

		if (elapsedTimer.elapsed(6.2f))
		{
			std::cout << "6.2 seconds have elapsed (elapsed)" << std::endl;
		}

	}

	system("pause");


	return 0;
}
#endif