#include "bs_Vector.h"
#include "../Utilities/bs_String.h"


namespace bs
{
	const Vector3 Vector3::zero(0, 0, 0);
	const Vector3 Vector3::unit(1, 1, 1);
	const Vector3 Vector3::up(0, 1, 0); 
	const Vector3 Vector3::forward(0, 0, 1);
	const Vector3 Vector3::right(1, 0, 0);

	Vector3::Vector3()
		:x(0),
		y(0),
		z(0)
	{

	}

	Vector3::Vector3(const Vector2& v)
		:x(v.x),
		y(v.y),
		z(0)
	{

	}

	Vector3::Vector3(const Vector2& v, real z)
		:x(v.x),
		y(v.y),
		z(z)
	{

	}

	Vector3::Vector3(real x, real y, real z)
		:x(x),
		y(y),
		z(z)
	{

	}

	Vector3::Vector3(const Vector4& v)
		:x(v.x),
		y(v.y),
		z(v.z)
	{

	}

	Vector3::Vector3(const Vector3& v)
		:x(v.x),
		y(v.y),
		z(v.z)
	{

	}

	Vector3::~Vector3()
	{

	}

	String Vector3::toString()
	{
		String result = "X = ";
		result.setFloatPrecision(6);
		result = result + x + ", Y = " + y + ", Z = " + z;
		return result;
	}
}