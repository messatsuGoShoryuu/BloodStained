#include "bs_Level.h"

//Test purposes.
#include <FileIO/bs_ResourceManager.h>
#include <Rendering/bs_Texture2D.h>

namespace bs
{
	Level::Level()
	{
	}

	Level::Level(const Level & l)
	{
	}

	Level::~Level()
	{
	}

	void Level::initialize()
	{
		const Texture2D* tex = ResourceManager::loadTexture2D("x23.png");
	}

	void Level::shutDown()
	{
	}

	void Level::update()
	{
	}
}

