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
	PFNGLCREATEPROGRAMPROC				WindowsOpenGL::glCreateProgram;
	PFNGLDELETEPROGRAMPROC				WindowsOpenGL::glDeleteProgram;
	PFNGLUSEPROGRAMPROC					WindowsOpenGL::glUseProgram;
	PFNGLLINKPROGRAMPROC				WindowsOpenGL::glLinkProgram;

	PFNGLBINDATTRIBLOCATIONPROC			WindowsOpenGL::glBindAttribLocation;
	PFNGLBINDFRAGDATALOCATIONPROC		WindowsOpenGL::glBindFragDataLocation;

	PFNGLGETPROGRAMIVPROC				WindowsOpenGL::glGetProgramiv;
	PFNGLGETPROGRAMINFOLOGPROC			WindowsOpenGL::glGetProgramInfoLog;
	PFNGLGETSHADERIVPROC				WindowsOpenGL::glGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC			WindowsOpenGL::glGetShaderInfoLog;

	PFNGLGENBUFFERSPROC					WindowsOpenGL::glGenBuffers;
	PFNGLDELETEBUFFERSPROC				WindowsOpenGL::glDeleteBuffers;
	PFNGLBINDBUFFERPROC					WindowsOpenGL::glBindBuffer;
	PFNGLGENVERTEXARRAYSPROC			WindowsOpenGL::glGenVertexArrays;
	PFNGLDELETEVERTEXARRAYSPROC			WindowsOpenGL::glDeleteVertexArrays;
	PFNGLENABLEVERTEXATTRIBARRAYPROC	WindowsOpenGL::glEnableVertexAttribArray;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC	WindowsOpenGL::glDisableVertexAttribArray;
	PFNGLVERTEXATTRIBPOINTERPROC		WindowsOpenGL::glVertexAttribPointer;

	PFNGLUNIFORM1FPROC					WindowsOpenGL::glUniform1f;
	PFNGLUNIFORM2FPROC					WindowsOpenGL::glUniform2f;
	PFNGLUNIFORM3FPROC					WindowsOpenGL::glUniform3f;
	PFNGLUNIFORM4FPROC					WindowsOpenGL::glUniform4f;
	PFNGLUNIFORM1FVPROC					WindowsOpenGL::glUniform1fv;
	PFNGLUNIFORM2FVPROC					WindowsOpenGL::glUniform2fv;
	PFNGLUNIFORM3FVPROC					WindowsOpenGL::glUniform3fv;
	PFNGLUNIFORM4FVPROC					WindowsOpenGL::glUniform4fv;

	PFNGLUNIFORM1IPROC					WindowsOpenGL::glUniform1i;
	PFNGLUNIFORM2IPROC					WindowsOpenGL::glUniform2i;
	PFNGLUNIFORM3IPROC					WindowsOpenGL::glUniform3i;
	PFNGLUNIFORM4IPROC					WindowsOpenGL::glUniform4i;
	PFNGLUNIFORM1IVPROC					WindowsOpenGL::glUniform1iv;
	PFNGLUNIFORM2IVPROC					WindowsOpenGL::glUniform2iv;
	PFNGLUNIFORM3IVPROC					WindowsOpenGL::glUniform3iv;
	PFNGLUNIFORM4IVPROC					WindowsOpenGL::glUniform4iv;

	PFNGLUNIFORM1UIPROC					WindowsOpenGL::glUniform1ui;
	PFNGLUNIFORM2UIPROC					WindowsOpenGL::glUniform2ui;
	PFNGLUNIFORM3UIPROC					WindowsOpenGL::glUniform3ui;
	PFNGLUNIFORM4UIPROC					WindowsOpenGL::glUniform4ui;
	PFNGLUNIFORM1UIVPROC				WindowsOpenGL::glUniform1uiv;
	PFNGLUNIFORM2UIVPROC				WindowsOpenGL::glUniform2uiv;
	PFNGLUNIFORM3UIVPROC				WindowsOpenGL::glUniform3uiv;
	PFNGLUNIFORM4UIVPROC				WindowsOpenGL::glUniform4uiv;

	PFNGLUNIFORMMATRIX2FVPROC			WindowsOpenGL::glUniformMatrix2fv;
	PFNGLUNIFORMMATRIX2X3DVPROC			WindowsOpenGL::glUniformMatrix2x3fv;
	PFNGLUNIFORMMATRIX2X4FVPROC			WindowsOpenGL::glUniformMatrix2x4fv;
	PFNGLUNIFORMMATRIX3FVPROC			WindowsOpenGL::glUniformMatrix3fv;
	PFNGLUNIFORMMATRIX3X2FVPROC			WindowsOpenGL::glUniformMatrix3x2fv;
	PFNGLUNIFORMMATRIX3X4FVPROC			WindowsOpenGL::glUniformMatrix3x4fv;
	PFNGLUNIFORMMATRIX4FVPROC			WindowsOpenGL::glUniformMatrix4fv;
	PFNGLUNIFORMMATRIX4X2FVPROC			WindowsOpenGL::glUniformMatrix4x2fv;
	PFNGLUNIFORMMATRIX4X3FVPROC			WindowsOpenGL::glUniformMatrix4x3fv;

	PFNGLGETUNIFORMLOCATIONPROC			WindowsOpenGL::glGetUniformLocation;

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

		//Load wgl ARB extensions
		_BS_GL_LOAD_FNC(wglChoosePixelFormatARB);
		_BS_GL_LOAD_FNC(wglCreateContextAttribsARB);

		//Shader related:
		_BS_GL_LOAD_FNC(glCreateShader);
		_BS_GL_LOAD_FNC(glShaderSource);
		_BS_GL_LOAD_FNC(glCompileShader);
		_BS_GL_LOAD_FNC(glAttachShader);
		_BS_GL_LOAD_FNC(glDetachShader);
		_BS_GL_LOAD_FNC(glDeleteShader);
		_BS_GL_LOAD_FNC(glCreateProgram);
		_BS_GL_LOAD_FNC(glDeleteProgram);
		_BS_GL_LOAD_FNC(glUseProgram);
		_BS_GL_LOAD_FNC(glBindAttribLocation);
		_BS_GL_LOAD_FNC(glBindFragDataLocation);
		_BS_GL_LOAD_FNC(glLinkProgram);
		
		//Shader debugging
		_BS_GL_LOAD_FNC(glGetShaderiv);
		_BS_GL_LOAD_FNC(glGetShaderInfoLog);
		_BS_GL_LOAD_FNC(glGetProgramiv);
		_BS_GL_LOAD_FNC(glGetProgramInfoLog);


		//VAO VBO function
		_BS_GL_LOAD_FNC(glGenBuffers);
		_BS_GL_LOAD_FNC(glDeleteBuffers);
		_BS_GL_LOAD_FNC(glBindBuffer);
		_BS_GL_LOAD_FNC(glGenVertexArrays);
		_BS_GL_LOAD_FNC(glDeleteVertexArrays);
		_BS_GL_LOAD_FNC(glEnableVertexAttribArray);
		_BS_GL_LOAD_FNC(glDisableVertexAttribArray);
		_BS_GL_LOAD_FNC(glVertexAttribPointer);

		//Uniforms
		_BS_GL_LOAD_FNC(glUniform1f);
		_BS_GL_LOAD_FNC(glUniform2f);
		_BS_GL_LOAD_FNC(glUniform3f);
		_BS_GL_LOAD_FNC(glUniform4f);
		_BS_GL_LOAD_FNC(glUniform1fv);
		_BS_GL_LOAD_FNC(glUniform2fv);
		_BS_GL_LOAD_FNC(glUniform3fv);
		_BS_GL_LOAD_FNC(glUniform4fv);

		_BS_GL_LOAD_FNC(glUniform1i);
		_BS_GL_LOAD_FNC(glUniform2i);
		_BS_GL_LOAD_FNC(glUniform3i);
		_BS_GL_LOAD_FNC(glUniform4i);
		_BS_GL_LOAD_FNC(glUniform1iv);
		_BS_GL_LOAD_FNC(glUniform2iv);
		_BS_GL_LOAD_FNC(glUniform3iv);
		_BS_GL_LOAD_FNC(glUniform4iv);

		_BS_GL_LOAD_FNC(glUniform1ui);
		_BS_GL_LOAD_FNC(glUniform2ui);
		_BS_GL_LOAD_FNC(glUniform3ui);
		_BS_GL_LOAD_FNC(glUniform4ui);
		_BS_GL_LOAD_FNC(glUniform1uiv);
		_BS_GL_LOAD_FNC(glUniform2uiv);
		_BS_GL_LOAD_FNC(glUniform3uiv);
		_BS_GL_LOAD_FNC(glUniform4uiv);

		_BS_GL_LOAD_FNC(glUniformMatrix2fv);
		_BS_GL_LOAD_FNC(glUniformMatrix2x3fv);
		_BS_GL_LOAD_FNC(glUniformMatrix2x4fv);

		_BS_GL_LOAD_FNC(glUniformMatrix3fv);
		_BS_GL_LOAD_FNC(glUniformMatrix3x2fv);
		_BS_GL_LOAD_FNC(glUniformMatrix3x4fv);

		_BS_GL_LOAD_FNC(glUniformMatrix4fv);
		_BS_GL_LOAD_FNC(glUniformMatrix4x3fv);
		_BS_GL_LOAD_FNC(glUniformMatrix4x2fv);

		_BS_GL_LOAD_FNC(glGetUniformLocation);

		//Destroy dummy stuff
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);
		DestroyWindow(hWnd);
		UnregisterClass(wc.lpszClassName, hInstance);

		return ERROR_ID::NONE;
	}

	ERROR_ID	WindowsOpenGL::setPixelFormat(HWND hWnd)
	{
		//Just as they show in khronos website
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
