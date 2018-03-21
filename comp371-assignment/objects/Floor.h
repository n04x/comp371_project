#ifndef FLOOR_H
#define FLOOR_H

#include "..\stdinclude.h"
#include "..\shaders\Shaders.h"

class Floor
{
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normal;
	std::vector<GLuint> indices;
	std::vector<glm::vec2> texture_coordinates;
	Floor();
	auto draw(Shader shdr) -> void;
	auto getSwap() -> bool;
	auto setSwap(bool texture_enable) -> void;
	auto loadTexture(char const *path)->GLuint;
	GLuint floor_texture;

protected:
	GLuint VAO, VBO, VBOnorm, VBOtx;
	GLuint EBO;
	bool swap = true;
	const char *texPath = "..\\comp371-assignment\\textures\\grass.png";
};
#endif // FLOOR_H



