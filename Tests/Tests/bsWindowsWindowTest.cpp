#include "controlTests.h"

#ifdef WINDOW_TEST

#include <Platform\Windows\WindowsWindow\bs_WindowsOpenGLWindow.h>
#include <Globals\bs_globals.h>
#include <Rendering\bs_Color.h>

LRESULT WindowProc(bs::WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return 1;
}


LRESULT ChildProc(bs::WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
			SetWindowLong(hwnd, 0, 0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BACKGROUND));
			TextOut(hdc, 0, 0, "This is an opengl window", 25);
			EndPaint(hwnd, &ps);
		}
		return 0;

	}
	return 1;
}

void simpleWindowTest();
void openGlWindowTest();

int main()
{
	bs::initialize();
	
	openGlWindowTest();

	return 0;
}

void openGlWindowTest()
{
	LPCSTR className = "OpenGlWindow";
	LPCSTR windowName = "OpenGLWindow";

	LPCSTR childName = "NonOpenGlWindow";
	LPCSTR childWindowName = "NonOpenGLWindow";

	bs::WindowCallback windowCallback;
	windowCallback = WindowProc;

	bs::WindowCallback childCallback;
	childCallback = ChildProc;

	bs::WindowsOpenGLWindow* window = new bs::WindowsOpenGLWindow(className, windowName, windowCallback, WS_OVERLAPPEDWINDOW);
	window->setMetrics(50, 50, CW_USEDEFAULT, CW_USEDEFAULT);

	if (!window->initialize()) std::cout << "Failed to initialize window" << std::endl;

	window->clearColor(bs::ColorRGBA32(150,100,0));
	window->swapBuffers();

	bs::WindowsWindow* child = new bs::WindowsWindow(childName, childWindowName, childCallback, WS_OVERLAPPEDWINDOW, window);
	child->setMetrics(0, 0, 500, 500);
	if (!child->initialize()) std::cout << "Failed to initialize child" << std::endl;

	SetWindowText(child->hwnd(), TEXT("ASDASD"));

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->destroy();
}

void simpleWindowTest()
{
	LPCSTR className = "Window1";
	LPCSTR windowName = "Window1";

	LPCSTR className2 = "Window2";
	LPCSTR windowName2 = "Window2";

	bs::WindowCallback windowCallback;
	windowCallback = WindowProc;

	bs::WindowCallback childCallback;
	childCallback = ChildProc;

	bs::WindowsWindow* window = new bs::WindowsWindow(className, windowName, windowCallback, WS_OVERLAPPEDWINDOW);
	window->setMetrics(50, 50, CW_USEDEFAULT, CW_USEDEFAULT);

	if (!window->initialize()) std::cout << "Failed to initialize window" << std::endl;

	bs::WindowsWindow* child = new bs::WindowsWindow(className2, windowName2, childCallback, WS_OVERLAPPEDWINDOW, window);
	child->setMetrics(0, 0, 500, 500);
	if (!child->initialize()) std::cout << "Failed to initialize child" << std::endl;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->destroy();
}

#endif