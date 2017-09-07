#ifndef _BS_FILESYSTEM_H_
#define _BS_FILESYSTEM_H_

#include "bs_Path.h"
#include <Platform/bs_Platform.h>

namespace bs
{
	//FileHandle platform specific typedefs
#ifdef BS_WINDOWS
	typedef void* FileHandle;
#elif defined BS_APPLE
	typedef int FileHandle;
#endif

	//A struct to store metadata about a file
	struct FileInfo
	{
		Path	path;
		char	extension[8];
		ptrsize	size;
		FileHandle handle;
	};


	class FileSystem
	{
	public:
		static void		initialize();
		static void		shutDown();
		static FileInfo	open(String fileName);
		static void		close(const FileInfo& fileInfo);

		/*Read bytes to buffer
		**@param info Holder of the file  handle
		**@param buffer Buffer to fill.
		*/
		static bool		read(const FileInfo& info, byte* buffer);

		/*Read full text.
		**@param info Holder of the file  handle
		**@param buffer Buffer to fill.
		*/
		static bool		read(const FileInfo& info, char* buffer);

		/*Read a line of text.
		**@param info Holder of the file  handle
		**@param buffer Buffer to fill.
		*/
		static bool		readLine(const FileInfo& info, char* buffer);

		/*Write file
		**@param info Holder of the file handle.
		**@param buffer Bytes to write.
		**@param length Byte count.
		*/
		static ptrsize		write(const FileInfo& info, const void* buffer, ptrsize length);

		/*Write to file and set the pointer to the end of the write.
		**@param info Holder of the file handle.
		**@param buffer Bytes to write.
		**@param length Byte count.
		*/
		static ptrsize		writeBuffered(const FileInfo& info, const void* buffer, ptrsize length);

		/*Create a new directory at pathName if it doesn't exist.
		**@param pathName New path
		*/
		static void		createDirectory(String pathName);
		
		/*Get extension of the file (.exe, .mp3, etc)
		**@param path Path to search
		**@param buffer Buffer to retrieve
		*/
		static void		getExtension(Path& path, char* buffer);

		/*Get directory list.
		**@param directory	Path of the directory.
		**@param array	Array to store file names.
		*/
		static void		getDirectoryContent(const char* directory, Array<String>& array);
	};
}


#endif