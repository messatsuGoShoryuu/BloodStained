#ifndef _BS_WINDOWSFILESYSTEM_H_
#define _BS_WINDOWSFILESYSTEM_H_

#include <Utilities/bs_types.h>



namespace bs
{
	template <class T>
	class Array;

	class String;

	class WindowsFileSystem
	{
	public:
		static void*	open(const char* filename);
		static void		close(void* handle);
		static bool		read(void* handle, void* buffer, ptrsize size);
		static bool		read(void* handle, char* buffer, ptrsize size);
		static bool		readLine(void* handle, char* buffer, ptrsize size);
		static ptrsize	write(void* handle, const void* buffer, ptrsize length);
		static ptrsize	writeBuffered(void* handle, const void* buffer, ptrsize length);
		static ptrsize	getFileSize(void* handle);
		static void		createDirectory(const char* pathName);
		static bool		getDirectoryContent(const char* directory, Array<String>& array);
	};
}


#endif // !BS_WINDOWSFILESYSTEM_H
