#ifndef COORDINATE_H
#define COORDINATE_H

#include "..\stdinclude.h"
#include "..\shaders\Shaders.h"
class Coordinate
{
public:
	std::vector<glm::vec3> vertices;
	Coordinate();
	auto draw(Shader shdr) -> void;
protected:
	GLuint VAO;
	GLuint VBO;
};

#endif // !COORDINATE_H

