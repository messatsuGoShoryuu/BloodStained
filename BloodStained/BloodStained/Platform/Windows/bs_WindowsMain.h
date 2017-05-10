#ifndef BS_WINDOWSMAIN_H
#define BS_WINDOWSMAIN_H

#include <Windows.h>
#include <thread>
#include "../../Functions/bs_MemberFunction.h"

namespace bs
{
	class WindowsMain
	{
	public:
		//Constructor.
		WindowsMain();

		//Destructor.
		~WindowsMain();

	private:
		//This can't be copied, leave it unimplemented.
		WindowsMain(const WindowsMain& w);

	public:
		inline const HINSTANCE hinstance(){ return m_hinstance; }

		bool	initialize();
		bool	shutDown();

		void	main();

		void	runGame();

		BaseMemberFunction<void, void>*	GameThread;

	private:
		HINSTANCE m_hinstance;
		std::thread	m_gameThread;
	};
}

#endif // !BS_WINDOWSMAIN_H
