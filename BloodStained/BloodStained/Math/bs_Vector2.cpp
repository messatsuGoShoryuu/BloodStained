#include "bs_Vector.h"
#include "../Utilities/bs_String.h"

namespace bs
{
	const Vector2 Vector2::zero(0, 0);
	const Vector2 Vector2::unit(1, 1);

	Vector2::Vector2()
		:x(0),
		y(0)
	{

	}

	Vector2::Vector2(const Vector3& v)
		:x(v.x),
		y(v.y)
	{

	}

	Vector2::Vector2(const Vector4& v)
		:x(v.x),
		y(v.y)
	{

	}

	Vector2::Vector2(real x, real y)
		:x(x),
		y(y)
	{

	}

	Vector2::Vector2(const Vector2& v)
		:x(v.x),
		y(v.y)
	{

	}

	Vector2::~Vector2()
	{

	}

	String Vector2::toString() const
	{
		String result = "X = ";
		result = result + x + ", Y = " + y;
		return result;
	}
}