#include "bs_PhysicalObject2D.h"

#include "Collisions/bs_Collision2D.h"

namespace bs
{
	/*
			m_Shape2D		m_shape;
	Body2D*		m_body;
	Shape2D*	m_relativeShape;
	EventDispatcher m_dispatcher;
	*/
	PhysicalObject2D::PhysicalObject2D():
		m_body(nullptr),
		m_relativeShape(nullptr)
	{
	}

	PhysicalObject2D::PhysicalObject2D(const PhysicalObject2D & p):
		m_body(p.m_body),
		m_shape(p.m_shape),
		m_relativeShape(p.m_relativeShape),
		m_dispatcher(p.m_dispatcher)
	{
	}

	PhysicalObject2D::~PhysicalObject2D()
	{
		
	}

	void PhysicalObject2D::_dispatch(EVENT_ID collisionType, Manifold2D manifold)
	{
		Event e;
		e.data = &manifold;
		e.id = collisionType;
		m_dispatcher.dispatch(e);
	}
}
