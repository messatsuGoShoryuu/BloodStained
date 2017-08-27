#include "bs_Quaternion.h"
#include "bs_Matrix4x4.h"
#include "../Utilities/bs_String.h"

namespace bs
{
	const	Quaternion Quaternion::identity(0.0, 0.0, 0.0, 1.0);

	Quaternion::Quaternion()
		:x(1.0), y(1.0), z(1.0), w(1.0)
	{

	}

	Quaternion::Quaternion(real x, real y, real z, real w)
		: x(x), y(y), z(z), w(w)
	{
		normalize();
	}

	Quaternion::Quaternion(const Vector3& v)
		: x(v.x), y(v.y), z(v.z), w(0)
	{

	}

	Quaternion::Quaternion(const Vector3& axis, real angle)
	{
		angleAxis(axis, angle);
	}

	Quaternion::Quaternion(const Quaternion& q)
		: x(q.x), y(q.y), z(q.z), w(q.w)
	{

	}

	Quaternion::~Quaternion()
	{

	}

	void	Quaternion::angleAxis(const Vector3& axis, real angle)
	{
		Vector3 a = axis.getNormalized();

		angle /= 2.0f;

		real sin = math::sin(angle);

		x = a.x * sin;
		y = a.y * sin;
		z = a.z * sin;
		w = math::cos(angle);

		normalize();
	}

	Vector3		Quaternion::toVector3()
	{
		return Vector3(x, y, z);
	}

	Vector3		Quaternion::toVector3() const
	{
		return Vector3(x, y, z);
	}

	Vector3		Quaternion::operator*(const Vector3& v)
	{
		Quaternion c = getConjugate();
		Quaternion qv(v);
		Quaternion r = getNormalized() * qv;
		r = r * c.getNormalized();
		return r.toVector3();
	}

	Vector3		Quaternion::operator*(const Vector3& v) const
	{
		Quaternion c = getConjugate();
		Quaternion qv(v);
		Quaternion r = getNormalized() * qv;
		r = r * c.getNormalized();
		return r.toVector3();
	}

	Vector3		Quaternion::toEuler()
	{
		//Pre-multiply stuff
		real x2 = x*x;
		real y2 = y*y;
		real z2 = z*z;
		real w2 = w*w;

		real xy = x * y;
		real xz = x * z;
		real xw = x * w;

		real yz = y * z;
		real yw = y * w;

		real zw = z * w;

		real t0 = 2.0 * (xw + xz);
		real t1 = 1.0 - 2.0 * (x2 + y2);

		real t2 = yw - xz;
		t2 = math::clamp(t2, (real)-1.0, (real)1.0);

		real t3 = 2.0 * (zw - xy);
		real t4 = 1.0 - 2.0 * (y2 + z2);

		return Vector3(math::atan2(t0, t1), math::sin(t2), math::atan2(t3, t4));
	}

	void	Quaternion::fromEuler(const Vector3& euler)
	{
		real cx = math::cos(euler.x) / 2.0;
		real cy = math::cos(euler.y) / 2.0;
		real cz = math::cos(euler.z) / 2.0;

		real sx = math::sin(euler.x) / 2.0;
		real sy = math::sin(euler.y) / 2.0;
		real sz = math::sin(euler.z) / 2.0;

		x = cx * cy * cz + sx * sy * sz;
		y = sx * cy * cz - cx * sy * sz;
		z = cx * sy * cz + sx * cy * sz;
		w = cx * cy * sz - sx * sy * cz;
	}


	void	Quaternion::toRotationMatrix(Matrix4x4& out)
	{
		//Pre-multiply stuff
		real x2 = x*x;
		real y2 = y*y;
		real z2 = z*z;
		real w2 = w*w;

		real xy = x * y;
		real xz = x * z;
		real xw = x * w;

		real yz = y * z;
		real yw = y * w;

		real zw = z * w;

		out[0][0] = 1.0 - 1.0 * y2 - 2.0 * z2;	out[1][0] = 2.0 * xy - 2.0 * zw;		out[2][0] = 2.0 * xz + 2.0 * yw;
		out[0][1] = 2.0 * xy + 2.0 * zw;		out[1][1] = 1 - 2.0 * x2 - 2.0 * z2;	out[2][1] = 2.0 * yz - 2.0 * xw;
		out[0][2] = 2.0 * xy + 2.0 * yw;		out[1][2] = 2.0 * yz + 2.0 * xw;		out[2][2] = 1.0 - 2.0 * x2 - 2.0 * y2;
	}

	String	Quaternion::toString()
	{
		String result = "X = ";
		result = result + x + ", Y = " + y + ", Z = " + z + ", W = " + w;
		return result;
	}
}