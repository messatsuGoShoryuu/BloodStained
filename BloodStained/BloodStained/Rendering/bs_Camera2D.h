#ifndef _BS_CAMERA2D_H_
#define _BS_CAMERA2D_H_

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

		inline	const	real		scale()			const	{ return m_scale; }

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

		inline void setScale(real scale)
		{
			m_scale = scale;
			_constructProjectionMatrix();
		}

		inline real		depth() const	{ return m_depth; }


		Vector2		screenToWorld(const Vector2& screenPoint);
		Vector2		pixelsToNDC(const Vector2& pixels);

	protected:
		//Helpers
		void	_constructProjectionMatrix();
		void	_updateViewMatrix();

	private:
		
		Vector2		m_position;
		real		m_orientation;
		real		m_depth;
		real		m_scale;
	};
}
#endif // !BS_CAMERA2D_H
