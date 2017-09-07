#ifndef _BS_SPRITE_H_
#define _BS_SPRITE_H_

#include <Math/bs_Vector.h>
namespace bs
{
	class Texture2D;
	class Shader;

	class Sprite
	{
	public:
		Sprite();
		Sprite(const Texture2D* texture, const  Shader* shader);
		Sprite(const Sprite& s);
		~Sprite();

		inline	void				setOrientation(f32 orientation)			{ m_orientation = orientation; }
		inline	f32					orientation() const						{ return m_orientation; }

		inline	void				setPosition(const Vector2& position)	{ m_position = position; }
		inline	void				setPosition(f32 x, f32 y)				{ m_position = Vector2(x, y); }
		inline	const Vector2&		position()	const						{ return m_position; }

		inline	void				setScale(const Vector2& scale)			{ m_scale = scale; }
		inline	void				setScale(f32 x, f32 y)					{ m_scale = Vector2(x, y); }
		inline	const Vector2&		scale()		const						{ return m_scale; }

		inline	void				setTexture(Texture2D* texture)			{ m_texture = texture; }
		inline	const Texture2D*	texture()	const						{ return m_texture; }

		inline	void				setShader(Shader* shader)				{ m_shader = shader; }
		inline const Shader*		shader()	const						{ return m_shader; }

		

	private:
		const	Texture2D*	m_texture;
		const	Shader*		m_shader;
		Vector2 m_position;
		Vector2 m_scale;
		f32		m_orientation;
	};
}

#endif // !_BS_SPRITE_H_