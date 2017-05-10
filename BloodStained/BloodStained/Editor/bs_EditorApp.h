#ifndef BS_EDITORAPP_H
#define BS_EDITORAPP_H

#include "bs_EditorPlatform.h"

//This class is the main application wrapper for the editor

namespace bs
{
	class OpenGLWindow;
	namespace editor
	{
		class FolderExplorer;
		class EditorApp
		{
		public:
			//Default constructor.
			EditorApp();
			//Destructor.
			~EditorApp();

		private:
			//Non implemented copy constructor.
			EditorApp(const EditorApp& e);

		public:
			//Manual init.
			bool	initialize();
			//Manual shut down.
			bool	shutDown();

			bool	initializeGameWindow();

		public:
			//Callbacks.
			MemberFunction<EditorApp, void, void>OnResizeGameDelegate;
			void OnResizeGame();

			MemberFunction<EditorApp, void, void> GameThreadDelegate;
			void GameThread();

		private:
			EditorWindow*	m_mainWindow;
			OpenGLWindow*	m_gameWindow;
			FolderExplorer*	m_folderExplorer;
		};
	}
}

#endif // !BS_EDITORAPP_H
