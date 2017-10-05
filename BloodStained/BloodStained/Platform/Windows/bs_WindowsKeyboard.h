#ifndef _BS_WINDOWSKEYBOARD_H_
#define _BS_WINDOWSKEYBOARD_H_
#include <Windows.h>

//unused in struct
#define KB_LEFTMENU				0xA4
#define KB_RIGHTMENU			0xA5
#define KB_BROWSERBACK			0xA6
#define KB_BROWSERFORWARD		0xA7
#define KB_BROWSERREFRESH		0xA8
#define KB_BROWSERSTOP			0xA9
#define KB_BROWSERSEARCH		0xAA
#define KB_BROWSERFAVORITES		0xAB
#define KB_BROWSERHOME			0xAC
#define KB_VOLUMEMUTE			0xAD
#define KB_VOLUMEDOWN			0xAE
#define KB_VOLUMEUP				0xAF
#define KB_MEDIANEXTTRACK		0xB0
#define KB_MEDIAPREVIOUSTRACK	0xB1
#define KB_MEDIASTOP			0xB2
#define KB_MEDIAPLAYPAUSE		0xB3
#define KB_LAUNCHMAIL			0xB4
#define KB_LAUNCHMEDIASELECT	0xB5
#define KB_LAUNCHAPP1			0xB6
#define KB_LAUNCHAPP2			0xB7

#define KB_KANA			0x15
#define KB_HANGUL		0x15
#define KB_JUNJA		0x17
#define KB_FINAL		0x18
#define KB_HANJA		0x19
#define KB_KANJI		0x19

#define KB_CONVERT		0x1C
#define KB_NONCONVERT	0x1D
#define KB_ACCEPT		0x1E
#define	KB_MODECHANGE	0x1F

//used in struct

//set 1
#define KB_BACKSPACE	0x08
#define KB_TAB			0x09
#define KB_CLEAR		0x0C
#define KB_ENTER		0x0D
#define KB_SHIFT		0x10
#define KB_CTRL			0x11
#define KB_ALT			0x12
#define KB_PAUSE		0x13
#define KB_CAPSLOCK		0x14
#define KB_ESCAPE		0x1B
#define KB_SPACE		0x20
#define KB_PAGEUP		0x21
#define KB_PAGEDOWN		0x22
#define KB_END			0x23
#define KB_HOME			0x24
#define KB_LEFTARROW	0x25
#define KB_UPARROW		0x26
#define KB_RIGHTARROW	0x27
#define KB_DOWNARROW	0x28
#define KB_SELECT		0x29
#define KB_PRINT		0x2A
#define KB_EXECUTE		0x2B
#define KB_PRINTSCREEN	0x2C
#define KB_INSERT		0x2D
#define KB_DELETE		0x2E
#define KB_HELP			0x2F
#define KB_0			0x30
#define KB_1			0x31
#define KB_2			0x32
#define KB_3			0x33
#define KB_4			0x34
#define KB_5			0x35
#define KB_6			0x36
#define KB_7			0x37
#define KB_8			0x38
#define KB_9			0x39
#define KB_A			0x41
#define KB_B			0x42
#define KB_C			0x43
#define KB_D			0x44
#define KB_E			0x45
#define KB_F			0x46
#define KB_G			0x47
#define KB_H			0x48
#define KB_I			0x49	
#define KB_J			0x4A
#define KB_K			0x4B
#define KB_L			0x4C
#define KB_M			0x4D
#define KB_N			0x4E
#define KB_O			0x4F
#define KB_P			0x50
#define KB_Q			0x51
#define KB_R			0x52
#define KB_S			0x53
#define KB_T			0x54
#define KB_U			0x55
#define KB_V			0x56
#define KB_W			0x57
#define KB_X			0x58
#define KB_Y			0x59	
#define KB_Z			0x5A
#define KB_LWIN				0x5B
#define KB_RWIN				0x5C

#define KB_SET_SWITCH_LIMIT_LOW 0x5C

//set 2
#define KB_APPS				0x5D
#define KB_SLEEP			0x5F
#define KB_NUMPAD0			0x60
#define KB_NUMPAD1			0x61
#define KB_NUMPAD2			0x62
#define KB_NUMPAD3			0x63
#define KB_NUMPAD4			0x64
#define KB_NUMPAD5			0x65
#define KB_NUMPAD6			0x66
#define KB_NUMPAD7			0x67
#define KB_NUMPAD8			0x68
#define KB_NUMPAD9			0x69
#define KB_ASTERISK			0x6A
#define KB_PLUS				0x6B
#define KB_MINUS			0x6D
#define KB_COMMA			0x6E
#define KB_FORWARDSLASH		0x6F
#define KB_NUMLOCK			0x90
#define KB_SCROLLLOCK		0x91
#define KB_F1				0x70
#define KB_F2				0x71
#define KB_F3				0x72
#define KB_F4				0x73
#define KB_F5				0x74
#define KB_F6				0x75
#define KB_F7				0x76
#define KB_F8				0x77
#define KB_F9				0x78	
#define KB_F10				0x79
#define KB_F11				0x7A
#define KB_F12				0x7B
#define KB_F13				0x7C
#define KB_F14				0x7D
#define KB_F15				0x7E
#define KB_F16				0x7F
#define KB_F17				0x80
#define KB_F18				0x81
#define KB_F19				0x82
#define KB_F20				0x83
#define KB_F21				0x84
#define KB_F22				0x85	
#define KB_F23				0x86	
#define KB_F24				0x87
#define KB_LEFTSHIFT			0xA0
#define KB_RIGHTSHIFT			0xA1
#define KB_LEFTCTRL				0xA2
#define KB_RIGHTCTRL			0xA3
#define KB_OEM1					0xBA
#define KB_OEM_PLUS				0XBB
#define KB_OEM_COMMA			0xBC
#define KB_OEM_MINUS			0xBD
#define KB_OEM_PERIOD			0xBE
#define KB_OEM_2				0xBF
#define KB_OEM_3				0xC0
#define KB_OEM_4				0xDB
#define KB_OEM_5				0xDC
#define KB_OEM_6				0xDD
#define KB_OEM_7				0xDE
#define KB_OEM_8				0xDF
#define KB_OEM_102				0xE2


//bitmasks

//set 1
#define KB_BITMASK_BACKSPACE	0x0000000000000001
#define KB_BITMASK_TAB			0x0000000000000002
#define KB_BITMASK_CLEAR		0x0000000000000004
#define KB_BITMASK_ENTER		0x0000000000000008
#define KB_BITMASK_SHIFT		0x0000000000000010
#define KB_BITMASK_CTRL			0x0000000000000020
#define KB_BITMASK_ALT			0x0000000000000040
#define KB_BITMASK_PAUSE		0x0000000000000080
#define KB_BITMASK_CAPSLOCK		0x0000000000000100
#define KB_BITMASK_ESCAPE		0x0000000000000200
#define KB_BITMASK_SPACE		0x0000000000000400
#define KB_BITMASK_PAGEUP		0x0000000000000800
#define KB_BITMASK_PAGEDOWN		0x0000000000001000
#define KB_BITMASK_END			0x0000000000002000
#define KB_BITMASK_HOME			0x0000000000004000
#define KB_BITMASK_LEFTARROW	0x0000000000008000
#define KB_BITMASK_UPARROW		0x0000000000010000
#define KB_BITMASK_RIGHTARROW	0x0000000000020000
#define KB_BITMASK_DOWNARROW	0x0000000000040000
#define KB_BITMASK_SELECT		0x0000000000080000
#define KB_BITMASK_PRINT		0x0000000000100000
#define KB_BITMASK_EXECUTE		0x0000000000200000
#define KB_BITMASK_PRINTSCREEN	0x0000000000400000
#define KB_BITMASK_INSERT		0x0000000000800000
#define KB_BITMASK_DELETE		0x0000000001000000
#define KB_BITMASK_HELP			0x0000000002000000
#define KB_BITMASK_0			0x0000000004000000
#define KB_BITMASK_1			0x0000000008000000
#define KB_BITMASK_2			0x0000000010000000
#define KB_BITMASK_3			0x0000000020000000
#define KB_BITMASK_4			0x0000000040000000
#define KB_BITMASK_5			0x0000000080000000
#define KB_BITMASK_6			0x0000000100000000
#define KB_BITMASK_7			0x0000000200000000
#define KB_BITMASK_8			0x0000000400000000
#define KB_BITMASK_9			0x0000000800000000
#define KB_BITMASK_A			0x0000001000000000
#define KB_BITMASK_B			0x0000002000000000
#define KB_BITMASK_C			0x0000004000000000
#define KB_BITMASK_D			0x0000008000000000
#define KB_BITMASK_E			0x0000010000000000
#define KB_BITMASK_F			0x0000020000000000
#define KB_BITMASK_G			0x0000040000000000
#define KB_BITMASK_H			0x0000080000000000
#define KB_BITMASK_I			0x0000100000000000
#define KB_BITMASK_J			0x0000200000000000
#define KB_BITMASK_K			0x0000400000000000
#define KB_BITMASK_L			0x0000800000000000
#define KB_BITMASK_M			0x0001000000000000
#define KB_BITMASK_N			0x0002000000000000
#define KB_BITMASK_O			0x0004000000000000
#define KB_BITMASK_P			0x0008000000000000
#define KB_BITMASK_Q			0x0010000000000000
#define KB_BITMASK_R			0x0020000000000000
#define KB_BITMASK_S			0x0040000000000000
#define KB_BITMASK_T			0x0080000000000000
#define KB_BITMASK_U			0x0100000000000000
#define KB_BITMASK_V			0x0200000000000000
#define KB_BITMASK_W			0x0400000000000000
#define KB_BITMASK_X			0x0800000000000000
#define KB_BITMASK_Y			0x1000000000000000
#define KB_BITMASK_Z			0x2000000000000000
#define KB_BITMASK_LWIN			0x4000000000000000
#define KB_BITMASK_RWIN			0x8000000000000000
//set 2
#define KB_BITMASK_APPS				0x0000000000000001
#define KB_BITMASK_SLEEP			0x0000000000000002
#define KB_BITMASK_NUMPAD0			0x0000000000000004
#define KB_BITMASK_NUMPAD1			0x0000000000000008
#define KB_BITMASK_NUMPAD2			0x0000000000000010
#define KB_BITMASK_NUMPAD3			0x0000000000000020
#define KB_BITMASK_NUMPAD4			0x0000000000000040
#define KB_BITMASK_NUMPAD5			0x0000000000000100
#define KB_BITMASK_NUMPAD6			0x0000000000000200
#define KB_BITMASK_NUMPAD7			0x0000000000000400
#define KB_BITMASK_NUMPAD8			0x0000000000000800
#define KB_BITMASK_NUMPAD9			0x0000000000001000
#define KB_BITMASK_ASTERISK			0x0000000000002000
#define KB_BITMASK_PLUS				0x0000000000004000
#define KB_BITMASK_MINUS			0x0000000000008000
#define KB_BITMASK_COMMA			0x0000000000010000
#define KB_BITMASK_FORWARDSLASH		0x0000000000020000
#define KB_BITMASK_NUMLOCK			0x0000000000040000
#define KB_BITMASK_SCROLLLOCK		0x0000000000080000
#define KB_BITMASK_F1				0x0000000000100000
#define KB_BITMASK_F2				0x0000000000200000
#define KB_BITMASK_F3				0x0000000000400000
#define KB_BITMASK_F4				0x0000000000800000
#define KB_BITMASK_F5				0x0000000001000000
#define KB_BITMASK_F6				0x0000000002000000
#define KB_BITMASK_F7				0x0000000004000000
#define KB_BITMASK_F8				0x0000000008000000
#define KB_BITMASK_F9				0x0000000010000000
#define KB_BITMASK_F10				0x0000000020000000
#define KB_BITMASK_F11				0x0000000040000000
#define KB_BITMASK_F12				0x0000000080000000
#define KB_BITMASK_F13				0x0000000100000000
#define KB_BITMASK_F14				0x0000000200000000
#define KB_BITMASK_F15				0x0000000400000000
#define KB_BITMASK_F16				0x0000000800000000
#define KB_BITMASK_F17				0x0000001000000000
#define KB_BITMASK_F18				0x0000002000000000
#define KB_BITMASK_F19				0x0000004000000000
#define KB_BITMASK_F20				0x0000008000000000
#define KB_BITMASK_F21				0x0000010000000000
#define KB_BITMASK_F22				0x0000020000000000
#define KB_BITMASK_F23				0x0000040000000000	
#define KB_BITMASK_F24				0x0000080000000000
#define KB_BITMASK_LEFTSHIFT		0x0000100000000000
#define KB_BITMASK_RIGHTSHIFT		0x0000200000000000
#define KB_BITMASK_LEFTCTRL			0x0000400000000000
#define KB_BITMASK_RIGHTCTRL		0x0000800000000000
#define KB_BITMASK_OEM1				0x0001000000000000
#define KB_BITMASK_OEM_PLUS			0x0002000000000000
#define KB_BITMASK_OEM_COMMA		0x0004000000000000
#define KB_BITMASK_OEM_MINUS		0x0008000000000000
#define KB_BITMASK_OEM_PERIOD		0x0010000000000000
#define KB_BITMASK_OEM_2			0x0020000000000000
#define KB_BITMASK_OEM_3			0x0040000000000000
#define KB_BITMASK_OEM_4			0x0080000000000000
#define KB_BITMASK_OEM_5			0x0100000000000000
#define KB_BITMASK_OEM_6			0x0200000000000000
#define KB_BITMASK_OEM_7			0x0400000000000000
#define KB_BITMASK_OEM_8			0x0800000000000000
#define KB_BITMASK_OEM_102			0x1000000000000000


#endif