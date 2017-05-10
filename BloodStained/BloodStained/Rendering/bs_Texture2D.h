#ifndef BS_TEXTURE2D_H
#define BS_TEXTURE2D_H

#include "../Utilities/bs_types.h"
#include <GL/glew.h>

namespace bs
{
	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(ui16 width, ui16 height, ui32 id, bool isTiled);
		Texture2D(const Texture2D& t);
		~Texture2D();

		inline	const ui16 width()	const	{ return m_width; }
		inline	const ui16 height()	const	{ return m_height; }
		inline	const ui32 id()		const	{ return m_id; }
		inline	const bool isTiled()const	{ return m_isTiled; }

		inline	bool operator==(const Texture2D& other) const{ return m_id == other.m_id; }
		inline	bool operator!=(const Texture2D& other) const{ return m_id != other.m_id; }

		inline void	bind()		const
		{ 
			::glEnable(GL_TEXTURE_2D);
			::glActiveTexture(_textureBindIndex());
			::glBindTexture(GL_TEXTURE_2D, m_id); 
			sm_boundTextureCount++;
		}
		inline void	unbind()	const
		{ 
			if (sm_boundTextureCount > 0) sm_boundTextureCount--;
			::glBindTexture(GL_TEXTURE_2D, 0); 
		}

		inline	static ui32 boundTextureCount(){ return sm_boundTextureCount; }
		static	Texture2D	create(i32 channels, ui32 width, ui32 height, byte* buffer, bool tiled);
		static	void		destroy(Texture2D& tex);

	private:
		GLenum	_textureBindIndex() const;

	private:
		ui32	m_id;
		ui16	m_width;
		ui16	m_height;		
		bool	m_isTiled;

		static	ui32 sm_boundTextureCount;
	};
}


#endif // !BS_TEXTURE_H
