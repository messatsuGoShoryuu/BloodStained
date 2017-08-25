#ifndef _BS_SHADER_H_
#define _BS_SHADER_H_

#include <Utilities/bs_types.h>

namespace bs
{
	enum class SHADER_ATTRIB_TYPE
	{
		NONE,
		INT,
		FLOAT,
		MATRIX4,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		SAMPLER2D
	};

	class Shader
	{
	public:
		Shader();
		Shader(ui32 id);

		Shader(const Shader& s);

		~Shader();

		ui32	id();
		void	bind();
		void	unbind();

	private:
		ui32 m_id;
	};
}

#endif // !_BS_SHADER_H