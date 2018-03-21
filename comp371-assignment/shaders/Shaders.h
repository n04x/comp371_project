#ifndef SHADER_H
#define SHADER_H

#include "../stdinclude.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint ID;
	Shader(std::string , std::string fs_path);

	// activation of the shader.
	auto useID() -> const void;
	auto programID()->GLuint;
private:
	
};

#endif

