#ifndef BS_TRANSFORM2D_H
#define BS_TRANSFORM2D_H

#include "../bs_Component.h"

#include "../../../../Math/bs_Matrix4x4.h"

namespace bs
{
	class Transform2D : public Component<Transform2D>
	{
	public:
		Transform2D();
		Transform2D(const Transform2D& t);
		~Transform2D();

		//Transformation functions

		//Translate by amount
		void	translate(const Vector2& amount);
		//Translate by a new vector of [x,y].
		void	translate(real x, real y);

		//Rotate by degrees
		void	rotate(real	degrees);

		//Set absolute position
		void	setPosition(const Vector2& newPosition);
		//Set absolute position
		void	setPosition(real x, real y);
		//Set absolute orientation
		void	setOrientation(real newOrientation);

		//Set scale
		void	setScale(const Vector2& newScale);
		//Set scale
		void	setScale(real x, real y);

		//Set scale
		void	scaleBy(real value);

		//Accessors:

		inline	const Vector2&	position(){ return m_position; }
		inline	const Vector2&	scale(){ return m_scale; }
		inline	const real		orientation(){ return m_orientation; }
		inline	const Matrix4x4& modelMatrix(){ return m_modelMatrix; }
	private:
		Matrix4x4	m_modelMatrix;

		Vector2		m_position;
		Vector2		m_scale;
		
		real		m_orientation;
	};
}

#endif // !BS_TRANSFORM2D_H
