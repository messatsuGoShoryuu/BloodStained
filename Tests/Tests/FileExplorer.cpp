
#include "FileExplorer.h"
#include <CommCtrl.h>
#include <Globals\bs_globals.h>
#include <resource.h>


FolderWindow::FolderWindow()
{

}

FolderWindow::FolderWindow(const WindowsWindow& w)
	:bs::WindowsWindow(w)
{

}

FolderWindow::FolderWindow(LPCSTR className, LPCSTR windowName, bs::WindowCallback wndProc, DWORD style)
	: bs::WindowsWindow(className, windowName, wndProc, style)
{

}

FolderWindow::FolderWindow(LPCSTR className, LPCSTR windowName, bs::WindowCallback wndProc, DWORD style, WindowsWindow* parent)
	: bs::WindowsWindow(className,windowName,wndProc,style,parent)
{

}

FolderWindow::FolderWindow(LPCSTR className, LPCSTR windowName, bs::WindowCallback wndProc, DWORD style, DWORD exStyle, WindowsWindow* parent)
	: bs::WindowsWindow(className,windowName,wndProc,style,exStyle,parent)
{

}

//Destructor.
FolderWindow::~FolderWindow() 
{

}

#define CX_ICON  32 
#define CY_ICON  32 
#define NUM_ICONS 3 

WNDPROC		previousWndProc;

LRESULT CALLBACK ChildProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_NOTIFY:
			std::cout << "WM_NOTIFY" << std::endl;
			NMLVDISPINFO* plvdi;

			switch (((LPNMHDR)lParam)->code)
			{
				case LVN_GETDISPINFO:

					plvdi = (NMLVDISPINFO*)lParam;
					std::cout << plvdi->item.iImage << std::endl;

					break;
			}
			return 0;
		case WM_CREATE:
			
			CallWindowProc(previousWndProc, hwnd, WM_CREATE, wParam, lParam);
			ListView_SetBkColor(hwnd, RGB(25, 30, 27));
			ListView_SetTextBkColor(hwnd, RGB(25, 30, 27));
			ListView_SetTextColor(hwnd, RGB(250, 250, 200));
			
			return 0;
		case WM_PAINT:
			std::cout << "WM_PAINT"<<std::endl;
			ListView_SetBkColor(hwnd, RGB(25, 30, 27));
			ListView_SetTextBkColor(hwnd, RGB(25, 30, 27));
			ListView_SetTextColor(hwnd, RGB(250, 240, 240));
			CallWindowProc(previousWndProc, hwnd, WM_PAINT, 0, 0);
			return 0;
		case WM_ERASEBKGND:
			CallWindowProc(previousWndProc, hwnd, WM_ERASEBKGND, wParam, lParam);
			return 0;
	}
	return CallWindowProc(previousWndProc, hwnd, uMsg, wParam, lParam);
}
LRESULT DummyProc(bs::WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	return 1;
}

LRESULT MainProc(bs::WindowsWindow* w, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			int bird; int tree;
			FolderWindow* f = dynamic_cast<FolderWindow*>(w);
			f->owner->updateFolderContent();
		}
			return 0;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
		{

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			HFONT font;
			HFONT oldFont;

			font = CreateFont(16, 0, 0, 0, 300, true, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Calibri");
			oldFont = (HFONT)SelectObject(hdc, font);

			HBRUSH brush = CreateSolidBrush(RGB(10, 15, 5));
			FillRect(hdc, &ps.rcPaint, brush);

			RECT textBox;
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkColor(hdc, RGB(10, 15, 5));
			
			GetClientRect(hwnd, &textBox);

			FolderWindow* f = dynamic_cast<FolderWindow*>(w);

			DrawText(hdc, f->content.utf8(), -1, &textBox, DT_TOP | DT_LEFT);

			EndPaint(hwnd, &ps);

			SelectObject(hdc, oldFont);
			return 0;
		}
		case WM_EXITSIZEMOVE:
			RECT rect;
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, false);
			return 0;
		
	}
	return 1;
}


FileExplorer::FileExplorer()
{

}

FileExplorer::~FileExplorer()
{

}

void FileExplorer::initialize()
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	bs::WindowCallback mainProc;
	mainProc = MainProc;
	m_mainWindow = new FolderWindow("MainWindow", "MainWindow", mainProc, WS_OVERLAPPEDWINDOW, 0);
	m_mainWindow->setMetrics(0, 0, 640, 480);
	m_mainWindow->owner = this;

	bs::WindowCallback dummyCallback;
	dummyCallback = DummyProc;
	m_childWindow = new bs::WindowsWindow(WC_LISTVIEW, "", dummyCallback, 
										  WS_CHILD | WS_VISIBLE | LVS_EDITLABELS | WS_VSCROLL, m_mainWindow);
	m_childWindow->setMetrics(10, 100, 600, 300);

	

	if (!m_mainWindow->initialize()) std::cout << "Failed to initialize window" << std::endl;

	

	if (!m_childWindow->initialize()) std::cout << "Failed to initialize child window" << std::endl;

	previousWndProc = (WNDPROC)GetWindowLong(m_childWindow->hwnd(), GWL_WNDPROC);
	SetWindowLong(m_childWindow->hwnd(), GWL_WNDPROC, (LONG)ChildProc);

	HICON icon;
	HIMAGELIST imageList;
	HIMAGELIST imageListSmall;
	imageList = ImageList_Create(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), ILC_MASK, 1, 1);
	imageListSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CXSMICON), ILC_MASK, 1, 1);

	icon = LoadIcon(bs::g_windowsMain.hinstance(), MAKEINTRESOURCE(IDI_FOLDER_ICON));
	if (!icon) std::cout << "loading icon failed" << std::endl;

	ImageList_AddIcon(imageList, icon);
	ImageList_AddIcon(imageListSmall, icon);

	ListView_SetImageList(m_childWindow->hwnd(), imageList, LVSIL_NORMAL);
	ListView_SetImageList(m_childWindow->hwnd(), imageListSmall, LVSIL_SMALL);

	DestroyIcon(icon);

	char szText[256];     // Temporary buffer.
	LVCOLUMN lvc;
	int iCol;

	
	LVITEM lvI;

	// Initialize LVITEM members that are common to all items.
	lvI.pszText = "Item"; 
	lvI.mask = LVIF_TEXT | LVIF_IMAGE;
	lvI.stateMask = 0;
	lvI.cchTextMax = strlen("Item");
	lvI.iSubItem = 0;
	lvI.state = 0;

	// Initialize LVITEM members that are different for each item.
	for (int index = 0; index < 3; index++)
	{
		lvI.iItem = index;
		lvI.iImage = 0;

		// Insert items into the list.
	
		if (ListView_InsertItem(m_childWindow->hwnd(), &lvI) == -1)
			std::cout << "item insertion failed" << std::endl;
		else std::cout << "Item inserted successfully" << std::endl;
	}

	if(ListView_SetView(m_childWindow->hwnd(), LV_VIEW_ICON) == -1) std::cout<<"Set view failed"<<std::endl;


	InvalidateRect(m_childWindow->hwnd(), NULL, TRUE);
	UpdateWindow(m_childWindow->hwnd());

}

void FileExplorer::shutDown()
{
	m_mainWindow->destroy();
	delete m_mainWindow;
}

void FileExplorer::updateFolderContent()
{
	m_mainWindow->content.clear();
	bs::Folder* f = (bs::Folder*)&bs::g_resourceManager.rootFolder();

	_getFolderContent(f, 0);	
}

void FileExplorer::_getFolderContent(bs::Folder* f, int level)
{
	for (ui32 i = 0; i < f->children.count(); i++)
	{
		for (ui32 j = 0; j < level; j++)m_mainWindow->content += "    ";
		m_mainWindow->content += f->children[i]->name + '\n';
		_getFolderContent(f->children[i], level + 1);
	}

	for (ui32 i = 0; i < f->list.count(); i++)
	{ 
		for (ui32 j = 0; j < level; j++)m_mainWindow->content += "    ";
		m_mainWindow->content += f->list[i] + '\n';
	}
		

	SwapBuffers(GetDC(m_mainWindow->hwnd()));
}