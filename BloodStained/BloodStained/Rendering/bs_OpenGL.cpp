#include "bs_OpenGL.h"

#include <Platform/bs_OpenGLPlatform.h>
#include <Utilities/bs_Error.h>
#include <Utilities/bs_String.h>
#include "bs_Shader.h"

#include <Math/bs_Matrix4x4.h>



namespace bs
{
	ui32 OpenGL::createShader(OPENGL_SHADER_TYPE type)
	{
		return (ui32)BS_glCreateShader((GLenum)type);
	}

	void OpenGL::shaderSource(ui32 id, int count, const char* source, i32 length)
	{
		BS_glShaderSource((GLuint)id, count, &source, &length);
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

	void OpenGL::clearColor(const ColorRGBAf & color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGL::clearColor(const ColorRGBA32 & color)
	{
		ColorRGBAf c = color;
		clearColor(c);
	}

	void OpenGL::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGL::genBuffers(int count, ui32 * buffers)
	{
		BS_glGenBuffers(count, buffers);
	}

	void OpenGL::deleteBuffers(int count, ui32 * buffers)
	{
		BS_glDeleteBuffers(count, buffers);
	}

	void OpenGL::bindBuffer(OPENGL_BUFFER_TYPE type, ui32 index)
	{
		BS_glBindBuffer((GLenum)type, index);
	}

	void OpenGL::genVertexArrays(int count, ui32 * buffers)
	{
		BS_glGenVertexArrays(count, buffers);
	}

	void OpenGL::deleteVertexArrays(int count, const ui32 * buffers)
	{
		BS_glDeleteVertexArrays(count, buffers);
	}

	void OpenGL::enableVertexAttribArray(ui32 index)
	{
		BS_glEnableVertexAttribArray(index);
	}

	void OpenGL::disableVertexAttribArray(ui32 index)
	{
		BS_glDisableVertexAttribArray(index);
	}

	void OpenGL::vertexAttribPointer(ui32 index, int size, OPENGL_TYPE type, bool normalized, int stride, const void * pointer)
	{
		BS_glVertexAttribPointer(index, size, (GLenum)type, normalized, stride, pointer);
	}

	void OpenGL::drawArrays(OPENGL_PRIMITIVE mode, i32 first, int count)
	{
		glDrawArrays((GLenum)mode, first, count);
	}

	void OpenGL::drawElements(OPENGL_PRIMITIVE mode, int count, OPENGL_TYPE type, const void * indices)
	{
		glDrawElements((GLenum)mode, count, (GLenum) type, indices);
	}

	ERROR_ID OpenGL::uniform(ui32 shaderID, const char * name, SHADER_ATTRIB_TYPE type, void * data, bool transpose)
	{
		int location = BS_glGetUniformLocation(shaderID, name);

		if (location == 0) return ERROR_ID::GL_UNIFORM_NOT_FOUND;

		//TODO: Maybe more types in the future?
		switch (type)
		{
		case SHADER_ATTRIB_TYPE::FLOAT:
		{
			f32*	d = reinterpret_cast<f32*>(data);
			BS_glUniform1f(location, *d);
		}
		break;
		case SHADER_ATTRIB_TYPE::INT:
		{
			i32*	d = reinterpret_cast<i32*>(data);
			BS_glUniform1i(location, *d);
		}
			break;
		case SHADER_ATTRIB_TYPE::MATRIX4:
		{
			f32	d[16];
			Matrix4x4* m = reinterpret_cast<Matrix4x4*>(data);
			m->toFloatArray(d);
			BS_glUniformMatrix4fv(location, 1, transpose, d);
		}
		break;
		case SHADER_ATTRIB_TYPE::SAMPLER2D:
		{
			ui32 i = reinterpret_cast<ui32>(data);
			BS_glUniform1i(location, i);
		}
		break;
		case SHADER_ATTRIB_TYPE::VECTOR2:
		{
			Vector2* d = reinterpret_cast<Vector2*>(data);
			BS_glUniform2f(location, d->x, d->y);
		}
		break;
		case SHADER_ATTRIB_TYPE::VECTOR3:
		{
			Vector3* d = reinterpret_cast<Vector3*>(data);
			BS_glUniform3f(location, d->x, d->y, d->z);
		}
		break;
		case SHADER_ATTRIB_TYPE::VECTOR4:
		{
			Vector4* d = reinterpret_cast<Vector4*>(data);
			BS_glUniform4f(location, d->x, d->y, d->z, d->w);
		}
		break;
		}
		return ERROR_ID::NONE;
	}
	

	void OpenGL::deleteShader(ui32 id)
	{
		BS_glDeleteShader(id);
	}
}
