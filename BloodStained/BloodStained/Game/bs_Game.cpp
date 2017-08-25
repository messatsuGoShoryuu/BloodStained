#include "bs_Game.h"

#include <FileIO/bs_FileSystem.h>
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_ShaderManager.h>

namespace bs
{
	bool	Game::s_quit;

	ERROR_ID Game::initialize()
	{
		s_quit = false;

		ERROR_ID error = ERROR_ID::NONE;

		FileSystem::initialize();
		error = ResourceManager::initialize();
		error = ShaderManager::initialize();

		return error;
	}

	ERROR_ID Game::shutDown()
	{
		ERROR_ID error = ERROR_ID::NONE;

		error = ShaderManager::shutDown();
		error = ResourceManager::shutDown();
		return error;
	}

	void Game::update()
	{

	}
}