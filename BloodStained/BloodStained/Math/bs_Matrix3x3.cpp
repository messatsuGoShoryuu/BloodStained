#include "bs_Matrix4x4.h"
#include "bs_Matrix3x3.h"


namespace bs
{
	Matrix3x3::Matrix3x3()
	{
		loadIdentity();
	}

	Matrix3x3::Matrix3x3(const Matrix4x4& m)
	{
		_copy(m);
	}

	Matrix3x3::Matrix3x3(const Matrix3x3& m)
	{
		_copy(m);
	}

	Matrix3x3::Matrix3x3(const f32* floatArray)
	{
		m_buffer[0][0] = floatArray[0];	m_buffer[1][0] = floatArray[3];	m_buffer[2][0] = floatArray[6];
		m_buffer[0][1] = floatArray[1];	m_buffer[1][1] = floatArray[4]; m_buffer[2][1] = floatArray[7];
		m_buffer[0][2] = floatArray[2];	m_buffer[1][2] = floatArray[5]; m_buffer[2][2] = floatArray[8];
	}

	Matrix3x3::~Matrix3x3()
	{

	}

	void Matrix3x3::loadIdentity()
	{
		m_buffer[0][0] = 1.0;	m_buffer[1][0] = 0.0; m_buffer[2][0] = 0.0; 
		m_buffer[0][1] = 0.0;	m_buffer[1][1] = 1.0; m_buffer[2][1] = 0.0; 
		m_buffer[0][2] = 0.0;	m_buffer[1][2] = 0.0; m_buffer[2][2] = 1.0; 
	}

	void	Matrix3x3::toFloatArray(f32* buffer)
	{
		ui32 bufferIndex = 0;
		for (ui32 i = 0; i < 3; i++)
		{
			for (ui32 j = 0; j < 3; j++)
			{
				buffer[bufferIndex] = m_buffer[i][j];
				bufferIndex++;
			}
		}
	}

	void Matrix3x3::_copy(const Matrix4x4& m)
	{
		for (ui32 i = 0; i < 3; i++)
		{
			m_buffer[i] = m[i];
		}
	}

	void Matrix3x3::_copy(const Matrix3x3& m)
	{
		for (ui32 i = 0; i < 3; i++)
		{
			m_buffer[i] = Vector3(m[i]);
		}
	}

	void Matrix3x3::operator=(const Matrix4x4& m)
	{
		_copy(m);
	}
}