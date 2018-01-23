#include "bs_GJK2D.h"
#include "bs_Shape2D.h"
#include  <Rendering/bs_RenderManager.h>
#include <Physics/2D/bs_Physics2D.h>

#define BS_PENETRATION_CLIP_TOLERANCE 0.00005f

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
		struct SupportSegment
		{
			SupportPoint a;
			SupportPoint b;
		};

		struct PolytopeSegment
		{
			SupportSegment s;
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


			PolytopeSegment* addVertex(SupportPoint& point, PolytopeSegment* face)
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
						first->normal = getPerpTowardsOrigin(first->s.a.point, first->s.b.point);
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
					ns->normal = getPerpTowardsOrigin(ns->s.a.point, ns->s.b.point);
					ns->normal.normalize();
					count++;
					PolytopeSegment* ns2 = newSegment();
					ns->next = ns2;
					ns2->previous = ns;
					ns2->s.a = ns->s.b;
					ns2->s.b = prev->s.a;
					ns2->normal = getPerpTowardsOrigin(ns2->s.a.point, ns2->s.b.point);
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

				l->normal = getPerpTowardsOrigin(l->s.a.point, l->s.b.point);
				r->normal = getPerpTowardsOrigin(r->s.a.point, r->s.b.point);

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
				*s = {};
				count--;
			}

			PolytopeSegment* findClosestEdge(real& out)
			{
				PolytopeSegment* s = first;
				if (!s) return nullptr;
				real dot = 0.0f;
				real bestDot = BS_MAX_FLOAT;
				PolytopeSegment* result = nullptr;
				do
				{
					dot = s->s.a.point.dot(s->normal);
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
		inline	Collision2D falseCollision()
		{
			Collision2D c = {};
			return c;
		}

            
		void clip(Manifold2D& m,const Shape2D& pointShape,const Shape2D& edgeShape, ui32 pointIndex, ui32 edgeA, ui32 edgeB, real tol)
		{
			
		/*
			TODO: add more cases?
			 R         
			  \       
			   \     
			  A-----------B
			 /   \         \
			/	  P---------\----Q
		   D-----------------C

		1-	if abs((AB . PQ)) > tolerance && abs((AB . RP)) > tolerance, P is the only point.
		2-	if abs(AB . PQ) < tolerance, 
				if(AB . PQ < 0) the point closest to P between A and Q is the second point.
				else the point closest t P between B and Q is the second point.
		3-  repeat 2 for (AB . PR) 
		
		*/        

			ui32 pointCount = pointShape.vertexCount();
			ui32 edgeCount = edgeShape.vertexCount();

			if (pointCount == 0) return;

			ui32 ai = edgeA;
			ui32 bi = edgeB;
			ui32 pi = pointIndex;

			ui32 ri = pi == 0 ? pointCount - 1 : pi-1;
			ui32 qi = (pi + 1) % pointCount;


			Vector2 a = edgeShape.getVertex(ai);
			Vector2 b = edgeShape.getVertex(bi);
			
			
			Vector2 p = pointShape.getVertex(pi);
			Vector2 q = pointShape.getVertex(qi);
			Vector2 r = pointShape.getVertex(ri);

			Vector2 ab = b - a;
			Vector2 pq = q - p;
			Vector2 pr = r - p;

			

			Vector2 abNormal = ab.getNormalized();
			Vector2 pqNormal = pq.getNormalized();
			Vector2 prNormal = pr.getNormalized();

			real ab_pq = abNormal.dot(pqNormal);
			real ab_pr = abNormal.dot(prNormal);

			real pqMag = pq.magnitude();
			real prMag = pr.magnitude();

			

			bool pqPass = math::abs(ab_pq) > 1.0f - tol && math::abs(ab_pq) < 1.0f + tol;
			bool prPass = math::abs(ab_pr) > 1.0f - tol && math::abs(ab_pr) < 1.0f + tol;

			m.contact[1] = m.contact[0];

			m.contact[1].point = p;
			m.pointCount = 1;

			if (pqPass)
			{
				if (ab_pq < 0)
				{
					Vector2 pa = a - p;
					real pa_pq = pa.dot(pqNormal);
					if (pa_pq > 0 && pa_pq < pqMag)
					{
						m.contact[1].point = a;
						m.contact[1].normal = -m.contact[0].normal;
						m.contact[1].tangent = -m.contact[0].tangent;
						m.contact[1].incident = false;
					}
					else
					{
						m.contact[1].point = q;	
					}

					Vector2 pb = b - p;
					real pb_pq = pb.dot(pqNormal);
					if (pb_pq > 0 && pb_pq < pqMag)
					{
						m.contact[0].point = b;
						m.contact[0].normal = -m.contact[0].normal;
						m.contact[0].tangent = -m.contact[0].tangent;
						m.contact[0].incident = false;
					}
				}
				else
				{
					Vector2 pb = b - p;
					real pb_pq = pb.dot(pqNormal);
					if (pb_pq > 0 &&  pb_pq < pqMag)
					{
						m.contact[1].point = b;
						m.contact[1].normal = -m.contact[0].normal;
						m.contact[1].tangent = -m.contact[0].tangent;
						m.contact[1].incident = false;
					}
					else
					{
						m.contact[1].point = q;
					}

					Vector2 pa = a - p;
					real pa_pq = pa.dot(pqNormal);
					if (pa_pq > 0 && pa_pq < pqMag)
					{
						m.contact[0].point = a;
						m.contact[0].normal = -m.contact[0].normal;
						m.contact[0].tangent = -m.contact[0].tangent;
						m.contact[0].incident = false;
					}
				}
				m.pointCount = 2;
			}
			else if (prPass)
			{
				if (ab_pr < 0)
				{
					Vector2 pa = a - p;

					real pa_pr = pa.dot(prNormal);
					if (pa_pr > 0 && pa_pr < prMag)
					{
						m.contact[1].point = a;
						m.contact[1].normal = -m.contact[0].normal;
						m.contact[1].tangent = -m.contact[0].tangent;
						m.contact[1].incident = false;
					}
					else
					{
						m.contact[1].point = r;
					}

					Vector2 pb = b - p;

					real pb_pr = pb.dot(prNormal);
					if (pb_pr > 0 && pb_pr < prMag)
					{
						m.contact[0].point = b;
						m.contact[0].normal = -m.contact[0].normal;
						m.contact[0].tangent = -m.contact[0].tangent;
						m.contact[0].incident = false;
					}
				}
				else
				{
					Vector2 pb = b - p;

					real pb_pr = pb.dot(prNormal);
					if (pb_pr > 0 && pb_pr < prMag)
					{
						m.contact[1].point = b;
						m.contact[1].normal = -m.contact[0].normal;
						m.contact[1].tangent = -m.contact[0].tangent;
						m.contact[1].incident = false;
					}
					else
					{
						m.contact[1].point = r;
					}

					Vector2 pa = a - p;

					real pa_pr = pa.dot(prNormal);
					if (pa_pr > 0 && pa_pr < prMag)
					{
						m.contact[0].point = a;
						m.contact[0].normal = -m.contact[0].normal;
						m.contact[0].tangent = -m.contact[0].tangent;
						m.contact[0].incident = false;
					}
				}
				m.pointCount = 2;
			}
		}


		Manifold2D findContactByEPA(const Shape2D& a, const Shape2D& b, SupportPoint s[3])
		{
			if (s == nullptr) return Manifold2D();
			Polytope p = {};

			PolytopeSegment* ps = nullptr;
			for (ui32 i = 0; i < 3; i++)
			{
				ps = p.addVertex(s[i], ps);
			}
			ps = p.first;

			real penetration = 0.0f;
			PolytopeSegment* closest = p.findClosestEdge(penetration);
			PolytopeSegment* newClosest = closest;
			SupportPoint sp;
			
			do
			{
				if (!newClosest) return Manifold2D();
				closest = newClosest;

				SupportPoint lastsp;
				lastsp = sp;
				sp = getSupportPoint(a, b, closest->normal);

				if (sp.point != lastsp.point) p.addVertex(sp, closest);
				if (p.count >= 16) break;
				newClosest = p.findClosestEdge(penetration);

			} while (closest != newClosest);

			Vector2 a1 = a.getVertex(closest->s.a.a);
			Vector2 b1 = b.getVertex(closest->s.a.b);

			Manifold2D manifold = {};

			if (closest->s.a.b == closest->s.b.b)
			{
				manifold.contact[0].normal = closest->normal;
				manifold.contact[0].penetration = penetration;
				manifold.contact[0].point = b1;
				manifold.contact[0].incident = true;

				clip(manifold, b, a,
					closest->s.a.b,
					closest->s.a.a,
					closest->s.b.a,
					BS_PENETRATION_CLIP_TOLERANCE);
				manifold.flip = false;
				if (!manifold.contact[0].incident) manifold.flip = !manifold.flip;
			}
			else
			{

				manifold.contact[0].normal = -closest->normal;
				manifold.contact[0].penetration = penetration;
				manifold.contact[0].point = a1;
				manifold.contact[0].incident = true;

				clip(manifold, a, b,
					closest->s.a.a,
					closest->s.a.b,
					closest->s.b.b,
					BS_PENETRATION_CLIP_TOLERANCE);

				manifold.flip = true;
				if (!manifold.contact[0].incident) manifold.flip = !manifold.flip;
			}

			manifold.contact[0].tangent = Vector2::cross(1,manifold.contact[0].normal);
			manifold.contact[1].tangent = Vector2::cross(1, manifold.contact[1].normal);
			return manifold;
		}


		struct DebugTestSimplexStruct
		{
			ui32 hits;
			ui32 failCount2a;
			ui32 failCount2b;
			ui32 failCount3a;
			ui32 failCount3b;
			ui32 failCount3c;
			ui32 failCountend;
			const char* lastHit;
		};
		
		static DebugTestSimplexStruct debugStruct;

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
			debugStruct.hits++;

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
					debugStruct.failCount2a++;
					debugStruct.lastHit = "failCount2a";
				}
				else
				{
					//Need to look further.
					simplexCount--;
					direction = AO;
					debugStruct.failCount2b++;
					debugStruct.lastHit = "failCount2b";
				}
				return false;
			}
			if (simplexCount == 3)
			{

				Vector2 BA = a - b;
				Vector2 CA = a - c;


				Vector2 AB = b - a;
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
					debugStruct.failCount3a++;
					debugStruct.lastHit = "failCount3a";

					Vector2 shape[3];
					for (ui32 i = 0; i < 3; i++)shape[i] = simplex[i].point;
					return false;
				}

				dot = normAB.dot(-a);
				
				if (dot > 0)
				{
					simplexCount--;
					direction = normAB;
					debugStruct.failCount3b++;
					debugStruct.lastHit = "failCount3b";

					Vector2 shape[3];
					for (ui32 i = 0; i < 3; i++)shape[i] = simplex[i].point;
					return false;
				}

				dot = normCA.dot(-c);

				if (dot > 0)
				{
					simplexCount--;
					direction = normCA;
					debugStruct.failCount3c++;
					debugStruct.lastHit = "failCount3c";

					Vector2 shape[3];
					for (ui32 i = 0; i < 3; i++)shape[i] = simplex[i].point;
					return false;
				}

				return true;
			}
			debugStruct.failCountend++;
			return true;
		}

		Collision2D testCollision(const Shape2D & a, const Shape2D & b)
		{
			if (a.vertexCount() > BS_SHAPE_VERTEX_COUNT) return falseCollision();
			if (b.vertexCount() > BS_SHAPE_VERTEX_COUNT) return falseCollision();
			ui32 maxIterations = a.vertexCount() + b.vertexCount();

			if (maxIterations < 6) return falseCollision();
			//Initialize
			Collision2D result = {};

			SupportPoint simplexPoint = getSupportPoint(a, b, Vector2::up);
			Vector2 direction = -simplexPoint.point;
			SupportPoint simplex[3];
			simplex[0] = simplexPoint;
			
			ui32 simplexCount = 1;
			ui32 index = 1;

			debugStruct = {};
			//loop
			for(ui32 i = 0; i<maxIterations;i++)
			{
				simplexPoint = getSupportPoint(a, b, direction);

				if (simplexPoint.point.dot(direction) < 0)
				{
					return result;
				}
				simplex[index] = simplexPoint;
				
				simplexCount++;

				BS_ASSERT(simplexCount <= 3);

				if (testSimplex(simplex, simplexCount, direction, index))
				{
					result.collided = true;
					result.manifold = findContactByEPA(a, b, simplex);
					return result;
				}

				index++;
				index %= 3;
			}
			result.collided = true;
			result.manifold.pointCount = 1;
			result.breakPoint = true;
			return result;
		}
	}
}


