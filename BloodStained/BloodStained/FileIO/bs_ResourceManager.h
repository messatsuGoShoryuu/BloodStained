#ifndef _BS_RESOURCEMANAGER_H_
#define _BS_RESOURCEMANAGER_H_

#include "../Containers/bs_HashMap.h"
#include <Containers/bs_LinkedArray.h>
#include <Allocator/bs_PoolAllocator.h>
#include "bs_Folder.h"


namespace bs
{
	enum class ERROR_ID;
	class Resource;
	class TextResource;
	class AudioResource;
	class MeshResource;
	class ImageResource;
	class FontResource;
	class ShaderScriptResource;

	class Texture2D;
	class Mesh;
	class Audio;
	class Font;

	class ResourceManager
	{

	public:
		//Manual init.
		static	ERROR_ID	initialize();
		//Manual shut down.
		static  ERROR_ID		shutDown();

		static void scanFolders(){ _scanFolders(); }
		static void scanFolders(Folder* f){ _scanSubfolders(f); }

	private:
		//Scan folders for files starting from the Data directory.
		static	void	_scanFolders();
		static	void	_scanSubfolders(Folder* f);
		static	void	_createSubFolder(Folder* parent, const String& newFolder);
		static	void	_destroyFolders();
		static	void	_clearFolder(Folder* f);

	private:
		//Place files in adequate arrays.
		static	void	_importFiles(Folder* f);

	public:
		//Load functions have 3 different overloads for each potential implicit constructors of String.
		static	String	loadText(const String& fileName);
		static	String  loadText(const char* fileName);
		static	String  loadText(const wchar_t* fileName);

		static void unload(const String& fileName);
		static void unload(const char* fileName);
		static void unload(const wchar_t* fileName);
	public:
		const Folder& rootFolder() const { return s_rootFolder; }

	private:
		//Each type of resource has its own array.
		static	PoolAllocator<TextResource>	s_texts;
		static  Array<ShaderScriptResource> s_shaderScripts;

		static	HashMap<String, Resource*>	s_resources;

		static	Folder	s_rootFolder;

	public:
		static	ShaderScriptResource&	getShaderScript(ui32 index);
		static	void	clearShaderScripts();
		static	ui32	shaderScriptCount() { return s_shaderScripts.count(); }
	};
}


#endif // !BS_RESOURCEMANAGER_H
