#include "bs_WindowsOpenGL.h"

#define _BS_GL_LOAD_FNC(name) if(!_loadFunction(#name, name))\
return fatalError(ERROR_ID::WGL_EXTENSION_LOAD_FAIL)

namespace bs
{
	PFNWGLCHOOSEPIXELFORMATARBPROC		WindowsOpenGL::wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC	WindowsOpenGL::wglCreateContextAttribsARB;

	PFNGLCREATESHADERPROC				WindowsOpenGL::glCreateShader;
	PFNGLSHADERSOURCEPROC				WindowsOpenGL::glShaderSource;
	PFNGLCOMPILESHADERPROC				WindowsOpenGL::glCompileShader;
	PFNGLATTACHSHADERPROC				WindowsOpenGL::glAttachShader;
	PFNGLDETACHSHADERPROC				WindowsOpenGL::glDetachShader;
	PFNGLDELETESHADERPROC				WindowsOpenGL::glDeleteShader;

	PFNGLGETSHADERIVPROC				WindowsOpenGL::glGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC			WindowsOpenGL::glGetShaderInfoLog;

	LRESULT CALLBACK dummyWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	ERROR_ID WindowsOpenGL::initialize(HINSTANCE hInstance)
	{
		//Create dummy window
		WNDCLASSEX wc = { 0 };
		
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = hInstance;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = dummyWndProc;
		wc.lpszClassName = "DummyWindow";

		if (!RegisterClassEx(&wc))
			return fatalError(ERROR_ID::WINDOW_CLASS_REGISTRATION_FAILED);

		HWND hWnd = CreateWindowEx(NULL, wc.lpszClassName,
			"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

		if (!hWnd) return fatalError(ERROR_ID::WINDOW_CREATION_FAILED);

		//Create dummy pfd
		PIXELFORMATDESCRIPTOR pfd = { 0 };

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;



		HDC hdc = GetDC(hWnd);
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if(pixelFormat == 0) return fatalError(ERROR_ID::PIXEL_FORMAT_FAIL);

		SetPixelFormat(hdc, pixelFormat, &pfd);

		//Create dummy context
		HGLRC hglrc = wglCreateContext(hdc);
		if (!hglrc) return fatalError(ERROR_ID::GL_DC_FAIL);

		wglMakeCurrent(hdc, hglrc);

		//Load wgl extensions
		_BS_GL_LOAD_FNC(wglChoosePixelFormatARB);
		_BS_GL_LOAD_FNC(wglCreateContextAttribsARB);

		//Shader related:
		//Shader initialization
		_BS_GL_LOAD_FNC(glCreateShader);
		_BS_GL_LOAD_FNC(glShaderSource);
		_BS_GL_LOAD_FNC(glCompileShader);
		_BS_GL_LOAD_FNC(glAttachShader);
		_BS_GL_LOAD_FNC(glDetachShader);
		_BS_GL_LOAD_FNC(glDeleteShader);


		//Shader debugging
		_BS_GL_LOAD_FNC(glGetShaderiv);
		_BS_GL_LOAD_FNC(glGetShaderInfoLog);
		

		//Destroy dummy stuff
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);
		DestroyWindow(hWnd);
		UnregisterClass(wc.lpszClassName, hInstance);

		return ERROR_ID::NONE;
	}

	ERROR_ID	WindowsOpenGL::setPixelFormat(HWND hWnd)
	{
		const int attribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};

		HDC hdc = GetDC(hWnd);

		int pixelFormat;
		UINT numFormats;

		if(!wglChoosePixelFormatARB(hdc, attribList, NULL, 1, &pixelFormat, &numFormats))
			return ERROR_ID::PIXEL_FORMAT_FAIL;

		PIXELFORMATDESCRIPTOR pfd;

		if (!SetPixelFormat(hdc, pixelFormat, &pfd))
			return ERROR_ID::PIXEL_FORMAT_FAIL;

		return ERROR_ID::NONE;
	}

	ERROR_ID	WindowsOpenGL::createContext(HWND hWnd)
	{
		int attribList[5] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 0, 0
		};

		HDC hdc = GetDC(hWnd);

		HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, attribList);

		if (!hglrc) return fatalError(ERROR_ID::GL_DC_FAIL);

		if(!wglMakeCurrent(hdc, hglrc)) return fatalError(ERROR_ID::GL_DC_FAIL);

		return ERROR_ID::NONE;
	}
}
#undef _BS_GL_LOAD_FNC(name) 
