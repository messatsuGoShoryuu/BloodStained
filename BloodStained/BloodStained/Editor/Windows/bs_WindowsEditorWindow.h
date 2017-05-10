#ifndef BS_WINDOWSEDITORWINDOW_H
#define BS_WINDOWSEDITORWINDOW_H

#include "../../Platform/Windows/WindowsWindow/bs_WindowsWindow.h"
#include "../../Rendering/bs_Color.h"
#include "../../Utilities/bs_String.h"
#include "../../Functions/bs_MemberFunction.h"


#define	BS_ITALIC		0x01
#define BS_UNDERLINE	0x02
#define BS_ALIGN_TOP	DT_TOP
#define BS_ALIGN_LEFT	DT_LEFT

#define	BS_COLOR(c) RGB(c.r,c.g,c.b)
namespace bs
{
	namespace editor
	{
		class WindowsListviewWindow;
		struct WindowsEditorWindowTextRegistry
		{
			RECT		rect;
			ColorRGB24	color;
			String		text;
			char		font[64];
			UINT		size;
			UINT		format;
			UINT		style;
		};


		class WindowsEditorWindow : public WindowsWindow
		{
		public:
			friend class WindowsListviewWindow;

			//Default constructor.
			WindowsEditorWindow();

			WindowsEditorWindow(const char* windowName);
			//Copy constructor.
			WindowsEditorWindow(const WindowsEditorWindow& w);
			//Virtual destructor.
			virtual ~WindowsEditorWindow() override;

			//Manual destruction
			virtual void destroy() override;


			ui32	addMenu();
			/*Adds a popup menu
			**@param utf8 An utf8 string for the text to be displayed.
			**Returns the index of the newly added menu.
			*/
			ui32	addPopupMenu(char* utf8, ui32 menuIndex);

			/*Adds a submenu to the specified menu.
			**@param utf8 An utf8 string for the text to be displayed.
			**Returns the index of the newly added menu.
			*/
			void	appendPopupMenu(char* utf8, ui32 menuIndex);

			//Registers menu to the window.
			void	registerMenu(ui32 menuIndex);

			void	setMetrics(ui32 x, ui32 y, ui32 w, ui32 h);

			void	createRightClickMenu();
			void	beginRightClickMenu();
			void	appendRightClickMenu(char* utf8, ui16 id);
			void	endRightClickMenu(i32 x, i32 y);
			

			/*Sets the window background color.
			*@param r Red (0 - 255)
			*@param g Green (0 - 255)
			*@param b Blue (0 - 255)
			*/
			void	setBackgroundColor(ui8 r, ui8 g, ui8 b);

			/*Sets the window background color.
			*@param color	24 bit color struct with rgb values.
			*/
			void	setBackgroundColor(const ColorRGB24& color);
			
			/*Sets the window text color.
			*@param r Red (0 - 255)
			*@param g Green (0 - 255)
			*@param b Blue (0 - 255)
			*/
			void	setTextColor(ui8 r, ui8 g, ui8 b);

			/*Sets the window text color.
			*@param color	24 bit color struct with rgb values.
			*/
			void	setTextColor(const ColorRGB24& color);

			/*Adds text to the window at the specified box.
			**Returns the index 
			**@param text C string to be placed.
			**@param boxTop Y coordinate of the top left point in window coordinates.
			**@param boxLeft X coordinate of the top left point in window coordinates.
			**@param boxWidth width of the textbox.
			**@param boxHeight height of the textbox.
			*/
			ui32	setText(const char* text, i32 boxTop, i32 boxLeft, i32 boxWidth, i32 boxHeight);
			//String version
			ui32	setText(const String& text, i32 boxTop, i32 boxLeft, i32 boxWidth, i32 boxHeight);

			//Adds text to the window with specified margins.
			ui32	setTextMargin(const char* text, i32 marginLeft, i32 marginRight, i32 marginTop, i32 marginBottom);
			//String version
			ui32	setTextMargin(const String& text, i32 marginLeft, i32 marginRight, i32 marginTop, i32 marginBottom);

			void	setTextProperties(ui32 format, ui32 style, ui32 size, const char* font);

			//Clears all texts.
			void	clearTexts();

			//Repaint window
			void	refreshDisplay();
		public:		
			//Callbacks
			BaseMemberFunction<void, void> OnCreateFunction;
			BaseMemberFunction<void,void> OnDestroyFunction;
			BaseMemberFunction <void, WindowsEditorWindow*> OnContextMenuFunction;

		private:

			static LRESULT	wndProc(WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		private:
			BaseMemberFunction<void, WPARAM, LPARAM>* m_listviewNotifyFunction;
			BaseMemberFunction<void, WPARAM, LPARAM>* m_listviewMouseMoveFunction;
			BaseMemberFunction<void, ui8, WPARAM, LPARAM>* m_listviewMouseUpFunction;
			BaseMemberFunction<void, ui16>*	m_commandFunction;
		protected:
			char	m_textFont[64];
			ColorRGB24	m_backgroundColor;
			ColorRGB24	m_textColor;

			ui32	m_rightClickMenu;
			UINT	m_textFormat;
			UINT	m_textStyle;
			UINT	m_textSize;

			Array<WindowsEditorWindowTextRegistry> m_texts;
			Array<HMENU>	m_menus;
		};
	}
}


#endif // !BS_WINDOWSEDITORWINDOW_H
