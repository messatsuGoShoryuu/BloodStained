#ifndef SPRITESHADER_H
#define SPRITESHADER_H

#include <Rendering/bs_ShaderScript.h>

class SpriteShader : public bs::ShaderScript
{
public:
	SpriteShader();
	~SpriteShader();

	static	SpriteShader instance;

	void	initialize();
};

#endif // !SPRITESHADER_H
