#ifndef TEXSHADER3D_H
#define TEXSHADER3D_H

#include <Rendering/bs_ShaderScript.h>

class TexShader3D : public bs::ShaderScript
{
public:
	TexShader3D();
	~TexShader3D();

	static	TexShader3D instance;

	void	initialize();
};

#endif // !TESTSHADER_H
