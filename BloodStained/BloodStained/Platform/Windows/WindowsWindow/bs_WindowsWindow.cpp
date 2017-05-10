#include "bs_WindowsWindow.h"
#include "../../../Globals/bs_globals.h"
#include <CommCtrl.h>

namespace bs
{
	WindowsWindow::WindowsWindow() :
		m_windowName("Windows Window"),
		m_style(WS_OVERLAPPEDWINDOW),
		m_parent(NULL),
		m_exStyle(WS_EX_CLIENTEDGE)
	{
		m_wndClass.hInstance = g_windowsMain.hinstance();
		m_wndClass.lpszClassName = "WindowsWindowClass";
		m_wndClass.lpfnWndProc = NULL;

		m_metrics.x = CW_USEDEFAULT;
		m_metrics.y = CW_USEDEFAULT;
		m_metrics.w = CW_USEDEFAULT;
		m_metrics.h = CW_USEDEFAULT;
	}

	WindowsWindow::WindowsWindow(const WindowsWindow& w)
		:m_windowName(w.m_windowName),
		m_hwnd(w.m_hwnd),
		m_parent(w.m_parent),
		m_wndClass(w.m_wndClass),
		m_style(w.m_style),
		m_exStyle(w.m_exStyle),
		m_metrics(w.m_metrics),
		m_childList(w.m_childList),
		memberWndProc(w.memberWndProc)
	{

	}

	WindowsWindow::WindowsWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style) :
		m_windowName(windowName),
		m_style(style),
		m_exStyle(WS_EX_CLIENTEDGE),
		m_parent(NULL),
		memberWndProc(wndProc)
	{
		if (className != WC_LISTVIEW)
		m_wndClass.hInstance = g_windowsMain.hinstance();
		m_wndClass.lpszClassName = className;
		m_wndClass.lpfnWndProc = WndProc;

		m_metrics.x = CW_USEDEFAULT;
		m_metrics.y = CW_USEDEFAULT;
		m_metrics.w = CW_USEDEFAULT;
		m_metrics.h = CW_USEDEFAULT;
	}

	WindowsWindow::WindowsWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style, WindowsWindow* parent) :
		m_windowName(windowName),
		m_style(style),
		m_exStyle(WS_EX_CLIENTEDGE),
		m_parent(parent),
		memberWndProc(wndProc)
	{
		m_wndClass.hInstance = g_windowsMain.hinstance();
		m_wndClass.lpszClassName = className;
		m_wndClass.lpfnWndProc = WndProc;
		

		m_metrics.x = CW_USEDEFAULT;
		m_metrics.y = CW_USEDEFAULT;
		m_metrics.w = CW_USEDEFAULT;
		m_metrics.h = CW_USEDEFAULT;

		if(m_parent) m_parent->m_childList.add(this);
	}

	WindowsWindow::WindowsWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style, DWORD exStyle, WindowsWindow* parent)
		:m_windowName(windowName),
		m_style(style),
		m_exStyle(exStyle),
		m_parent(parent),
		memberWndProc(wndProc)
	{
		m_wndClass.hInstance = g_windowsMain.hinstance();
		m_wndClass.lpszClassName = className;
		m_wndClass.lpfnWndProc = WndProc;

		m_metrics.x = CW_USEDEFAULT;
		m_metrics.y = CW_USEDEFAULT;
		m_metrics.w = CW_USEDEFAULT;
		m_metrics.h = CW_USEDEFAULT;

		if (m_parent) m_parent->m_childList.add(this);
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::setMetrics(ui32 x, ui32 y, ui32 w, ui32 h)
	{
		m_metrics.x = x;
		m_metrics.y = y;
		m_metrics.w = w;
		m_metrics.h = h;
	}

	void WindowsWindow::setParent(WindowsWindow* other)
	{
		m_parent = other;
		m_parent->m_childList.add(this);
		m_style &= (~WS_OVERLAPPEDWINDOW);
	}

	void WindowsWindow::destroy()
	{
		ui32 s = m_childList.count();
		for (ui32 i = 0; i < s; i++)
		{
			m_childList[i]->destroy();
			if (m_childList[i])
			{
				delete m_childList[i];
				m_childList[i] = nullptr;
			}
		}
		m_childList.clear();
	}

	bool WindowsWindow::initialize()
	{
		m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

		bool isListView = strcmp(m_wndClass.lpszClassName, WC_LISTVIEW) == 0;

		if(!isListView)RegisterClass(&m_wndClass);
		
		if (!m_parent) m_style |= WS_CLIPCHILDREN;
		

		m_hwnd = NULL;

		RECT rect;
		rect.left = m_metrics.x;
		rect.right = m_metrics.w;
		rect.top = m_metrics.y+100;
		rect.bottom = m_metrics.h;
		AdjustWindowRectEx(&rect, m_style, false, m_exStyle);

		std::cout << "Creating window" << m_windowName << std::endl;
		m_hwnd = CreateWindowEx(
			m_exStyle,                              // Optional window styles.
			m_wndClass.lpszClassName,       // Window class
			m_windowName,					// Window text
			m_style,						// Window style

			// Size and position
			m_metrics.x, m_metrics.y, rect.right, rect.bottom,

			m_parent ? m_parent->m_hwnd : NULL,			// Parent window    
			NULL,										// Menu
			m_wndClass.hInstance,						// Instance handle
			this										// Additional application data
			);


		if (!m_hwnd)
		{
			return false;
		}

		ShowWindow(m_hwnd, SW_NORMAL);
		
		GetClientRect(m_hwnd, &rect);
		InvalidateRect(m_hwnd, &rect, false);

		m_metrics.x = rect.left;
		m_metrics.y = rect.right;
		m_metrics.w = rect.right;
		m_metrics.h = rect.bottom;
		return true;
	}

	void WindowsWindow::update(MSG* msg)
	{
		while (GetMessage(msg, m_hwnd, 0, 0))
		{
			TranslateMessage(msg);
			DispatchMessage(msg);
		}
	}


	LRESULT CALLBACK WindowsWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_ERASEBKGND) return 0;
		WindowsWindow* w = nullptr;

		if (uMsg == WM_CREATE)
		{
			w = static_cast<WindowsWindow*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
			if (w->OnCreate)
			{
				if (w->OnCreate->canExecute())
				{
					(*(w->OnCreate))();
				}
			}
		}

		if (uMsg == WM_NCCREATE)
		{
			w = static_cast<WindowsWindow*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

			SetLastError(0);
			if (!SetWindowLongPtr(hwnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(w)))
			{
				if (GetLastError() != 0)
					return 0;
			}
		}
		else
		{
			w = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hwnd, GWL_USERDATA));
		}

		int result = 1;
		if (w)
		{
			if (uMsg == WM_SIZING || uMsg == WM_MOVING)
			{
				RECT* rect = reinterpret_cast<RECT*>(lParam);

				w->m_metrics.x = rect->left;
				w->m_metrics.y = rect->top;
				w->m_metrics.w = max(rect->right, rect->left) - min(rect->right, rect->left);
				w->m_metrics.h = max(rect->top, rect->bottom) - min(rect->top, rect->bottom);

				if (w->OnResize)
				{
					if (w->OnResize->canExecute())
					{
						(*(w->OnResize))();
					}
				}
			}

			if (w->memberWndProc.getPointer() != NULL)
			{
				result = w->memberWndProc(w, hwnd, uMsg, wParam, lParam);
			}
		}

		if (result == 0) return result;
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}