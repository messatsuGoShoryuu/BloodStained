#include "bs_Physics2D.h"
#include "Collisions/bs_GJK2D.h"

#include <Rendering/bs_RenderManager.h>

#define BS_DEBUG_PHYSICS

namespace bs
{
	PoolAllocator<Shape2D>			PhysicsManager2D::s_shapePool;
	PoolAllocator<Body2D>			PhysicsManager2D::s_bodyPool;
	PoolAllocator<PhysicalObject2D> PhysicsManager2D::s_physicalObjectPool;
	Array<PhysicalObject2D*>			PhysicsManager2D::s_physicalObjects;

	Array<Shape2D*>		PhysicsManager2D::s_shapes;
	Stack<ptrsize>		PhysicsManager2D::s_shapeFreeList;
	Array<Body2D*>		PhysicsManager2D::s_bodies;
	Stack<ptrsize>		PhysicsManager2D::s_bodyFreeList;
	StackAllocator		PhysicsManager2D::s_collisionPairs;
	ptrsize				PhysicsManager2D::s_collisionPairCount;
	Vector2				PhysicsManager2D::s_gravity;

	ERROR_ID PhysicsManager2D::initialize()
	{
		s_collisionPairCount = 0;
		s_collisionPairs = StackAllocator(64 * BS_MEGABYTE, true);
		s_collisionPairs.initialize();
		s_shapePool = PoolAllocator<Shape2D>(1024);
		s_bodyPool = PoolAllocator<Body2D>(1024);
		s_physicalObjectPool = PoolAllocator<PhysicalObject2D>(1024);
		s_gravity = -Vector2::up * 2.0f;

		return ERROR_ID();
	}
	ERROR_ID PhysicsManager2D::shutDown()
	{
		return ERROR_ID();
	}
	void PhysicsManager2D::update(real dt)
	{
		_integrate(dt);
		_syncShapes();
		_collideShapes();
		_resolveCollisions(dt);
		_correctPositions();
		_syncShapes();
#ifdef BS_DEBUG_PHYSICS
		ptrsize n = s_shapes.count();
		for (ui32 i = 0; i < n; i++)
		{
			RenderManager::drawDebugShape(s_shapes[i]->getVertices(), s_shapes[i]->vertexCount(), ColorRGBAf::black);
			RenderManager::drawDebugCircle(s_shapes[i]->centerOfGravity(), 0.01f, 32,

				ColorRGBAf::black);
		}
#endif
	}

	PhysicalObject2D * PhysicsManager2D::addPhysicalObject()
	{
		PhysicalObject2D* p = s_physicalObjectPool.allocate();
		s_physicalObjects.add(p);
		p->m_body = _addBody();
		p->m_relativeShape = _addShape();

		p->m_relativeShape->setOwner(p);
		p->m_body->setOwner(p);

		return p;
	}

	void PhysicsManager2D::removePhysicalObject(PhysicalObject2D * obj)
	{
		_removeBody(obj->m_body);
		_removeShape(obj->m_relativeShape);

		s_physicalObjects.remove(obj);
		s_physicalObjectPool.deallocate(obj);
	}

	Shape2D * PhysicsManager2D::_addShape()
	{
		Shape2D* s = s_shapePool.allocate();
		s_shapes.add(s);
		return s;
	}

	Body2D * PhysicsManager2D::_addBody()
	{
		Body2D* b = s_bodyPool.allocate();
		s_bodies.add(b);
		return b;
	}

	void PhysicsManager2D::_removeShape(Shape2D * shape)
	{
		s_shapes.remove(shape);
		s_shapePool.deallocate(shape);
	}

	void PhysicsManager2D::_removeBody(Body2D * body)
	{
		s_bodies.remove(body);
		s_bodyPool.deallocate(body);
	}

	void PhysicsManager2D::_collideShapes()
	{
		ptrsize countB = s_shapes.count();
		if (countB == 0) return;
		ptrsize countA = countB - 1;
		s_collisionPairs.deallocateWhole();
		s_collisionPairCount = 0;

		for (ptrsize a = 0; a < countA; a++)
		{
			for (ptrsize b = a+1; b < countB; b++)
			{
				Collision2D col = gjk2D::testCollision(*s_shapes[a], *s_shapes[b]);

				if (col.collided)
				{
					CollisionPair2D* p = (CollisionPair2D*)s_collisionPairs.getFrame();

					s_collisionPairs.allocate(sizeof(CollisionPair2D), alignof(CollisionPair2D));
					s_collisionPairCount++;
					p->r = (PhysicalObject2D*)s_shapes[a]->owner();
					p->i = (PhysicalObject2D*)s_shapes[b]->owner();

					p->collision = col;
					RenderManager::drawDebugLine(p->collision.manifold.contact[0].point, p->collision.manifold.contact[0].point + p->collision.manifold.contact[0].normal * 3, ColorRGBAf::green);
					RenderManager::drawDebugLine(p->collision.manifold.contact[1].point, p->collision.manifold.contact[1].point + p->collision.manifold.contact[1].normal * 3, ColorRGBAf::green);
				}
			}
		}
	}

	void PhysicsManager2D::_resolveCollisions(real dt)
	{
		ptrsize n = s_collisionPairCount;
		for (ptrsize k = 0; k < n; k++)
		{
			CollisionPair2D* pair = (CollisionPair2D*)s_collisionPairs.base();
			pair += k;

			ptrsize pointCount = pair->collision.manifold.pointCount;

			if (pair->collision.collided)
			{
				bool flip = pair->collision.manifold.flip;

				Body2D* ref = flip ? pair->i->body() : pair->r->body();
				Body2D* inc = flip ? pair->r->body() : pair->i->body();


				for (ptrsize i = 0; i < pair->collision.manifold.pointCount; i++)
				{

					Vector2 n = pair->collision.manifold.contact[i].normal;

					Vector2 posRef = pair->collision.manifold.contact[i].point - ref->transform().position();
					Vector2 posInc = pair->collision.manifold.contact[i].point - inc->transform().position();

					Vector2 vRef = ref->velocity();
					Vector2 vInc = inc->velocity();

					real iRef = ref->inertia();
					real iInc = inc->inertia();

					iRef = iRef == 0.0f ? 0.0f : 1.0f / iRef;
					iInc = iInc == 0.0f ? 0.0f : 1.0f / iInc;

					real wRef = ref->angularVelocity();
					real wInc = inc->angularVelocity();

					Vector2 relV = vInc + Vector2::cross(-wInc, posInc) - vRef - Vector2::cross(-wRef, posRef);
					real contactV = relV.dot(n);

					real e = 0.0f;
					real impulseScalar = -(1.0f - e) * contactV;
					impulseScalar /= (real)pair->collision.manifold.pointCount;
					real refXn = Vector2::cross(posRef, n);
					real incXn = Vector2::cross(posInc, n);
					real divisor = 1.0f + refXn * refXn * iRef + incXn * incXn * iInc;
					impulseScalar /= divisor;

					{
						Vector2 impulse = n * impulseScalar;
						vRef -= impulse;
						vInc += impulse;

						wRef -= iRef * Vector2::cross(posRef, impulse);
						wInc += iInc * Vector2::cross(posInc, impulse);

						if (ref->inertia() > 0.0f)
						{
							ref->setAngularVelocity(wRef);
							ref->setVelocity(vRef);
						}

						if (inc->inertia() > 0.0f)
						{
							inc->setAngularVelocity(wInc);
							inc->setVelocity(vInc);
						}
					}
				}
			}
		}
	}

	void PhysicsManager2D::_correctPositions()
	{
		ptrsize n = s_collisionPairCount;
		for (ptrsize k = 0; k < n; k++)
		{
			CollisionPair2D* pair = (CollisionPair2D*)s_collisionPairs.base() + k;

			if (pair->collision.collided)
			{
				bool flip = pair->collision.manifold.flip;

				Body2D* a = flip ? pair->i->body() : pair->r->body();
				Body2D* b = flip ? pair->r->body() : pair->i->body();

				bool inverse = pair->collision.manifold.contact[0].normal == -pair->collision.manifold.contact[1].normal;
				real p = pair->collision.manifold.contact[0].penetration;
				real c = (real)pair->collision.manifold.pointCount;

				for (int i = 0; i < pair->collision.manifold.pointCount; i++)
				{

					real coef = math::maximum(p - 0.000005f, 0.0f);
					Vector2 correction = pair->collision.manifold.contact[i].normal * (coef * 1.0f / c);
					real scalar = 1.0f;
					if (i == 1 && inverse)scalar *= -1.0f;

					//TODO: add mass and calculate this correctly
					if (a->inertia() > 0.0f) a->transform().translate(-correction * scalar);
					if (b->inertia() > 0.0f) b->transform().translate(correction * scalar);

				}
			}
		}
	}
	void PhysicsManager2D::_integrate(real dt)
	{
		ptrsize count = s_bodies.count();

		for (ptrsize i = 0; i < count; i++)
		{
			s_bodies[i]->addAcceleration(s_gravity * s_bodies[i]->gravityScale() * dt);
			s_bodies[i]->integrate(dt);
		}
	}

	void PhysicsManager2D::_syncShapes()
	{
		ptrsize count = s_physicalObjects.count();
		for (ptrsize i = 0; i < count; i++)
		{
			PhysicalObject2D* p = s_physicalObjects[i];
			*p->m_relativeShape =
				attachShapeToBasis(p->m_body->transform(), p->m_shape);
			p->m_relativeShape->setOwner(p);
			p->m_body->setOwner(p);
		}
	}
}
