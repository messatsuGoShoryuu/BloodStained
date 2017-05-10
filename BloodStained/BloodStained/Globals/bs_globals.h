#ifndef BS_GLOBALS_H
#define BS_GLOBALS_H

#include "../Platform/Windows/bs_WindowsMain.h"
#include "../Resources/bs_ResourceManager.h"
#include "../Game/bs_Game.h"
#include "../Rendering/bs_Screen.h"
#include "../Rendering/bs_ShaderManager.h"
#include "../Rendering/RenderedObjects/Sprite/bs_SpriteRenderer.h"
#include "../Rendering/RenderedObjects/Debug/bs_DebugRenderer.h"
#include "../Rendering/RenderedObjects/Font/bs_FontManager.h"
#include "../Input/bs_InputManager.h"



namespace bs
{
	bool initialize();
	bool gameThreadInitialize();
	bool shutDown();

	extern WindowsMain		g_windowsMain;
	extern ResourceManager	g_resourceManager;
	extern Game				g_game;
	extern Screen			g_screen;
	extern ShaderManager	g_shaderManager;
	extern InputManager		g_inputManager;
	extern SpriteRenderer	g_spriteRenderer;
	extern DebugRenderer	g_debugRenderer;
	extern FontManager		g_fontManager;
}


#endif // !BS_GLOBALS_H
