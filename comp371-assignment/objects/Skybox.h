#ifndef SKYBOX_H
#define SKYBOX_H

#include "..\stdinclude.h"
#include "..\shaders\Shaders.h"
class Skybox
{
public:
	std::vector<std::string> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normal;
	std::vector<GLuint> indices;
	std::vector<glm::vec2> texture_coordinates;

	Skybox();
	auto draw(Shader shdr) -> void;
	auto loadTexture(char const *path)->GLuint;
	GLuint skybox_texture;

protected:
	GLuint VAO, VBO, VBOnorm, VBOtx;
	const char *texPath = "...";
};

#endif // !SKYBOX_H

