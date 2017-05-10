#ifndef BS_SHADERMANAGER_H
#define BS_SHADERMANAGER_H

#include "../Containers/bs_HashMap.h"
#include "../Containers/bs_Array.h"
#include "../Utilities/bs_String.h"
#include "../Rendering/bs_Shader.h"

namespace bs
{
	//A shader script is an interface to create custom shaders.
	//Shaders will be compiled from information created from ShaderScript arrays.
	//The array will be obsolete after that.
	class ShaderScript;

	class ShaderManager
	{
		friend class ResourceManager;
	
	public:
		//Constructor
		ShaderManager();
		//Destructor
		~ShaderManager();

	private:
		//Non implemented copy constructor
		ShaderManager(const ShaderManager& s);

	public:
		
		bool	initialize();
		bool	shutDown();

		void	addShaderScript(ShaderScript* s);

		inline HashMap<String,Shader>&		getShaderMap(){ return m_shaders; }
		inline String&		getShaderSource(String id){ return m_shaderSources[id]; }

	private:
		HashMap<String, Shader> m_shaders;
		HashMap<String, String> m_shaderSources;
		Array<ShaderScript*>	m_shaderScripts;
	};
}


#endif // !BS_SHADERMANAGER_H
