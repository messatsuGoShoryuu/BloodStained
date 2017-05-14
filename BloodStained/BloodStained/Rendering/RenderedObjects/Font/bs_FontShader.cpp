#include "bs_FontShader.h"

#include "../../bs_Shader.h"
#include "../../../Globals/bs_globals.h"
#include "../../../Utilities/bs_Error.h"

namespace bs
{
	FontShader::FontShader()
		:ShaderScript()
	{

	}

	FontShader::~FontShader()
	{

	}

	void FontShader::initialize()
	{
		name = "FontShader";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		bs::String vertexSourceString = bs::g_resourceManager.loadText("Shaders/Default/Vertex_DefaultFont.txt");
		bs::String fragmentSourceString = bs::g_resourceManager.loadText("Shaders/Default/Fragment_DefaultFont.txt");

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
			char buffer[1024];
			glGetShaderInfoLog(vertexShader, 1024, NULL, buffer);
			Error::fatalError(ERROR_ID::FAIL_VERT_SHADER_LOAD, buffer);
		}


		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			char buffer[1024];
			glGetShaderInfoLog(fragmentShader, 1024, NULL, buffer);
			Error::fatalError(ERROR_ID::FAIL_FRAG_SHADER_LOAD, buffer);
		}

		GLuint shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

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

		s->addUniform("projection", bs::UNIFORM_TYPE::MATRIX4);
		s->addUniform("textureContent", bs::UNIFORM_TYPE::SAMPLER2D);
	}
}