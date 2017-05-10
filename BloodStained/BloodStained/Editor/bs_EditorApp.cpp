#include "bs_Editor.h"
#include "../Rendering/bs_OpenGLWindow.h"
#include "../Globals/bs_globals.h"
#include "../Rendering/bs_ScreenInitializer.h"

namespace bs
{
	namespace editor
	{
		EditorApp::EditorApp()
		{

		}

		EditorApp::~EditorApp()
		{

		}

		bool EditorApp::initialize()
		{
			//Create main window 
			m_mainWindow = new EditorWindow("Bloodstained Editor");
			m_mainWindow->setMetrics(0, 0, 1000, 1080);
			m_mainWindow->setBackgroundColor(15, 15, 10);
			m_mainWindow->setTextColor(180, 180, 180);

			//Assign Delegate to game thread.
			GameThreadDelegate.setCaster(this);
			GameThreadDelegate = &EditorApp::GameThread;
			g_windowsMain.GameThread = &GameThreadDelegate;


			//Initialize main window.
			if (!m_mainWindow->initialize()) return false;
			
			//Initialize folder explorer.
			m_folderExplorer = new FolderExplorer();
			if (m_mainWindow)
			{
				m_folderExplorer->setParent(m_mainWindow);
			}
			if(!m_folderExplorer->initialize()) return false;
			
			//Create game window.
			m_gameWindow = new OpenGLWindow("Gameplay");
			m_gameWindow->setParent(m_mainWindow);
			m_gameWindow->setMetrics(0, 0, 800, 600);
			m_gameWindow->embed(true);

			//Assign game window to game thread.
			g_game.CreateGameWindowDelegate.setCaster(&g_game);
			g_game.CreateGameWindowDelegate = &Game::OnCreateGameWindow;
			m_gameWindow->OnCreate = &g_game.CreateGameWindowDelegate;

			//Initialize game window.
			if (!m_gameWindow->initialize()) return false;
			
			return true;
		}

		void EditorApp::GameThread()
		{
			//Game thread.
			initializeGameWindow();

			//Shaders should be initialized in this thread.
			bs::g_shaderManager.initialize();

			//Acquire current level
			while (!g_game.m_currentLevel){}

			g_game.loadCurrentLevel();
			
			//Start game loop
			while (g_game.isRunning())
			{
				g_game.execute();
			}
		}

		bool	EditorApp::initializeGameWindow()
		{

			//Wait for main window creation.
			while (!m_mainWindow)
			{
				std::cout << "Waiting for main window" << std::endl;
			}

			//Wait for main window initialization.
			while (!m_mainWindow->hwnd())
			{
				std::cout << "Waiting for main window hwnd" << std::endl;
			}

			m_gameWindow->initializeGL();

			m_gameWindow->clearColor(ColorRGBA32(255, 0, 0));
			m_gameWindow->swapBuffers();

			g_game.setWindow(m_gameWindow);
			g_inputManager.initialize();

			OnResizeGameDelegate.setCaster(this);
			OnResizeGameDelegate = &EditorApp::OnResizeGame;
			m_gameWindow->OnResize = &OnResizeGameDelegate;

			ScreenInitializer::setDimensions(g_screen, m_gameWindow->metrics().w, m_gameWindow->metrics().h);
	
			return true;
		}

		void EditorApp::OnResizeGame()
		{
			g_game._render();
		}

		bool EditorApp::shutDown()
		{
			bool result = true;
			
			if (m_gameWindow)
			{
				m_gameWindow->destroy();
			}

			if (m_folderExplorer)
			{
				if (!m_folderExplorer->shutDown()) result = false;
			}

			if (m_mainWindow)
			{
				m_mainWindow->destroy();
			}

			if (m_mainWindow) delete m_mainWindow;
			if (m_folderExplorer) delete m_folderExplorer;

			return true;
		}
	}
}