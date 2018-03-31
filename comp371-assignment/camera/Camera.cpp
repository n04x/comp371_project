#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : c_front(glm::vec3(0.0f, 0.0f, -1.0f)), c_mov_speed(SPEED), c_mouse_sens(SENS), c_zoom(ZOOM)
{
	c_pos = position;
	c_world_up = up;
	c_yaw = yaw;
	c_pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : c_front(glm::vec3(0.0f, 0.0f, 0.0f)), c_mov_speed(SPEED), c_mouse_sens(SENS), c_zoom(ZOOM)
{
	c_pos = glm::vec3(posX, posY, posZ);
	c_world_up = glm::vec3(upX, upY, upZ);
	c_yaw = yaw;
	c_pitch = pitch;
	updateCameraVectors();
}
auto Camera::startingView() -> glm::mat4
{
	return glm::lookAt(c_pos, c_front, c_up);
}
auto Camera::getViewMatrix() -> glm::mat4
{
	return glm::lookAt(c_pos, c_pos + c_front, c_up);
}

auto Camera::processKB(c_movement direction, GLfloat dTime) -> void
{
	GLfloat velocity = c_mov_speed * dTime;
	if (direction == UP)
		c_pos += c_up * velocity;
	if (direction == DOWN)
		c_pos -= c_up * velocity;
	if (direction == LEFT)
		c_pos -= c_right * velocity;
	if (direction == RIGHT)
		c_pos += c_right * velocity;

}

auto Camera::process_m_move_x(GLfloat xoffset, GLboolean constrainPitch) -> void
{
	xoffset *= c_mouse_sens;


	c_yaw += xoffset;


	//check the pitch, to avoid going out of bounds.
	if (constrainPitch)
	{
		if (c_pitch > 89.0f)
			c_pitch = 89.0f;
		if (c_pitch < -89.0f)
			c_pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	updateCameraVectors();
}
auto Camera::process_m_move_y(GLfloat yoffset, GLboolean constrainPitch) -> void
{
	yoffset *= c_mouse_sens;

	c_pitch += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (c_pitch > 89.0f)
			c_pitch = 89.0f;
		if (c_pitch < -89.0f)
			c_pitch = -89.0f;
	}
	updateCameraVectors();
}

auto Camera::process_m_zoom(GLfloat yoffset) -> void
{
	c_zoom += yoffset;
}

auto Camera::updateCameraVectors() -> void
{
	// calcuate the new c_front vector.
	glm::vec3 front;
	front.x = cos(glm::radians(c_yaw)) * cos(glm::radians(c_pitch));
	front.y = sin(glm::radians(c_pitch));
	front.z = sin(glm::radians(c_yaw)) * cos(glm::radians(c_pitch));
	c_front = glm::normalize(front);

	// recalculate right/up vector. 
	c_right = glm::normalize(glm::cross(c_front, c_world_up));
	c_up = glm::normalize(glm::cross(c_right, c_front));
}
