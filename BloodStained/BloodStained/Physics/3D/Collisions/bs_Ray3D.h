#ifndef BS_RAY3D_H
#define BS_RAY3D_H
#include "../../../Math/bs_Vector.h"

namespace bs
{
	struct Ray3D
	{
		Vector3	origin;
		Vector3	normal;
	};

	struct Plane;

	Vector3	hitTest3D(const Ray3D& ray, const Plane& p);
}
#endif // !BS_RAY3D_H
