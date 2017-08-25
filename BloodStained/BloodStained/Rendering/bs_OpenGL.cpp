#include "bs_OpenGL.h"

#include <Platform/bs_Platform.h>
#include <Utilities/bs_String.h>

#ifdef BS_WINDOWS
	#include <Platform/Windows/bs_WindowsOpenGL.h>
#define BS_glCreateShader(type)										WindowsOpenGL::glCreateShader(type) 
#define BS_glShaderSource(shader, count, string, length)			WindowsOpenGL::glShaderSource(shader,count,string,length)
#define BS_glCompileShader(id)										WindowsOpenGL::glCompileShader(id)
#define BS_glGetShaderIV(id, type, success)							WindowsOpenGL::glGetShaderiv(id,type, success)
#define BS_glGetShaderInfoLog(id, bufferSize, length, infoLog)		WindowsOpenGL::glGetShaderInfoLog(id,bufferSize,length,infoLog)
#define BS_glDeleteShader(id)										WindowsOpenGL::glDeleteShader(id)
#define BS_glAttachShader(program, shader)							WindowsOpenGL::glAttachShader(program, shader)
#define BS_glDetachShader(program, shader)							WindowsOpenGL::glDetachShader(program, shader)
#define BS_glCreateProgram()										WindowsOpenGL::glCreateProgram()
#define BS_glDeleteProgram(id)										WindowsOpenGL::glDeleteProgram(id)
#define BS_glUseProgram(id)											WindowsOpenGL::glUseProgram(id)
#define BS_glBindAttribLocation(program, index, name)				WindowsOpenGL::glBindAttribLocation(program, index, name)
#define BS_glBindFragDataLocation(program, color, name)				WindowsOpenGL::glBindFragDataLocation(program, color, name)
#define BS_glLinkProgram(id)										WindowsOpenGL::glLinkProgram(id)
#define BS_glGetProgramiv(id, type, success)						WindowsOpenGL::glGetProgramiv(id, type, success) 
#define BS_glGetProgramInfoLog(id, buffersize, length, infoLog)		WindowsOpenGL::glGetProgramInfoLog(id, buffersize, length, infoLog)
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
		GLint success = 0;
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

	ui32 OpenGL::createProgram()
	{
		return BS_glCreateProgram();
	}

	void OpenGL::deleteProgram(ui32 id)
	{
		return BS_glDeleteProgram(id);
	}

	void OpenGL::attachShader(ui32 program, ui32 shader)
	{
		BS_glAttachShader(program, shader);
	}

	void OpenGL::detachShader(ui32 program, ui32 shader)
	{
		BS_glDetachShader(program, shader);
	}

	void OpenGL::bindAttribLocation(ui32 program, ui32 index, const char * name)
	{
		BS_glBindAttribLocation(program, index, name);
	}

	void OpenGL::bindFragDataLocation(ui32 program, ui32 color, const char * name)
	{
		BS_glBindFragDataLocation(program, color, name);
	}

	void OpenGL::useProgram(ui32 id)
	{
		BS_glUseProgram(id);
	}

	void OpenGL::linkProgram(ui32 id)
	{
		BS_glLinkProgram(id);
	}

	bool OpenGL::isProgramLinkingSuccessful(ui32 id)
	{
		GLint success = 0;
		BS_glGetProgramiv(id, GL_LINK_STATUS, &success);
		return success == GL_TRUE;
	}

	String OpenGL::getProgramLinkingFailMessage(ui32 id)
	{
		GLint logLength = 0;
		BS_glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

		String result;
		BS_glGetProgramInfoLog(id, logLength, 0, &result[0]);

		return result;
	}

	void OpenGL::deleteShader(ui32 id)
	{
		BS_glDeleteShader(id);
	}
}
