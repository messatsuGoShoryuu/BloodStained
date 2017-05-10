#include "../Globals/bs_globals.h"
#include "../Rendering/bs_OpenGLWindow.h"
#include "../Rendering/bs_Color.h"
#include "../Utilities/bs_Clock.h"
namespace bs
{
	Game::Game()
		:m_gameWindow(nullptr),
		m_quit(false),
		m_initialized(false)
	{
		m_lastTime = Clock::now();
	}

	Game::~Game()
	{

	}

	void	Game::OnCreateGameWindow()
	{
		m_initialized = true;
		std::cout << "Create game window" << std::endl;
	}

	void	Game::loadCurrentLevel()
	{
		if (m_currentLevel)
		{
			m_currentLevel->initialize();
			m_lastTime = Clock::now();
			m_lastRenderTime = Clock::now();
		}
	}

	bool	Game::shutDown()
	{
		if (m_currentLevel) m_currentLevel->shutDown();
		m_levels.destroy();
		m_levelPointers.reset();
		return true;
	}

	void	Game::execute()
	{
		if (!m_initialized) return;
		real time = Clock::now();
		real fps = 1.0 / 60.0;
		_update(time - m_lastTime);
		if (time - m_lastRenderTime > fps)
		{
			_render();
			m_lastRenderTime = time;
		}
		m_lastTime = time;
	}

	void	Game::_render()
	{
		m_gameWindow->clearColor(ColorRGBA32(0, 0, 20));

		if (m_currentLevel)
		{
			m_currentLevel->render();
		}
		
		m_gameWindow->swapBuffers();
	}

	void	Game::_update(real dt)
	{
		if (m_currentLevel)
		{
			m_currentLevel->update(dt);
		}
	}

	Level*	Game::addLevel()
	{
		String name = "Level ";
		name += (i32)m_levels.count();

		return addLevel(name);
	}

	Level*	Game::addLevel(String name)
	{
		if (m_levelPointers.isEmptyAt(name))
		{
			Level* ptr = m_levels.construct(name);
			m_levelPointers[name] = ptr;
			if (!m_currentLevel) m_currentLevel = ptr;
			return ptr;
		}

		return nullptr;
	}
}