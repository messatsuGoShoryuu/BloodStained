#ifndef BS_QUATERNION_H
#define BS_QUATERNION_H

#include "../Utilities/bs_types.h"
#include "bs_math.h"

namespace bs
{
	class Vector3;
	class Vector2;
	class Matrix4x4;
	class String;

	class Quaternion
	{
	public:
		//Default constructor.
		Quaternion();

		//Parameter constructors
		/*
		**@param v Directly copy values to x, y, z. w is considered 1.
		*/
		Quaternion(const Vector3& v);

		Quaternion(real x, real y, real z, real w);

		/*
		**@param axis 3D normal in world space
		**@param angle angle around the axis.
		*/
		Quaternion(const Vector3& axis, real angle);

		//Copy constrcutor.
		Quaternion(const Quaternion& q);

		~Quaternion();

		static	const Quaternion identity;

		//This quaternion becomes a representation of the rotation about axis by angle.
		void	angleAxis(const Vector3& angle, real axis);

		//Create a rotation matrix from this quaternion.
		void	toRotationMatrix(Matrix4x4& out);

		//Return the vector part of the quaternion.
		Vector3	toVector3();
		Vector3	toVector3() const;

		//Rotates a vector by this quaternion
		Vector3 operator*(const Vector3& vector);
		Vector3 operator*(const Vector3& vector) const;

		//Converts this to eulerAngles.
		Vector3 toEuler();

		//Converts from euler Angles to this
		void	fromEuler(const Vector3& euler);

		inline	void conjugate(){ x *= -1.0f; y *= -1.0f; z *= -1.0f; }
		
		inline	Quaternion	getConjugate()
		{
			Quaternion result(-x, -y, -z, w);
			return result;
		}

		inline	Quaternion	getConjugate() const
		{
			Quaternion result(-x, -y, -z, w);
			return result;
		}

		inline	real	squareMagnitude()
		{
			return x * x + y * y + z * z + w * w;
		}

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

		inline	bool	isNormalized()
		{
			real mag2 = squareMagnitude();
			if (mag2 > 0.99999f && mag2 < 1.0001f) return true;
			return false;
		}

		inline	bool	isNormalized() const
		{
			real mag2 = squareMagnitude();
			if (mag2 > 0.99999f && mag2 < 1.0001f) return true;
			return false;
		}

		inline void		normalize()
		{
			if (isNormalized()) return;
			real mag = 1.0f / magnitude();
			x *= mag;
			y *= mag;
			z *= mag;
			w *= mag;
		}

		inline	Quaternion getNormalized()
		{
			Quaternion result;

			real mag = 1.0f / magnitude();
			result.x = x * mag;
			result.y = y * mag;
			result.z = z * mag;
			result.w = w * mag;

			return result;
		}

		inline	Quaternion getNormalized()	const
		{
			Quaternion result;

			real mag = 1.0f / magnitude();
			result.x = x * mag;
			result.y = y * mag;
			result.z = z * mag;
			result.w = w * mag;

			return result;
		}

		String	toString();

	public:
		real x;
		real y;
		real z;
		real w;

	public:

		//Operators:
		inline	Quaternion	operator*(const Quaternion& other)
		{
			Quaternion result;
			result.w = w * other.w - x * other.x - y * other.y - z * other.z;
			result.x = w * other.x + x * other.w + y * other.z - z * other.y;
			result.y = w * other.y - x * other.z + y * other.w + z * other.x;
			result.z = w * other.z + x * other.y - y * other.x + z * other.w;

			return result;
		}

		inline Quaternion operator*(const Quaternion& other) const
		{
			Quaternion result;
			result.w = w * other.w - x * other.x - y * other.y - z * other.z;
			result.x = w * other.x + x * other.w + y * other.z - z * other.y;
			result.y = w * other.y - x * other.z + y * other.w + z * other.x;
			result.z = w * other.z + x * other.y - y * other.x + z * other.w;

			return result;
		}

		inline void operator*= (const Quaternion& other)
		{
			SELF = SELF * other;
		}

		inline	Quaternion operator*(const real scalar)
		{
			Quaternion result;
			result.x = x * scalar;
			result.y = y * scalar;
			result.z = z * scalar;
			result.w = w * scalar;

			return result;
		}

		inline	Quaternion operator*(const real scalar) const
		{
			Quaternion result;
			result.x = x * scalar;
			result.y = y * scalar;
			result.z = z * scalar;
			result.w = w * scalar;

			return result;
		}

		inline void		operator*=(const real scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
		}

		inline	Quaternion	operator+(const Quaternion& other)
		{
			Quaternion result;
			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z + other.z;
			result.w = w + other.w;

			return result;
		}

		inline	Quaternion	operator+(const Quaternion& other) const
		{
			Quaternion result;
			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z + other.z;
			result.w = w + other.w;

			return result;
		}

		inline	Quaternion	operator-(const Quaternion& other)
		{
			Quaternion result;
			result.x = x - other.x;
			result.y = y - other.y;
			result.z = z - other.z;
			result.w = w - other.w;

			return result;
		}

		inline	Quaternion	operator-(const Quaternion& other) const
		{
			Quaternion result;
			result.x = x - other.x;
			result.y = y - other.y;
			result.z = z - other.z;
			result.w = w - other.w;

			return result;
		}

		inline	Quaternion	operator-()
		{
			Quaternion result;
			result.x = -x;
			result.y = -y;
			result.z = -z;
			result.w = -w;

			return result;
		}

		inline	Quaternion	operator-() const
		{
			Quaternion result;
			result.x = -x;
			result.y = -y;
			result.z = -z;
			result.w = -w;

			return result;
		}

		inline	void	operator-=(const Quaternion& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
		}

		inline	void	operator+=(const Quaternion& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
		}

		inline void operator=(const Quaternion& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}
	
	};
}
#endif // !BS_QUATERNION_H
