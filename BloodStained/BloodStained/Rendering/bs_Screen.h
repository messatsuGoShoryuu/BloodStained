#ifndef BS_SCREEN_H
#define BS_SCREEN_H

#include "../Utilities/bs_types.h"

/*This class holds information about the game window,
**such as screen width, screen height, aspect ratio, etc.
*/

namespace bs
{
	class Screen
	{
	public:
		friend class ScreenInitializer;

		//Default constructor.
		Screen()
			:m_width(0),
			m_height(0),
			m_aspectRatio(0.0f)
		{

		}
		//Copy constructor.
		Screen(const Screen& s)
			:m_width(s.m_width),
			m_height(s.m_height),
			m_aspectRatio(s.m_aspectRatio)
		{

		}
		//Destructor.
		~Screen()
		{

		}

	public:
		//Accessors
		inline	const ui16	width(){ return m_width; }
		inline	const ui16	height(){ return m_height; }
		inline	const f32	aspectRatio(){ return m_aspectRatio; }

	private:
		inline	void	_setWidth(ui16 width){ m_width = width; }
		inline	void	_setHeight(ui16 height){ m_height = height; }
		inline  void	_calculateAspectRatio(){ m_aspectRatio = static_cast<f32>(m_width) / static_cast<f32>(m_height); }

	private:
		ui16	m_width;
		ui16	m_height;
		f32		m_aspectRatio;
	};
}
#endif // !BS_SCREEN_H
