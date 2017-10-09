#ifndef _BS_COLLISION2D_H_
#define _BS_COLLISION2D_H_

#include <Math/bs_Vector.h>

namespace bs
{
	struct Contact2D
	{
		Vector2 normal;
		Vector2 tangent;
		real penetration;
	};

	struct Manifold2D
	{
		Vector2 point[2];
		Contact2D contact[2];
		ui32 pointCount;
		bool flip;
	};

	struct Collision2D
	{
		Manifold2D manifold;
		bool collided;
		bool breakPoint;
	};
}
#endif // !_BS_COLLISION2D_H_