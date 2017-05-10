#ifndef BS_WINDOWSOPENGLWINDOW_H
#define BS_WINDOWSOPENGLWINDOW_H


#include <GL\glew.h>
#include <GL\wglew.h>

#include"bs_WindowsWindow.h"

namespace bs
{
	
	class WindowsOpenGLInitializer
	{
	public:
		static bool		setPixelFormat(HWND& hwnd, HDC& hdc);
		static bool		createContext(HWND& hwnd, HDC& hdc, HGLRC& hglrc);
		static bool		initializeGlew();
	};

	class OpenGLWindows
	{
	public:
		static	bool	initialize(HWND& hwnd, HDC& hdc);
		static	void	shutDown(HWND& hwnd, HDC& hdc);
		static	HGLRC	hglrc;
	};

	class WindowsOpenGLWindow : public WindowsWindow
	{
	public:
		//Default constructor.
		WindowsOpenGLWindow();

		//Copy constructor.
		WindowsOpenGLWindow(const WindowsOpenGLWindow& w);

		/*Parent window constructor.
		**@param className WindowClass classname.
		**@param windowName Name to be displayed on the toolbar.
		**@param wndProc Window procedure callback.
		**@param style Window style.
		*/
		WindowsOpenGLWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style);

		/*Child window constructor.
		**@param className WindowClass classname.
		**@param windowName Name to be displayed on the toolbar.
		**@param wndProc Window procedure callback.
		**@param style Window style.
		**@param parent Pointer to parent window.
		*/
		WindowsOpenGLWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style, WindowsWindow* parent);

		virtual ~WindowsOpenGLWindow() override;

		bool		initializeGL();

		virtual bool initialize() override;
		virtual void update(MSG* msg) override;
		virtual void destroy() override;

		inline	void	setBlend(bool value){ m_blend = value; }
		inline	bool	blend(){ return m_blend; }

		bool makeCurrent();
		bool releaseContext();

		void	clearColor(class ColorRGBA32 color);
		void	swapBuffers();

	public:
		//Callbacks.
		BaseMemberFunction<void, void>*	OnResize;

	private:
		bool	m_blend;
		HDC		m_hdc;
	};
}

#endif // !BS_WINDOWSOPENGLWINDOW_H
