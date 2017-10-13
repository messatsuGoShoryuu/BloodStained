#ifndef _BS_TRANSFORM2D_H_
#define _BS_TRANSFROM2D_H_

#include <Math/bs_Vector.h>
#include <Utilities/bs_types.h>

namespace bs
{
	class Transform2D;
	class Basis2D
	{
	public:
		Basis2D();
		Basis2D(const Transform2D& t);
		Basis2D(const Basis2D& b);
		~Basis2D();

		Vector2 transform(const Vector2& absoluteCenter, const Vector2& target) const;

		void	calculate(const Transform2D& t);
		
		inline	const Vector2& x() const	{ return m_x; }
		inline	const Vector2& y() const	{ return m_y; }

		//For being explicit
		inline  const real cos() const	{ return m_x.x; }
		inline  const real sin() const	{ return m_x.y; }

	private:
		//Right vector
		Vector2 m_x;
		//Up vector
		Vector2 m_y;

	};
	class Transform2D
	{
		friend class Basis2D;
	public:
		Transform2D();
		Transform2D(const Transform2D& t);
		~Transform2D();

		const Basis2D& basis() const { return m_basis; }

		const Vector2&	position()	const { return m_position; }
		const Vector2&	scale()		const { return m_scale; }
		real			orientation() const { return m_orientation; }

		void setOrientation(real newOrientation);
		void rotate(real amount);

		void setPosition(const Vector2& newPosition);
		void translate(const Vector2& amount);

		void setScale(const Vector2& newScale);
		void multScale(const Vector2& amount);

	private:
		Basis2D m_basis;

		Vector2 m_position;
		Vector2 m_scale;
		real	m_orientation;


	};
}
#endif // !_BS_TRANSFORM2D_H_
