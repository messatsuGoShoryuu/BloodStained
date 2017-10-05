#include "bs_GJK2D.h"
#include "bs_Shape2D.h"
#include  <Rendering/bs_RenderManager.h>
#include <Physics/2D/bs_Physics2D.h>


namespace bs
{
	namespace gjk2D
	{
		struct SupportPoint
		{
			ui32 a;
			ui32 b;
			Vector2 point;
		};

		struct PolytopeSegment
		{
			Segment2D s;
			Vector2 normal;
			PolytopeSegment* previous;
			PolytopeSegment* next;
			ui32 index;
		};


		inline Vector2 getPerpTowardsOrigin(const Vector2& a, const Vector2& b)
		{
			// Create the perpendicular in the direction of the oriign
			Vector2 ab = b - a;
			Vector2 ao = -a;

			real scalar = Vector2::cross(ab, ao);

			return Vector2::cross(scalar, ab);
		}

		inline Vector2 getPerpTowardsOutside(const Vector2& old, const Vector2& current, const Vector2& future)
		{
			Vector2 ab = current - old;
			Vector2 bc = future - current;

			real sign = Vector2::cross(bc, ab);
			sign = math::sign(sign);

			return Vector2::cross(bc, sign);
		}


		class Polytope
		{
		public:
			Polytope():
				count(0),
				freeTop(0)
			{
				for (ui32 i = 0; i < BS_SHAPE_VERTEX_COUNT * 2; i++) freeList[i] = i;
			}


			PolytopeSegment* addVertex(Vector2& point, PolytopeSegment* face)
			{
				if (count == 0)
				{
					if (face == nullptr)
					{
						first = newSegment();
						first->s.a = point;
					}
					else
					{
						first->s.b = point;
						first->normal = getPerpTowardsOrigin(first->s.a, first->s.b);
						first->normal.normalize();
						count++;
					}
					return first;
				}
				else if(count <3)
				{
					PolytopeSegment* prev = first;
					PolytopeSegment* ns = newSegment();
					prev->next = ns;
					ns->previous = prev;
					ns->s.a = prev->s.b;
					ns->s.b = point;
					ns->normal = getPerpTowardsOrigin(ns->s.a, ns->s.b);
					ns->normal.normalize();
					count++;
					PolytopeSegment* ns2 = newSegment();
					ns->next = ns2;
					ns2->previous = ns;
					ns2->s.a = ns->s.b;
					ns2->s.b = prev->s.a;
					ns2->normal = getPerpTowardsOrigin(ns2->s.a, ns2->s.b);
					ns2->normal.normalize();
					ns2->next = first;
					first->previous = ns2;
					count++;
					return ns;
				}


				PolytopeSegment* l = newSegment();
				PolytopeSegment* r = newSegment();

				l->previous = face->previous;
				if (face->previous)
				{
					l->previous->next = l;
				}
				else first = l;
				l->next = r;
				r->previous = l;
				r->next = face->next;
				if (face->next)
				{
					r->next->previous = r;
				}

				l->s.a = face->s.a;
				l->s.b = point;
				r->s.a = point;
				r->s.b = face->s.b;

				l->normal = getPerpTowardsOrigin(l->s.a, l->s.b);
				r->normal = getPerpTowardsOrigin(r->s.a, r->s.b);

				l->normal.normalize();
				r->normal.normalize();

				count+=2;

				if (face == first) first = l;

				removeSegment(face,false);

				return l;
			}

			PolytopeSegment* newSegment()
			{
				ui32 index = freeList[freeTop++];
				segments[index] = {};
				segments[index].index = index;
				return &segments[index];
			}

			void removeSegment(PolytopeSegment* s, bool disconnect)
			{
				if (freeTop == 0) return;
				if (disconnect)
				{
					if (s->previous)
					{
						s->previous->next = s->next;
					}
					else first = s->next;
					if (s->next)
					{
						s->next->previous = s->previous;
					}
				}
				freeList[--freeTop] = s->index;
				count--;
			}

			PolytopeSegment* findClosestEdge(real& out)
			{
				PolytopeSegment* s = first;
				real dot = 0.0f;
				real bestDot = BS_MAX_FLOAT;
				PolytopeSegment* result = nullptr;
				do
				{
					dot = s->s.a.dot(s->normal);
					if (dot < bestDot)
					{
						bestDot = dot;
						result = s;
					}
					s = s->next;
				} while (s != first);

				out = bestDot;
				return  result;
			}

			

			PolytopeSegment segments[BS_SHAPE_VERTEX_COUNT * 2];
			PolytopeSegment* first;
			ui32 freeList[BS_SHAPE_VERTEX_COUNT * 2];
			ui32 freeTop;
			ui32 count;
		};

		//Finds the furthest point in the direction of "direction" vector along the Minkowski
		//sum (difference) of shapes a and b.
		inline	SupportPoint getSupportPoint(const Shape2D& a, const Shape2D& b, Vector2 direction)
		{
			direction.normalize();
			SupportPoint result;
			result.a = a.getSupportIndex(direction);
			result.b = b.getSupportIndex(-direction);
			result.point = a.getVertex(result.a) - b.getVertex(result.b);
			return result;
		}

		//ease of use
		inline	Collision falseCollision()
		{
			Collision c = {};
			return c;
		}

		


		Contact findContactByEPA(const Shape2D& a, const Shape2D& b, SupportPoint s[3])
		{
			Polytope p;

			PolytopeSegment* ps = nullptr;
			for (ui32 i = 0; i < 3; i++)
			{
				ps = p.addVertex(s[i].point, ps);
			}
			ps = p.first;

			real penetration = 0.0f;
			PolytopeSegment* closest = p.findClosestEdge(penetration);
			PolytopeSegment* newClosest = closest;
			SupportPoint sp;
			
			do
			{
				closest = newClosest;

				SupportPoint lastsp;
				lastsp = sp;
				sp = getSupportPoint(a, b, closest->normal);

				if (sp.point != lastsp.point) p.addVertex(sp.point, closest);
				newClosest = p.findClosestEdge(penetration);

			} while (closest != newClosest);
			
			Contact contact = {};	
			contact.mtd[0].normal = closest->normal;
			contact.mtd[0].penetration = penetration;
			contact.point[0] = a.getVertex(sp.a);
			contact.point[1] = b.getVertex(sp.b);
			return contact;
		}

		
		/*
		simplex:		Simplex containing 3 Miknowski points
		simplexCount:	How many points the simplex has
		direction:		Direction for the soon to be new support point
		index:			Index of the last added point

		Returns true if a simplex point contains origin (means there is collision)
		*/
		bool testSimplex(SupportPoint simplex[3], ui32& simplexCount, 
			Vector2& direction, ui32 index)
		{
			if (simplexCount == 3)
			{
				int j = 12;
			}
			//Helper variables
			ui32 nextIndex = index == 0 ? 2 : index - 1;
			ui32 prevIndex = nextIndex == 0 ? 2 : nextIndex - 1;
			

			Vector2 c = simplex[prevIndex].point;
			Vector2 b = simplex[nextIndex].point;
			Vector2 a = simplex[index].point;

			Vector2 AO = -a;

			if (simplexCount == 2)
			{
				real dot = b.dot(AO);
				if (dot > 0)
				{
					direction = getPerpTowardsOrigin(a, b);
				}
				else
				{
					//Need to look further.
					simplexCount--;
					direction = AO;
				}
				return false;
			}
			if (simplexCount == 3)
			{
				Vector2 BA = a - b;
				Vector2 CA = a - c;
				Vector2 BC = c - b;

				Vector2 normAB = getPerpTowardsOutside(c, a, b);
				Vector2 normBC = getPerpTowardsOutside(a, b, c);
				Vector2 normCA = getPerpTowardsOutside(b, c, a);


				real dot;

				dot = normBC.dot(-b);
				
				if (dot > 0)
				{
					simplexCount--;
					direction = normBC;
					return false;
				}

				dot = normAB.dot(-a);
				
				if (dot > 0)
				{
					simplexCount--;
					direction = normAB;
					return false;
				}

				dot = normCA.dot(-c);

				if (dot > 0)
				{
					simplexCount--;
					direction = normCA;
					return false;
				}

				Vector2 shape[3];
				shape[0] = simplex[0].point;
				shape[1] = simplex[1].point;
				shape[2] = simplex[2].point;

				return true;
			}
			return false;
		}

		Collision testCollision(const Shape2D & a, const Shape2D & b)
		{
			ui32 maxIterations = a.vertexCount() + b.vertexCount();

			if (maxIterations < 6) return falseCollision();
			//Initialize
			Collision result = {};

			SupportPoint simplexPoint = getSupportPoint(a, b, - (a.center() - b.center()));
			Vector2 direction = -simplexPoint.point;
			SupportPoint simplex[3];
			simplex[0] = simplexPoint;
			
			ui32 simplexCount = 1;
			ui32 index = 1;
			
			
			maxIterations *= 3;
			//loop
			for(int i = 0; i<maxIterations;i++)
			{
				simplexPoint = getSupportPoint(a, b, direction);

				if (simplexPoint.point.dot(direction) < 0)
				{
					result.collided = false;
					result.contact.point[0] = simplex[index].point;
					result.contact.point[1] = simplex[(index + 1) % 3].point;
					for (ui32 j = 0; j < 3; j++)
					{
						result.simplex[j] = simplex[j].point;
						int newIndex = j == 0 ? 2 : j - 1;
						Vector2 previousface = simplex[newIndex].point;
						Vector2 face = simplex[(j + 1) % 3].point;
						result.simplexNormals[j] = getPerpTowardsOutside(previousface, face,simplex[j].point);
					}
					
					return result;
				}
				simplex[index] = simplexPoint;
				
				simplexCount++;

				BS_ASSERT(simplexCount <= 3);

				if (testSimplex(simplex, simplexCount, direction, index))
				{
					result.collided = true;

					result.contact = findContactByEPA(a, b, simplex);
					RenderManager::drawDebugLine(result.contact.point[0],
						result.contact.point[0] + result.contact.mtd[0].normal 
						* result.contact.mtd[0].penetration,ColorRGBAf::blue);
					RenderManager::drawDebugLine(result.contact.point[1], 
						result.contact.point[1] + result.contact.mtd[0].normal 
						* result.contact.mtd[0].penetration, ColorRGBAf::red);
					result.contact.point[0] = simplex[index].point;
					result.contact.point[1] = simplex[(index + 1) % 3].point;
					
					for (ui32 j = 0; j < 3; j++)
					{
						result.simplex[j] = simplex[j].point;
						int newIndex = j == 0 ? 2 : j - 1;
						Vector2 previousface = simplex[newIndex].point;
						Vector2 face = simplex[(j + 1) % 3].point;
						result.simplexNormals[j] = getPerpTowardsOutside(previousface, face, simplex[j].point);
					}
					return result;
				}

				index++;
				index %= 3;
			}


			{
				result.collided = false;
				result.contact.point[0] = simplex[index].point;
				result.contact.point[1] = simplex[(index + 1) % 3].point;
				for (ui32 j = 0; j < 3; j++)
				{
					result.simplex[j] = simplex[j].point;
					int newIndex = j == 0 ? 2 : j - 1;
					Vector2 previousface = simplex[newIndex].point;
					Vector2 face = simplex[(j + 1) % 3].point;
					result.simplexNormals[j] = getPerpTowardsOutside(previousface, face, simplex[j].point);
				}
				return result;
			}
		}

	}
	
}


