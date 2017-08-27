#include "bs_Vector.h"
#include "../Utilities/bs_String.h"

namespace bs
{
	
	const Vector4 Vector4::zero(0, 0, 0, 0);
	const Vector4 Vector4::unit(1, 1, 1, 1);


	Vector4::Vector4()
		:x(0),
		y(0),
		z(0),
		w(0)
	{

	}

	Vector4::Vector4(const Vector2& v)
		:x(v.x),
		y(v.y),
		z(0),
		w(0)
	{

	}

	Vector4::Vector4(const Vector2& v, real z, real w)
		:x(v.x),
		y(v.y),
		z(z),
		w(w)
	{

	}

	Vector4::Vector4(real x, real y, real z, real w)
		:x(x),
		y(y),
		z(z),
		w(w)
	{

	}

	Vector4::Vector4(const Vector3& v)
		:x(v.x),
		y(v.y),
		z(v.z),
		w(0)
	{

	}

	Vector4::Vector4(const Vector3& v, real w)
		:x(v.x),
		y(v.y),
		z(v.z),
		w(w)
	{

	}

	Vector4::Vector4(const Vector4& v)
		:x(v.x),
		y(v.y),
		z(v.z),
		w(v.w)
	{

	}

	Vector4::~Vector4()
	{

	}

	String Vector4::toString()
	{
		String result = "X = ";
		result.setFloatPrecision(5);
		result = result + x + ", Y = " + y + ", Z = " + z + ", W = " + w;
		return result;
	}
	
}