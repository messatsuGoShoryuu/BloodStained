#include "bs_Physics2D.h"


namespace bs
{
	Shape2D attachShapeToBasis(const Transform2D& transform, const Shape2D& shape)
	{
		const	Basis2D* basis = &transform.basis();

		Vector2 position = transform.position();
		Vector2 scale = transform.scale();

		ui32 count = shape.vertexCount();
		const Vector2* sourceVertices = shape.getVertices();

		Shape2D result;


		for (ui32 i = 0; i < count; i++)
		{
			Vector2 vertex = sourceVertices[i];
			Vector2 pivot = sourceVertices[i] - shape.center();

			vertex.x = pivot.x * basis->cos() - pivot.y * basis->sin();
			vertex.y = pivot.x * basis->sin() + pivot.y * basis->cos();

			vertex.x *= scale.x;
			vertex.y *= scale.y;

			vertex += position;

			result.addVertex(vertex);
		}

		result.calculateNormals();
		result.calculateCenter();
		result.getInertiaMoment();

		return result;
	}

	bool intersect(const Vector2 & a1, const Vector2 & a2, const Vector2 & b1, const Vector2 & b2, Vector2 & out)
	{
		//Calculate slopes
		Vector2 diffA = a2 - a1;
		Vector2 diffB = b2 - b1;
		real sA = diffA.y / diffA.x;
		real sB = diffB.y / diffB.x;

		if (sA - sB < 0.0001f && sA - sB > -0.0001f)
		{
			out = a1 + diffA / 2.0f;
			if(a1 == b1 && a2 == b2) return true;
			if (a2 == b1 && b2 == a1) return true;
			return false;
		}

		/*
		yA = sA*x + a
		yB = sB*x + b

		sA*x + a = sB*x + b
		sA*x - sB * x = b - a
		x(sA - sB) = b - a
		x = (b - a) / (sA - sB)

		*/

		real a = a1.y - sA * a1.x;
		real b = b1.y - sB * b1.x;

		real c = b - a;
		real s = sA - sB;

		out.x = c / s;
		out.y = sA * out.x + a;	

		Vector2 diffOutA = out - a1;
		Vector2 diffOutB = out - b1;

		real dotA = diffA.dot(diffOutA);
		if (dotA < 0) return false;
		real dotB = diffB.dot(diffOutB);
		if (dotB < 0) return false;

		if (diffOutA.squareMagnitude() > diffA.squareMagnitude()) return false;
		if (diffOutB.squareMagnitude() > diffB.squareMagnitude()) return false;
		
		return true;
	}

	Shape2D makeShapeRelativeToBasis(const Transform2D & transform, const Shape2D & shape)
	{
		const	Basis2D* basis = &transform.basis();

		Vector2 position = transform.position();
		Vector2 scale = transform.scale();

		ui32 count = shape.vertexCount();
		const Vector2* sourceVertices = shape.getVertices();

		Shape2D result;

		for (ui32 i = 0; i < count; i++)
		{
			Vector2 vertex = sourceVertices[i];

			Vector2 relVertex = sourceVertices[i] - position;

			vertex.x = basis->x().dot(relVertex);
			vertex.y = basis->y().dot(relVertex);

			vertex.x *= scale.x;
			vertex.y *= scale.y;

			result.addVertex(vertex);
		}

		result.calculateNormals();
		result.calculateCenter();
		result.getInertiaMoment();

		return result;
	}

	Shape2D makeShapeRelativeToBasis(const Transform2D & basisTransform,
		const Transform2D & shapeTransform,
		const Shape2D & shape)
	{
		Transform2D transform;
		transform.setPosition(shapeTransform.position() - basisTransform.position());
		transform.setOrientation(shapeTransform.orientation() - basisTransform.orientation());

		return makeShapeRelativeToBasis(transform, shape);
	}
	Vector2 makeVector2RelativeToBasis(const Transform2D & transform, const Vector2 & v)
	{
		Vector2 position = transform.position();
		Vector2 result = v;
		Vector2 vertex = v;
		real cos = math::cos(-transform.orientation());
		real sin = math::sin(-transform.orientation());

		vertex -= position;
		vertex.x /= transform.scale().x;
		vertex.y /= transform.scale().y;

		result.x = vertex.x *  cos + vertex.y * sin;
		result.y = -vertex.x * sin + vertex.y * cos;


		return result;
	}





}