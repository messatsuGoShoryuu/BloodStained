#ifndef BASICS_INPUTMANAGER_H
#define BASICS_INPUTMANAGER_H

#include "../Containers/bs_Array.h"
#include "../Utilities/bs_String.h"

#define MOUSE_BUTTON_1 0x01
#define MOUSE_BUTTON_2 0x02
#define INVALID_KEYCODE 0xFFFF

#ifdef _WIN32 || _WIN64
#include "../Platform/Windows/Input/bs_windowsKeyboard.h"
#endif


namespace bs
{

	class Joystick
	{
#ifdef _WIN32 || _WIN64
		friend class WindowsInput;
#endif

	public:
		Joystick();
		~Joystick();

		bool isButtonPressed(ui32 button);
		bool isButtonReleased(ui32 button);
		bool isButtonHeld(ui32 button);
		void setName(const wchar_t* name);
		inline const String& getName(){ return m_name; }

	private:
		//first half of bits represent current presses, last half last presses.
		ui32 m_buttons;
		String	m_name;
	};

	class Mouse
	{
#ifdef _WIN32 || _WIN64
		friend class WindowsInput;
#endif
		friend class InputManager;
	public:
		Mouse();
		~Mouse();

		bool isButtonPressed(ui32 button);
		bool isButtonReleased(ui32 button);
		bool isButtonHeld(ui32 button);

		ui32 getX();
		ui32 getY();
		ui32 getLastX();
		ui32 getLastY();
		i16  getDeltaX();
		i16  getDeltaY();
		short getDeltaWheel();
	private:
		void setPosition(ui32 x, ui32 y);
		void setLastStates();
		void setDeltaPosition(int deltaX, int deltaY);
		void setButtons(ui16 buttons);
		void setWheel(short value);
		void setLastDeltas();

		short m_deltaWheel;
		byte m_buttons;
		byte m_lastButtons;
		//x = m_position & 4095;
		//y = m_position << 16;
		//y = y & 4095;
		ui32 m_position;
		ui32 m_lastPosition;
		i32	 m_deltaPosition;
		bool m_isDirty;
	};

	typedef ui16 KeyCode;

	class Keyboard
	{
#ifdef _WIN32 || _WIN64
		friend class WindowsInput;
#endif
		friend class InputManager;
	public:
		Keyboard();
		~Keyboard();

		bool isKeyPressed(KeyCode keyCode);
		bool isKeyReleased(KeyCode keyCode);
		bool isKeyHeld(KeyCode keyCode);
		bool isAnykeyPressed(){ return m_anyKeyPressed; }
		bool isAnykeyHeld(){ return m_pressedKeyCount != 0; }
		bool isAnykeyReleased(){ return m_anyKeyReleased; }

		inline String getLayoutName(){ return m_layoutName; }
		inline ui16 getLastPressedKey(){ return m_lastPressedKey; }
	private:
		void setLastKeystates();

		void setKeyPressed(ui16 keyCode);
		void setKeyReleased(ui16 keyCode);

		ui64 keyCodeToBitMask(ui16 keyCode);
		ui64 bitMaskToKeyCode(ui64 bitMask);

		void _pushToPressBuffer(ui16 keyCode);
		ui16 _popFromPressBuffer();
		void _pushToReleaseBuffer(ui16 keyCode);
		ui16 _popFromReleaseBuffer();

		inline void setLayoutName(String name){ m_layoutName = name; }


		ui16 m_pressBuffer[16];
		ui16 m_releaseBuffer[16];
		ui64 m_keyset1;
		ui64 m_keyset2;
		ui64 m_lastKeyset1;
		ui64 m_lastKeyset2;
		String m_layoutName;
		ui16 m_lastPressedKey;
		ui16 m_pressedKeyCount;
		ui8	 m_releaseBufferTop;
		ui8	 m_pressBufferTop;
		bool m_anyKeyPressed;
		bool m_anyKeyReleased;
	};



	class InputManager
	{
#ifdef _MSC_VER
		friend class WindowsInput;
#endif
	public:
		InputManager();
		~InputManager();

		bool initialize();
		bool shutDown();

		void update();
		void resetDeltas();
		void poll();

		static Mouse mouse;
		static Keyboard keyboard;


	private:
		InputManager(const InputManager& i);

	private:
		Array<Joystick> m_joysticks;
	};
}
#endif