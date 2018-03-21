#include "Grid.h"

Grid::Grid()
{
	vertices = {
		// positions
		glm::vec3(-50.0f, 0.0f, 0.0f),
		glm::vec3( 50.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -50.0f),
		glm::vec3(0.0f, 0.0f,  50.0f),
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

}

auto Grid::draw(Shader shdr) -> void {
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-45.0f / 2), glm::vec3(0.0f, 1.0f, 0.0f));
	GLuint mm_addr = glGetUniformLocation(shdr.ID, "m_m");
	
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -51.0f));
	for (int i = 0; i <= 100; i++) {
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(mm_addr, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(shdr.ID, "color"), 1.0f, 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_LINES, 0, 2);
	}
	model = glm::translate(model, glm::vec3(-51.0f, 0.0f, -50.0f));
	for (int i = 0; i <= 100; i++) {
		
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(mm_addr, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(shdr.ID, "color"), 1.0f, 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_LINES, 2, 2);
	}
}


