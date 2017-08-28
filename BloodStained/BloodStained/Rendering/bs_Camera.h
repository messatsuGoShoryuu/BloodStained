#ifndef _BS_CAMERA_H_
#define _BS_CAMERA_H_

#include "../Math/bs_Matrix4x4.h"
#include "../Math/bs_Rect.h"
#include "../Math/bs_Quaternion.h"
namespace bs
{
	class Camera
	{
	public:
		Camera();
		Camera(const Camera& c);
		virtual ~Camera();

	public:
		//Accessors:
		inline	const	Matrix4x4&	projection()			{ return m_projection; }
		inline	const	Matrix4x4&	projection()	const	{ return m_projection; }

		inline	const	Matrix4x4&	view()					{ return m_view; }
		inline	const	Matrix4x4&	view()			const	{ return m_view; }

		inline	const	real		nearPlane()				{ return m_nearPlane; }
		inline	const	real		nearPlane()		const	{ return m_nearPlane; }

		inline	const	real		farPlane()				{ return m_farPlane; }
		inline	const	real		farPlane()		const	{ return m_farPlane; }

		inline	const	Rectf32		viewPort()				{ return m_viewPort; }
		inline	const	Rectf32		viewPort()		const	{ return m_viewPort; }

		inline const	f32			aspectRatio()			{ return m_aspectRatio; }
		inline const	f32			aspectRatio()	const	{ return m_aspectRatio; }



		void	setNearPlane(f32 nearPlane);


		void	setFarPlane(f32 farPlane);


		void		setViewport(const Rectf32& r);

	protected:
		//Helpers
		virtual	void	_constructProjectionMatrix();
		virtual	void	_updateViewMatrix();
		void	_calculateAspectRatio();

	protected:
		//Orthographic projection matrix.
		Matrix4x4	m_projection;
		//Viev matrix
		Matrix4x4	m_view;

		f32			m_nearPlane;
		f32			m_farPlane;
		f32			m_aspectRatio;
		Rectf32		m_viewPort;
	};
}
#endif // !BS_CAMERA_H
