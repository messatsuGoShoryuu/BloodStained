#include "bs_Keyboard.h"
#include "bs_InputManager.h"


namespace bs
{
	Keyboard::Keyboard()
		:m_keyset1(0),
		m_keyset2(0),
		m_lastKeyset1(0),
		m_lastKeyset2(0)
	{
	}

	Keyboard::Keyboard(const Keyboard & k)
		:m_keyset1(k.m_keyset1),
		m_keyset2(k.m_keyset2),
		m_lastKeyset1(k.m_lastKeyset1),
		m_lastKeyset2(k.m_lastKeyset2)
	{
	}

	Keyboard::~Keyboard()
	{
	}

	bool Keyboard::isKeyPressed(KeyCode keyCode)
	{
		ui64 bitMask = _keyCodeToBitMask(keyCode);
		bool result = false;
		if (keyCode > KB_SET_SWITCH_LIMIT_LOW)
		{
			if ((m_lastKeyset2 & bitMask) == bitMask)return false;
			if ((m_keyset2 & bitMask) == bitMask) return true;
		}
		else
		{
			if ((m_lastKeyset1 & bitMask) == bitMask)return false;
			if ((m_keyset1 & bitMask) == bitMask)return true;
		}
		return false;
	}

	bool Keyboard::isKeyReleased(KeyCode keyCode)
	{
		ui64 bitMask = _keyCodeToBitMask(keyCode);
		if (keyCode > KB_SET_SWITCH_LIMIT_LOW)
		{
			if ((m_lastKeyset2 & bitMask) == 0) return false;
			if ((m_keyset2 & bitMask) == 0) return true;
		}
		else
		{
			if ((m_lastKeyset1 & bitMask) == 0) return false;
			if ((m_keyset1 & bitMask) == 0) return true;
		}
		return false;
	}

	bool Keyboard::isKeyHeld(KeyCode keyCode)
	{
		ui64 bitMask = _keyCodeToBitMask(keyCode);
		return (keyCode > KB_SET_SWITCH_LIMIT_LOW) ? bitMask & m_keyset2 : bitMask & m_keyset1;
	}

	void Keyboard::_setLastKeystates()
	{

	}

	void Keyboard::_setKeyPressed(ui16 keyCode)
	{
		ui64 bitMask = _keyCodeToBitMask(keyCode);
		ui64 lastKeyset2 = m_keyset2;
		ui64 lastKeyset1 = m_keyset1;

		if (keyCode > KB_SET_SWITCH_LIMIT_LOW)
		{
			m_keyset2 = m_keyset2 | bitMask;
		}
		else
		{
			m_keyset1 = m_keyset1 | bitMask;
		}
	}

	void Keyboard::_setKeyReleased(ui16 keyCode)
	{
		ui64 bitMask = ~_keyCodeToBitMask(keyCode);

		if (keyCode > KB_SET_SWITCH_LIMIT_LOW)
		{
			m_keyset2 = m_keyset2 & bitMask;
		}
		else
		{
			m_keyset1 = m_keyset1 & bitMask;
		}
	}

	ui64 Keyboard::_keyCodeToBitMask(ui16 keyCode)
	{
		switch (keyCode)
		{
		case KB_BACKSPACE:		return KB_BITMASK_BACKSPACE;
		case KB_TAB:			return KB_BITMASK_TAB;
		case KB_CLEAR:			return KB_BITMASK_CLEAR;
		case KB_ENTER:			return KB_BITMASK_ENTER;
		case KB_SHIFT:			return KB_BITMASK_SHIFT;
		case KB_CTRL:			return KB_BITMASK_CTRL;
		case KB_ALT:			return KB_BITMASK_ALT;
		case KB_PAUSE:			return KB_BITMASK_PAUSE;
		case KB_CAPSLOCK:		return KB_BITMASK_CAPSLOCK;
		case KB_ESCAPE:			return KB_BITMASK_ESCAPE;
		case KB_SPACE:			return KB_BITMASK_SPACE;
		case KB_PAGEUP:			return KB_BITMASK_PAGEUP;
		case KB_PAGEDOWN:		return KB_BITMASK_PAGEDOWN;
		case KB_END:			return KB_BITMASK_END;
		case KB_HOME:			return KB_BITMASK_HOME;
		case KB_LEFTARROW:		return KB_BITMASK_LEFTARROW;
		case KB_RIGHTARROW:		return KB_BITMASK_RIGHTARROW;
		case KB_DOWNARROW:		return KB_BITMASK_DOWNARROW;
		case KB_UPARROW:		return KB_BITMASK_UPARROW;
		case KB_SELECT:			return KB_BITMASK_SELECT;
		case KB_PRINT:			return KB_BITMASK_PRINT;
		case KB_EXECUTE:		return KB_BITMASK_EXECUTE;
		case KB_PRINTSCREEN:	return KB_BITMASK_PRINTSCREEN;
		case KB_INSERT:			return KB_BITMASK_INSERT;
		case KB_DELETE:			return KB_BITMASK_DELETE;
		case KB_HELP:			return KB_BITMASK_HELP;
		case KB_0:				return KB_BITMASK_0;
		case KB_1:				return KB_BITMASK_1;
		case KB_2:				return KB_BITMASK_2;
		case KB_3:				return KB_BITMASK_3;
		case KB_4:				return KB_BITMASK_4;
		case KB_5:				return KB_BITMASK_5;
		case KB_6:				return KB_BITMASK_6;
		case KB_7:				return KB_BITMASK_7;
		case KB_8:				return KB_BITMASK_8;
		case KB_9:				return KB_BITMASK_9;
		case KB_A:				return KB_BITMASK_A;
		case KB_B:				return KB_BITMASK_B;
		case KB_C:				return KB_BITMASK_C;
		case KB_D:				return KB_BITMASK_D;
		case KB_E:				return KB_BITMASK_E;
		case KB_F:				return KB_BITMASK_F;
		case KB_G:				return KB_BITMASK_G;
		case KB_H:				return KB_BITMASK_H;
		case KB_I:				return KB_BITMASK_I;
		case KB_J:				return KB_BITMASK_J;
		case KB_K:				return KB_BITMASK_K;
		case KB_L:				return KB_BITMASK_L;
		case KB_M:				return KB_BITMASK_M;
		case KB_N:				return KB_BITMASK_N;
		case KB_O:				return KB_BITMASK_O;
		case KB_P:				return KB_BITMASK_P;
		case KB_Q:				return KB_BITMASK_Q;
		case KB_R:				return KB_BITMASK_R;
		case KB_S:				return KB_BITMASK_S;
		case KB_T:				return KB_BITMASK_T;
		case KB_U:				return KB_BITMASK_U;
		case KB_V:				return KB_BITMASK_V;
		case KB_W:				return KB_BITMASK_W;
		case KB_X:				return KB_BITMASK_X;
		case KB_Y:				return KB_BITMASK_Y;
		case KB_Z:				return KB_BITMASK_Z;
		case KB_LWIN:			return KB_BITMASK_LWIN;
		case KB_RWIN:			return KB_BITMASK_RWIN;
		case KB_APPS:			return KB_BITMASK_APPS;
		case KB_SLEEP:			return KB_BITMASK_SLEEP;
		case KB_NUMPAD0:		return KB_BITMASK_NUMPAD0;
		case KB_NUMPAD1:		return KB_BITMASK_NUMPAD1;
		case KB_NUMPAD2:		return KB_BITMASK_NUMPAD2;
		case KB_NUMPAD3:		return KB_BITMASK_NUMPAD3;
		case KB_NUMPAD4:		return KB_BITMASK_NUMPAD4;
		case KB_NUMPAD5:		return KB_BITMASK_NUMPAD5;
		case KB_NUMPAD6:		return KB_BITMASK_NUMPAD6;
		case KB_NUMPAD7:		return KB_BITMASK_NUMPAD7;
		case KB_NUMPAD8:		return KB_BITMASK_NUMPAD8;
		case KB_NUMPAD9:		return KB_BITMASK_NUMPAD9;
		case KB_ASTERISK:		return KB_BITMASK_ASTERISK;
		case KB_PLUS:			return KB_BITMASK_PLUS;
		case KB_MINUS:			return KB_BITMASK_MINUS;
		case KB_COMMA:			return KB_BITMASK_COMMA;
		case KB_FORWARDSLASH:	return KB_BITMASK_FORWARDSLASH;
		case KB_NUMLOCK:		return KB_BITMASK_NUMLOCK;
		case KB_SCROLLLOCK:     return KB_BITMASK_SCROLLLOCK;
		case KB_F1:				return KB_BITMASK_F1;
		case KB_F2:				return KB_BITMASK_F2;
		case KB_F3:				return KB_BITMASK_F3;
		case KB_F4:				return KB_BITMASK_F4;
		case KB_F5:				return KB_BITMASK_F5;
		case KB_F6:				return KB_BITMASK_F6;
		case KB_F7:				return KB_BITMASK_F7;
		case KB_F8:				return KB_BITMASK_F8;
		case KB_F9:				return KB_BITMASK_F9;
		case KB_F10:			return KB_BITMASK_F10;
		case KB_F11:			return KB_BITMASK_F11;
		case KB_F12:			return KB_BITMASK_F12;
		case KB_F13:			return KB_BITMASK_F13;
		case KB_F14:			return KB_BITMASK_F14;
		case KB_F15:			return KB_BITMASK_F15;
		case KB_F16:			return KB_BITMASK_F16;
		case KB_F17:			return KB_BITMASK_F17;
		case KB_F18:			return KB_BITMASK_F18;
		case KB_F19:			return KB_BITMASK_F19;
		case KB_F20:			return KB_BITMASK_F20;
		case KB_F21:			return KB_BITMASK_F21;
		case KB_F22:			return KB_BITMASK_F22;
		case KB_F23:			return KB_BITMASK_F23;
		case KB_F24:			return KB_BITMASK_F24;
		case KB_LEFTSHIFT:		return KB_BITMASK_LEFTSHIFT;
		case KB_RIGHTSHIFT:		return KB_BITMASK_RIGHTSHIFT;
		case KB_LEFTCTRL:		return KB_BITMASK_LEFTCTRL;
		case KB_RIGHTCTRL:		return KB_BITMASK_RIGHTCTRL;
		case KB_OEM1:			return KB_BITMASK_OEM1;
		case KB_OEM_PLUS:		return KB_BITMASK_OEM_PLUS;
		case KB_OEM_COMMA:		return KB_BITMASK_OEM_COMMA;
		case KB_OEM_MINUS:		return KB_BITMASK_OEM_MINUS;
		case KB_OEM_PERIOD:		return KB_BITMASK_OEM_PERIOD;
		case KB_OEM_2:			return KB_BITMASK_OEM_2;
		case KB_OEM_3:			return KB_BITMASK_OEM_3;
		case KB_OEM_4:			return KB_BITMASK_OEM_4;
		case KB_OEM_5:			return KB_BITMASK_OEM_5;
		case KB_OEM_6:			return KB_BITMASK_OEM_6;
		case KB_OEM_7:			return KB_BITMASK_OEM_7;
		case KB_OEM_8:			return KB_BITMASK_OEM_8;
		case KB_OEM_102:			return KB_BITMASK_OEM_102;
		}
		return 0;
	}

	ui64 Keyboard::_bitMaskToKeyCode(ui64 bitMask)
	{
		return ui64();
	}
}