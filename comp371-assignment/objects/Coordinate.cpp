#include "Coordinate.h"

Coordinate::Coordinate()
{
	vertices = {
		// positions
		glm::vec3(0.0f,0.0f,0.0f), glm::vec3(5.0f,0.0f,0.0f), //X-axis line
		glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,5.0f,0.0f), //Y-axis line
		glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,5.0f)  //Z-axis line
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

auto Coordinate::draw(Shader shdr) -> void
{
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-45.0f / 2), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, false, glm::value_ptr(model));
	glDisable(GL_DEPTH_TEST);
	glUniform4f(glGetUniformLocation(shdr.ID, "color"), 0.0f, 0.0f, 1.0f, 1.0f); // blue line for x axis
	glDrawArrays(GL_LINES, 0, 2);
	glUniform4f(glGetUniformLocation(shdr.ID, "color"), 0.0f, 1.0f, 0.0f, 1.0f); // green line for y axis
	glDrawArrays(GL_LINES, 2, 2);
	glUniform4f(glGetUniformLocation(shdr.ID, "color"), 1.0, 0.0, 0.0, 1.0); // red line for z axis
	glDrawArrays(GL_LINES, 4, 2);
	glEnable(GL_DEPTH_TEST);
	glUniform4f(glGetUniformLocation(shdr.ID, "color"), 1.0f, 1.0f, 1.0f, 1.0f);
}

