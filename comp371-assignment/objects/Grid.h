#ifndef GRID_H
#define GRID_H

#include "..\stdinclude.h"
#include "..\shaders\Shaders.h"

class Grid
{
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normal;
	std::vector<glm::vec3> colors;
	Grid();
	auto draw(Shader shdr) -> void;

protected:
	
	GLuint VAO;
	GLuint VBO;
};


#endif // !GRID_H
