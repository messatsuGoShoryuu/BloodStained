#ifndef _BS_MATRIX4X4_H_
#define _BS_MATRIX4X4_H_

#include "bs_Vector.h"

namespace bs
{
	class Matrix3x3;
	class String;

	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& m);

		//Create matrix from float array
		Matrix4x4(const f32* floatArray);

		Matrix4x4(const Matrix3x3& m);
		~Matrix4x4();

		void	loadIdentity();

		void	toFloatArray(f32* buffer);
		void	toFloatArray(f32* buffer) const;
		
		bool	inverse(Matrix4x4& out);

		void	transpose();

	private:
		void	_copy(const Matrix4x4& m);
		void	_copy(const Matrix3x3& m);

	public:
		inline	Vector4&	operator[](ui32 index){ return m_buffer[index]; }
		inline	const	Vector4&	operator[](ui32 index) const{ return m_buffer[index]; }
		inline	void	operator=(const Matrix4x4& m){ _copy(m); }
		void			operator=(const Matrix3x3& m);

		Matrix4x4			operator*(const Matrix4x4& m);
		Matrix4x4			operator*(const Matrix4x4& m) const;
		void				operator*=(const Matrix4x4& m);

		Vector3				operator*(const Vector3& v);
		Vector4				operator*(const Vector4& v);
		Vector3				operator*(const Vector3& v) const;
		Vector4				operator*(const Vector4& v) const;

		String				toString() const;
	private:
		Vector4	m_buffer[4];
		
	};
}
#endif // !BS_MATRIX4X4_H
