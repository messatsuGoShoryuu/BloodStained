#include "bs_Game.h"

#include <FileIO/bs_FileSystem.h>
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_ShaderManager.h>
#include <Rendering/bs_RenderManager.h>





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

	void Game::update()
	{
//		OpenGL::clearColor(ColorRGBA32::red);
//		OpenGL::clear();

//		currentLevel()->update();
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