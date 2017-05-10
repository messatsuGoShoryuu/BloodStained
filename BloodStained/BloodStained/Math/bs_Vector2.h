#ifndef BS_VECTOR2_H
#define BS_VECTOR2_H

#include "bs_math.h"

namespace bs
{
	class Vector3;
	class Vector4;
	class String;

	class Vector2
	{
	public:
		//Default constructor
		Vector2();

		//Construct with other types of vectors.
		Vector2(const Vector3& v);
		Vector2(const Vector4& v);

		//Float constructor
		Vector2(real x, real y);

		//Copy constructor
		Vector2(const Vector2& v);

		//Destructor.
		~Vector2();

	public:
		//Static vectors.
		static	const Vector2 zero;
		static  const Vector2 unit;

	public:
		//Members of a vector are public.
		real x;
		real y;

	public:
		//Inline Operators
		inline real&	operator[](ui32 index)
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				default: return x;
			}
		}

		inline const	real&	operator[](ui32 index) const
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				default: return x;
			}
		}

		//Inline arithmetic operators:

		inline	void	operator=(const Vector2& v)
		{
			x = v.x;
			y = v.y;
		}

		inline	Vector2		operator+(const Vector2& v)
		{
			Vector2 result;
			result.x = x + v.x;
			result.y = y + v.y;
			return result;
		}

		inline	Vector2		operator-(const Vector2& v)
		{
			Vector2 result;
			result.x = x - v.x;
			result.y = y - v.y;
			return result;
		}

		inline	Vector2		operator*(const real& f)
		{
			Vector2 result;
			result.x = x * f;
			result.y = y * f;
			return result;
		}

		inline	Vector2		operator/(const real& f)
		{
			Vector2 result;
			result.x = x / f;
			result.y = y / f;
			return result;
		}

		inline	Vector2		operator+(const Vector2& v) const
		{
			Vector2 result;
			result.x = x + v.x;
			result.y = y + v.y;
			return result;
		}

		inline	Vector2		operator-(const Vector2& v) const
		{
			Vector2 result;
			result.x = x - v.x;
			result.y = y - v.y;
			return result;
		}

		inline	Vector2		operator*(const real& f) const
		{
			Vector2 result;
			result.x = x * f;
			result.y = y * f;
			return result;
		}

		inline	Vector2		operator/(const real& f) const
		{
			Vector2 result;
			result.x = x / f;
			result.y = y / f;
			return result;
		}

		inline	void		operator+=(const Vector2& v)
		{
			x += v.x;
			y += v.y;
		}

		inline	void		operator-=(const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
		}

		inline	void		operator*=(const real& f)
		{
			x *= f;
			y *= f;
		}

		inline	void		operator/=(const real& f)
		{
			x /= f;
			y /= f;
		}

		String		toString() const;

	
	};
}

#endif // !BS_VECTOR3_H
