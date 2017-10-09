#ifndef _BS_PHYSICALOBJECT2D_
#define _BS_PHYSICALOBJECT2D_

#include "Collisions/bs_Shape2D.h"
#include "bs_Body2D.h"

namespace bs
{
	class PhysicalObject2D
	{
		friend class PhysicsManager2D;
	public:

		inline Body2D* body()		const	{ return m_body; }

		inline Shape2D& shape()		{ return m_shape; }
		inline const Shape2D& shape() const { return m_shape; }
		inline const Shape2D*	relativeShape() const { return m_relativeShape; }

	private:
		Shape2D		m_shape;
		Body2D*		m_body;
		Shape2D*	m_relativeShape;
	};
}

#endif