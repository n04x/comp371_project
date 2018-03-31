#include "Floor.h"

Floor::Floor()
{
	vertices = {
		// positions
		glm::vec3(511.0f, 0.0f, 511.0f),		// 0
		glm::vec3(511.0f, 0.0f,-512.0f),		// 1
		glm::vec3(-512.0f, 0.0f, 511.0f),		// 3

		glm::vec3(511.0f, 0.0f,-512.0f),		// 1
		glm::vec3(-512.0f, 0.0f,-512.0f),		// 2
		glm::vec3(-512.0f, 0.0f, 511.0f),		// 3

	};
	normal = {
		glm::vec3(0.f, 1.0f, 0.0f),
		glm::vec3(0.f, 1.0f, 0.0f),
		glm::vec3(0.f, 1.0f, 0.0f),
		glm::vec3(0.f, 1.0f, 0.0f),
		glm::vec3(0.f, 1.0f, 0.0f),
		glm::vec3(0.f, 1.0f, 0.0f),
	};
	texture_coordinates = {
		glm::vec2(1.0f, 1.0f),		// 0
		glm::vec2(1.0f, 0.0f),		// 1
		glm::vec2(0.0f, 1.0f),		// 3

		glm::vec2(1.0f, 0.0f),		// 1
		glm::vec2(0.0f, 0.0f),		// 2
		glm::vec2(0.0f, 1.0f)		// 3
	};

	indices = {
		0, 1, 3,
		1, 2, 3
	};
	
	floor_texture = loadTexture(texPath);
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
	
	glGenBuffers(1, &VBOnorm);
	glBindBuffer(GL_ARRAY_BUFFER, VBOnorm);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normal.size(), &normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
	
	
	
}

auto Floor::draw(Shader shdr) -> void
{

	glBindVertexArray(VAO);

	if (swap) {
		glEnableVertexAttribArray(1);
	}
	else {
		glDisableVertexAttribArray(1);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floor_texture);
	glUniform1i(glGetUniformLocation(shdr.ID, "tex"), 0);
	glm::mat4 floor_model = glm::mat4(1.0f);
	//floor_model = glm::rotate(floor_model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//floor_model = glm::rotate(floor_model, glm::radians(-45.0f / 2), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(floor_model));
	
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

auto Floor::getSwap() -> bool
{
	return swap;
}

auto Floor::setSwap(bool texture_enable) -> void
{
	//std::cout << texture_enable << std::endl;
	this->swap = texture_enable;
}

auto Floor::loadTexture(char const *path) -> GLuint
{
	GLuint textureID;
	
	// texture
	glGenTextures(1, &textureID);
	int width, height, nrChannel;
	auto *data = stbi_load(path, &width, &height, &nrChannel, 0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load and generate the texture
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load grass texture " << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}
