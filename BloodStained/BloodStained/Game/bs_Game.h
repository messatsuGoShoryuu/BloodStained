#ifndef BS_GAME_H
#define BS_GAME_H

#include "bs_Level.h"
#include "../Containers/bs_LinkedArray.h"
#include "../Containers/bs_HashMap.h"
#include "../Functions/bs_MemberFunction.h"
namespace bs
{
	namespace editor
	{
		class EditorApp;
	}
	class OpenGLWindow;

	//Main game application. Will be ran in WindowsMain class.
	class Game
	{
	public:
		friend class editor::EditorApp;
		//Default constructor.
		Game();
		//Default destructor.
		~Game();

	private:
		//Copy constructor (not implemented)
		Game(const Game& g);
	public:
		void	execute();

		//Create an empty level.
		Level*	addLevel();
		Level*	addLevel(String name);

		//Load level.
		void	loadCurrentLevel();
		bool	shutDown();

		inline	void	setWindow(OpenGLWindow* window){ m_gameWindow = window; }
		inline  void	run()
		{ 
			m_quit = false; 
			m_initialized = true;
		}
		inline  void	quit(){ m_quit = true; }
		inline  bool	isRunning() { return !m_quit; }

		inline	const	OpenGLWindow*	window() const { return m_gameWindow; }

		inline const Level*	currentLevel() const { return m_currentLevel; }

		inline void render(){ _render(); }

		MemberFunction<Game, void, void>	CreateGameWindowDelegate;
		void	OnCreateGameWindow();
	private:
		void	_update(real dt);
		void	_render();
		
	private:
		//Screen (may be temporary)
		OpenGLWindow*	m_gameWindow;

		//If this is true, the game doesn't run.
		bool			m_quit;
		bool			m_initialized;

		//Level array.
		LinkedArray<Level>	m_levels;
		HashMap<String, Level*> m_levelPointers;
		Level*	m_currentLevel;

		f64 m_lastTime;
		f64 m_lastRenderTime;
	};
}

#endif // !BS_GAME_H
