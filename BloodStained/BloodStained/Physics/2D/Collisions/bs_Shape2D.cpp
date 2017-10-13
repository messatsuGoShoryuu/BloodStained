#include "bs_Shape2D.h"
#include <Utilities/bs_arrayOperations.h>

namespace bs
{
	Shape2D::Shape2D()
		:m_vertexCount(0),
		m_center(Vector2::zero),
		m_centerOfGravity(Vector2::zero),
		m_radius(0),
		m_owner(nullptr)
	{
	}

	Shape2D::Shape2D(const Shape2D & s)
		:m_vertexCount(s.m_vertexCount),
		m_center(s.m_center),
		m_centerOfGravity(s.m_centerOfGravity),
		m_radius(s.m_radius),
		m_owner(s.m_owner)
	{
		copyArray((Vector2*)s.m_vertices, m_vertices, s.m_vertexCount);
		copyArray((Vector2*)s.m_normals, m_normals, s.m_vertexCount);
	}

	Shape2D::~Shape2D()
	{
	}

	bool Shape2D::addVertex(const Vector2 & vertex)
	{
		if (m_vertexCount >= BS_SHAPE_VERTEX_COUNT) return false;
		m_vertices[m_vertexCount] = vertex;

		if (m_vertexCount > 1)
		{
			i32 index = (i32)m_vertexCount - 1;
			index = index % m_vertexCount;
		}
		m_vertexCount++;
		return true;
	}

	bool Shape2D::addVertex(real x, real y)
	{
		if (m_vertexCount >= BS_SHAPE_VERTEX_COUNT) return false;
		m_vertices[m_vertexCount].x = x;
		m_vertices[m_vertexCount].y = y;

		m_vertexCount++;
		
		return true;
	}
	Segment2D Shape2D::getEdgeFromNormal(ui32 normalIndex) const
	{
		Segment2D result;
		result.a = m_vertices[normalIndex];
		result.b = m_vertices[(normalIndex + 1) % m_vertexCount];
		return result;
	}
	void Shape2D::calculateNormals()
	{
		if (m_vertexCount < 2) return;
		Vector2 lastFace;
		f32 cross = 0.0f;
		for (ui32 i = 0; i < m_vertexCount; i++)
		{
			ui32 lastIndex = i;
			if (i == 0) lastIndex = m_vertexCount - 1;
			else lastIndex--;
			ui32 nextIndex = (i + 1) % m_vertexCount;

			BS_ASSERT(lastIndex < m_vertexCount);
			BS_ASSERT(nextIndex < m_vertexCount);

			Vector2 lastFace = m_vertices[i] - m_vertices[lastIndex];
			Vector2 face = m_vertices[nextIndex] - m_vertices[i];
			cross = Vector2::cross(face, lastFace);
			
			real sign = math::sign(cross);

			m_normals[i] = Vector2::cross(face, sign);
			
			m_normals[i].normalize();
			lastFace = face;
		}
	}
	void Shape2D::calculateCenter()
	{
		Vector2 sum = Vector2::zero;
		for (ui32 i = 0; i < m_vertexCount; i++)
		{
			sum += m_vertices[i];
		}

		sum /= (real)m_vertexCount;

		m_center = sum;

		m_radius = 0.0f;
		
		for (ui32 i = 0; i < m_vertexCount; i++)
		{
			real radius = (m_vertices[i] - m_center).squareMagnitude();
			if (radius > m_radius) m_radius = radius;
		}

		m_radius = math::sqrt(m_radius);

		getInertiaMoment();
	}

	//Just like in box2D ;)
	real Shape2D::getInertiaMoment()
	{
		real inertia = 0.0f;

		Vector2 c = Vector2::zero;

		for (ui32 i = 0; i < m_vertexCount; i++)
		{
			Vector2 triA = m_vertices[i] - m_center;
			Vector2 triB = m_vertices[(i + 1) % m_vertexCount] - m_center;

			real sumX = triA.x * triA.x + triA.x * triB.x + triB.x * triB.x;
			real sumY = triA.y * triA.y + triA.y * triB.y + triB.y * triB.y;

			real j = Vector2::cross(triA, triB);

			real triangleArea = 0.5f * j;

			// Area weighted centroid
			c += (triA + triB) * triangleArea * 1.0f/3.0f;

			inertia +=  (0.25f * 1.0f / 3.0f) * j  * (sumX + sumY);
		}

		m_centerOfGravity = m_center + c;
		return math::abs(inertia);
	}

	Vector2 Shape2D::getSupportPoint(const Vector2 & direction) const
	{
		ui32 index = getSupportIndex(direction);
		if (index == -1) return Vector2::zero;
		return m_vertices[index];
	}

	ui32 Shape2D::getSupportIndex(const Vector2 & direction) const
	{
		real bestDistance = -BS_MAX_FLOAT;
		ui32 index = -1;

		for (ui32 i = 0; i < m_vertexCount; i++)
		{
			real dot = m_vertices[i].dot(direction);
			if (dot > bestDistance)
			{
				bestDistance = dot;
				index = i;
			}
		}
		return index;
	}
}