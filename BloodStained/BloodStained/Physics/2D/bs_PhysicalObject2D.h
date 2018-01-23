#ifndef _BS_PHYSICALOBJECT2D_
#define _BS_PHYSICALOBJECT2D_

#include "Collisions/bs_Shape2D.h"
#include "bs_Body2D.h"
#include <Events/bs_EventManager.h>

namespace bs
{
	struct Manifold2D;
	class PhysicalObject2D
	{
		friend class PhysicsManager2D;
	public:
		PhysicalObject2D();
		PhysicalObject2D(const PhysicalObject2D& p);
		~PhysicalObject2D();

		inline Body2D* body()		const	{ return m_body; }

		inline Shape2D& shape()		{ return m_shape; }
		inline const Shape2D& shape() const { return m_shape; }
		inline Shape2D*	relativeShape() { return m_relativeShape; }
		
		template<class T>
		inline void addListener(T * item, EVENT_FUNCTION(function));

		template<class T>
		inline void removeListener(T* item, EVENT_FUNCTION(function));

		inline const bool canDispatch() const { return m_dispatcher.canDispatch(); }

	private:
		//To be only called by PhysicsManager
		void _dispatch(EVENT_ID collisionType, Manifold2D manifold);


	private:
		Shape2D		m_shape;
		Body2D*		m_body;
		Shape2D*	m_relativeShape;
		EventDispatcher m_dispatcher;
	};

	//TODO: Make PhysicalObject2D its own event handling mechanism.

	template<class T>
	inline void PhysicalObject2D::addListener(T * item, EVENT_FUNCTION(function))
	{
		//TODO: make this cache friendly!
		MemberFunction<T, void, Event>* func = EventManager::allocateFunction(item, function, EVENT_ID::COLLISION_BEGIN);

		func->setCaster(item);
		m_dispatcher.addListener(func);
	}

	template<class T>
	inline void PhysicalObject2D::removeListener(T * item, EVENT_FUNCTION(function))
	{
		MemberFunction<T, void, Event> func(function);
		func.setCaster(item);
		EventManager::deallocateFunction(m_dispatcher.removeListener(&func));
	}
}

#endif