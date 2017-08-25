#include "bs_ShaderManager.h"
#include <FileIO/bs_Resource.h>
#include <FileIO/bs_ResourceManager.h>
#include <Utilities/bs_Error.h>
#include "bs_OpenGL.h"
#include "bs_Shader.h"


#define BS_SHADER_COMPILE_VERTEX_BIT 0x0001
#define BS_SHADER_COMPILE_FRAGMENT_BIT 0x0002

namespace bs
{
	//Shader attributes to use with attribs / uniform binding
	struct ShaderAttribute
	{	
		String	 name;
		SHADER_ATTRIB_TYPE type;
	};

	//Struct that enables correct compilation from shader script
	struct ShaderCompilationData
	{
		String key;
		String fragmentShader;
		String vertexShader;
		Array<ShaderAttribute> attribList;
		Array<ShaderAttribute> uniformList;
		ui16 flags;
	};


	ERROR_ID bs::ShaderManager::initialize()
	{
		_compileShaders();

		return ERROR_ID::NONE;
	}

	ERROR_ID bs::ShaderManager::shutDown()
	{
		return ERROR_ID::NONE;
	}

	void bs::ShaderManager::_compileShaders()
	{
		ui32 count = ResourceManager::shaderScriptCount();
		String s = "";

		//Iterate through files with the extension .shader
		for (ui32 i = 0; i < count; i++)
		{
			ShaderScriptResource r = ResourceManager::getShaderScript(i);

			r.load();
			s = r.getData();
			
			//Prepare compilation data struct
			ShaderCompilationData compilationData;
			compilationData.key = r.fileName().getSubString(Path::data().length());
			compilationData.flags = 0;

			//Parse script:

			//Split script into lines
			const char* splitters = "\r\n;";
			Array<String> splittedString = s.split(splitters);

			//Find keywords and and data
			ui32 splittedStringCount = splittedString.count();
			for (ui32 j = 0; j < splittedStringCount; j++)
			{
				ui32 current = 0;
				String keyword = splittedString[j].getNextWord(current);

				if (keyword == "fragment")
				{
					_extractShaderFromSplittedString(splittedString[j], r, current, compilationData.fragmentShader);
					compilationData.flags |= BS_SHADER_COMPILE_FRAGMENT_BIT;
				}
				else if (keyword == "vertex")
				{
					 _extractShaderFromSplittedString(splittedString[j], r, current, compilationData.vertexShader);
					 compilationData.flags |= BS_SHADER_COMPILE_VERTEX_BIT;
				}
			}

			//Free resources.
			r.unload();

			//Compile shader from data.
			_compileShader(compilationData);
		}

		ResourceManager::clearShaderScripts();
	}

	ERROR_ID ShaderManager::_compileShader(const ShaderCompilationData& data)
	{
		//Check flags
		bool hasFragment = (data.flags & BS_SHADER_COMPILE_FRAGMENT_BIT) == BS_SHADER_COMPILE_FRAGMENT_BIT;
		bool hasVertex = (data.flags & BS_SHADER_COMPILE_VERTEX_BIT) == BS_SHADER_COMPILE_VERTEX_BIT;

		//Initialize shader indexes.
		ui32 fragment = 0;
		ui32 vertex = 0;

		//Compile and check fragment shader if there is any.
		if (hasFragment)
		{
			fragment = OpenGL::createShader(OPENGL_SHADER_TYPE::FRAGMENT);
			if (fragment == 0) return fatalError(ERROR_ID::SHADER_CREATION_FAIL);

			OpenGL::shaderSource(fragment, 1, data.fragmentShader.utf8(), data.fragmentShader.length());
			OpenGL::compileShader(fragment);

			if (!OpenGL::isCompilationSuccessful(fragment))
			{
				ERROR_ID err =  fatalError(ERROR_ID::SHADER_COMPILATION_FAIL, OpenGL::getCompilationFailMessage(fragment));
				OpenGL::deleteShader(fragment);
				return err;
			}
		}

		//Compile and check vertex shader if there is any.
		if (hasVertex)
		{
			vertex = OpenGL::createShader(OPENGL_SHADER_TYPE::VERTEX);
			if (vertex == 0) return fatalError(ERROR_ID::SHADER_CREATION_FAIL);

			OpenGL::shaderSource(vertex, 1, data.vertexShader.utf8(), data.vertexShader.length());
			OpenGL::compileShader(vertex);

			if (!OpenGL::isCompilationSuccessful(vertex))
			{
				ERROR_ID err = fatalError(ERROR_ID::SHADER_COMPILATION_FAIL, OpenGL::getCompilationFailMessage(fragment));
				OpenGL::deleteShader(vertex);
				return err;
			}
		}

		return ERROR_ID::NONE;
	}

	void ShaderManager::_extractShaderFromSplittedString(const class String& splittedString, 
		ShaderScriptResource & r, ui32 & current, String& out)
	{

		String filename = splittedString.getNextWord(current);
		Path p = r.fileName();
		p.toParent();
		String key = (p.string()).getSubString(Path::data().string().length()) + filename;
		out = ResourceManager::loadText(key);
		ResourceManager::unload(key);
	}
}
