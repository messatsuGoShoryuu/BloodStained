#ifndef _BS_GJK2D_H_
#define _BS_GJK2D_H_

#include"bs_Collision2D.h"

namespace bs
{
	class Shape2D;

	namespace gjk2D
	{
		///Assumes that both shapes are in the same frame of reference
		Collision2D testCollision(const Shape2D& a, const Shape2D& b);
	}
}

#endif // !_BS_GJK2D_H_