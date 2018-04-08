// ======================================================
// Title: Project COMP 371 - Computer Graphics.
// Student Name: Thomas Backs
// Student ID: 27554524
// ======================================================

#define _USE_MATH_DEFINES

#include "stdinclude.h"
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "camera\Camera.h"
#include "shaders\Shaders.h"
#include "objects\Grid.h"
#include "objects\Coordinate.h"
#include "objects\Horse.h"
#include "objects\Floor.h"
#include "objects\horse_movement.h"
#include "objects\Skybox.h"
#include "objects\Player.h"

// SETTINGS
GLFWwindow* window;
GLuint SCR_WIDTH = 800;
GLuint SCR_HEIGHT = 800;
auto texture_enable = true;
auto shadow_enable = false;
auto walk_cycle_enable = false;			// AI Horse Running
auto player_walk = false;				// Player zebra run.

// shadow settings
GLuint depthMapFBO;
const GLuint SHADOW_WIDTH = 1024;
const GLuint SHADOW_HEIGHT = 1024;

// HORSE
// rendering mode, the default is fill to draw Triangle.
modes choice = FILL;
auto const HORSE_SIZE_VECTOR = 20;
// camera transformation.
GLfloat posX = 0.0f;
GLfloat posY = 15.0f;
GLfloat posZ = 20.0f;
GLfloat upX = 0.0f;
GLfloat upY = 5.0f;
GLfloat upZ = 0.0f;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;

// CAMERA
Camera ourCamera(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
GLfloat lastX = 800 / 2.0f;
GLfloat lastY = 800 / 2.0f;
auto firstMouse = true;

// TIMING
auto dTime = 0.0f; // time between current frame and last frame
auto lastFrame = 0.0f;

// FUNCTION DEFINITION
auto render_world_object(Floor ourFloor, Coordinate coordaxes, Player playerHorse, std::vector<Horse> &ourHorses, Shader shdr) -> void;
auto mouse_callback_input(GLFWwindow *window, GLdouble xpos, GLdouble ypos) -> void;
auto key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void;
auto load_texture(char const * path)->GLuint;

auto init() -> int{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project for 371", nullptr, nullptr);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback_input);
	if (window == nullptr) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	if (glewInit() != 0) {
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	return 0;
}

auto main() -> int{

	if (init() != 0) {
		return -1;
	}

	// create my shaders.
	Shader shdr("shaders\\vs.ogl", "shaders\\fs.ogl");
	Shader depth_shdr("shaders\\depthvs.ogl", "shaders\\depthfs.ogl");
	Shader sky_shdr("shaders\\vs_sky.ogl", "shaders\\fs_sky.ogl");

	// create my objects.
	Grid ourGrid;
	Floor ourFloor;
	Coordinate coordaxes;
	Player playerHorse;
	//anotherHorse.x_t = 10;
	std::vector<Horse> ourHorses;
	srand(time(NULL));
	for (int i = 0; i < HORSE_SIZE_VECTOR; i++) {
		Horse horse;
		horse.setBBWorld(makeBB(100, -100, -50, 50));
		horse.random_horse_position();
		ourHorses.push_back(horse);
	}

	//horse_movement ourHorse_movement;
	Skybox ourSkybox;
	// ===== PROJECTION MATRIX CONFIGURATION =====
	glm::mat4 pm = glm::perspective(glm::radians(ourCamera.c_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.f);
	
	
	// load textures
	GLuint grass_texture = load_texture("..\\comp371-assignment\\textures\\grass.jpg");
	// use the depth shader id.

	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	GLuint depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float border_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// shader config.
	shdr.useID();
	glUniform1i(glGetUniformLocation(shdr.ID, "tex"), 0);
	glUniform1i(glGetUniformLocation(shdr.ID, "shadow_map"), 1);

	// ====== LIGHTHING POSITION CONFIGURATION =====
	glm::vec3 light_position = glm::vec3(0.0f, 20.0f, 0.0f);
	glUniform3fv(glGetUniformLocation(shdr.ID, "v_p"), 1, glm::value_ptr(ourCamera.c_pos));
	glUniform3fv(glGetUniformLocation(shdr.ID, "l_p"), 1, glm::value_ptr(light_position));
	glUniform4f(glGetUniformLocation(shdr.ID, "color"), 0.5f, 0.5f, 0.5f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		// pre-frame time logic.
		float currentFrame = glfwGetTime();
		dTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// clear the screen.
		glClearColor(.7, .7, .7, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//1st pass: render depth map from light's perspective.
		glm::mat4 light_projection;
		glm::mat4 light_view;
		glm::mat4 light_space_matrix;
		float near_plane = 0.1f;
		float far_plane = 40.0;
		light_projection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);
		light_view = glm::lookAt(light_position, glm::vec3(0.0f), glm::vec3(0.0, 0.0, 1.0));
		light_space_matrix = light_projection * light_view;
		
		// render the scene from light point of view.
		depth_shdr.useID();
		glUniformMatrix4fv(glGetUniformLocation(depth_shdr.ID, "light_space_matrix"), 1, GL_FALSE, glm::value_ptr(light_space_matrix));

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, grass_texture);
		if(shadow_enable)
			render_world_object(ourFloor, coordaxes, playerHorse, ourHorses, depth_shdr);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// reset our viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// 2nd pass: render the scene normally
		// projection and view matrices setting.
		pm = glm::perspective(glm::radians(ourCamera.c_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.f);
		glm::mat4 vm = ourCamera.getViewMatrix();
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw the skybox
		glDisable(GL_DEPTH_TEST);
		sky_shdr.useID();
		glUniformMatrix4fv(glGetUniformLocation(sky_shdr.ID, "v_m"), 1, false, glm::value_ptr(glm::mat4(glm::mat3(vm))));
		glUniformMatrix4fv(glGetUniformLocation(sky_shdr.ID, "p_m"), 1, false, glm::value_ptr(pm));
		ourSkybox.draw(sky_shdr);
		glEnable(GL_DEPTH_TEST);
		
		// draw the horses
		shdr.useID();
		glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "p_m"), 1, false, glm::value_ptr(pm));
		glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "v_m"), 1, false, glm::value_ptr(vm));
		glUniform3fv(glGetUniformLocation(shdr.ID, "v_p"), 1, glm::value_ptr(ourCamera.c_pos));
		glUniform3fv(glGetUniformLocation(shdr.ID, "l_p"), 1, glm::value_ptr(light_position));
		glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "light_space_matrix"), 1, GL_FALSE, glm::value_ptr(light_space_matrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, grass_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		render_world_object(ourFloor, coordaxes, playerHorse, ourHorses, shdr);
		if (player_walk)
			playerHorse.player_horse_running(dTime);
		if (walk_cycle_enable) {
			for (int i = 0; i < ourHorses.size(); i++) {
				bool collide = false;
					for (int j = 0; j < ourHorses.size(); j++) {
						if (i != j) {
							if (ourHorses.at(i).check_collision(ourHorses.at(j))) {
								collide = true;
								break;
							}
						}
					}
					if (i % 2) {
						ourHorses.at(i).horse_running(dTime, collide);
					}
					else
						ourHorses.at(i).horse_eating_grass(dTime);
			}
		}
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	return 0;
}

auto key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) -> void {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		ourCamera.processKB(UP, dTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		ourCamera.processKB(DOWN, dTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ourCamera.processKB(LEFT, dTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ourCamera.processKB(RIGHT, dTime);
		
	// TEXTURE SWAPPING
	if (glfwGetKey(window, GLFW_KEY_X)) {
		if (texture_enable) {
			texture_enable = false;
		}
		else
			texture_enable = true;
	}
	
	// SHADOW SWAPPING
	if (glfwGetKey(window, GLFW_KEY_B)) {
		if (!shadow_enable) {
			shadow_enable = true;
		}
		else
			shadow_enable = false;
	}
	// HORSE WALK CYCLE FOR MY 20 STUPID HORSES
	if (glfwGetKey(window, GLFW_KEY_H)) {
		if (walk_cycle_enable) {
			walk_cycle_enable = false;

		}
		else
			walk_cycle_enable = true;
	}
	if (glfwGetKey(window, GLFW_KEY_R)) {
		if (player_walk) {
			player_walk = false;

		}
		else
			player_walk = true;
	}
	// HORSE DRAWING METHOD
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		choice = LINES;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		choice = POINTS;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		choice = FILL;
}

auto render_world_object(Floor ourFloor, Coordinate coordaxes, Player playerHorse, std::vector<Horse> &ourHorses, Shader shdr) -> void
{
	ourFloor.setSwap(texture_enable);
	ourFloor.draw(shdr);
	coordaxes.draw(shdr);
	playerHorse.setSwap(texture_enable);
	playerHorse.draw_horse(shdr);
	playerHorse.zebra_callback_input(window);
	for (auto count =0; count < ourHorses.size(); count++) {
		ourHorses.at(count).setSwap(texture_enable);
		ourHorses.at(count).draw_horse(shdr, choice);
	}
	for (auto i = 0; i < ourHorses.size(); i++) {
		if (playerHorse.player_hit_horse(ourHorses.at(i))) {
			ourHorses.erase(ourHorses.begin() + i);
			std::cout << "collision!" << std::endl;
		}
	}
}

auto mouse_callback_input(GLFWwindow * window, GLdouble xpos, GLdouble ypos) -> void
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (firstMouse) {
			lastX = xpos;
			firstMouse = false;
		}
		GLdouble xoffset = xpos - lastX;

		lastX = xpos;

		ourCamera.process_m_move_x(xoffset);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		if (firstMouse) {
			lastY = ypos;
			firstMouse = false;
		}
		GLdouble yoffset = ypos - lastY;

		lastY = ypos;

		ourCamera.process_m_move_y(yoffset);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (firstMouse) {
			lastY = ypos;
			firstMouse = false;
		}
		GLdouble yoffset = ypos - lastY;

		lastY = ypos;
		ourCamera.process_m_zoom(yoffset);
	}
}

auto load_texture(char const * path) -> GLuint
{
	; GLuint textureID;
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
