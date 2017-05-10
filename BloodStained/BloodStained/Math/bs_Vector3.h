#ifndef BS_VECTOR3_H
#define BS_VECTOR3_H

#include "bs_math.h"

namespace bs
{
	class Vector2;
	class Vector4;
	class String;

	class Vector3
	{
	public:
		//Default constructor.
		Vector3();

		//Construct with other types of vector.
		Vector3(const Vector2& v);
		explicit Vector3(const Vector2& v, real z);
		Vector3(const Vector4& v);

		//Construct from floats
		Vector3(real x, real y, real z);

		//Copy constructor.
		Vector3(const Vector3& v);

		//Destructor.
		~Vector3();

	public:
		//Static vectors.
		static	const Vector3 zero;
		static  const Vector3 unit;
		static	const Vector3 up;
		static	const Vector3 forward;
		static	const Vector3 right;
	
	public:
		//Members of a vector are public.
		real x;
		real y;
		real z;

	public:
		String		toString();

	public:
		//Magnitude

		inline	real	squareMagnitude() const
		{
			return x * x + y * y + z * z;
		}

		inline real		magnitude()
		{
			return math::sqrt(squareMagnitude());
		}

		inline real		magnitude() const
		{
			return math::sqrt(squareMagnitude());
		}

		//Normalisation

		inline void		normalize()
		{
			real mag = 1.0f / magnitude();
			x *= mag;
			y *= mag;
			z *= mag;
		}

		inline	Vector3 getNormalized()
		{
			Vector3 result;
			real mag = 1.0f / magnitude();
			result.x = x * mag;
			result.y = y * mag;
			result.z = z * mag;

			return result;
		}

		inline	Vector3 getNormalized() const
		{
			Vector3 result;
			real mag = 1.0f / magnitude();
			result.x = x * mag;
			result.y = y * mag;
			result.z = z * mag;

			return result;
		}

		//Cross product:

		inline Vector3 cross(const Vector3& other)
		{
			Vector3 result;
			result.x = y * other.z - z * other.y;
			result.y = z * other.x - x * other.z;
			result.z = x * other.y - y * other.x;
			return result;
		}

		inline Vector3 cross(const Vector3& other) const
		{
			Vector3 result;
			result.x = y * other.z - z * other.y;
			result.y = z * other.x - x * other.z;
			result.z = x * other.y - y * other.x;
			return result;
		}

		//Dot product

		inline real dot(const Vector3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

	public:
		//Operators
		inline real&	operator[](ui32 index)
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				default: return x;
			}
		}

		inline const	real&	operator[](ui32 index) const
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				default: return x;
			}
		}

		//Inline arithmetic operators:

		inline	void	operator=(const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		inline	Vector3		operator+(const Vector3& v)
		{
			Vector3 result;
			result.x = x + v.x;
			result.y = y + v.y;
			result.z = z + v.z;
			return result;
		}

		inline	Vector3		operator-(const Vector3& v)
		{
			Vector3 result;
			result.x = x - v.x;
			result.y = y - v.y;
			result.z = z - v.z;
			return result;
		}

		inline	Vector3		operator-()
		{
			Vector3 result;
			result.x = -x;
			result.y = -y;
			result.z = -z;
			return result;
		}

		inline	Vector3		operator*(const real& f)
		{
			Vector3 result;
			result.x = x * f;
			result.y = y * f;
			result.z = z * f;
			return result;
		}

		inline	Vector3		operator/(const real& f)
		{
			Vector3 result;
			result.x = x / f;
			result.y = y / f;
			result.z = z / f;
			return result;
		}

		inline	Vector3		operator+(const Vector3& v) const
		{
			Vector3 result;
			result.x = x + v.x;
			result.y = y + v.y;
			result.z = z + v.z;
			return result;
		}

		inline	Vector3		operator-(const Vector3& v) const
		{
			Vector3 result;
			result.x = x - v.x;
			result.y = y - v.y;
			result.z = z - v.z;
			return result;
		}

		inline	Vector3		operator-()	const
		{
			Vector3 result;
			result.x = -x;
			result.y = -y;
			result.z = -z;
			return result;
		}

		inline	Vector3		operator*(const real& f) const
		{
			Vector3 result;
			result.x = x * f;
			result.y = y * f;
			result.z = z * f;
			return result;
		}

		inline	Vector3		operator/(const real& f) const
		{
			Vector3 result;
			result.x = x / f;
			result.y = y / f;
			result.z = z / f;
			return result;
		}

		inline	void		operator+=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		inline	void		operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		inline	void		operator*=(const real& f)
		{
			x *= f;
			y *= f;
			z *= f;
		}

		inline	void		operator/=(const real& f)
		{
			x /= f;
			y /= f;
			z /= f;
		}

		

	};
}

#endif // !BS_VECTOR3_H
