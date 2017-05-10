#include "FootballApp.h"

#include <Rendering\bs_OpenGLWindow.h>
#include <Globals\bs_globals.h>
#include <Rendering\bs_ScreenInitializer.h>
#include <Rendering\bs_Color.h>

FootballApp::FootballApp()
{

}

FootballApp::~FootballApp()
{

}

bool FootballApp::initialize()
{
	//Assign Delegate to game thread.
	GameThreadDelegate.setCaster(this);
	GameThreadDelegate = &FootballApp::GameThread;
	bs::g_windowsMain.GameThread = &GameThreadDelegate;

	//Create game window.
	m_gameWindow = new bs::OpenGLWindow("Gameplay");
	m_gameWindow->setMetrics(0, 0, 800, 600);

	//Assign game window to game thread.
	bs::g_game.CreateGameWindowDelegate.setCaster(&bs::g_game);
	bs::g_game.CreateGameWindowDelegate = &bs::Game::OnCreateGameWindow;
	m_gameWindow->OnCreate = &bs::g_game.CreateGameWindowDelegate;

	//Initialize game window.
	if (!m_gameWindow->initialize()) return false;

	return true;
}

void FootballApp::GameThread()
{
	//Game thread.
	initializeGameWindow();

	bs::gameThreadInitialize();

	//Acquire current level
	while (!bs::g_game.currentLevel()){}

	bs::g_game.loadCurrentLevel();

	//Start game loop
	while (bs::g_game.isRunning())
	{
		bs::g_game.execute();
	}
}

bool	FootballApp::initializeGameWindow()
{

	//Wait for main window creation.
	while (!m_gameWindow)
	{
		std::cout << "Waiting for main window" << std::endl;
	}

	//Wait for main window initialization.
	while (!m_gameWindow->hwnd())
	{
		std::cout << "Waiting for main window hwnd" << std::endl;
	}

	m_gameWindow->initializeGL();

	m_gameWindow->clearColor(bs::ColorRGBA32(255, 0, 0));
	m_gameWindow->swapBuffers();

	bs::g_game.setWindow(m_gameWindow);
	bs::g_inputManager.initialize();

	OnResizeGameDelegate.setCaster(this);
	OnResizeGameDelegate = &FootballApp::OnResizeGame;
	m_gameWindow->OnResize = &OnResizeGameDelegate;

	bs::ScreenInitializer::setDimensions(bs::g_screen, m_gameWindow->metrics().w, m_gameWindow->metrics().h);

	return true;
}

void FootballApp::OnResizeGame()
{
	bs::g_game.render();
}

bool FootballApp::shutDown()
{
	bool result = true;

	if (m_gameWindow)
	{
		m_gameWindow->destroy();
	}

	if (m_gameWindow) delete m_gameWindow;

	return true;
}
	