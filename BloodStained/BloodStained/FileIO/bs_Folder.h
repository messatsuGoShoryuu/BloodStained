#ifndef _BS_FOLDER_H_
#define _BS_FOLDER_H_

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
