#include "SpriteShader.h"
#include <Globals\bs_globals.h>
#include <Rendering\bs_Shader.h>

SpriteShader::SpriteShader()
	:bs::ShaderScript()
{

}

SpriteShader::~SpriteShader()
{

}

void	SpriteShader::initialize()
{
	std::cout << "Init sprite shader" << std::endl;
	name = "DefaultSpriteShader";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	bs::String vertexSourceString = bs::g_resourceManager.loadText("Shaders/Default/Vertex_DefaultSprite.txt");
	bs::String fragmentSourceString = bs::g_resourceManager.loadText("Shaders/Default/Fragment_DefaultSprite.txt");

	const char* vertexSource = vertexSourceString.utf8();
	const char* fragmentSource = fragmentSourceString.utf8();

	GLint	vertexSourceLength = vertexSourceString.length();
	GLint	fragmentSourceLength = fragmentSourceString.length();

	glShaderSource(vertexShader, 1, &vertexSource, &vertexSourceLength);
	glShaderSource(fragmentShader, 1, &fragmentSource, &fragmentSourceLength);

	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << "Tex vertex shader load error : " << buffer << std::endl;
	}


	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << "Tex fragment shader load error : " << buffer << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << "Tex fragment shader load error : " << buffer << std::endl;
	}

	glBindFragDataLocation(shaderProgram, 0, "outColor");

	
	//Get shader
	bs::g_shaderManager.getShaderMap()[name] = bs::Shader(name, shaderProgram);
	bs::Shader* s = &bs::g_shaderManager.getShaderMap()[name];

	s->addAttribute("positionVertex");
	s->addAttribute("uvVertex");
	s->addAttribute("colorVertex");

	glLinkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);


	s->addUniform("view", bs::UNIFORM_TYPE::MATRIX4);
	s->addUniform("projection", bs::UNIFORM_TYPE::MATRIX4);
	s->addUniform("textureContent", bs::UNIFORM_TYPE::SAMPLER2D);
}