#ifndef _BS_KEYBOARD_H_
#define _BS_KEYBOARD_H_

#include <Platform/bs_Platform.h>
#include <Utilities/bs_types.h>
#include <Utilities/bs_String.h>

#ifdef BS_WINDOWS
#include <Platform/Windows/bs_WindowsKeyboard.h>
#endif


namespace bs
{
	typedef ui16 KeyCode;
	class Keyboard
	{
	public:
		Keyboard();
		Keyboard(const Keyboard& k);
		~Keyboard();

	private:

#ifdef BS_WINDOWS
		friend class WindowsInput;
#endif
		friend class InputManager;
	public:
		bool isKeyPressed(KeyCode keyCode);
		bool isKeyReleased(KeyCode keyCode);
		bool isKeyHeld(KeyCode keyCode);
	private:
		void _setLastKeystates();

		void _setKeyPressed(ui16 keyCode);
		void _setKeyReleased(ui16 keyCode);

		ui64 _keyCodeToBitMask(ui16 keyCode);
		ui64 _bitMaskToKeyCode(ui64 bitMask);

		ui64 m_keyset1;
		ui64 m_keyset2;
		ui64 m_lastKeyset1;
		ui64 m_lastKeyset2;
	};
}

#endif // !_BS_KEYBOARD_H_