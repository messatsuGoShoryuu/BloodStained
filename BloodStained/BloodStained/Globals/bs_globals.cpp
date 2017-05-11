#include "bs_globals.h"
#include "../Utilities/bs_Clock.h"
#include "../Resources/bs_FileSystem.h"
#include "../Game/Entity/Component/bs_ComponentManager.h"

namespace bs
{
	bool initialize()
	{
		std::cout << "initialize" << std::endl;

		if (!g_windowsMain.initialize()) return false;
		std::cout << "windows main initialization done" << std::endl;

		FileSystem::initialize();
		if (!g_resourceManager.initialize()) return false;

		std::cout << "Resource manager initialized" << std::endl;

		if (!Clock::initialize()) return false;

		std::cout << "Clock initialized " << std::endl;

#ifdef BS_STANDALONE
		if (!g_shaderManager.initialize())return false;
#endif // BS_STANDALONE

		

		return true;
	}

	bool gameThreadInitialize()
	{
		if (!g_shaderManager.initialize()) return false;
		if (g_spriteRenderer.initialize() != ERROR_ID::NONE) return false;
		if (!g_debugRenderer.initialize()) return false;
		if (g_fontManager.initialize()) return false;
		return true;
	}

	bool shutDown()
	{
		if (!g_fontManager.shutDown()) return false;
		if (!g_debugRenderer.shutDown()) return false;
		if (g_spriteRenderer.shutDown() != ERROR_ID::NONE) return false;
		if (!g_inputManager.shutDown()) return false;
		if (!g_game.shutDown()) return false;
		if (!g_shaderManager.shutDown()) return false;
		if (!g_componentManager.shutDown()) return false;
		if (!g_resourceManager.shutDown()) return false;
		FileSystem::shutDown();
		if (!g_windowsMain.shutDown()) return false;
		return true;
	}

	WindowsMain	g_windowsMain;
	ResourceManager	g_resourceManager;
	Game			g_game;
	Screen			g_screen;
	ComponentManager	g_componentManager;
	ShaderManager		g_shaderManager;
	InputManager		g_inputManager;
	SpriteRenderer	g_spriteRenderer;
	DebugRenderer	g_debugRenderer;
	FontManager		g_fontManager;
}