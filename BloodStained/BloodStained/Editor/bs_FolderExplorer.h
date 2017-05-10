#ifndef BS_FOLDEREXPLORER_H
#define BS_FOLDEREXPLORER_H

#include "bs_EditorPlatform.h"

namespace bs
{
	enum class FOLDEREXPLORER_COMMAND
	{
		NONE,
		BACK,
		NEW_FOLDER,
		RENAME
	};
	class Folder;

	namespace editor
	{

		class FolderExplorer
		{
		public:
			//Default constructor
			FolderExplorer::FolderExplorer();
			//Copy constcructor
			FolderExplorer::FolderExplorer(const FolderExplorer& f);

			//Destructor
			virtual FolderExplorer::~FolderExplorer();

			bool	initialize();
			bool	shutDown();

			void	setParent(EditorWindow* e);

			//Callbacks
			MemberFunction<FolderExplorer, void, ui32>					OnDoubleClickDelegate;
			MemberFunction<FolderExplorer, void, const Array<Path>&>	OnDropFilesDelegate;
			MemberFunction<FolderExplorer, void, ui16>					OnCommandDelegate;
			MemberFunction<FolderExplorer, void, ListviewWindow*, i32, i32>		OnContextDelegate;
			void	OnDoubleClick(ui32 index);
			void	OnDropFiles(const Array<Path>& a);
			void	OnCommand(ui16 command);
			void	OnContext(ListviewWindow* w, i32 x, i32 y);


		private:
			//Helpers
			void	_updateWindowToCurrentFolder();
			LISTVIEW_ICON	_findIconByExtension(const String& name);

		private:
			ListviewWindow*	m_listView;
			EditorWindow*	m_window;
			EditorWindow*	m_textPreviewWindow;
			Folder*	m_currentFolder;
		};
	}

}

#endif // !BS_FOLDEREXPLORER_H
