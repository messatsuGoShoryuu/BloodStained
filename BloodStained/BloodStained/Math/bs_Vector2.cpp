#include "bs_Vector.h"
#include "../Utilities/bs_String.h"

namespace bs
{
	const Vector2 Vector2::zero(0, 0);
	const Vector2 Vector2::unit(1, 1);
	const Vector2 Vector2::right(1, 0);
	const Vector2 Vector2::up(0, 1);

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

	void Vector2::rotateAround(const Vector2 & v, f32 angle)
	{
		f32 cos = math::cos(angle);
		f32 sin = math::sin(angle);

		Vector2 d = SELF - v;

		x = d.x * cos + d.y * sin;
		y = -d.x * sin + d.y * cos;

		SELF += v;
	}

	String Vector2::toString() const
	{
		String result = "X = ";
		result = result + x + ", Y = " + y;
		return result;
	}
	real Vector2::cross(const Vector2 & lhs, const Vector2 & rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
	Vector2 Vector2::cross(real lhs, const Vector2 & rhs)
	{
		return Vector2(lhs * rhs.y, -lhs * rhs.x);
	}
	Vector2 Vector2::cross(const Vector2 & lhs, real rhs)
	{
		return Vector2(-rhs * lhs.y, rhs * lhs.x);
	}
}