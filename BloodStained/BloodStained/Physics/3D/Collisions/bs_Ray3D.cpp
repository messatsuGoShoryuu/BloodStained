#include"bs_Ray3D.h"
#include "bs_Primitives.h"



namespace bs
{
	Vector3	hitTest(const Ray3D& ray, const Plane& plane)
	{
		real dotRay = ray.origin.dot(plane.normal);
		real dotPlane = -plane.point.dot(plane.normal);
		real dotNormal = ray.normal.dot(plane.normal);

		real scalar = -(dotRay + dotPlane) / dotNormal;

		return ray.origin + ray.normal * scalar;
	}
}