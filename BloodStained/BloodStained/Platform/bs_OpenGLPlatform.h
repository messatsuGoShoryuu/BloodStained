#ifndef _BS_OPENGLPLATFORM_H_
#define _BS_OPENGLPLATFORM_H_

#include <Platform/bs_Platform.h>

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
#define BS_glGenBuffers(count, buffers)								WindowsOpenGL::glGenBuffers(count, buffers)
#define BS_glDeleteBuffers(count, buffers)							WindowsOpenGL::glDeleteBuffers(count, buffers)
#define BS_glBindBuffer(type, index)								WindowsOpenGL::glBindBuffer(type, index)
#define BS_glGenVertexArrays(count, buffers)						WindowsOpenGL::glGenVertexArrays(count, buffers)
#define BS_glDeleteVertexArrays(count, buffers)						WindowsOpenGL::glDeleteVertexArrays(count, buffers)
#define BS_glEnableVertexAttribArray(index)							WindowsOpenGL::glEnableVertexAttribArray(index)
#define BS_glDisableVertexAttribArray(index)						WindowsOpenGL::glDisableVertexAttribArray(index)
#define BS_glVertexAttribPointer(index,size,type,normalized,stride,pointer)			WindowsOpenGL::glVertexAttribPointer(index,size,type,normalized,stride,pointer)

#define BS_glUniform1f(location, v0)								WindowsOpenGL::glUniform1f(location, v0)
#define BS_glUniform2f(location, v0, v1)							WindowsOpenGL::glUniform2f(location, v0, v1)
#define BS_glUniform3f(location, v0, v1, v2)						WindowsOpenGL::glUniform3f(location, v0, v1, v2)
#define BS_glUniform4f(location, v0, v1, v2, v3)					WindowsOpenGL::glUniform4f(location, v0, v1, v2, v3)
#define BS_glUniform1fv(location, v0)								WindowsOpenGL::glUniform1fv(location, v0)
#define BS_glUniform2fv(location, v0, v1)							WindowsOpenGL::glUniform2fv(location, v0, v1)
#define BS_glUniform3fv(location, v0, v1, v2)						WindowsOpenGL::glUniform3fv(location, v0, v1, v2)
#define BS_glUniform4fv(location, v0, v1, v2, v3)					WindowsOpenGL::glUniform4fv(location, v0, v1, v2, v3)

#define BS_glUniform1i(location, v0)								WindowsOpenGL::glUniform1i(location, v0)
#define BS_glUniform2i(location, v0, v1)							WindowsOpenGL::glUniform2i(location, v0, v1)
#define BS_glUniform3i(location, v0, v1, v2)						WindowsOpenGL::glUniform3i(location, v0, v1, v2)
#define BS_glUniform4i(location, v0, v1, v2, v3)					WindowsOpenGL::glUniform4i(location, v0, v1, v2, v3)
#define BS_glUniform1iv(location, v0)								WindowsOpenGL::glUniform1iv(location, v0)
#define BS_glUniform2iv(location, v0, v1)							WindowsOpenGL::glUniform2iv(location, v0, v1)
#define BS_glUniform3iv(location, v0, v1, v2)						WindowsOpenGL::glUniform3iv(location, v0, v1, v2)
#define BS_glUniform4iv(location, v0, v1, v2, v3)					WindowsOpenGL::glUniform4iv(location, v0, v1, v2, v3)

#define BS_glUniform1ui(location, v0)								WindowsOpenGL::glUniform1ui(location, v0)
#define BS_glUniform2ui(location, v0, v1)							WindowsOpenGL::glUniform2ui(location, v0, v1)
#define BS_glUniform3ui(location, v0, v1, v2)						WindowsOpenGL::glUniform3ui(location, v0, v1, v2)
#define BS_glUniform4ui(location, v0, v1, v2, v3)					WindowsOpenGL::glUniform4ui(location, v0, v1, v2, v3)
#define BS_glUniform1uiv(location, v0)								WindowsOpenGL::glUniform1uiv(location, v0)
#define BS_glUniform2uiv(location, v0, v1)							WindowsOpenGL::glUniform2uiv(location, v0, v1)
#define BS_glUniform3uiv(location, v0, v1, v2)						WindowsOpenGL::glUniform3uiv(location, v0, v1, v2)
#define BS_glUniform4uiv(location, v0, v1, v2, v3)					WindowsOpenGL::glUniform4uiv(location, v0, v1, v2, v3)

#define BS_glUniformMatrix2fv(location, count, transpose, value)	WindowsOpenGL::glUniformMatrix2fv(location,count,transpose,value)
#define BS_glUniformMatrix2x4fv(location,count,transpose,value)		WindowsOpenGL::glUniformMatrix2x4fv(location,count,transpose,value)
#define BS_glUniformMatrix2x3fv(location,count,transpose,value)		WindowsOpenGL::glUniformMatrix2x3fv(location,count,transpose,value)

#define BS_glUniformMatrix3fv(location, count, transpose, value)	WindowsOpenGL::glUniformMatrix3fv(location,count,transpose,value)
#define BS_glUniformMatrix3x4fv(location,count,transpose,value)		WindowsOpenGL::glUniformMatrix3x4fv(location,count,transpose,value)
#define BS_glUniformMatrix3x2fv(location,count,transpose,value)		WindowsOpenGL::glUniformMatrix3x2fv(location,count,transpose,value)

#define BS_glUniformMatrix4fv(location, count, transpose, value)	WindowsOpenGL::glUniformMatrix4fv(location,count,transpose,value)
#define BS_glUniformMatrix4x3fv(location,count,transpose,value)		WindowsOpenGL::glUniformMatrix4x3fv(location,count,transpose,value)
#define BS_glUniformMatrix4x2fv(location,count,transpose,value)		WindowsOpenGL::glUniformMatrix4x2fv(location,count,transpose,value)

#define	BS_glGetUniformLocation(program, name)						WindowsOpenGL::glGetUniformLocation(program, name)
#define BS_glActiveTexture(texture)									WindowsOpenGL::glActiveTexture(texture)
#define BS_glPixelStorei(name, param)								WindowsOpenGL::glPixelStorei(name,param)
#define BS_glBufferData(type, size, data, usage)					WindowsOpenGL::glBufferData(type, size, data,usage)
#define BS_glGetError()												WindowsOpeNGL::glGetError()
#endif
#endif // !_BS_OPENGLPLATFORM_H_