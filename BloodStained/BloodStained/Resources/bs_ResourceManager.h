#ifndef BS_RESOURCEMANAGER_H
#define BS_RESOURCEMANAGER_H

#include "../Containers/bs_HashMap.h"
#include "../Containers/bs_LinkedArray.h"
#include "bs_Folder.h"

namespace bs
{
	class Resource;
	class TextResource;
	class AudioResource;
	class MeshResource;
	class ImageResource;
	class FontResource;

	class Texture2D;
	class Mesh;
	class Audio;
	class Font;

	class ResourceManager
	{
	public:
		//Default constructor.
		ResourceManager();
		//Default destructor.
		~ResourceManager();

	private:
		//Shouldn't be copied
		ResourceManager(const ResourceManager& r);

	public:
		//Manual init.
		bool	initialize();
		//Manual shut down.
		bool	shutDown();

		inline void scanFolders(){ _scanFolders(); }
		inline void scanFolders(Folder* f){ _scanSubfolders(f); }

	private:
		//Scan folders for files starting from the Data directory.
		void	_scanFolders();
		void	_scanSubfolders(Folder* f);
		void	_createSubFolder(Folder* parent, const String& newFolder);
		void	_destroyFolders();
		void	_clearFolder(Folder* f);

	private:
		//Place files in adequate arrays.
		void	_importFiles(Folder* f);

	public:
		//Load functions have 3 different overloads for each potential implicit constructors of String.
		String	loadText(const String& fileName);
		String  loadText(const char* fileName);
		String  loadText(const wchar_t* fileName);

		Texture2D	loadImage(const String& fileName);
		Texture2D	loadImage(const char* fileName);
		Texture2D	loadImage(const wchar_t* fileName);

		Font*	loadFont(const String& fileName);
		Font*	loadFont(const char* fileName);
		Font*	loadFont(const wchar_t* fileName);


	public:
		const Folder& rootFolder() const { return m_rootFolder; }

	private:
		//Each type of resource has its own array.
		LinkedArray<TextResource>	m_texts;
		LinkedArray<ImageResource>	m_images;
		LinkedArray<MeshResource>	m_meshes;
		LinkedArray<AudioResource>	m_audio;
		LinkedArray<FontResource>	m_fonts;

		HashMap<String, Resource*>	m_resources;

		Folder	m_rootFolder;
	};
}


#endif // !BS_RESOURCEMANAGER_H
