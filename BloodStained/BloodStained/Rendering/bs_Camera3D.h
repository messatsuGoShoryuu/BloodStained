#ifndef _BS_CAMERA3D_H_
#define _BS_CAMERA3D_H_

#include "bs_Camera.h"

namespace bs
{
	struct Ray3D;

	class Camera3D : public Camera
	{
	public:
		Camera3D();
		Camera3D(const Camera3D& c);
		~Camera3D();

	public:
		//Accessors:

		inline	const	Quaternion		orientation()			{ return m_orientation; }
		inline	const	Quaternion		orientation()	const	{ return m_orientation; }

		inline	const	Vector3&	position()				{ return m_position; }
		inline	const	Vector3&	position()		const	{ return m_position; }

		inline	const	Vector3&	up()					{ return m_up; }
		inline	const	Vector3&	up()			const	{ return m_up; }

		inline	const	Vector3&	right()					{ return m_right; }
		inline	const	Vector3&	right()			const	{ return m_right; }

		inline	const	Vector3&	forward()					{ return m_forward; }
		inline	const	Vector3&	forward()			const	{ return m_forward; }

		inline	const	f32			fov()					{ return m_fov; }
		inline	const	f32			fov()			const	{ return m_fov; }

		inline void		setFov(f32 fov)
		{
			m_fov = math::clamp(fov, 0.0f, 180.0f);
			_constructProjectionMatrix();
		}

		inline	void	setOrientation(Quaternion orientation)
		{
			m_orientation = orientation;
			_updateBasis();
			_updateViewMatrix();
			
		}

		inline	void	rotate(const Quaternion& amount)
		{ 
			m_orientation = amount * m_orientation;
			_updateBasis();
			_updateViewMatrix();
			
		}

		//Setters:
		inline	void	setPosition(const Vector3& position)
		{
			m_position = position;
			_updateViewMatrix();
		}

		inline	void	translate(const Vector3& amount)
		{
			m_position += amount;
			_updateViewMatrix();
		}

		inline void setAspectRatio(real r)
		{
			m_aspectRatio = r;
			_constructProjectionMatrix();
		}

		Ray3D		screenToWorld(const Vector2& screenPoint);
		Vector3		pixelsToNDC(const Vector2& pixels, real desiredZ);


	protected:
		//Helpers
		void	_constructProjectionMatrix();
		void	_updateViewMatrix();
		
	private:
		inline	void _updateBasis()
		{
			m_up = m_orientation * Vector3::up;
			m_forward = m_orientation * Vector3::forward;
			m_right = m_orientation * Vector3::right;

			m_forward.normalize();
			m_right.normalize();
			m_up.normalize();
		}

	private:
		//Rotation of the camera.
		Quaternion	m_orientation;
		Vector3		m_position;
		Vector3		m_up;
		Vector3		m_right;
		Vector3		m_forward;
		f32			m_fov;
	};
}
#endif // !BS_CAMERA2D_H
