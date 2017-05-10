#ifndef BS_TRANSFORM3D_H
#define BS_TRANSFORM3D_H

#include "../bs_Component.h"
#include "../../../../Math/bs_Quaternion.h"

#include "../../../../Math/bs_Matrix4x4.h"

namespace bs
{
	class Transform3D : public Component<Transform3D>
	{
	public:
		Transform3D();
		Transform3D(const Transform3D& t);
		~Transform3D();

		//Transformation functions

		//Translate by amount
		void	translate(const Vector3& amount);
		//Translate by a new vector of [x,y].
		void	translate(real x, real y, real z);

		//Rotate by degrees
		void	rotate(const Quaternion&	amount);

		//Rotate by degrees
		void	rotate(const Vector3&	amount);

		//Rotate by degrees
		void	rotate(real right, real up, real forward);
		

		//Set absolute position
		void	setPosition(const Vector3& newPosition);
		//Set absolute position
		void	setPosition(real x, real y, real z);
		//Set absolute orientation
		void	setOrientation(const Quaternion& newOrientation);
		//Set absolute orientation
		void	setOrientation(const Vector3& orientation);
		//Set absolute orientation
		void	setOrientation(real right, real up, real forward);

		//Set scale
		void	setScale(const Vector3& newScale);
		//Set scale
		void	setScale(real x, real y, real z);

		//Set scale
		void	scaleBy(real value);

		//Accessors:

		inline	const Vector3&	position(){ return m_position; }
		inline	const Vector3&	scale(){ return m_scale; }
		inline	const Quaternion&	orientation(){ return m_orientation; }
		inline	const Matrix4x4& modelMatrix(){ return m_modelMatrix; }

	private:
		void	_updateBasis();
	private:
		Matrix4x4	m_modelMatrix;

		Vector3		m_position;
		Vector3		m_scale;

		Vector3		m_forward;
		Vector3		m_up;
		Vector3		m_right;

		Quaternion		m_orientation;
	};
}

#endif // !BS_TRANSFORM2D_H
