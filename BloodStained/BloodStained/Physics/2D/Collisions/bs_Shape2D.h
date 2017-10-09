#ifndef _BS_SHAPE2D_
#define _BS_SHAPE2D_

#include <Math/bs_Vector.h>
namespace bs
{
#define	BS_SHAPE_VERTEX_COUNT 8

	struct Segment2D
	{
		Vector2 a;
		Vector2 b;
	};

	class Shape2D
	{
	public:
		Shape2D();
		Shape2D(const Shape2D& s);
		~Shape2D();

	public:
		bool addVertex(const Vector2& vertex);
		bool addVertex(real x, real y);

		inline	Vector2* getVertices()	{ return m_vertices; }
		inline	Vector2* getNormals()	{ return m_normals; }

		inline	const	Vector2* getVertices() const { return m_vertices; }
		inline	const	Vector2* getNormals() const	{ return m_normals; }

		inline	Vector2 getVertex(ui32 index) const { return index == -1 ? Vector2::zero : m_vertices[index]; }
		inline	Vector2 getNormal(ui32 index) const { return m_normals[index]; }

		Segment2D	getEdgeFromNormal(ui32 normalIndex) const;

		inline ui32 vertexCount() const { return m_vertexCount; }

		void	calculateNormals();
		void	calculateCenter();
		real	getInertiaMoment();

		inline const Vector2& center() const { return m_center; }
		inline const Vector2& centerOfGravity() const { return m_centerOfGravity; }
		
		inline real radius() { return m_radius; }

		Vector2 getSupportPoint(const Vector2& direction) const;
		ui32 getSupportIndex(const Vector2& direction) const;
		 
		
		inline	void* owner() { return m_owner; }
		inline	void	setOwner(void* owner) { m_owner = owner; }
	private:
		Vector2 m_vertices[BS_SHAPE_VERTEX_COUNT];
		Vector2 m_normals[BS_SHAPE_VERTEX_COUNT];
		Vector2 m_center;
		Vector2 m_centerOfGravity;
		real	m_radius;
		ui32 m_vertexCount;

		void* m_owner;
	};


	
}

#endif // !_BS_SHAPE2D_