#include "bs_WindowsListviewWindow.h"
#include "../../resource.h"
#include "../../Globals/bs_globals.h"
#include "../../Resources/bs_Path.h"


namespace bs
{
	namespace editor
	{
		WNDPROC		WindowsListviewWindow::sm_defaultWndProc;

		WindowsListviewWindow::WindowsListviewWindow()
			:WindowsEditorWindow("Editor Listview Window")
		{
			m_wndClass.lpszClassName = WC_LISTVIEW;
			m_style = LVS_EDITLABELS | WS_CHILD | WS_VISIBLE;
			m_exStyle = WS_EX_ACCEPTFILES;
		}

		WindowsListviewWindow::WindowsListviewWindow(const char* windowName)
			: WindowsEditorWindow(windowName)
		{
			m_wndClass.lpszClassName = WC_LISTVIEW;
			m_style = LVS_EDITLABELS | WS_CHILD | WS_VISIBLE;
			m_exStyle = WS_EX_ACCEPTFILES;
		}

		WindowsListviewWindow::WindowsListviewWindow(const WindowsListviewWindow& w)
			: WindowsEditorWindow(w)
		{
			m_wndClass.lpszClassName = WC_LISTVIEW;
			m_style = LVS_EDITLABELS | WS_CHILD | WS_VISIBLE;
			m_exStyle = WS_EX_ACCEPTFILES;
		}

		WindowsListviewWindow::~WindowsListviewWindow()
		{
			WindowsEditorWindow::~WindowsEditorWindow();
		}

		bool WindowsListviewWindow::initialize()
		{
			bool result = WindowsWindow::initialize();
			if (!_initializeWndProc()) std::cout << "WNDPROC initialization failed" << std::endl;
			if (!_initializeIcons()) std::cout << "Icon initialization failed" << std::endl;		
			if (m_parent)
			{
				WindowsEditorWindow* parent = dynamic_cast<WindowsEditorWindow*>(m_parent);
				m_notifyDelegate.setCaster(this);
				m_notifyDelegate = &WindowsListviewWindow::_notify;
				parent->m_listviewNotifyFunction = &m_notifyDelegate;

				m_mouseMoveDelegate.setCaster(this);
				m_mouseMoveDelegate = &WindowsListviewWindow::_mouseMove;
				parent->m_listviewMouseMoveFunction = &m_mouseMoveDelegate;

				m_mouseButtonUpDelegate.setCaster(this);
				m_mouseButtonUpDelegate = &WindowsListviewWindow::_mouseButtonUp;
				parent->m_listviewMouseUpFunction = &m_mouseButtonUpDelegate;

			}
			refreshDisplay();
			return result;
		}

		bool WindowsListviewWindow::_initializeWndProc()
		{
			if(!sm_defaultWndProc) sm_defaultWndProc = (WNDPROC)GetWindowLong(m_hwnd, GWL_WNDPROC);
			if (sm_defaultWndProc == 0) return false;

			LONG result = SetWindowLongPtr(m_hwnd, GWL_WNDPROC, (LONG_PTR)lvWndProc);
			SetWindowLongPtr(m_hwnd, GWL_USERDATA, (LONG_PTR)this);
			return result != 0;
		}

		void WindowsListviewWindow::destroy()
		{
			WindowsWindow::destroy();
		}

		bool WindowsListviewWindow::_initializeIcons()
		{
			HICON icon = NULL;
			HIMAGELIST imageList;
			HIMAGELIST imageListSmall;
			imageList = ImageList_Create(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), ILC_MASK | ILC_COLOR32, 9, 9);
			imageListSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CXSMICON), ILC_MASK | ILC_COLOR32, 9, 9);

			if (!imageList)
			{
				return false;
			}

			if (!imageListSmall)
			{
				return false;
			}

			for (ui32 i = 0; i < 9; i++)
			{
				switch ((LISTVIEW_ICON)i)
				{
					case LISTVIEW_ICON::OTHER:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_FILE_ICON));
						break;
					case LISTVIEW_ICON::FOLDER:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_FOLDER_ICON));
						break;
					case LISTVIEW_ICON::JPG:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_JPG_ICON));
						break;
					case LISTVIEW_ICON::PNG:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_PNG_ICON));
						break;
					case LISTVIEW_ICON::ZIP:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_ZIP_ICON));
						break;
					case LISTVIEW_ICON::TEXT:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_TEXT_ICON));
						break;
					case LISTVIEW_ICON::AUDIO:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_AUDIO_ICON));
						break;
					case LISTVIEW_ICON::SHADER:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_SHADER_ICON));
						break;
					default:
						icon = LoadIcon(m_wndClass.hInstance, MAKEINTRESOURCE(IDI_FILE_ICON));
						break;
				}

				if (!icon)
				{
					return false;
				}

				m_icons[i] =		ImageList_AddIcon(imageList, icon);
				m_smallIcons[i] =	ImageList_AddIcon(imageListSmall, icon);

				if (m_smallIcons[i] == -1 || m_icons[i] == -1)
				{
					return false;
				}

				DestroyIcon(icon);
				icon = NULL;
				
			}

			ListView_SetImageList(m_hwnd, imageList, LVSIL_NORMAL);			
			ListView_SetImageList(m_hwnd, imageListSmall, LVSIL_SMALL);

			return true;
		}

		void WindowsListviewWindow::addItem(const char* itemName, LISTVIEW_ICON icon)
		{
			LVITEM lvI;

			// Initialize LVITEM members that are common to all items.
			lvI.pszText = (LPSTR)itemName;
			lvI.mask = LVIF_TEXT | LVIF_IMAGE;
			lvI.stateMask = 0;
			lvI.cchTextMax = strlen(itemName);
			lvI.iSubItem = 0;
			lvI.state = 0;
			
			lvI.iItem = m_lastInsertedItemIndex++;
			lvI.iImage = m_icons[(ui32)icon];

			if (ListView_InsertItem(m_hwnd, &lvI) == -1)

			if (ListView_SetView(m_hwnd, LV_VIEW_ICON) == -1) std::cout << "Set view failed" << std::endl;
		}

		void WindowsListviewWindow::_notify(WPARAM wParam, LPARAM lParam)
		{
			UINT code = ((LPNMHDR)lParam)->code;

			switch (code)
			{
				case LVN_BEGINDRAG:
					LPNMLISTVIEW lv;
					lv = (LPNMLISTVIEW)(lParam);
					m_dragImageList = NULL;
					HIMAGELIST tempImageList;
					IMAGEINFO imageInfo;
					i32 height;
					height = 0;
					bool first;
					first = true;
					i32 pos;
					pos = ListView_GetNextItem(m_hwnd, -1, LVNI_SELECTED);
					POINT p;

					p.x = 0;
					p.y = 0;

				//	while (pos != -1)
					{
						if (first)
						{
							m_dragImageList = ListView_CreateDragImage(m_hwnd, pos, &p);
							ImageList_GetImageInfo(m_dragImageList, 0, &imageInfo);
							height = imageInfo.rcImage.bottom;
							first = false;
						}
					}

					ImageList_BeginDrag(m_dragImageList, 0, 0, 0);
					POINT actionPoint;
					actionPoint = lv->ptAction;

					ClientToScreen(m_hwnd, &actionPoint);
					ImageList_DragEnter(GetDesktopWindow(), actionPoint.x, actionPoint.y);

					m_stateFlags |= BS_LISTVIEW_DRAG;

					SetCapture(m_parent->hwnd());

					break;
				case LVN_BEGINLABELEDIT:
					break;
				case NM_DBLCLK:
					lv = (LPNMLISTVIEW)(lParam);

					if (OnDoubleClick)
					if (OnDoubleClick->canExecute())
					{
						(*OnDoubleClick)((ui32)lv->iItem);
					}
					break;
			}
		}

		void	WindowsListviewWindow::_mouseMove(WPARAM wParam, LPARAM lParam)
		{
			std::cout << "Mouse move" << std::endl;
			if ((m_stateFlags | BS_LISTVIEW_DRAG) != BS_LISTVIEW_DRAG) return;

			m_dragAndDropCursor.x = LOWORD(lParam);
			m_dragAndDropCursor.y = HIWORD(lParam);

			ClientToScreen(m_parent->hwnd(), &m_dragAndDropCursor);
			ImageList_DragMove(m_dragAndDropCursor.x, m_dragAndDropCursor.y);
		}

		void WindowsListviewWindow::_mouseButtonUp(ui8 button, WPARAM wParam, LPARAM lParam)
		{
			// End the drag-and-drop process
			m_stateFlags = (m_stateFlags & (~BS_LISTVIEW_DRAG));
			ImageList_DragLeave(m_hwnd);
			ImageList_EndDrag();
			ImageList_Destroy(m_dragImageList);

			ReleaseCapture();
		}

		void	WindowsListviewWindow::clearWindow()
		{
			m_lastInsertedItemIndex = 0;
			ListView_DeleteAllItems(m_hwnd);
		}

		LRESULT CALLBACK	WindowsListviewWindow::lvWndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
		{
			WindowsListviewWindow* w = nullptr;
			switch (uMsg)
			{
				case WM_PAINT:
					w = reinterpret_cast<WindowsListviewWindow*>(GetWindowLong(hwnd, GWL_USERDATA));
					ListView_SetBkColor(hwnd, BS_COLOR(w->m_backgroundColor));
					ListView_SetTextBkColor(hwnd, BS_COLOR(w->m_backgroundColor));
					ListView_SetTextColor(hwnd, BS_COLOR(w->m_textColor));
					return CallWindowProc(sm_defaultWndProc, hwnd, WM_PAINT, wparam, lparam);

				case WM_CONTEXTMENU:

					w = reinterpret_cast<WindowsListviewWindow*>(GetWindowLong(hwnd, GWL_USERDATA));
					if (w)
					{
						i32 x = ((i32)(i16)LOWORD(lparam));
						i32 y = ((i32)(i16)HIWORD(lparam));
						if (w->OnContext)
						{
							if (w->OnContext->canExecute())
							{
								(*(w->OnContext))(w, x, y);
							}
						}
					}
					return CallWindowProc(sm_defaultWndProc, hwnd, WM_CONTEXTMENU, wparam, lparam);

				case WM_COMMAND:
					w = reinterpret_cast<WindowsListviewWindow*>(GetWindowLong(hwnd, GWL_USERDATA));
					ui16 id;
					id = LOWORD(wparam);

					if (w->OnCommand)
					{
						if (w->OnCommand->canExecute())
						{
							(*(w->OnCommand))(id);
						}
					}
					return CallWindowProc(sm_defaultWndProc, hwnd, WM_COMMAND, wparam, lparam);
				
				case WM_DROPFILES:
					w = reinterpret_cast<WindowsListviewWindow*>(GetWindowLong(hwnd, GWL_USERDATA));
					HDROP hDrop = (HDROP)wparam;
					UINT fileCount = DragQueryFile(hDrop, BS_INVALID_INDEX, NULL, NULL);
					char fileName[MAX_PATH];

					Array<Path> pathArray;

					for (ui32 i = 0; i < fileCount; i++)
					{
						DragQueryFile(hDrop, i, fileName, sizeof(fileName));
						pathArray.add(Path(fileName));
					}
					
					if (w->OnDropFiles)
					if (w->OnDropFiles->canExecute()) (*(w->OnDropFiles))(pathArray);
					return CallWindowProc(sm_defaultWndProc, hwnd, WM_DROPFILES, wparam, lparam);

				
				

			}
			return CallWindowProc(sm_defaultWndProc, hwnd, uMsg, wparam, lparam);
			return 1;
		}
		
	}
}