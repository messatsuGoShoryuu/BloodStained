#ifndef BS_WINDOWSWINDOW_H
#define BS_WINDOWSWINDOW_H

#include <Windows.h>

#include "../../../Containers/bs_Array.h"
#include "../../../Functions/bs_Function.h"
#include "../../../Functions/bs_MemberFunction.h"

namespace bs
{
	class WindowsWindow;
	typedef Array<WindowsWindow*> ChildWindowList;
	typedef Function<LRESULT, WindowsWindow*, HWND, UINT, WPARAM, LPARAM> WindowCallback;

	//Bounding box of a window.
	struct WindowMetrics
	{
		ui32 x;
		ui32 y;
		ui32 w;
		ui32 h;
	};

	class WindowsWindow
	{
	public:
		//Default constructor.
		WindowsWindow();

		//Copy constructor.
		WindowsWindow(const WindowsWindow& w);

		/*Parent window constructor.
		**@param className WindowClass classname.
		**@param windowName Name to be displayed on the toolbar.
		**@param wndProc Window procedure callback.
		**@param style Window style.
		*/
		WindowsWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style);

		/*Child window constructor.
		**@param className WindowClass classname.
		**@param windowName Name to be displayed on the toolbar.
		**@param wndProc Window procedure callback.
		**@param style Window style.
		**@param parent Pointer to parent window.
		*/
		WindowsWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style, WindowsWindow* parent);

		/*Child window constructor.
		**@param className WindowClass classname.
		**@param windowName Name to be displayed on the toolbar.
		**@param wndProc Window procedure callback.
		**@param style Window style.
		**@param exStyle ExWindow style.
		**@param parent Pointer to parent window.
		*/
		WindowsWindow(LPCSTR className, LPCSTR windowName, WindowCallback wndProc, DWORD style, DWORD exStyle, WindowsWindow* parent);

		//Destructor.
		virtual ~WindowsWindow();

		/*Set the bounding box of the window.
		**@param x X coordinate of the top left point of the bounding box.
		**@param y Y coordinate of the top right point of the bounding box.
		**@param w width of the bounding box.
		**@param h height of the bounding box.
		*/
		void setMetrics(ui32 x, ui32 y, ui32 w, ui32 h);

		//Overridable stuff
		virtual bool initialize();
		virtual void update(MSG* msg);
		virtual void destroy();

		void setParent(WindowsWindow* other);
		inline const WindowsWindow* parent(){ return m_parent; }
		
		const WindowMetrics& metrics(){ return m_metrics; }

		HWND hwnd() const { return m_hwnd; }

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		inline void setResizeable(bool value)
		{
			if (value)
				m_style |= WS_THICKFRAME;
			else
				m_style &= ~(WS_THICKFRAME);
		}

		inline void setCaption(bool value)
		{
			if (value)
				m_style |= WS_CAPTION | WS_SYSMENU;
			else
				m_style &= ~(WS_CAPTION | WS_SYSMENU);
		}

		inline void embed(bool value)
		{
			if (value)
				m_style |= WS_CHILD | WS_VISIBLE;
			else
				m_style &= (~WS_CHILD | WS_VISIBLE);
		}

	public:
		//Window procedure.
		WindowCallback memberWndProc;

		//Callbacks
		BaseMemberFunction<void, void>*	OnCreate;
		BaseMemberFunction<void, void>* OnResize;

	protected:
		//Window handle.
		HWND				m_hwnd;
		WNDCLASS			m_wndClass;
		LPCSTR				m_windowName;
		DWORD				m_style;
		DWORD				m_exStyle;

		//Pointer to parent.
		WindowsWindow*		m_parent;
		
		//Bounding box.
		WindowMetrics		m_metrics;

		//Array of children.
		ChildWindowList		m_childList;
	};
}

#endif // !BS_WINDOWSWINDOW_H

