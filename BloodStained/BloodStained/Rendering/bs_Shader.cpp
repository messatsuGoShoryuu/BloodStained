#include "bs_Shader.h"
#include "bs_OpenGL.h"

namespace bs
{
	Shader::Shader()
		:m_id(0)
	{

	}

	Shader::Shader(ui32 id)
		:m_id(id)
	{

	}

	Shader::Shader(const Shader& s)
		:m_id(s.m_id)
	{

	}

	Shader::~Shader()
	{

	}

	void Shader::bind()
	{
		OpenGL::useProgram(m_id);
	}

	void Shader::unbind()
	{
		OpenGL::useProgram(0);
	}
}