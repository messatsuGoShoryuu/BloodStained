#ifndef _BS_WINDOWSOPENGL_H_
#define _BS_WINDOWSOPENGL_H_

#include <Utilities/bs_Error.h>
#include <Windows.h>

#include <GL/GL.h>
#include <GL/glext.h>
#include <GL/wglext.h>





namespace bs
{
	class WindowsOpenGL
	{
		friend class OpenGL;
	public:
		static	ERROR_ID	initialize(HINSTANCE hInstance);
		static  ERROR_ID	setPixelFormat(HWND hWnd);
		static	ERROR_ID	createContext(HWND hWnd);
	private:

		template <class T>
		static bool _loadFunction(const char* procAddress, T& functionPtr);

		//Initialization calls
		static PFNWGLCHOOSEPIXELFORMATARBPROC	wglChoosePixelFormatARB;
		static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

		//Shader calls
		static PFNGLCREATESHADERPROC	glCreateShader;
		static PFNGLSHADERSOURCEPROC	glShaderSource;
		static PFNGLCOMPILESHADERPROC	glCompileShader;
		static PFNGLATTACHSHADERPROC	glAttachShader;
		static PFNGLDETACHSHADERPROC	glDetachShader;
		static PFNGLDELETESHADERPROC	glDeleteShader;


		//Shader error handling
		static PFNGLGETSHADERIVPROC		glGetShaderiv;
		static PFNGLGETSHADERINFOLOGPROC	glGetShaderInfoLog;

	};

	template<class T>
	inline bool WindowsOpenGL::_loadFunction(const char * procAddress, T & functionPtr)
	{
		functionPtr = (T)wglGetProcAddress(procAddress);
		return functionPtr != NULL;
	}
}

#endif // !_BS_WINDOWSOPENGL_H_