#ifndef _BS_GJK2D_H_
#define _BS_GJK2D_H_

#include <Math/bs_Vector.h>

namespace bs
{
	class Shape2D;

	

	namespace gjk2D
	{
		

		struct MTD
		{
			Vector2 normal;
			real penetration;
		};

		struct Contact
		{
			Vector2 point[2];
			MTD mtd[2];
			ui32 pointCount;
		};

		struct Collision
		{
			Contact contact;
			bool collided;

			Vector2 simplex[3];
			Vector2 simplexNormals[3];
		};

		///Assumes that both shapes are in the same frame of reference
		Collision testCollision(const Shape2D& a, const Shape2D& b);
		

	}
}

#endif // !_BS_GJK2D_H_