#include "bs_Line.h"


namespace bs
{
	Line3D::Line3D()
		:m_thickness(0.1)
	{

	}

	Line3D::Line3D(const Line3D& l)
		:m_thickness(l.m_thickness),
		m_points(l.m_points),
		m_vertices(l.m_vertices)
	{

	}

	Line3D::~Line3D()
	{

	}

	void Line3D::_generateVerticesFromPoints()
	{
		real vertexCount = m_points.count() * 6;
		if (m_vertices.count() != vertexCount) m_vertices.resize(vertexCount);

		ui32 count = m_points.count() - 1;
		if (count < 1) return;

		real  halfWidth = m_thickness / 2.0f;

		for (ui32 i = 0; i < count; i++)
		{
			Vector3 shaft = m_points[i + 1] - m_points[i];
			Vector3 perp = shaft;
			perp.y = -perp.y;
			perp.normalize();
			perp *= halfWidth;

			ui32 offset = i*vertexCount;
			ui32 tl = offset;
			ui32 bl = offset + 1;
			ui32 br = offset + 2;
			ui32 br2 = offset + 3;
			ui32 tr = offset + 4;
			ui32 tl2 = offset + 5;

			m_vertices[tl]	=	m_points[i] + perp;
			m_vertices[tr] = m_points[i] - perp;
			m_vertices[br] = m_points[i + 1] - perp;
			m_vertices[bl] = m_points[i + 1] + perp;
			m_vertices[tl2] = m_vertices[tl];
			m_vertices[br2] = m_vertices[br];
		}
	}


}