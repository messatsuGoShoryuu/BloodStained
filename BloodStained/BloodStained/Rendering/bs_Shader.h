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

	enum  class SHADER_MATRIX_FLAGS
	{
		NONE = 0x00,
		M = 0x01,
		V = 0x02,
		P = 0x04,
		MV = 0x03,
		MP = 0x05,
		VP = 0x06,
		MVP = 0x07
	};

	inline	SHADER_MATRIX_FLAGS operator|(SHADER_MATRIX_FLAGS lhs, SHADER_MATRIX_FLAGS rhs) 
	{
		return(SHADER_MATRIX_FLAGS)((byte)lhs | (byte)rhs);
	}

	inline	void operator|=(SHADER_MATRIX_FLAGS& lhs, SHADER_MATRIX_FLAGS rhs)
	{
		lhs = lhs | rhs;
	}

	inline	SHADER_MATRIX_FLAGS operator&(SHADER_MATRIX_FLAGS lhs, SHADER_MATRIX_FLAGS rhs)
	{
		return(SHADER_MATRIX_FLAGS)((byte)lhs & (byte)rhs);
	}

	class Shader
	{
	public:
		Shader();
		Shader(ui32 id, SHADER_MATRIX_FLAGS matrixFlags);

		Shader(const Shader& s);

		~Shader();

		inline	ui32	id() const {	return m_id; };
		inline	SHADER_MATRIX_FLAGS matrixFlags()  const{ return m_matrixFlags; }
		void	bind() const;
		void	unbind() const;


	private:
		ui32 m_id;
		SHADER_MATRIX_FLAGS m_matrixFlags;
	};
}

#endif // !_BS_SHADER_H