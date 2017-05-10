#include "bs_Resource.h"
#include "bs_ResourceManager.h"
#include "../Globals/bs_globals.h"
#include "../Rendering/bs_Shader.h"
#include "bs_FileSystem.h"
#include "../Rendering/bs_Texture2D.h"


namespace bs
{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{

	}


	bool ResourceManager::initialize()
	{
		m_rootFolder.name = "Data/";
		m_rootFolder.fullPath = Path::data().string();
		m_rootFolder.parent = nullptr;
		_scanFolders();

		return true;
	}

	bool ResourceManager::shutDown()
	{
		_destroyFolders();

		m_images.~LinkedArray();
		m_audio.~LinkedArray();
		m_texts.~LinkedArray();
		m_meshes.~LinkedArray();
		m_fonts.~LinkedArray();
		m_resources.~HashMap();

	
		Path::root().~Path();
		Path::data().~Path();

		return true;
	}

	String ResourceManager::loadText(const String& fileName)
	{
		//Cast to text pointer.
		if (m_resources.isEmptyAt(fileName)) return String("Text not found");
		TextResource* text = dynamic_cast<TextResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!text->isLoaded()) error = text->load();

		std::cout << "Loading text failed ? " << error << std::endl;

		//If loading has failed return empty string
		//TODO: add error message
		if (error) return String("");

		//Everything is good: return data.
		return text->getData();
	}

	String ResourceManager::loadText(const char* fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return String("Text not found");
		TextResource* text = dynamic_cast<TextResource*>(m_resources[fileName]);

		bool error = false;
		if (!text->isLoaded()) error = text->load();

		if (error) return String("");

		return text->getData();
	}

	String ResourceManager::loadText(const wchar_t* fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return String("Text not found");
		TextResource* text = dynamic_cast<TextResource*>(m_resources[fileName]);

		bool error = false;
		if (!text->isLoaded()) error = text->load();

		if (error) return String("Load failed");

		return text->getData();
	}

	Texture2D ResourceManager::loadImage(const String& fileName)
	{
		//Cast to text pointer.
		if (m_resources.isEmptyAt(fileName)) return Texture2D();
		ImageResource* image = dynamic_cast<ImageResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!image->isLoaded()) error = image->load();

		std::cout << "Loading text failed ? " << error << std::endl;

		//If loading has failed return empty string
		//TODO: add error message
		if (error) return Texture2D();

		//Everything is good: return data.
		return image->getData();
	}

	Texture2D ResourceManager::loadImage(const char* fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return Texture2D();
		ImageResource* image = dynamic_cast<ImageResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!image->isLoaded()) error = image->load();

		//If loading has failed return empty string
		//TODO: add error message
		if (error)
		{
			std::cout << "Image loading failed" << std::endl;
			return Texture2D();
		}

		//Everything is good: return data.
		return image->getData();
	}

	Texture2D ResourceManager::loadImage(const wchar_t* fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return Texture2D();
		ImageResource* image = dynamic_cast<ImageResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!image->isLoaded()) error = image->load();

		//If loading has failed return empty string
		//TODO: add error message
		if (error) return Texture2D();

		//Everything is good: return data.
		return image->getData();
	}

	Font* ResourceManager::loadFont(const String& fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return nullptr;
		FontResource* font = dynamic_cast<FontResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!font->isLoaded()) error = font->load();

		//If loading has failed return empty string
		//TODO: add error message
		if (error) return nullptr;

		//Everything is good: return data.
		return font->getData();
	}

	Font* ResourceManager::loadFont(const char* fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return nullptr;
		FontResource* font = dynamic_cast<FontResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!font->isLoaded()) error = font->load();

		//If loading has failed return empty string
		//TODO: add error message
		if (error)
		{
			std::cout << "Font loading error" << std::endl;
			return nullptr;
		}

		//Everything is good: return data.
		return font->getData();
	}

	Font* ResourceManager::loadFont(const wchar_t* fileName)
	{
		if (m_resources.isEmptyAt(fileName)) return nullptr;
		FontResource* font = dynamic_cast<FontResource*>(m_resources[fileName]);

		//Load if not loaded
		bool error = false;
		if (!font->isLoaded()) error = font->load();

		//If loading has failed return empty string
		//TODO: add error message
		if (error) return nullptr;

		//Everything is good: return data.
		return font->getData();
	}

	void	ResourceManager::_importFiles(Folder* f)
	{
		ui32 folderCount = f->children.count();
		ui32 listCount = f->list.count();
		Folder* cf = f;
		Folder* r = &m_rootFolder;

		//Recursive call for subfolders.
		for (ui32 i = 0; i < folderCount; i++)_importFiles(f->children[i]);

		//Extract folder path relative to the Data folder.
		String folderName;
		if (cf != r)
		{
			while (cf != r)
			{
				folderName = cf->name + folderName;
				cf = cf->parent;
			}
		}
		
		Path fileName;
		char extensionArray[10];
		String extension;

		for (ui32 i = 0; i < listCount; i++)
		{
			//Extract extension
			fileName = folderName + f->list[i];
			FileSystem::getExtension(fileName, extensionArray);
			extension = extensionArray;

			//Parse by extension.

			//Text
			if (extension == "txt" || extension == ".txt")
			{
				//Check if hashmap is empty
				if (m_resources.isEmptyAt(fileName.string()))
				{
					//Add text resource.
					TextResource* t = m_texts.add(TextResource());

					//Add to hashmap.
					m_resources[fileName.utf8()] = t;

					//Create full path
					fileName = f->fullPath;
					fileName.toFileName(f->list[i]);
					t->_setFileName(fileName.utf8());
					std::cout << fileName.utf8() << std::endl;
				}
			}
			
			//Shader
			if (extension == "shader" || extension == ".shader")
			{
				//Check if source hashmap is empty.
				if (g_shaderManager.m_shaderSources.isEmptyAt(fileName.string()))
				{
					//Get shader name (hashmap key)
					String shaderName = fileName.string();

					//Load text
					TextResource text;
					fileName = f->fullPath;
					fileName.toFileName(f->list[i]);
					text._setFileName(fileName.string());

					//Add source to shader list.
					text.load();
					g_shaderManager.m_shaderSources[shaderName] = text.getData();				
					text.unload();
				}
			}

			//Image
			if (extension == "png" || extension == ".png")
			{
				//Check if hashmap is empty
				if (m_resources.isEmptyAt(fileName.string()))
				{
					//Add text resource.
					ImageResource* ir = m_images.add(ImageResource());
					ir->setChannels(GL_RGBA);

					//Add to hashmap.
					m_resources[fileName.utf8()] = ir;

					//Create full path
					fileName = f->fullPath;
					fileName.toFileName(f->list[i]);
					ir->_setFileName(fileName.utf8());
					std::cout << fileName.utf8() << std::endl;
				}
			}

			//Font
			if (extension == "ttf" || extension == ".ttf")
			{
				//Check if hashmap is empty
				if (m_resources.isEmptyAt(fileName.string()))
				{
					//Add text resource.
					FontResource* fr = m_fonts.add(FontResource());

					//Add to hashmap.
					m_resources[fileName.utf8()] = fr;

					//Create full path
					fileName = f->fullPath;
					fileName.toFileName(f->list[i]);
					fr->_setFileName(fileName.utf8());
				}
			}
		}
	}

	void ResourceManager::_scanFolders()
	{
		_scanSubfolders(&m_rootFolder);
	}

	void	ResourceManager::_scanSubfolders(Folder* f)
	{
		//Create a local array (will be used to compare if there are new files).
		Array<String> newFiles;
		
		//Fill the array with directory content.
		FileSystem::getDirectoryContent(f->fullPath.utf8(), newFiles);
		
		//Create Folder structs if we find any string ending with slashes.
		ui32 count = newFiles.count();
		for (ui32 i = 0; i < count; i++)
		{
			ui32 stringLength = newFiles[i].length();
			ui32 last = stringLength - 1;

			if (newFiles[i][last] == '/') //This is a folder.
			{
				_createSubFolder(f, newFiles[i]);
			}
			else if (!f->list.contains(newFiles[i]))
			{
				f->list.add(newFiles[i]); 
			}
		}

		_importFiles(f);
	}

	void	ResourceManager::_createSubFolder(Folder* parent, const String& newFolder)
	{
		//Create new path from parent.
		Path newPath = parent->fullPath;
		newPath.toChild(newFolder);

		//Create name from path.
		String name = newPath.relativeName();

		//Check for valid folder.
		if (name != "./" && name != "../")
		{
			for (ui32 i = 0; i < parent->children.count(); i++)
			{
				
				if (parent->children[i]->name == name)
				{
					return;
				}
			}
			//Fill in folder struct.
			Folder* newFolder = new Folder();
			newFolder->parent = parent;
			newFolder->name = name;
			newFolder->fullPath = newPath;
			parent->children.add(newFolder);

			//Scan recursively.
			_scanSubfolders(newFolder);
		}
	}

	void	ResourceManager::_destroyFolders()
	{
		_clearFolder(&m_rootFolder);
		m_rootFolder.fullPath.~Path();
		m_rootFolder.list.reset();
		m_rootFolder.name.clearFromMemory();
		m_rootFolder.children.reset();
		m_rootFolder.parent = nullptr;
		m_rootFolder.~Folder();
	}

	void	ResourceManager::_clearFolder(Folder* f)
	{
		ui32 count = f->children.count();
		for (ui32 i = 0; i < count; i++)
		{
			_clearFolder(f->children[i]);
			delete(f->children[i]);
		}

		f->fullPath.~Path();
		f->list.~Array<String>();
		f->name.clearFromMemory();
		f->children.~Array<Folder*>();		
	}


}