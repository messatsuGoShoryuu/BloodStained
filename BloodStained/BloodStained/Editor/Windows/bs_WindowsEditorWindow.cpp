#include "bs_WindowsEditorWindow.h"
#include <CommCtrl.h>
#include "bs_WindowsListviewWindow.h"
#include "../../Globals/bs_globals.h"
#include "../../Platform/Windows/Input/bs_WindowsInput.h"


namespace bs
{
	namespace editor
	{
		WindowsEditorWindow::WindowsEditorWindow()
			:WindowsWindow("WindowsEditorClass", "Bloodstained Editor Window", wndProc, WS_OVERLAPPEDWINDOW),
			m_backgroundColor(ColorRGB24::black),
			m_textColor(ColorRGB24::white),
			m_textStyle(0),
			m_textSize(16),
			m_textFormat(BS_ALIGN_LEFT | BS_ALIGN_TOP)
		{
			strcpy_s(m_textFont, "Calibri");
		}

		WindowsEditorWindow::WindowsEditorWindow(const WindowsEditorWindow& w)
			:WindowsWindow(w),
			m_backgroundColor(w.m_backgroundColor),
			m_textColor(w.m_textColor),
			m_textStyle(w.m_textStyle),
			m_textSize(w.m_textSize),
			m_textFormat(w.m_textFormat)
		{
			strcpy_s(m_textFont, w.m_textFont);
		}

		WindowsEditorWindow::WindowsEditorWindow(const char* windowName)
			:WindowsWindow(windowName, windowName, wndProc, WS_OVERLAPPEDWINDOW),
			m_backgroundColor(ColorRGB24::black),
			m_textColor(ColorRGB24::white),
			m_textStyle(0),
			m_textSize(16),
			m_textFormat(BS_ALIGN_LEFT | BS_ALIGN_TOP)
		{
			std::cout << BS_UNDECORATED_FUNCTION << " " << windowName << std::endl;
			strcpy_s(m_textFont, "Calibri");
		}

		WindowsEditorWindow::~WindowsEditorWindow()
		{
			WindowsWindow::~WindowsWindow();
		}

		void WindowsEditorWindow::destroy()
		{
			WindowsWindow::destroy();
			ui32 menuCount = m_menus.count();
			for (ui32 i = 0; i < menuCount; i++)
			{
				if (m_menus[i] != NULL) DestroyMenu(m_menus[i]);
			}
			m_menus.reset();
			m_texts.reset();
		}

		void	WindowsEditorWindow::setMetrics(ui32 x, ui32 y, ui32 w, ui32 h)
		{
			WindowsWindow::setMetrics(x, y, w, h);
		}

		ui32	WindowsEditorWindow::addMenu()
		{
			return	m_menus.add(CreateMenu());
		}

		void WindowsEditorWindow::registerMenu(ui32 menuIndex)
		{
			SetMenu(m_hwnd, m_menus[menuIndex]);
		}

		void	WindowsEditorWindow::createRightClickMenu()
		{
			HMENU dummy = NULL;
			m_rightClickMenu = m_menus.add(dummy);
		}

		void	WindowsEditorWindow::beginRightClickMenu()
		{
			m_menus[m_rightClickMenu] = CreatePopupMenu();
			
		}

		void	WindowsEditorWindow::appendRightClickMenu(char* utf8, ui16 id)
		{
			if (m_menus[m_rightClickMenu])
			InsertMenu(m_menus[m_rightClickMenu], 0, MF_BYCOMMAND | MF_STRING, id, utf8);
		}

		void	WindowsEditorWindow::endRightClickMenu(i32 x, i32 y)
		{
			if (m_menus[m_rightClickMenu])
			{
				SetForegroundWindow(m_hwnd);
				TrackPopupMenu(m_menus[m_rightClickMenu], TPM_TOPALIGN | TPM_LEFTALIGN, x, y, 0, m_hwnd, NULL);
			}
		}

		ui32	WindowsEditorWindow::addPopupMenu(char* utf8, ui32 menuIndex)
		{
			HMENU parent = m_menus[menuIndex];
			HMENU child = CreatePopupMenu();
			AppendMenu(parent, MF_STRING | MF_POPUP, (UINT)child, utf8);
			return m_menus.add(child);
		}

		void	WindowsEditorWindow::appendPopupMenu(char* utf8, ui32 menuIndex)
		{
			AppendMenu(m_menus[menuIndex], MF_STRING, 0, utf8);
		}

		void	WindowsEditorWindow::setBackgroundColor(ui8 r, ui8 g, ui8 b)
		{
			m_backgroundColor.r = r;
			m_backgroundColor.g = g;
			m_backgroundColor.b = b;
		}

		void	WindowsEditorWindow::setBackgroundColor(const ColorRGB24& color)
		{
			m_backgroundColor = color;
		}


		void	WindowsEditorWindow::setTextColor(ui8 r, ui8 g, ui8 b)
		{
			m_textColor.r = r;
			m_textColor.g = g;
			m_textColor.b = b;
		}

		void WindowsEditorWindow::setTextProperties(ui32 format, ui32 style, ui32 size, const char* font)
		{
			m_textFormat = format;
			m_textStyle = style;
			m_textSize = size;
			strcpy_s(m_textFont, font);
		}

		void	WindowsEditorWindow::setTextColor(const ColorRGB24& color)
		{
			m_textColor = color;
		}

		ui32	WindowsEditorWindow::setText(const char* text, i32 boxTop, i32 boxLeft, i32 boxWidth, i32 boxHeight)
		{
			ui32 index = m_texts.add(WindowsEditorWindowTextRegistry());
			//String
			m_texts[index].text = text;
			//Textbox
			m_texts[index].rect.top = boxTop;
			m_texts[index].rect.bottom = boxTop + boxHeight;
			m_texts[index].rect.left = boxLeft;
			m_texts[index].rect.right = boxLeft + boxWidth;

			m_texts[index].color = m_textColor;
			strcpy_s(m_texts[index].font, m_textFont);
			m_texts[index].format = m_textFormat;
			m_texts[index].style = m_textStyle;
			m_texts[index].size = m_textSize;

			return index;
		}

		ui32	WindowsEditorWindow::setText(const String& text, i32 boxTop, i32 boxLeft, i32 boxWidth, i32 boxHeight)
		{
			ui32 index = m_texts.add(WindowsEditorWindowTextRegistry());
			//String
			m_texts[index].text = text;
			//Textbox
			m_texts[index].rect.top = boxTop;
			m_texts[index].rect.bottom = boxTop + boxHeight;
			m_texts[index].rect.left = boxLeft;
			m_texts[index].rect.right = boxLeft + boxWidth;

			m_texts[index].color = m_textColor;
			strcpy_s(m_texts[index].font, m_textFont);
			m_texts[index].format = m_textFormat;
			m_texts[index].style = m_textStyle;
			m_texts[index].size = m_textSize;

			return index;
		}

		ui32	WindowsEditorWindow::setTextMargin(const char* text, i32 marginLeft, i32 marginRight, i32 marginTop, i32 marginBottom)
		{
			ui32 index = m_texts.add(WindowsEditorWindowTextRegistry());
			//String
			m_texts[index].text = text;

			RECT clientRect;
			GetClientRect(m_hwnd, &clientRect);
			//Textbox

			m_texts[index].rect.top = clientRect.top + marginTop;
			m_texts[index].rect.bottom = clientRect.bottom - marginBottom;
			m_texts[index].rect.left = clientRect.left + marginLeft;
			m_texts[index].rect.right = clientRect.right - marginRight;

			m_texts[index].color = m_textColor;
			strcpy_s(m_texts[index].font, m_textFont);
			m_texts[index].format = m_textFormat;
			m_texts[index].style = m_textStyle;
			m_texts[index].size = m_textSize;

			return index;
		}

		ui32	WindowsEditorWindow::setTextMargin(const String& text, i32 marginLeft, i32 marginRight, i32 marginTop, i32 marginBottom)
		{
			ui32 index = m_texts.add(WindowsEditorWindowTextRegistry());
			//String
			m_texts[index].text = text;
			//Textbox
			RECT clientRect;
			GetClientRect(m_hwnd, &clientRect);

			m_texts[index].rect.top = clientRect.top + marginTop;
			m_texts[index].rect.bottom = clientRect.bottom - marginBottom;
			m_texts[index].rect.left = clientRect.left + marginLeft;
			m_texts[index].rect.right = clientRect.right - marginRight;

			m_texts[index].color = m_textColor;
			strcpy_s(m_texts[index].font, m_textFont);
			m_texts[index].format = m_textFormat;
			m_texts[index].style = m_textStyle;
			m_texts[index].size = m_textSize;

			return index;
		}

		void	WindowsEditorWindow::clearTexts()
		{
			if (m_texts.count() > 0)
			m_texts.clear();
		}

		void	WindowsEditorWindow::refreshDisplay()
		{
			RECT rect;
			GetClientRect(m_hwnd, &rect);
			InvalidateRect(m_hwnd, &rect, false);
		}

		LRESULT	WindowsEditorWindow::wndProc(WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			WindowsEditorWindow* derived = dynamic_cast<WindowsEditorWindow*>(w);
			switch (uMsg)
			{
				case WM_CREATE:
				{
					if (derived->OnCreateFunction.canExecute()) derived->OnCreateFunction();
				}
				return 0;
				case WM_INPUT:
					if (!derived->parent())
						WindowsInput::getInput(lParam);
					return 0;
				case WM_CLOSE:
					DestroyWindow(hwnd);
					return 0;
				case WM_DESTROY:
					if (!w->parent())
					{
						PostQuitMessage(0);
						g_game.quit();
					}
					return 0;
				case WM_NOTIFY:
					if (derived->m_listviewNotifyFunction)
					{
						if ((*(derived->m_listviewNotifyFunction)).canExecute())
						{
							(*(derived->m_listviewNotifyFunction))(wParam, lParam);
						}
					}

					return 0;

				case WM_MOUSEMOVE:
					if (derived->m_listviewMouseMoveFunction)
					{
						if ((*(derived->m_listviewMouseMoveFunction)).canExecute())
						{
							(*(derived->m_listviewMouseMoveFunction))(wParam, lParam);
						}
					}
					return 0;

				case WM_LBUTTONUP:

					if (derived->m_listviewMouseUpFunction)
					{
						if ((*(derived->m_listviewMouseUpFunction)).canExecute())
						{
							(*(derived->m_listviewMouseUpFunction))(0, wParam, lParam);
						}
					}
					return 0;

				case WM_RBUTTONUP:
					if (derived->m_listviewMouseUpFunction)
					{
						if ((*(derived->m_listviewMouseUpFunction)).canExecute())
						{
							(*(derived->m_listviewMouseUpFunction))(1, wParam, lParam);
						}
					}
					return 0;
				case WM_PAINT:
				{

					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hwnd, &ps);

					HFONT font = NULL;
					HFONT oldFont = NULL;

					HBRUSH brush = CreateSolidBrush(BS_COLOR(derived->m_backgroundColor));
					FillRect(hdc, &ps.rcPaint, brush);

					ui32 textCount = derived->m_texts.count();

					for (ui32 i = 0; i < textCount; i++)
					{
						font = CreateFont(
							derived->m_texts[i].size,
							0, 0, 0, 300,
							derived->m_texts[i].style & BS_ITALIC,
							derived->m_texts[i].style & BS_UNDERLINE,
							false,
							DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
							derived->m_texts[i].font);

						oldFont = (HFONT)SelectObject(hdc, font);

						SetTextColor(hdc, BS_COLOR(derived->m_texts[i].color));
						SetBkColor(hdc, BS_COLOR(derived->m_backgroundColor));

						DrawText(hdc, derived->m_texts[i].text.utf8(),
								 -1,
								 &derived->m_texts[i].rect,
								 derived->m_texts[i].format);

						DeleteObject(font);
					}
					EndPaint(hwnd, &ps);

					SelectObject(hdc, oldFont);
					return 0;
				}
				case WM_EXITSIZEMOVE:
					RECT rect;
					GetClientRect(hwnd, &rect);
					InvalidateRect(hwnd, &rect, false);

					return 0;

				case WM_COMMAND:
					ui16 id;
					id = LOWORD(wParam);

					if (derived->m_commandFunction)
					{
						if (derived->m_commandFunction->canExecute())
						{
							(*(derived->m_commandFunction))(id);
						}
					}
					return 0;
				case WM_SIZING:
					GetClientRect(hwnd, &rect);
					for (ui32 i = 0; i < derived->m_childList.count(); i++)
					{
						LONG right = (LONG)(derived->m_childList[i]->metrics().x + derived->m_childList[i]->metrics().w);
						LONG bottom = (LONG)(derived->m_childList[i]->metrics().y + derived->m_childList[i]->metrics().h);

						right = rect.right <= right ? (rect.right - 1) : right;
						bottom = rect.bottom <=  bottom ? (rect.bottom -1) : bottom;


						SetWindowPos(derived->m_childList[i]->hwnd(), 
									 NULL,
									 derived->m_childList[i]->metrics().x, 
									 derived->m_childList[i]->metrics().y,
									 right, 
									 bottom, 
									 SWP_NOZORDER | SWP_NOACTIVATE);
					}

					GetClientRect(hwnd, &rect);
					InvalidateRect(hwnd, &rect, false);

					return 0;

			}
			return 1;
		}
	}
}
