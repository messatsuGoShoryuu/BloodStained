#ifndef _BS_VECTOR4_H_
#define _BS_VECTOR4_H_

#include "bs_math.h"

namespace bs
{
	class Vector2;
	class Vector3;
	class String;

	class Vector4
	{
	public:
		//Constructor.
		Vector4();

		//Construct from other types of vectors.
		Vector4(const Vector2& v);
		Vector4(const Vector2& v, real z, real w);
		Vector4(real x, real y, real z, real w);
		Vector4(const Vector3& v);
		Vector4(const Vector3& v, real w);
		
		//Copy constructor.
		Vector4(const Vector4& v);

		//Destructor.
		~Vector4();
	public:
		//Static vectors.
		static	const Vector4 zero;
		static  const Vector4 unit;

	
	public:
		//Members of a vector are public.
		real x;
		real y;
		real z;
		real w;

	public:

		inline	real	squareMagnitude() const
		{
			return x * x + y * y + z * z + w * w;
		}

		inline real		magnitude()
		{
			return math::sqrt(squareMagnitude());
		}

		inline real		magnitude() const
		{
			return math::sqrt(squareMagnitude());
		}

		inline void		normalize()
		{
			real mag = 1.0f / magnitude();
			x *= mag;
			y *= mag;
			z *= mag;
			w *= mag;
		}

		//Inline Operators
		inline real&	operator[](ui32 index)
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
				default: return x;
			}
		}

		inline const real&	operator[](ui32 index) const
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;
				default: return x;
			}
		}

		inline	void	operator=(const Vector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}


		inline	Vector4		operator+(const Vector4& v)
		{
			Vector4 result;
			result.x = x + v.x;
			result.y = y + v.y;
			result.z = z + v.z;
			result.w = w + v.w;
			return result;
		}

		inline	Vector4		operator-(const Vector4& v)
		{
			Vector4 result;
			result.x = x - v.x;
			result.y = y - v.y;
			result.z = z - v.z;
			result.w = w - v.w;
			return result;
		}

		inline	Vector4	operator*(const real& f)
		{
			Vector4 result;
			result.x = x * f;
			result.y = y * f;
			result.z = z * f;
			result.w = w * f;
			return result;
		}

		inline	Vector4		operator/(const real& f)
		{
			Vector4 result;
			result.x = x / f;
			result.y = y / f;
			result.z = z / f;
			result.w = w / f;
			return result;
		}

		inline	Vector4		operator+(const Vector4& v) const
		{
			Vector4 result;
			result.x = x + v.x;
			result.y = y + v.y;
			result.z = z + v.z;
			result.w = w + v.w;
			return result;
		}

		inline	Vector4		operator-(const Vector4& v) const
		{
			Vector4 result;
			result.x = x - v.x;
			result.y = y - v.y;
			result.z = z - v.z;
			result.w = w - v.w;
			return result;
		}

		inline	Vector4		operator*(const real& f) const
		{
			Vector4 result;
			result.x = x * f;
			result.y = y * f;
			result.z = z * f;
			result.w = w * f;
			return result;
		}

		inline	Vector4		operator/(const real& f) const
		{
			Vector4 result;
			result.x = x / f;
			result.y = y / f;
			result.z = z / f;
			result.w = w / f;
			return result;
		}

		inline	void		operator+=(const Vector4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}

		inline	void		operator-=(const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}

		inline	void		operator*=(const real& f)
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;
		}

		inline	void		operator/=(const real& f)
		{
			x /= f;
			y /= f;
			z /= f;
			w /= f;
		}


		String		toString();
		
	};
}

#endif
