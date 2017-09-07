#ifndef _BS_GAME_
#define _BS_GAME_

#include <Utilities/bs_Error.h>
#include <Containers/bs_Array.h>
#include "bs_Level.h"

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

		static void		update(f32 dt, f32 now);

		static void		setCurrentLevel(ui32 index);
		static Level*	currentLevel() { return &s_levels[s_currentLevel]; }

		static void		addLevel();

	private:
		static bool	s_quit;
		static Array<Level>	s_levels;
		static ui32 s_currentLevel;
	};
}

#endif // !_BS_GAME_