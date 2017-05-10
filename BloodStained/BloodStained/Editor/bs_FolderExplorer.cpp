#include "bs_FolderExplorer.h"
#include "../Globals/bs_globals.h"

namespace bs
{
	namespace editor
	{
		FolderExplorer::FolderExplorer()
			:m_listView(nullptr),
			m_currentFolder(nullptr),
			m_textPreviewWindow(nullptr)
		{

		}

		FolderExplorer::FolderExplorer(const FolderExplorer& f)
			: m_listView(f.m_listView),
			m_currentFolder(f.m_currentFolder),
			m_textPreviewWindow(f.m_textPreviewWindow)
		{

		}

		FolderExplorer::~FolderExplorer()
		{

		}

		bool	FolderExplorer::initialize()
		{
			if(!m_window) m_window = new EditorWindow("Folder Explorer");

			m_window->setMetrics(0, 800, 1000, 200);

			if (!m_window->initialize()) return false;
			m_window->setBackgroundColor(20, 20, 10);
			m_window->setTextColor(200, 200, 200);

			//Initialize listview window
			if (m_listView) return false;

			m_listView = new ListviewWindow("Folder Explorer Listview");
			m_listView->setParent(m_window);
			m_listView->setMetrics(0, 0, m_window->metrics().w - 1, m_window->metrics().h - 1);
			if (!m_listView->initialize()) return false;

			m_listView->setBackgroundColor(20, 20, 10);
			m_listView->setTextColor(200, 200, 200);

			//Initialize callbacks.
			OnDoubleClickDelegate.setCaster(this);
			OnDoubleClickDelegate = &FolderExplorer::OnDoubleClick;
			m_listView->OnDoubleClick = &OnDoubleClickDelegate;
			
			OnDropFilesDelegate.setCaster(this);
			OnDropFilesDelegate = &FolderExplorer::OnDropFiles;
			m_listView->OnDropFiles = &OnDropFilesDelegate;

			OnCommandDelegate.setCaster(this);
			OnCommandDelegate = &FolderExplorer::OnCommand;
			m_listView->OnCommand = &OnCommandDelegate;

			OnContextDelegate.setCaster(this);
			OnContextDelegate = &FolderExplorer::OnContext;
			m_listView->OnContext = &OnContextDelegate;

			//Update current folder to root.
			m_currentFolder = (Folder*)&g_resourceManager.rootFolder();

			m_listView->createRightClickMenu();

			if (!m_currentFolder) return false;
			_updateWindowToCurrentFolder();

			m_listView->refreshDisplay();
			
			//Text preview window
			if (m_textPreviewWindow) return false;
			m_textPreviewWindow = new EditorWindow("Text preview");
			m_textPreviewWindow->setBackgroundColor(20, 20, 10);
			m_textPreviewWindow->setTextColor(200, 200, 200);
			m_textPreviewWindow->setMetrics(0, 0, 500, 900);
			
			return true;
		}

		bool	FolderExplorer::shutDown()
		{
			bool result = true;

			if (m_textPreviewWindow)
			{
				m_textPreviewWindow->destroy();
				delete m_textPreviewWindow;
			}
			if (m_window->parent()) return true;
			result = false;			
			if (m_listView)
			{
				m_listView->destroy();
				delete m_listView;
			}
			else result = false;
			if (m_window)
			{
				m_window->destroy();
				delete m_window;
			}
			else result = false;
			return result;
		}

		void	FolderExplorer::setParent(EditorWindow* e)
		{
			if (!m_window) m_window = new EditorWindow("Folder Explorer");
			m_window->setParent(e);
			m_window->setResizeable(true);
			m_window->embed(true);
		}


		void	FolderExplorer::_updateWindowToCurrentFolder()
		{
			ui32 folderCount = m_currentFolder->children.count();

			m_listView->clearWindow();
			String name;
			for (ui32 i = 0; i < folderCount; i++)
			{
				name = m_currentFolder->children[i]->name;
				name.backSpace();
				m_listView->addItem(name.utf8(), LISTVIEW_ICON::FOLDER);
				
			}

			ui32 fileCount = m_currentFolder->list.count();

			for (ui32 i = 0; i < fileCount; i++)
			{
				name = m_currentFolder->list[i];
				m_listView->addItem(name.utf8(), _findIconByExtension(name));
			}
		}

		LISTVIEW_ICON FolderExplorer::_findIconByExtension(const String& name)
		{
			String extension;
			i32 lastCharacter = name.length() - 1;
			while (name[lastCharacter] != '.' && lastCharacter >= 0)
			{
				lastCharacter--;
			}

			ui32 stringLength = name.length();
			for (ui32 i = lastCharacter; i < stringLength; i++)
			{
				extension.add(name[i]);
			}

			if (extension == ".txt") return LISTVIEW_ICON::TEXT;
			if (extension == ".png") return LISTVIEW_ICON::PNG;
			if (extension == ".jpg") return LISTVIEW_ICON::JPG;
			if (extension == ".zip" || extension == ".rar") return LISTVIEW_ICON::ZIP;
			if (extension == ".mp3" || extension == ".wav" || extension == ".ogg") return LISTVIEW_ICON::AUDIO;
			if (extension == ".shader") return LISTVIEW_ICON::SHADER;
			return LISTVIEW_ICON::OTHER;
		}

		void FolderExplorer::OnDoubleClick(ui32 index)
		{
			if (index < m_currentFolder->children.count())
			{
				m_listView->clearWindow();
				m_currentFolder = m_currentFolder->children[index];
				_updateWindowToCurrentFolder();
			}
			else
			{

				index -= m_currentFolder->children.count();
				if (index < m_currentFolder->list.count())
				{
					String name = m_currentFolder->list[index].utf8();
					Folder* r = (Folder*)&g_resourceManager.rootFolder();
					Folder* f = m_currentFolder;
					
					if (f != r)
					{
						while (f != r)
						{
							name = f->name + name;
							f = f->parent;
						}
					}
					
					if (m_textPreviewWindow)
					{
						m_textPreviewWindow->setParent(m_window);
						m_textPreviewWindow->setResizeable(true);
						m_textPreviewWindow->clearTexts();
						m_textPreviewWindow->initialize();
						m_textPreviewWindow->setText(g_resourceManager.loadText(name).utf8(),0,0,1000,1000);
						m_textPreviewWindow->refreshDisplay();
					}

				}
				else std::cout << "Clicking into the void" << std::endl;
			}
			
		}

		void FolderExplorer::OnDropFiles(const Array<Path>& a)
		{
			ui32 count = a.count();
			for (ui32 i = 0; i < count; i++)
			{
				std::cout << a[i].utf8() << std::endl;
				
				String s = a[i].relativeName();

				String newPath = m_currentFolder->fullPath.utf8();
				newPath += s;

				//Todo: create a copyfile routine in FileSystem.
				//Todo: ability to copy folders.
				CopyFile(a[i].utf8(), newPath.utf8(), true);
			
			}

			g_resourceManager.scanFolders(m_currentFolder);
			_updateWindowToCurrentFolder();
			
			m_listView->refreshDisplay();
		}

		void	FolderExplorer::OnCommand(ui16 command)
		{
			switch ((FOLDEREXPLORER_COMMAND)command)
			{
				case FOLDEREXPLORER_COMMAND::BACK:
					if (m_currentFolder != &g_resourceManager.rootFolder())
					{
						m_currentFolder = m_currentFolder->parent;
						_updateWindowToCurrentFolder();
					}
					break;
				case FOLDEREXPLORER_COMMAND::NEW_FOLDER:
					break;
				case FOLDEREXPLORER_COMMAND::RENAME:
					break;
			}
		}

		void	FolderExplorer::OnContext(ListviewWindow* w, i32 x, i32 y)
		{
			w->beginRightClickMenu();
			w->appendRightClickMenu("Back",(ui16)FOLDEREXPLORER_COMMAND::BACK);
			w->appendRightClickMenu("Create Folder",(ui16)FOLDEREXPLORER_COMMAND::NEW_FOLDER);
			w->appendRightClickMenu("Rename",(ui16)FOLDEREXPLORER_COMMAND::RENAME);
			w->endRightClickMenu(x, y);
		}
	}
}





