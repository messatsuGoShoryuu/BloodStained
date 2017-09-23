#include "bs_Mouse.h"
#include "bs_InputManager.h"

#define BITMASK_MOUSE_POS_X	 0x0000FFFF	 
#define BITMASK_MOUSE_POS_Y  0xFFFF0000
namespace bs
{
	Mouse::Mouse():
		m_buttons(0),
		m_lastButtons(0),
		m_deltaPosition(0),
		m_deltaWheel(0)
	{
		_setPosition(100.0f, 100.0f);
	}
	Mouse::~Mouse()
	{
	}
	bool Mouse::isButtonPressed(ui32 button)
	{
		if ((button & m_buttons) && !(button & m_lastButtons)) return true;
		return false;
	}
	bool Mouse::isButtonReleased(ui32 button)
	{
		if (!(button & m_buttons) && (button & m_lastButtons)) return true;
		return false;
	}
	bool Mouse::isButtonHeld(ui32 button)
	{
		if ((button & m_buttons) && (button & m_lastButtons)) return true;
		return false;
	}
	ui32 Mouse::getX()
	{
		return m_position & BITMASK_MOUSE_POS_X;
	}
	ui32 Mouse::getY()
	{
		return (m_position & BITMASK_MOUSE_POS_Y) >> 16;
	}
	ui32 Mouse::getLastX()
	{
		return m_lastPosition & BITMASK_MOUSE_POS_X;
	}
	ui32 Mouse::getLastY()
	{
		return (m_lastPosition & BITMASK_MOUSE_POS_Y) >> 16;
	}
	i16 Mouse::getDeltaX()
	{
		return m_deltaPosition & BITMASK_MOUSE_POS_X;
	}
	i16 Mouse::getDeltaY()
	{
		return (m_deltaPosition & BITMASK_MOUSE_POS_Y) >> 16;
	}
	i16 Mouse::getDeltaWheel()
	{
		return m_deltaWheel;
	}
	void Mouse::_setPosition(ui32 x, ui32 y)
	{
		x = x & BITMASK_MOUSE_POS_X;
		y = y << 16;
		m_position = x | y;
	}
	void Mouse::_setLastStates()
	{
		m_lastButtons = m_buttons;
		m_lastPosition = m_position;
	}
	void Mouse::_setDeltaPosition(i32 deltaX, i32 deltaY)
	{
		deltaX = deltaX & BITMASK_MOUSE_POS_X;
		deltaY = deltaY << 16;
		m_deltaPosition = deltaX | deltaY;
	}
	void Mouse::_setButtons(ui16 flags)
	{
		if ((flags & RI_MOUSE_BUTTON_1_DOWN) == RI_MOUSE_BUTTON_1_DOWN)		m_buttons = m_buttons | MOUSE_BUTTON_1;
		else if ((flags & RI_MOUSE_BUTTON_1_UP) == RI_MOUSE_BUTTON_1_UP)	m_buttons = m_buttons & (~MOUSE_BUTTON_1);

		if ((flags & RI_MOUSE_BUTTON_2_DOWN) == RI_MOUSE_BUTTON_2_DOWN)		m_buttons = m_buttons | MOUSE_BUTTON_2;
		else if ((flags & RI_MOUSE_BUTTON_2_UP) == RI_MOUSE_BUTTON_2_UP)	m_buttons = m_buttons & (~MOUSE_BUTTON_2);
		//the rest is to do
	}
	void Mouse::_setWheel(i16 value)
	{
		m_deltaWheel = value;
	}
	void Mouse::_setLastDeltas()
	{
		m_deltaPosition = 0;
		m_deltaWheel = 0;
	}
}