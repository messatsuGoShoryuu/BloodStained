#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <Utilities\bs_String.h>
#include <Platform\Windows\WindowsWindow\bs_WindowsWindow.h>
#include <Resources\bs_Folder.h>
#include <CommCtrl.h>

class FolderWindow :public bs::WindowsWindow
{
public:
	FolderWindow();
	//Copy constructor.
	FolderWindow(const WindowsWindow& w);

	FolderWindow(LPCSTR className, LPCSTR windowName, bs::WindowCallback wndProc, DWORD style);

	FolderWindow(LPCSTR className, LPCSTR windowName, bs::WindowCallback wndProc, DWORD style, WindowsWindow* parent);

	FolderWindow(LPCSTR className, LPCSTR windowName, bs::WindowCallback wndProc, DWORD style, DWORD exStyle, WindowsWindow* parent);

	//Destructor.
	virtual ~FolderWindow() override;

	bs::String	content;
	class FileExplorer* owner;
	HIMAGELIST	imageList;
	bs::Array<int> imageIndexes;
};

class  FileExplorer
{
public:
	FileExplorer();
	~FileExplorer();

	void initialize();
	void shutDown();

	void updateFolderContent();

	inline bs::WindowsWindow*	mainWindow(){ return m_mainWindow; }

private:
	void _getFolderContent(bs::Folder* f, int level);
private:
	FolderWindow*	m_mainWindow;
	bs::WindowsWindow*	m_childWindow;
};

#endif // !FILEEXPLORER_H
