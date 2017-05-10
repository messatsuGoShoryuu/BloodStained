#ifndef BS_EDITORPLATFORM_H
#define BS_EDITORPLATFORM_H

#ifdef _WIN32 || _WIN64
#include "Windows\bs_WindowsEditorWindow.h"
#include "Windows\bs_WindowsListviewWindow.h"

namespace bs
{
	namespace editor
	{
		typedef WindowsEditorWindow EditorWindow;
		typedef WindowsListviewWindow ListviewWindow;
	}
}
#endif
#endif // !BS_EDITORPLATFORM_H
