// This build is inspired from this website:	https://learnopengl.com/Getting-started/Camera
// modified and re-adjusted to adapt the assignment reuirement.

#ifndef CAMERA_H
#define CAMERA_H

#include "..\stdinclude.h"

enum c_movement { LEFT, RIGHT, UP, DOWN };

// default camera values in order to reset camera position upon call.
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENS = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	// attributes for the camera.
	glm::vec3 c_pos;
	glm::vec3 c_front;
	glm::vec3 c_up;
	glm::vec3 c_right;
	glm::vec3 c_world_up;

	// angles.
	GLfloat c_yaw;
	GLfloat c_pitch;

	// camera options.
	GLfloat c_mov_speed;
	GLfloat c_mouse_sens;
	GLfloat c_zoom;

	// Constructor with vector input.
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	// Constructor with scalar input.
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// function to return the view matrix.
	auto getViewMatrix()->glm::mat4;

	// process keyboard input, accept param. from enum value.
	auto processKB(c_movement direction, GLfloat dTime) -> void;
	auto process_m_zoom(GLfloat yoffset) -> void;
	auto process_m_move_x(GLfloat xoffset, GLboolean constrainPitch = true) -> void;
	auto process_m_move_y(GLfloat xoffset, GLboolean constrainPitch = true) -> void;
private:
	auto updateCameraVectors() -> void;
};

#endif // !CAMERA_H
