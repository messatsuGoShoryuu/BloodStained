#ifndef BS_FOLDER_H
#define BS_FOLDER_H

#include "bs_Path.h"


namespace bs
{
	struct Folder
	{
		Folder()
			:parent(nullptr)
		{}

		Array<String>	list;
		Array<Folder*>	children;
		String			name;
		Path			fullPath;
		Folder*			parent;
	};
}


#endif // !BS_FOLDER_H
