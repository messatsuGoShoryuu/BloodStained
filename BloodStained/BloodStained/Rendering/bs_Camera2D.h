#ifndef BS_CAMERA2D_H
#define BS_CAMERA2D_H

#include "bs_Camera.h"

namespace bs
{
	class Camera2D : public Camera
	{
	public:
		Camera2D();
		Camera2D(const Camera2D& c);
		~Camera2D();

	public:
		//Accessors:

		inline	const	real		orientation()			{ return m_orientation; }
		inline	const	real		orientation()	const	{ return m_orientation; }

		inline	const	Vector2&	position()				{ return m_position; }
		inline	const	Vector2&	position()		const	{ return m_position; }

		inline	void	setOrientation(real orientation)
		{ 
			m_orientation = orientation; 
			_updateViewMatrix();
		}

		inline	void	rotate(real amount)
		{ 
			m_orientation += amount; 
			_updateViewMatrix();
		}

		//Setters:
		inline	void	setPosition(const Vector2& position)
		{
			m_position = position;
			_updateViewMatrix();
		}

		inline	void	translate(const Vector2& amount)
		{
			m_position += amount;
			_updateViewMatrix();
		}

		inline void		setDepth(real depth)
		{
			m_depth = depth;
			_updateViewMatrix();
		}

		inline real		depth() const	{ return m_depth; }

	protected:
		//Helpers
		void	_constructProjectionMatrix();
		void	_updateViewMatrix();

	private:
		//Rotation of the camera.
		real		m_orientation;
		Vector2		m_position;
		real		m_depth;
	};
}
#endif // !BS_CAMERA2D_H
