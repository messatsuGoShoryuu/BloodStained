#include "bs_Shader.h"
#include "../Math/bs_Matrix4x4.h"
#include "bs_Texture2D.h"


namespace bs
{
	Shader::Shader()
		:m_uniformCount(0),
		m_lastUploadedUniform(0),
		m_handle(0),
		m_lastAddedAttribute(0)
	{

	}

	Shader::Shader(String name, ShaderHandle handle)
		:m_name(name),
		m_handle(handle),
		m_uniformCount(0),
		m_lastUploadedUniform(0),
		m_lastAddedAttribute(0)
	{

	}
	
	Shader::Shader(const Shader& s)
		:m_name(s.m_name),
		m_handle(s.m_handle),
		m_uniformCount(s.m_uniformCount),
		m_lastUploadedUniform(s.m_lastUploadedUniform),
		m_lastAddedAttribute(s.m_lastAddedAttribute)
	{

	}
	
	Shader::~Shader()
	{

	}

	void	Shader::addAttribute(const char* attributeName)
	{
		glBindAttribLocation(m_handle, m_lastAddedAttribute, attributeName);
		m_lastAddedAttribute++;
	}

	ui32	Shader::uploadUniform(void* data)
	{
		if (m_lastUploadedUniform >= m_uniformCount) return 0;
		_uploadUniformByType(m_lastUploadedUniform, data);
		m_lastUploadedUniform++;
		return m_lastUploadedUniform;
	}

	void	Shader::_uploadUniformByType(ui32 index, void* data)
	{
		//Get uniform location.
		GLint location = glGetUniformLocation(m_handle, m_uniformSlots[index].id.utf8());

		//Cast according to type and upload
		switch (m_uniformSlots[index].type)
		{
			case UNIFORM_TYPE::FLOAT:
			{
				f32*	d1 = reinterpret_cast<f32*>(data);
				glUniform1f(location, *d1);
			}
				break;

			case UNIFORM_TYPE::MATRIX4:
			{
				f32	d2[16];
				Matrix4x4* m = reinterpret_cast<Matrix4x4*>(data);
				m->toFloatArray(d2);
				glUniformMatrix4fv(location, 1, false, d2);
			}
				break;

			case UNIFORM_TYPE::VECTOR2:
			{
				Vector2* d3 = reinterpret_cast<Vector2*>(data);
				glUniform2f(location, d3->x, d3->y);
			}
				break;

			case UNIFORM_TYPE::VECTOR3:
			{
				Vector3* d4 = reinterpret_cast<Vector3*>(data);
				glUniform3f(location, d4->x, d4->y, d4->z);
			}
				break;

			case UNIFORM_TYPE::VECTOR4:
			{
				Vector4* d5 = reinterpret_cast<Vector4*>(data);
				glUniform4f(location, d5->x, d5->y, d5->z, d5->w);
			}
				break;
			case UNIFORM_TYPE::SAMPLER2D:
			{
				ui32 i = reinterpret_cast<ui32>(data);
				glUniform1i(location, i);
			}
		}
	}

	void Shader::addUniform(String name, UNIFORM_TYPE type)
	{
		m_uniformSlots[m_uniformCount].id = name;
		m_uniformSlots[m_uniformCount].type = type;
		m_uniformCount++;
	}

}
