#include "bs_Shader.h"
#include "bs_OpenGL.h"

namespace bs
{
	Shader::Shader()
		:m_id(0),
		m_matrixFlags(SHADER_MATRIX_FLAGS::NONE)
	{

	}

	Shader::Shader(ui32 id, SHADER_MATRIX_FLAGS matrixFlags)
		:m_id(id),
		m_matrixFlags(matrixFlags)
	{

	}

	Shader::Shader(const Shader& s)
		:m_id(s.m_id),
		m_matrixFlags(s.m_matrixFlags)
	{

	}

	Shader::~Shader()
	{

	}

	void Shader::bind() const
	{
		OpenGL::useProgram(m_id);
	}

	void Shader::unbind() const
	{
		OpenGL::useProgram(0);
	}
}