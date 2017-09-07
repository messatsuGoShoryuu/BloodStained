#ifndef _BS_WINDOWSOPENGL_H_
#define _BS_WINDOWSOPENGL_H_

#include <Utilities/bs_Error.h>
#include <Windows.h>

#include <GL/GL.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <GL/glcorearb.h>




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
		static PFNWGLCHOOSEPIXELFORMATARBPROC		wglChoosePixelFormatARB;
		static PFNWGLCREATECONTEXTATTRIBSARBPROC	wglCreateContextAttribsARB;

		//Shader calls
		static PFNGLCREATESHADERPROC				glCreateShader;
		static PFNGLSHADERSOURCEPROC				glShaderSource;
		static PFNGLCOMPILESHADERPROC				glCompileShader;
		static PFNGLATTACHSHADERPROC				glAttachShader;
		static PFNGLDETACHSHADERPROC				glDetachShader;
		static PFNGLDELETESHADERPROC				glDeleteShader;
		static PFNGLCREATEPROGRAMPROC				glCreateProgram;
		static PFNGLDELETEPROGRAMPROC				glDeleteProgram;
		static PFNGLUSEPROGRAMPROC					glUseProgram;
		static PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation;
		static PFNGLBINDFRAGDATALOCATIONPROC		glBindFragDataLocation;
		static PFNGLLINKPROGRAMPROC					glLinkProgram;
		

		//Shader error handling
		static PFNGLGETPROGRAMIVPROC				glGetProgramiv;
		static PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
		static PFNGLGETSHADERIVPROC					glGetShaderiv;
		static PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;

		//VBO, VAO etc..
		static PFNGLGENBUFFERSPROC					glGenBuffers;
		static PFNGLDELETEBUFFERSPROC				glDeleteBuffers;
		static PFNGLBINDBUFFERPROC					glBindBuffer;
		static PFNGLGENVERTEXARRAYSPROC				glGenVertexArrays;
		static PFNGLDELETEVERTEXARRAYSPROC			glDeleteVertexArrays;
		static PFNGLENABLEVERTEXATTRIBARRAYPROC		glEnableVertexAttribArray;
		static PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray;
		static PFNGLVERTEXATTRIBPOINTERPROC			glVertexAttribPointer;
		static PFNGLBINDVERTEXARRAYPROC				glBindVertexArray;

		//Uniforms
		//float
		static PFNGLUNIFORM1FPROC					glUniform1f;
		static PFNGLUNIFORM2FPROC					glUniform2f;
		static PFNGLUNIFORM3FPROC					glUniform3f;
		static PFNGLUNIFORM4FPROC					glUniform4f;
		static PFNGLUNIFORM1FVPROC					glUniform1fv;
		static PFNGLUNIFORM2FVPROC					glUniform2fv;
		static PFNGLUNIFORM3FVPROC					glUniform3fv;
		static PFNGLUNIFORM4FVPROC					glUniform4fv;
		
		//int
		static PFNGLUNIFORM1IPROC					glUniform1i;
		static PFNGLUNIFORM2IPROC					glUniform2i;
		static PFNGLUNIFORM3IPROC					glUniform3i;
		static PFNGLUNIFORM4IPROC					glUniform4i;
		static PFNGLUNIFORM1IVPROC					glUniform1iv;
		static PFNGLUNIFORM2IVPROC					glUniform2iv;
		static PFNGLUNIFORM3IVPROC					glUniform3iv;
		static PFNGLUNIFORM4IVPROC					glUniform4iv;
		
		//unsigned int
		static PFNGLUNIFORM1UIPROC					glUniform1ui;
		static PFNGLUNIFORM2UIPROC					glUniform2ui;
		static PFNGLUNIFORM3UIPROC					glUniform3ui;
		static PFNGLUNIFORM4UIPROC					glUniform4ui;
		static PFNGLUNIFORM1UIVPROC					glUniform1uiv;
		static PFNGLUNIFORM2UIVPROC					glUniform2uiv;
		static PFNGLUNIFORM3UIVPROC					glUniform3uiv;
		static PFNGLUNIFORM4UIVPROC					glUniform4uiv;

		//Matrices
		static PFNGLUNIFORMMATRIX2FVPROC			glUniformMatrix2fv;
		static PFNGLUNIFORMMATRIX2X3DVPROC			glUniformMatrix2x3fv;
		static PFNGLUNIFORMMATRIX2X4FVPROC			glUniformMatrix2x4fv;
		static PFNGLUNIFORMMATRIX3FVPROC			glUniformMatrix3fv;
		static PFNGLUNIFORMMATRIX3X2FVPROC			glUniformMatrix3x2fv;
		static PFNGLUNIFORMMATRIX3X4FVPROC			glUniformMatrix3x4fv;
		static PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv;
		static PFNGLUNIFORMMATRIX4X2FVPROC			glUniformMatrix4x2fv;
		static PFNGLUNIFORMMATRIX4X3FVPROC			glUniformMatrix4x3fv;

		//Uniform location
		static PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation;
		
		//Texture
		static PFNGLACTIVETEXTUREPROC				glActiveTexture;
		static PFNGLBUFFERDATAPROC					glBufferData;
		static PFNGLGENERATEMIPMAPPROC				glGenerateMipmap;
	
	};

	template<class T>
	inline bool WindowsOpenGL::_loadFunction(const char * procAddress, T & functionPtr)
	{
		functionPtr = (T)wglGetProcAddress(procAddress);
		return functionPtr != NULL;
	}
}

#endif // !_BS_WINDOWSOPENGL_H_