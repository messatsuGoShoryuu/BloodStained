#ifndef _BS_GAME_
#define _BS_GAME_

#include <Utilities/bs_Error.h>

namespace bs
{
	//Controls the states of the application
	class Game
	{
	public:
		static	ERROR_ID	initialize();
		static	ERROR_ID	shutDown();

		static	bool	isRunning() { return !s_quit; }
		static	void	quit() { s_quit = true; }

		static void		update();
	private:
		static bool	s_quit;
	};
}

#endif // !_BS_GAME_