#ifndef _BS_PHYSICS2D_H_
#define _BS_PHYSICS2D_H_

#include "Collisions/bs_Shape2D.h"
#include "bs_Transform2D.h"

namespace bs
{
	Shape2D	makeShapeRelativeToBasis(const Transform2D& transform, const Shape2D& shape);

	Shape2D makeShapeRelativeToBasis(const Transform2D& basisTransform,
		const Transform2D& shapeTransform, 
		const Shape2D& shape);

	Vector2 makeVector2RelativeToBasis(const Transform2D& transform, const Vector2& v);

	Shape2D attachShapeToBasis(const Transform2D& transform, const Shape2D& shape);

	bool intersect(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2, Vector2& out);
}

#endif // !_BS_PHYSICS2D_H_