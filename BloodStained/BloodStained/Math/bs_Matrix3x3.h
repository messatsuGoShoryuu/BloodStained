#ifndef BS_MATRIX3X3_H
#define BS_MATRIX3X3_H

#include	"bs_math.h"
#include	"bs_Vector.h"

namespace bs
{
	class Matrix4x4;

	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(const Matrix4x4& m);

		//Create matrix from float array
		Matrix3x3(const f32* floatArray);

		Matrix3x3(const Matrix3x3& m);
		~Matrix3x3();

		void	loadIdentity();
		void	toFloatArray(f32* buffer);

	private:
		void	_copy(const Matrix4x4& m);
		void	_copy(const Matrix3x3& m);

	public:
		inline	Vector3&	operator[](ui32 index){ return m_buffer[index]; }
		inline	const	Vector3&	operator[](ui32 index) const{ return m_buffer[index]; }
		inline	void	operator=(const Matrix3x3& m){ _copy(m); }
		void			operator=(const Matrix4x4& m);

	private:
		Vector3	m_buffer[3];
	};
}
#endif // !BS_MATRIX3X3_H
