#include "bs_Game.h"

#include <FileIO/bs_FileSystem.h>
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_ShaderManager.h>
#include <Rendering/bs_RenderManager.h>
#include <Input/bs_InputManager.h>
#include <Time/bs_Clock.h>

namespace bs
{
	bool	Game::s_quit;
	Array<Level>	Game::s_levels;
	ui32 Game::s_currentLevel;

	ERROR_ID Game::initialize()
	{
		s_quit = false;

		ERROR_ID error = ERROR_ID::NONE;

		FileSystem::initialize();
		error = ResourceManager::initialize();
		if (error != ERROR_ID::NONE) return fatalError(error);
		error = ShaderManager::initialize();
		if (error != ERROR_ID::NONE) return fatalError(error);
		error = RenderManager::initialize();
		if (error != ERROR_ID::NONE) return fatalError(error);

		addLevel();
		currentLevel()->initialize();
		return ERROR_ID::NONE;
	}

	ERROR_ID Game::shutDown()
	{
		currentLevel()->shutDown();
		ERROR_ID error = ERROR_ID::NONE;

		error = ShaderManager::shutDown();
		if (error != ERROR_ID::NONE) return fatalError(error);
		error = ResourceManager::shutDown();
		if (error != ERROR_ID::NONE) return fatalError(error);
		error = RenderManager::shutDown();
		if (error != ERROR_ID::NONE) return fatalError(error);
		return ERROR_ID::NONE;
	}

	void Game::update(f32 dt, f32 now)
	{
		Clock::update(dt, now);
		
		OpenGL::clearColor(ColorRGBA32(245,250,255,255));
		OpenGL::clear();

		currentLevel()->update(dt);
		InputManager::update();
	}

	void Game::setCurrentLevel(ui32 index)
	{
		if (currentLevel()) currentLevel()->shutDown();
		s_currentLevel = index;
		currentLevel()->initialize();
	}
	void Game::addLevel()
	{
		s_levels.construct();
	}
}