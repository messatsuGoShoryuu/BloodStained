#include "../../Globals/bs_globals.h"
#include "WindowsWindow\bs_WindowsOpenGLWindow.h"
#include <CommCtrl.h>
#include <thread>

namespace bs
{
	WindowsMain::WindowsMain()
	{

	}

	WindowsMain::~WindowsMain()
	{
		if (m_gameThread.joinable())
			m_gameThread.join();
	}

	bool WindowsMain::initialize()
	{
		
		m_hinstance = GetModuleHandle(NULL);
		if (!m_hinstance) return false;

		INITCOMMONCONTROLSEX icex;           
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);

		if (!WindowsOpenGLInitializer::initializeGlew()) return false;

		return true;
	}

	bool WindowsMain::shutDown()
	{
		return true;
	}

	void WindowsMain::main()
	{
		
		m_gameThread = std::thread(&WindowsMain::runGame, this);
		MSG msg;
		
		ui32 iterations = 0;
		while (g_game.isRunning())
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					g_game.quit();
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}	
		}
	}

	void WindowsMain::runGame()
	{
		if (GameThread)
		{
			if (GameThread->canExecute())
			{
				(*(GameThread))();
			}
		}
	}
}