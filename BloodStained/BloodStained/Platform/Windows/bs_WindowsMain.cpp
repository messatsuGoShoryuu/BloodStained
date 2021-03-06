#include <Windows.h>
#include <Utilities/bs_Error.h>

#include <Game/bs_Game.h>
#include <Rendering/bs_Screen.h>
#include "bs_WindowsInput.h"
#include "bs_WindowsOpenGL.h"

LRESULT		CALLBACK	mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//TODO: add raw input message processing
	switch (uMsg)
	{
	case WM_ACTIVATEAPP:
		return 0;
	case WM_CREATE:

		//OpenGL stuff:
		//Set pixel format
		if (bs::WindowsOpenGL::setPixelFormat(hWnd) != bs::ERROR_ID::NONE) return -1;

		//Create OpenGL context
		if (bs::WindowsOpenGL::createContext(hWnd) != bs::ERROR_ID::NONE) return -1;

		//Initialize screen
		{
			RECT clientRect;
			GetClientRect(hWnd, &clientRect);
			bs::ScreenInitializer::initScreen(clientRect.right, clientRect.bottom);
		}

		//Initialize Windows Input
		bs::WindowsInput::initialize();

		return 0;
	case WM_INPUT:
	{
		bs::WindowsInput::getRawInput(hWnd, lParam);
		return 0;
	}
	case WM_DESTROY:
		bs::Game::quit();
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//Init OpenGL
	if(bs::WindowsOpenGL::initialize(hInstance) != bs::ERROR_ID::NONE) return -1;

	//Fill window class
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = mainWndProc;
	wc.hIcon =	LoadIcon(hInstance, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "Blooadstained_Game_Window_Class";
	
	//Register window
	if (!RegisterClassEx(&wc))
		return (int)bs::winFatalError(bs::ERROR_ID::WINDOW_CLASS_REGISTRATION_FAILED);

	//Create main window

	HWND hWnd = CreateWindowEx(NULL,
		wc.lpszClassName, "BloodStained",WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,
		NULL, hInstance, NULL);

	if (!hWnd) return(int)bs::fatalError(bs::ERROR_ID::WINDOW_CREATION_FAILED);


	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	//Init game
	bs::ERROR_ID err = bs::Game::initialize();
	if (err != bs::ERROR_ID::NONE) return -1;

	
	MSG msg;

	LARGE_INTEGER performanceFrequency;
	QueryPerformanceFrequency(&performanceFrequency);
	f32 cyclesPerSecond = 1.0f / (f32)performanceFrequency.QuadPart;


	LARGE_INTEGER performanceCounter;
	QueryPerformanceCounter(&performanceCounter);

	f32 start = (f32)((f64)performanceCounter.QuadPart / (f64)performanceFrequency.QuadPart);
	f32 now = 0.0;
	f32 lastFrame = now;
	//Main loop
	while (bs::Game::isRunning())
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		QueryPerformanceCounter(&performanceCounter);

		
		now = (f32)((f64)performanceCounter.QuadPart / (f64)performanceFrequency.QuadPart);
		now = now - start;
		f32 dt = now - lastFrame;
		if (dt >= 1.0f / 60.0f)
		{
			lastFrame = now;
			bs::Game::update(dt, now);
			SwapBuffers(GetDC(hWnd));
		}
	}
	
	bs::Game::shutDown();

	return 0;
}



