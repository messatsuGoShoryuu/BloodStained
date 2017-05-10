#ifndef BS_WINDOWSLISTVIEWWINDOW_H
#define BS_WINDOWSLISTVIEWWINDOW_H

#include "bs_WindowsEditorWindow.h"

#define BS_LISTVIEW_REST 0x00000000
#define BS_LISTVIEW_DRAG 0x00000001

#include <CommCtrl.h>
#include "../../Resources/bs_Path.h"
#include "../bs_EditorEnums.h"

namespace bs
{
	namespace editor
	{
		

		class WindowsListviewWindow : public WindowsEditorWindow
		{
		public:
			WindowsListviewWindow();
			WindowsListviewWindow(const char* windowName);
			WindowsListviewWindow(const WindowsListviewWindow& w);
			~WindowsListviewWindow();

			bool	initialize() override;
			void	destroy() override;

			void addItem(const char* itemName, LISTVIEW_ICON icon);
			void clearWindow();

		public:
			BaseMemberFunction<void, ui32>* OnDoubleClick;
			BaseMemberFunction<void, const Array<Path>&>*	OnDropFiles;
			BaseMemberFunction<void, ui16>*	OnCommand;
			//t0 = this, t1 = x, t2 = y.
			BaseMemberFunction<void, WindowsListviewWindow*, i32, i32>* OnContext;
		private:
			bool	_initializeIcons();
			bool	_initializeWndProc();

			void	_notify(WPARAM wParam, LPARAM lParam);
			void	_mouseMove(WPARAM wParam, LPARAM lParam);
			void	_mouseButtonUp(ui8 button, WPARAM wParam, LPARAM lParam);

			MemberFunction<WindowsListviewWindow, void, WPARAM, LPARAM> m_notifyDelegate;
			MemberFunction<WindowsListviewWindow, void, WPARAM, LPARAM> m_mouseMoveDelegate;
			MemberFunction<WindowsListviewWindow, void, ui8, WPARAM, LPARAM> m_mouseButtonUpDelegate;

		private:
			//WndProc
			static	LRESULT CALLBACK	lvWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
		private:
			//Wndproc to override.
			static WNDPROC	sm_defaultWndProc;
			i32	m_icons[9];
			i32	m_smallIcons[9];
			ui32 m_lastInsertedItemIndex;

			//Drag and drop
			POINT	m_dragAndDropCursor;
			HIMAGELIST m_dragImageList;

			ui32	m_stateFlags;

		};
	}
}


#endif // !BS_WINDOWSLISTVIEWWINDOW_H
