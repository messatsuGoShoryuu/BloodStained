#ifndef BS_OPENGLWINDOW_H
#define BS_OPENGLWINDOW_H

#ifdef _WIN32 || _WIN64
#include "../Platform/Windows/WindowsWindow/bs_WindowsOpenGLWindow.h"

namespace bs
{
	typedef WindowsOpenGLWindow		BaseOpenGLWindow;
}
#endif


namespace bs
{
	class OpenGLWindow : public	BaseOpenGLWindow
	{
	public:
		//Default constructor.
		OpenGLWindow();
		//Parametrized constructor.
		OpenGLWindow(const char* windowName);
		//Copy constructor.
		OpenGLWindow(const OpenGLWindow& w);
		//Default destructor.
		virtual		~OpenGLWindow();

		

	private:
		static LRESULT	wndProc(WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	};
}
#endif // !BS_OPENGLWINDOW_H
