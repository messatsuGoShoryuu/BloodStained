#include "bs_WindowsOpenGLWindow.h"
#include "../../../Rendering/bs_Color.h"
#include <assert.h>

namespace bs
{
	HGLRC OpenGLWindows::hglrc;

	bool OpenGLWindows::initialize(HWND& hwnd, HDC& hdc)
	{

		if (!WindowsOpenGLInitializer::initializeGlew()) return false;
		wglGetCurrentDC();
		if (!WindowsOpenGLInitializer::setPixelFormat(hwnd, hdc)) return false;

		if (!WindowsOpenGLInitializer::createContext(hwnd, hdc, hglrc)) return false;

		//				glEnable(GL_ALPHA_TEST);
		//				glAlphaFunc(GL_GREATER, 0.0f);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	void	OpenGLWindows::shutDown(HWND& hwnd, HDC& hdc)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);
	}

	LRESULT CALLBACK TempWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	bool	WindowsOpenGLInitializer::initializeGlew()
	{
		//create temp window
		HINSTANCE hInstance = GetModuleHandle(0);
		HDC hdc;
		HGLRC hglrc;

		//register window class
		LPCSTR	className = "DummyWindow";
		LPCSTR	tempstring = "temp";
		//fill window class
		WNDCLASSEX	windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_VREDRAW | CS_HREDRAW;
		windowClass.lpfnWndProc = TempWndProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = className;
		windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (RegisterClassEx(&windowClass) == 0)
		{
			/*
			std::cout << GetLastError() << std::endl;
			errorQuit("Dummy window class registration failed");
			*/
			return false;
		}

		HWND hwnd;

		
		//create temp window
		hwnd = CreateWindow(className, tempstring, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
							NULL, hInstance, NULL);

		if (hwnd == 0)
		{
			/*
			std::cout << "last error = " << GetLastError() << std::endl;
			errorQuit("Dummy window creation failed");
			*/
			return false;
		}

		//create amd choose temp pixel format
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.iLayerType = PFD_MAIN_PLANE;


		int pixelFormat = 0;

		//get device context
		hdc = GetDC(hwnd);

		//choose pixel format
		pixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixelFormat, &pfd);

		//create ogl context
		hglrc = wglCreateContext(hdc);
		if (hglrc == 0)
		{
			/*
			std::cout << GetLastError() << std::endl;
			GLenum err = glGetError();
			::basics::String s("Dummy window context creation fail with error ");

			s += (char*)glewGetErrorString(err);
			errorQuit(s.getUTF8());
			*/
			return false;
		}
		//make it current
		wglMakeCurrent(hdc, hglrc);

		//initialize glew
		glewExperimental = TRUE;
		GLenum err = glewInit();

		if (err != GLEW_OK)
		{
			/*
			char cause[256];
			sprintf_s(cause, "GLEW initialization failed with error:\n%s", glewGetErrorString(err));
			errorQuit(cause);
			*/
			return false;
		}



		//delete temp contexts
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);
		DestroyWindow(hwnd);
		UnregisterClass(className, hInstance);


		if (WGLEW_EXT_swap_control)
		{
		//	if (!wglSwapIntervalEXT(false));
				/*
				errorWarn("V sync could not be disabled");
				*/
		}
		return true;

	}

	bool	WindowsOpenGLInitializer::setPixelFormat(HWND& hwnd, HDC& hdc)
	{
		//add OGL version stuff
		PIXELFORMATDESCRIPTOR pfd;

		const int pixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0,        //End
		};

		//choose pixel format
		int		pixelFormat;
		UINT	numFormats;

		assert(hwnd != NULL);

		//set pixel format

//		if (!WGLEW_ARB_pixel_format) errorQuit("WGL_ARB_pixel_format not supported");
		if (!wglChoosePixelFormatARB(hdc, pixelFormatAttribList, NULL, 1, &pixelFormat, &numFormats))
		{
		//	errorQuit("Error: pixel format could not be created");
			return false;
		}
		else
		{
			SetPixelFormat(hdc, pixelFormat, &pfd);
		}



		return true;
	}

	bool	WindowsOpenGLInitializer::createContext(HWND& hwnd, HDC& hdc, HGLRC& hglrc)
	{
		//create real context
		if (!hglrc)
		{
			int contextAttribList[5] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 0, 0
			};

			if (!WGLEW_ARB_create_context)
			{	
			//	errorQuit("WGL_ARB_create_context not supported");
				return false;
			}
		
			hglrc = wglCreateContextAttribsARB(hdc, 0, contextAttribList);

			if (!hglrc)
			{
				//	errorQuit("WGL ARB context couldn't be created");
				return false;
			}
		}

		if (!wglMakeCurrent(hdc, hglrc))
		{
		//	errorQuit("OpenGL context creation failed");
			return false;
		}

		return true;
	}

	WindowsOpenGLWindow::WindowsOpenGLWindow()
		:WindowsWindow(),
		m_blend(true)
	{
		
	}

	WindowsOpenGLWindow::WindowsOpenGLWindow(const WindowsOpenGLWindow& w)
		:WindowsWindow(w),
		m_blend(w.m_blend),
		m_hdc(w.m_hdc)
	{

	}

	WindowsOpenGLWindow::WindowsOpenGLWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style)
		: WindowsWindow(className, windowName, wndProc, style),
		m_blend(true)
	{

	}

	WindowsOpenGLWindow::WindowsOpenGLWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style, WindowsWindow* parent)
		: WindowsWindow(className, windowName, wndProc, style, parent),
		m_blend(true)
	{

	}

	WindowsOpenGLWindow::~WindowsOpenGLWindow()
	{

	}

	bool WindowsOpenGLWindow::initializeGL()
	{
		m_hdc = GetDC(m_hwnd);
		if (!m_hdc) return false;

		if (!WindowsOpenGLInitializer::setPixelFormat(m_hwnd, m_hdc)) return false;
		if (!WindowsOpenGLInitializer::createContext(m_hwnd, m_hdc, OpenGLWindows::hglrc)) return false;

		//Setup GL_Blend
		if (m_blend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		return true;
	}

	bool WindowsOpenGLWindow::initialize()
	{
		if (!WindowsWindow::initialize()) return false;

		
		return true;
	}

	void WindowsOpenGLWindow::update(MSG* msg)
	{
		WindowsWindow::update(msg);
	}

	void WindowsOpenGLWindow::destroy()
	{
		WindowsWindow::destroy();
		releaseContext();

	}

	bool WindowsOpenGLWindow::makeCurrent()
	{
		return wglMakeCurrent(m_hdc, OpenGLWindows::hglrc);
	}

	bool WindowsOpenGLWindow::releaseContext()
	{
		return wglMakeCurrent(m_hdc, NULL);
	}

	void	WindowsOpenGLWindow::clearColor(ColorRGBA32 color)
	{
		GLclampf r = (GLclampf)color.r / 255.0f;
		GLclampf g = (GLclampf)color.g / 255.0f;
		GLclampf b = (GLclampf)color.b / 255.0f;
		GLclampf a = (GLclampf)color.a / 255.0f;

		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	}

	void WindowsOpenGLWindow::swapBuffers()
	{
		SwapBuffers(m_hdc);
	}
}
