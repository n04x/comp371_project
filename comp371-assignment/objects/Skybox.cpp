#include "Skybox.h"



Skybox::Skybox()
{
	vertices = {
		// Square #1
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		// Square #2
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		// Square #3
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		// Square #4
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		// Square #5
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		// Square #6
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f)
	};
	normal = {
		// Square #1
		glm::vec3(0.0f, 0.0f,-1.0f),
		glm::vec3(0.0f, 0.0f,-1.0f),
		glm::vec3(0.0f, 0.0f,-1.0f),
		glm::vec3(0.0f, 0.0f,-1.0f),
		glm::vec3(0.0f, 0.0f,-1.0f),
		glm::vec3(0.0f, 0.0f,-1.0f),
		// Square #2
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		// Square #3
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		// Square #4
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		// Square #5
		glm::vec3(0.0f,-1.0f, 0.0f),
		glm::vec3(0.0f,-1.0f, 0.0f),
		glm::vec3(0.0f,-1.0f, 0.0f),
		glm::vec3(0.0f,-1.0f, 0.0f),
		glm::vec3(0.0f,-1.0f, 0.0f),
		glm::vec3(0.0f,-1.0f, 0.0f),
		// Square #6
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	texture_coordinates = {
		// Square #1
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(0.0, 0.0),
		// Square #2
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(0.0, 0.0),
		// Square #3
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(0.0, 0.0),
		// Square #4
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(0.0, 0.0),
		// Square #5
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(0.0, 0.0),
		// Square #6
		glm::vec2(0.0, 0.0),
		glm::vec2(1.0, 0.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(1.0, 1.0),
		glm::vec2(0.0, 1.0),
		glm::vec2(0.0, 0.0),
	};
	faces = {
		"..\\comp371-assignment\\textures\\right.jpg",
		"..\\comp371-assignment\\textures\\left.jpg",
		"..\\comp371-assignment\\textures\\top.jpg",
		"..\\comp371-assignment\\textures\\bottom.jpg",
		"..\\comp371-assignment\\textures\\back.jpg",
		"..\\comp371-assignment\\textures\\front.jpg",
	};
	skybox_texture = loadTexture(texPath);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &VBOtx);
	glBindBuffer(GL_ARRAY_BUFFER, VBOtx);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*texture_coordinates.size(), &texture_coordinates[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &VBOnorm);
	glBindBuffer(GL_ARRAY_BUFFER, VBOnorm);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normal.size(), &normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

auto Skybox::loadTexture(char const * path) -> GLuint
{
	GLuint textureID;
	// texture
	glGenTextures(1, &textureID);
	int width, height, nrChannel;
	unsigned char *data;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	// load and generate the texture
	for (int i = 0; i < 6; i++) {
		data = stbi_load(faces[i].c_str(), &width, &height, &nrChannel, 0);
		std::cout << faces[i].c_str() << std::endl;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(data);

	return textureID;
}
auto Skybox::draw(Shader shdr) -> void {
	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
	glUniform1i(glGetUniformLocation(shdr.ID, "tex"), 0);
	glm::mat4 skybox_model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(skybox_model));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
