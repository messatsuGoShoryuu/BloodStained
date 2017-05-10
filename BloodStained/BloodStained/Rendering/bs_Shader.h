#ifndef BS_SHADER_H
#define BS_SHADER_H

#include <GL/glew.h>
#include "../Containers/bs_HashMap.h"
#include "../Utilities/bs_String.h"

#define BS_MAX_UNIFORM_COUNT 16

namespace bs
{
	typedef GLuint ShaderHandle;

	enum class UNIFORM_TYPE
	{
		NONE,
		FLOAT,
		MATRIX4,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		SAMPLER2D
	};

	struct Uniform
	{
		String id;
		UNIFORM_TYPE type;
	};

	class Shader
	{
	public:
		Shader();
		Shader(String name, ShaderHandle handle);
		Shader(const Shader& s);
		~Shader();

		//Shader initialization functions:
		bool	addSource(const String& source);


		//Create new uniform
		void	addUniform(String name, UNIFORM_TYPE type);

		/*Upload uniform
		**@param data Data to be uploaded, will be cast depending on uniform type
		**Returns next uniform index. Will return 0 if no more uniforms exist.
		*/
		ui32	uploadUniform(void* data);

		void	addAttribute(const char* attributeName);

		//Returns the id of the next uniform to be uploaded.
		inline	const String&	getNextUniform(){ return m_uniformSlots[m_uniformCount].id; }

		//Accessors
		inline	const	String&	name()								{ return m_name; }
		inline	const	String&	name()						const	{ return m_name; }
		inline	const	ui32	uniformCount()						{ return m_uniformCount; }
		inline	const	ui32	uniformCount()				const	{ return m_uniformCount; }
		inline	const	ShaderHandle	handle()					{ return m_handle; }
		inline	const	ShaderHandle	handle()			const	{ return m_handle; }
		inline			void			bind()				const	
		{ 
			glUseProgram(m_handle);
			for (ui32 i = 0; i < m_lastAddedAttribute; i++) glEnableVertexAttribArray(i);
		}
		
		inline			void			unbind()			const	
		{ 
			glUseProgram(0); 
			for (ui32 i = 0; i < m_lastAddedAttribute; i++) glDisableVertexAttribArray(i);
		}

		inline void		beginScope(){ m_lastUploadedUniform = 0; }

	private:
		void			_uploadUniformByType(ui32 index, void* data);

	private:
		Uniform			m_uniformSlots[BS_MAX_UNIFORM_COUNT];
		String			m_name;

		//Filled uniform slots
		ui32			m_uniformCount;
		
		//Needed for sequential update of uniforms.
		ui32			m_lastUploadedUniform;
		ui32			m_lastAddedAttribute;
		ShaderHandle	m_handle;
	};
}
#endif // !BS_SHADER_H
