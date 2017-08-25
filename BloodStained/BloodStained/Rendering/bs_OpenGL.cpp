#include "bs_OpenGL.h"

#include <Platform/bs_Platform.h>
#include <Utilities/bs_String.h>

#ifdef BS_WINDOWS
	#include <Platform/Windows/bs_WindowsOpenGL.h>
#define BS_glCreateShader(type) WindowsOpenGL::glCreateShader(type) 
#define BS_glShaderSource(shader, count, string, length) WindowsOpenGL::glShaderSource(shader,count,string,length)
#define BS_glCompileShader(id) WindowsOpenGL::glCompileShader(id)
#define BS_glGetShaderIV(id, type, success) WindowsOpenGL::glGetShaderiv(id,type, success)
#define BS_glGetShaderInfoLog(id, bufferSize, length, infoLog)
#define BS_glDeleteShader(id) WindowsOpenGL::glDeleteShader(id)
#endif

namespace bs
{
	ui32 OpenGL::createShader(OPENGL_SHADER_TYPE type)
	{
		return (ui32)BS_glCreateShader((GLenum)type);
	}

	void OpenGL::shaderSource(ui32 id, int count, const char* source, i32 length)
	{
		BS_glShaderSource((GLuint)id, (GLsizei)count, &source, &length);
	}

	void OpenGL::compileShader(ui32 id)
	{
		BS_glCompileShader(id);
	}

	bool OpenGL::isCompilationSuccessful(ui32 id)
	{
		GLint success;
		BS_glGetShaderIV(id, GL_COMPILE_STATUS, &success);
		return success == GL_TRUE;
	}

	String OpenGL::getCompilationFailMessage(ui32 id)
	{
		GLint logLength = 0;
		BS_glGetShaderIV(id, GL_INFO_LOG_LENGTH, &logLength);

		String result;
		result.resize(logLength);

		BS_glGetShaderInfoLog(id, logLength, NULL, &result[0]);
		return result;
	}

	void OpenGL::deleteShader(ui32 id)
	{
		BS_glDeleteShader(id);
	}



}
