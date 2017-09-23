#include "bs_Shape2D.h"
#include <Utilities/bs_arrayOperations.h>

namespace bs
{
	Shape2D::Shape2D()
		:m_vertexCount(0),
		m_center(Vector2::zero)
	{
	}

	Shape2D::Shape2D(const Shape2D & s)
		:m_vertexCount(s.m_vertexCount),
		m_center(s.m_center)
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
	}
}