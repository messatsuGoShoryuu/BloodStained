#ifndef _BS_PHYSICS2D_H_
#define _BS_PHYSICS2D_H_

#include "bs_PhysicalObject2D.h"
#include "Collisions/bs_Collision2D.h"

#include <Utilities/bs_Error.h>

#include <Allocator/bs_PoolAllocator.h>
#include <Allocator/bs_StackAllocator.h>
#include <Containers/bs_Array.h>
#include <Containers/bs_Stack.h>



namespace bs
{
	Shape2D	makeShapeRelativeToBasis(const Transform2D& transform, const Shape2D& shape);

	Shape2D makeShapeRelativeToBasis(const Transform2D& basisTransform,
		const Transform2D& shapeTransform, 
		const Shape2D& shape);

	Vector2 makeVector2RelativeToBasis(const Transform2D& transform, const Vector2& v);

	Shape2D attachShapeToBasis(const Transform2D& transform, const Shape2D& shape);

	bool intersect(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2, Vector2& out);

	struct CollisionPair2D
	{
		PhysicalObject2D* a;
		PhysicalObject2D* b;
		Collision2D collision;
	};

	class PhysicsManager2D
	{
		friend class PhysicalObject2D;
	public:
		static ERROR_ID initialize();
		static ERROR_ID shutDown();

		static void update(real dt);

	public:
		static	PhysicalObject2D*	addPhysicalObject();
		static	void				removePhysicalObject(PhysicalObject2D* obj);

		static	inline	void setGravity(const Vector2& newGravity) { s_gravity = newGravity; }
		static	inline	Vector2 gravity() { return s_gravity; }
	private:
		static	Shape2D* _addShape();
		static	Body2D*	 _addBody();
		static	void	 _removeShape(Shape2D* shape);
		static	void	 _removeBody(Body2D* body);

	private :
		static	void	_collideShapes();
		static	void	_resolveCollisions();
		static	void	_correctPositions();
		static	void	_integrate(real dt);
		static  void	_syncShapes();

	private:
		static PoolAllocator<Shape2D> s_shapePool;
		static PoolAllocator<Body2D> s_bodyPool;
		static PoolAllocator<PhysicalObject2D> s_physicalObjectPool;
		static Array<PhysicalObject2D*> s_physicalObjects;

		static Array<Shape2D*> s_shapes;
		static Stack<ptrsize>  s_shapeFreeList;
		static Array<Body2D*> s_bodies;
		static Stack<ptrsize> s_bodyFreeList;

		static StackAllocator s_collisionPairs;
		static ptrsize s_collisionPairCount;
		static Vector2 s_gravity;
	};
}

#endif // !_BS_PHYSICS2D_H_