#include "bs_Game.h"

#include <FileIO/bs_FileSystem.h>
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_ShaderManager.h>
#include <Rendering/bs_RenderManager.h>




namespace bs
{
	bool	Game::s_quit;

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

		return ERROR_ID::NONE;
	}

	ERROR_ID Game::shutDown()
	{
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
		OpenGL::clearColor(ColorRGBA32::red);
		OpenGL::clear();
	}
}