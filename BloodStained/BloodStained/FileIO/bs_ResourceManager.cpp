#include "bs_Resource.h"
#include "bs_ResourceManager.h"
#include "bs_FileSystem.h"
#include <Utilities/bs_Error.h>


namespace bs
{
	PoolAllocator<TextResource>	ResourceManager::s_texts;

	Array<ShaderScriptResource> ResourceManager::s_shaderScripts;
	HashMap<String, Resource*>	ResourceManager::s_resources;

	Folder	ResourceManager::s_rootFolder;


	ERROR_ID ResourceManager::initialize()
	{
		s_rootFolder.name = "Data/";
		s_rootFolder.fullPath = Path::data().string();
		s_rootFolder.parent = nullptr;
		_scanFolders();

		return ERROR_ID::NONE;
	}

	ERROR_ID ResourceManager::shutDown()
	{
		_destroyFolders();

		s_texts.shutDown();
		s_resources.~HashMap();

	
		Path::root().~Path();
		Path::data().~Path();

		return ERROR_ID::NONE;
	}

	String ResourceManager::loadText(const String& fileName)
	{
		//Cast to text pointer.
		if (s_resources.isEmptyAt(fileName)) return String("Text not found");
		TextResource* text = dynamic_cast<TextResource*>(s_resources[fileName]);

		//Load if not loaded
		ERROR_ID error = ERROR_ID::NONE;
		if (!text->isLoaded()) error = text->load();



		//If loading has failed return empty string
		if (error != ERROR_ID::NONE)
		{
			warning(error);
			return String("");
		}

		//Everything is good: return data.
		return text->getData();
	}

	String ResourceManager::loadText(const char* fileName)
	{
		if (s_resources.isEmptyAt(fileName)) return String("Text not found");
		TextResource* text = dynamic_cast<TextResource*>(s_resources[fileName]);

		ERROR_ID error = ERROR_ID::NONE;
		if (!text->isLoaded()) error = text->load();

		//If loading has failed return empty string
		if (error != ERROR_ID::NONE)
		{
			warning(error);
			return String("");
		}

		return text->getData();
	}

	String ResourceManager::loadText(const wchar_t* fileName)
	{
		if (s_resources.isEmptyAt(fileName)) return String("Text not found");
		TextResource* text = dynamic_cast<TextResource*>(s_resources[fileName]);

		ERROR_ID error = ERROR_ID::NONE;
		if (!text->isLoaded()) error = text->load();

		//If loading has failed return empty string
		if (error != ERROR_ID::NONE)
		{
			warning(error);
			return String("");
		}

		return text->getData();
	}

	void ResourceManager::unload(const String & fileName)
	{
		if (s_resources.isEmptyAt(fileName)) return;
		s_resources[fileName]->unload();
	}

	void ResourceManager::unload(const char * fileName)
	{
		if (s_resources.isEmptyAt(fileName)) return;
		s_resources[fileName]->unload();
	}

	void ResourceManager::unload(const wchar_t * fileName)
	{
		if (s_resources.isEmptyAt(fileName)) return;
		s_resources[fileName]->unload();
	}

	ShaderScriptResource&	ResourceManager::getShaderScript(ui32 index)
	{
		return s_shaderScripts[index];
	}

	void ResourceManager::clearShaderScripts()
	{
		s_shaderScripts.~Array();
	}

	void	ResourceManager::_importFiles(Folder* f)
	{
		ui32 folderCount = f->children.count();
		ui32 listCount = f->list.count();
		Folder* cf = f;
		Folder* r = &s_rootFolder;

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
				if (s_resources.isEmptyAt(fileName.string()))
				{
					//Add text resource.
					TextResource* t = s_texts.allocate();

					//Add to hashmap.
					s_resources[fileName.utf8()] = t;

					//Create full path
					fileName = f->fullPath;
					fileName.toFileName(f->list[i]);
					t->_setFileName(fileName.utf8());
				}
			}

			//Shader script
			if (extension == "shader" || extension == ".shader")
			{
				bool hasShader = false;
				for (ui32 i = 0; i < s_shaderScripts.count(); i++)
				{
					if (s_shaderScripts[i].fileName().getSubString(Path::data().length()) == fileName.string())
					{
						hasShader = true;
						break;
					}
				}
		
				if (!hasShader)
				{
					//Add text resource.
					ui32 id = s_shaderScripts.construct();
					ShaderScriptResource* s = &s_shaderScripts[id];

					//Create full path
					fileName = f->fullPath;
					fileName.toFileName(f->list[i]);
					s->_setFileName(fileName.utf8());
				}
			}
		}
	}

	void ResourceManager::_scanFolders()
	{
		_scanSubfolders(&s_rootFolder);
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
		_clearFolder(&s_rootFolder);
		s_rootFolder.fullPath.~Path();
		s_rootFolder.list.reset();
		s_rootFolder.name.clearFromMemory();
		s_rootFolder.children.reset();
		s_rootFolder.parent = nullptr;
		s_rootFolder.~Folder();
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