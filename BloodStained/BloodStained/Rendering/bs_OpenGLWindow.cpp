#include "bs_OpenGLWindow.h"
#include "../Platform/Windows/Input/bs_WindowsInput.h"
#include "../Globals/bs_globals.h"

namespace bs
{
	OpenGLWindow::OpenGLWindow()
		:BaseOpenGLWindow("OpenGlWindowClass", "Bloodstained OpenGL Window", wndProc, WS_OVERLAPPEDWINDOW)
	{

	}

	OpenGLWindow::OpenGLWindow(const char* fileName)
		: BaseOpenGLWindow(fileName, fileName, wndProc, WS_OVERLAPPEDWINDOW)
	{

	}

	OpenGLWindow::OpenGLWindow(const OpenGLWindow& w)
		:BaseOpenGLWindow(w)
	{

	}

	OpenGLWindow::~OpenGLWindow()
	{
		WindowsOpenGLWindow::~WindowsOpenGLWindow();
	}

	LRESULT	OpenGLWindow::wndProc(WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (!w->parent())
		{
			switch (uMsg)
			{
				case WM_INPUT:

					WindowsInput::getInput(lParam);
					return 0;
				case WM_CLOSE:
					DestroyWindow(hwnd);
					return 0;
				case WM_DESTROY:
					if (!w->parent())
					{
						PostQuitMessage(0);
						g_game.quit();
					}
					return 0;
			}

		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}