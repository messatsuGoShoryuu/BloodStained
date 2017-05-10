#include "bs_Matrix4x4.h"
#include "bs_Matrix3x3.h"
#include "../Utilities/bs_String.h"


namespace bs
{
	Matrix4x4::Matrix4x4()
	{
		loadIdentity();
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& m)
	{
		_copy(m);
	}

	Matrix4x4::Matrix4x4(const Matrix3x3& m)
	{
		_copy(m);
	}

	Matrix4x4::Matrix4x4(const f32* floatArray)
	{
		m_buffer[0][0] = floatArray[0];	m_buffer[1][0] = floatArray[4];	m_buffer[2][8] = floatArray[6];	 m_buffer[3][0] = floatArray[12];
		m_buffer[0][1] = floatArray[1];	m_buffer[1][1] = floatArray[5]; m_buffer[2][9] = floatArray[7];  m_buffer[3][1] = floatArray[13];
		m_buffer[0][2] = floatArray[2];	m_buffer[1][2] = floatArray[6]; m_buffer[2][10] = floatArray[8]; m_buffer[3][2] = floatArray[14];
		m_buffer[0][3] = floatArray[3];	m_buffer[1][3] = floatArray[7]; m_buffer[2][11] = floatArray[8]; m_buffer[3][3] = floatArray[15];
	}

	Matrix4x4::~Matrix4x4()
	{

	}

	void Matrix4x4::loadIdentity()
	{
		m_buffer[0][0] = 1.0;	m_buffer[1][0] = 0.0; m_buffer[2][0] = 0.0; m_buffer[3][0] = 0.0;
		m_buffer[0][1] = 0.0;	m_buffer[1][1] = 1.0; m_buffer[2][1] = 0.0; m_buffer[3][1] = 0.0;
		m_buffer[0][2] = 0.0;	m_buffer[1][2] = 0.0; m_buffer[2][2] = 1.0; m_buffer[3][2] = 0.0;
		m_buffer[0][3] = 0.0;	m_buffer[1][3] = 0.0; m_buffer[2][3] = 0.0; m_buffer[3][3] = 1.0;
	}

	void	Matrix4x4::toFloatArray(f32* buffer)
	{
		ui32 bufferIndex = 0;
		for (ui32 i = 0; i < 4; i++)
		{
			for (ui32 j = 0; j < 4; j++)
			{
				buffer[bufferIndex] = m_buffer[i][j];
				bufferIndex++;
			}
		}
	}


	bool	Matrix4x4::inverse(Matrix4x4& out)
	{
		//This is an adaptation of gluInvertMatrix

		out[0][0] =			SELF[1][1]	*	SELF[2][2]	*	SELF[3][3] -
							SELF[1][1]	*	SELF[2][3]	*	SELF[3][2] -
							SELF[2][1]	*	SELF[1][2]	*	SELF[3][3] +
							SELF[2][1]	*	SELF[1][3]	*	SELF[3][2] +
							SELF[3][1]	*	SELF[1][2]	*	SELF[2][3] -
							SELF[3][1]  *	SELF[1][3]	*	SELF[2][2];

		out[1][0] =		-	SELF[1][0]	*	SELF[2][2]	*	SELF[3][3] +
							SELF[1][0]	*	SELF[2][3]  *	SELF[3][2] +
							SELF[2][0]	*	SELF[1][2]	*	SELF[3][3] -
							SELF[2][0]	*	SELF[1][3]	*	SELF[3][2] -
							SELF[3][0]  *	SELF[1][2]	*	SELF[2][3] +
							SELF[3][0]  *	SELF[1][3]	*	SELF[2][2];

		out[2][0] =			SELF[1][0]	*	SELF[2][1]	*	SELF[3][3] -
							SELF[1][0]	*	SELF[2][3]	*	SELF[3][1] -
							SELF[2][0]	*	SELF[1][1]	*	SELF[3][3] +
							SELF[2][0]	*	SELF[1][3]	*	SELF[3][1] +
							SELF[3][0]	*	SELF[1][1]	*	SELF[2][3] -
							SELF[3][0]	*	SELF[1][3]	*	SELF[2][1];

		out[3][0] =		-	SELF[1][0]	*	SELF[2][1]	*	SELF[3][2] +
							SELF[1][0]	*	SELF[2][2]	*	SELF[3][1] +
							SELF[2][0]	*	SELF[1][1]	*	SELF[3][2] -
							SELF[2][0]	*	SELF[1][2]	*	SELF[3][1] -
							SELF[3][0]  *	SELF[1][1]	*	SELF[2][2] +
							SELF[3][0]  *	SELF[1][2]	*	SELF[2][1];

		out[0][1] =		-	SELF[0][1]	*	SELF[2][2]	*	SELF[3][3] +
							SELF[0][1]	*	SELF[2][3]	*	SELF[3][2] +
							SELF[2][1]	*	SELF[0][2]	*	SELF[3][3] -
							SELF[2][1]	*	SELF[0][3]	*	SELF[3][2] -
							SELF[3][1]  *	SELF[0][2]	*	SELF[2][3] +
							SELF[3][1]  *	SELF[0][3]	*	SELF[2][2];

		out[1][1] =			SELF[0][0]	*	SELF[2][2]	*	SELF[3][3] -
							SELF[0][0]	*	SELF[2][3]	*	SELF[3][2] -
							SELF[2][0]	*	SELF[0][2]	*	SELF[3][3] +
							SELF[2][0]	*	SELF[0][3]	*	SELF[3][2] +
							SELF[3][0]	*	SELF[0][2]	*	SELF[2][3] -
							SELF[3][0]	*	SELF[0][3]	*	SELF[2][2];

		out[2][1] =		-	SELF[0][0]	*	SELF[2][1]	*	SELF[3][3] +
							SELF[0][0]	*	SELF[2][3]	*	SELF[3][1] +
							SELF[2][0]	*	SELF[0][1]	*	SELF[3][3] -
							SELF[2][0]	*	SELF[0][3]	*	SELF[3][1] -
							SELF[3][0]	*	SELF[0][1]	*	SELF[2][3] +
							SELF[3][0]	*	SELF[0][3]	*	SELF[2][1];

		out[3][1] =			SELF[0][0]	*	SELF[2][1]	*	SELF[3][2] -
							SELF[0][0]	*	SELF[2][2]	*	SELF[3][1] -
							SELF[2][0]	*	SELF[0][1]	*	SELF[3][2] +
							SELF[2][0]	*	SELF[0][2]	*	SELF[3][1] +
							SELF[3][0]  *	SELF[0][1]	*	SELF[2][2] -
							SELF[3][0]	*	SELF[0][2]	*	SELF[2][1];

		out[0][2] =			SELF[0][1]	*	SELF[1][2]	*	SELF[3][3] -
							SELF[0][1]	*	SELF[1][3]	*	SELF[3][2] -
							SELF[1][1]	*	SELF[0][2]	*	SELF[3][3] +
							SELF[1][1]	*	SELF[0][3]	*	SELF[3][2] +
							SELF[3][1]	*	SELF[0][2]	*	SELF[1][3] -
							SELF[3][1]	*	SELF[0][3]	*	SELF[1][2];

		out[1][2] =		-	SELF[0][0]	*	SELF[1][2]	*	SELF[3][3] +
							SELF[0][0]	*	SELF[1][3]	*	SELF[3][2] +
							SELF[1][0]	*	SELF[0][2]	*	SELF[3][3] -
							SELF[1][0]	*	SELF[0][3]	*	SELF[3][2] -
							SELF[3][0]	*	SELF[0][2]	*	SELF[1][3] +
							SELF[3][0]	*	SELF[0][3]	*	SELF[1][2];

		out[2][2] =			SELF[0][0]	*	SELF[1][1]	*	SELF[3][3] -
							SELF[0][0]	*	SELF[1][3]	*	SELF[3][1] -
							SELF[1][0]	*	SELF[0][1]	*	SELF[3][3] +
							SELF[1][0]	*	SELF[0][3]	*	SELF[3][1] +
							SELF[3][0]	*	SELF[0][1]	*	SELF[1][3] -
							SELF[3][0]	*	SELF[0][3]	*	SELF[1][1];

		out[3][2] =		-	SELF[0][0]	*	SELF[1][1]	*	SELF[3][2] +
							SELF[0][0]	*	SELF[1][2]	*	SELF[3][1] +
							SELF[1][0]	*	SELF[0][1]	*	SELF[3][2] -
							SELF[1][0]	*	SELF[0][2]	*	SELF[3][1] -
							SELF[3][0]	*	SELF[0][1]	*	SELF[1][2] +
							SELF[3][0]	*	SELF[0][2]	*	SELF[1][1];

		out[0][3] =		-	SELF[0][1]	*	SELF[1][2]	*	SELF[2][3] +
							SELF[0][1]	*	SELF[1][3]	*	SELF[2][2] +
							SELF[1][1]	*	SELF[0][2]	*	SELF[2][3] -
							SELF[1][1]	*	SELF[0][3]	*	SELF[2][2] -
							SELF[2][1]	*	SELF[0][2]	*	SELF[1][3] +
							SELF[2][1]	*	SELF[0][3]	*	SELF[1][2];

		out[1][3] =			SELF[0][0]	*	SELF[1][2]	*	SELF[2][3] -
							SELF[0][0]	*	SELF[1][3]	*	SELF[2][2] -
							SELF[1][0]	*	SELF[0][2]	*	SELF[2][3] +
							SELF[1][0]	*	SELF[0][3]	*	SELF[2][2] +
							SELF[2][0]	*	SELF[0][2]	*	SELF[1][3] -
							SELF[2][0]	*	SELF[0][3]	*	SELF[1][2];

		out[2][3] =		-	SELF[0][0]	*	SELF[1][1]	*	SELF[2][3] +
							SELF[0][0]	*	SELF[1][3]	*	SELF[2][1] +
							SELF[1][0]	*	SELF[0][1]	*	SELF[2][3] -
							SELF[1][0]	*	SELF[0][3]	*	SELF[2][1] -
							SELF[2][0]	*	SELF[0][1]	*	SELF[1][3] +	
							SELF[2][0]	*	SELF[0][3]	*	SELF[1][1];

		out[3][3] =			SELF[0][0]	*	SELF[1][1]	*	SELF[2][2] -
							SELF[0][0]	*	SELF[1][2]	*	SELF[2][1] -
							SELF[1][0]	*	SELF[0][1]	*	SELF[2][2] +
							SELF[1][0]	*	SELF[0][2]	*	SELF[2][1] +
							SELF[2][0]	*	SELF[0][1]	*	SELF[1][2] -
							SELF[2][0]	*	SELF[0][2]	*	SELF[1][1];

		real determinant =	SELF[0][0]	*	out[0][0] +
							SELF[0][1]	*	out[1][0] +
							SELF[0][2]	*	out[2][0] +
							SELF[0][3]	*	out[3][0];

		//Matrices with a determinant of 0 are not invertible.

		if (determinant == 0) return false;

		determinant = 1.0f / determinant;

		for (ui32 x = 0; x < 4; x++)
		{
			for (ui32 y = 0; y < 4; y++)
			{
				out[x][y] *= determinant;
			}
		}

		return true;
	}

	void Matrix4x4::transpose()
	{
		Matrix4x4 temp;
		for (ui32 y = 0; y < 4; y++)
		{
			for (ui32 x = 0; x < 4; x++)temp[x][y] = SELF[y][x];
		}
		SELF = temp;
	}

	void	Matrix4x4::toFloatArray(f32* buffer) const
	{
		ui32 bufferIndex = 0;
		for (ui32 i = 0; i < 4; i++)
		{
			for (ui32 j = 0; j < 4; j++)
			{
				buffer[bufferIndex] = m_buffer[i][j];
				bufferIndex++;
			}
		}
	}

	void Matrix4x4::_copy(const Matrix4x4& m)
	{
		for (ui32 i = 0; i < 4; i++)
		{
			m_buffer[i] = m[i];
		}
	}

	void Matrix4x4::_copy(const Matrix3x3& m)
	{
		for (ui32 i = 0; i < 3; i++)
		{
			m_buffer[i] = Vector4(m[i]);
		}
		m_buffer[3] = Vector4::zero;
	}

	void Matrix4x4::operator=(const Matrix3x3& m)
	{
		_copy(m);
	}

	Matrix4x4			Matrix4x4::operator*(const Matrix4x4& m)
	{
		Matrix4x4 result;

		for (ui32 x = 0; x < 4; x++)
		{
			for (ui32 y = 0; y < 4; y++)
			{
				result[x][y] = SELF[x][0] * m[0][y] + SELF[x][1] * m[1][y] + SELF[x][2] * m[2][y] + SELF[x][3] * m[3][y];
			}
		}
		return result;
	}

	Matrix4x4			Matrix4x4::operator*(const Matrix4x4& m) const
	{
		Matrix4x4 result;

		for (ui32 x = 0; x < 4; x++)
		{
			for (ui32 y = 0; y < 4; y++)
			{
				result[x][y] = SELF[0][y] * m[x][0] + SELF[1][y] * m[x][1] + SELF[2][y] * m[x][2] + SELF[3][y] * m[x][3];
			}
		}
		return result;
	}

	void				Matrix4x4::operator*=(const Matrix4x4& m)
	{
		SELF = SELF * m;
	}

	
	Vector3				Matrix4x4::operator*(const Vector3& v)
	{
		Vector3 result = v;
	
		//As if multiplying by Vector4(x,y,z,1)	
		result.x = v.x * SELF[0].x + v.y * SELF[1].x + v.z * SELF[2].x + SELF[3].x;
		result.y = v.x * SELF[0].y + v.y * SELF[1].y + v.z * SELF[2].y + SELF[3].y;
		result.z = v.x * SELF[0].z + v.y * SELF[1].z + v.z * SELF[2].z + SELF[3].z;

		return result; 
	}

	Vector4				Matrix4x4::operator*(const Vector4& v)
	{
		Vector4 result = v;

		result.x = v.x * SELF[0].x + v.y * SELF[1].x + v.z * SELF[2].x + v.w * SELF[3].x;
		result.y = v.x * SELF[0].y + v.y * SELF[1].y + v.z * SELF[2].y + v.w * SELF[3].y;
		result.z = v.x * SELF[0].z + v.y * SELF[1].z + v.z * SELF[2].z + v.w * SELF[3].z;
		result.w = v.x * SELF[0].w + v.y * SELF[1].w + v.z * SELF[2].w + v.w * SELF[3].w;

		return result;
	}

	Vector3				Matrix4x4::operator*(const Vector3& v) const
	{
		Vector3 result = v;

		//As if multiplying by Vector4(x,y,z,1)	
		result.x = v.x * SELF[0].x + v.y * SELF[1].x + v.z * SELF[2].x + SELF[3].x;
		result.y = v.x * SELF[0].y + v.y * SELF[1].y + v.z * SELF[2].y + SELF[3].y;
		result.z = v.x * SELF[0].z + v.y * SELF[1].z + v.z * SELF[2].z + SELF[3].z;

		return result;
	}

	Vector4				Matrix4x4::operator*(const Vector4& v) const
	{
		Vector4 result = v;

		result.x = v.x * SELF[0].x + v.y * SELF[1].x + v.z * SELF[2].x + v.w * SELF[3].x;
		result.y = v.x * SELF[0].y + v.y * SELF[1].y + v.z * SELF[2].y + v.w * SELF[3].y;
		result.z = v.x * SELF[0].z + v.y * SELF[1].z + v.z * SELF[2].z + v.w * SELF[3].z;
		result.w = v.x * SELF[0].w + v.y * SELF[1].w + v.z * SELF[2].w + v.w * SELF[3].w;

		return result;
	}

	String			Matrix4x4::toString() const
	{
		String result;
		result.setFloatPrecision(5);
		for (ui32 y = 0; y < 4; y++)
		{
			for (ui32 x = 0; x < 4; x++)
			{
				result = result + SELF[x][y] + "\t";
			}
			result += "\n";
		}
		return result;
	}
}