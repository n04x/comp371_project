#include "Player.h"

GLfloat Player::player_x = 0.0f;
GLfloat Player::player_z = 0.0f;

glm::mat4 Player::player_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_scale = glm::mat4(1.0f);
glm::mat4 Player::player_torso_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_head_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_neck_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_front_upper_right_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_front_lower_right_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_hind_upper_right_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_hind_lower_right_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_front_upper_left_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_front_lower_left_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_hind_upper_left_leg_rotation = glm::mat4(1.0f);
glm::mat4 Player::player_hind_lower_left_leg_rotation = glm::mat4(1.0f);
glm::vec3 Player::horse_position_max = glm::vec3(player_x + 1.0f, 0.0f, player_z + 0.25f);
glm::vec3 Player::horse_position_min = glm::vec3(player_x - 1.0f, 0.0f, player_z - 0.25f);
// the max angle condition.
static int torso_angle_counter = 0;
static int head_angle_counter = 0;
static int neck_angle_counter = 0;
static int furl_angle_counter = 0;
static int flrl_angle_counter = 0;
static int hurl_angle_counter = 0;
static int hlrl_angle_counter = 0;
static int full_angle_counter = 0;
static int flll_angle_counter = 0;
static int hull_angle_counter = 0;
static int hlll_angle_counter = 0;
static bool forward_running = true;
int player_running_counter = 0;
int player_run_cycle = 1;
auto Player::zebra_callback_input(GLFWwindow * window) -> void
{

	// horse movement.
	if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			player_x -= 1.0f;
		}
		else {
			player_rotation = glm::translate(player_rotation, glm::vec3(player_x, 0.0f, player_z));
			player_rotation = glm::rotate(player_rotation, glm::radians(-5.0f), glm::vec3(0, 0, 1));
			player_rotation = glm::translate(player_rotation, -glm::vec3(player_x, 0.0f, player_z));

		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			player_x += 1.0f;
		else {
			player_rotation = glm::translate(player_rotation, glm::vec3(player_x, 0.0f, player_z));
			player_rotation = glm::rotate(player_rotation, glm::radians(5.0f), glm::vec3(0, 0, 1));
			player_rotation = glm::translate(player_rotation, -glm::vec3(player_x, 0.0f, player_z));
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			player_z -= 1.0f;
		else {
			player_rotation = glm::translate(player_rotation, glm::vec3(player_x, 0.0f, player_z));
			player_rotation = glm::rotate(player_rotation, glm::radians(-5.0f), glm::vec3(0, 1, 0));
			player_rotation = glm::translate(player_rotation, -glm::vec3(player_x, 0.0f, player_z));
		}

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			player_z += 1.0f;
		else {
			player_rotation = glm::translate(player_rotation, glm::vec3(player_x, 0.0f, player_z));
			player_rotation = glm::rotate(player_rotation, glm::radians(5.0f), glm::vec3(0, 1, 0));
			player_rotation = glm::translate(player_rotation, -glm::vec3(player_x, 0.0f, player_z));
		}
	}

	//  random horse location.
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		player_x = (rand() % 100) - 50.0f;
		player_z = (rand() % 100) - 50.0f;
	}
	// reset to default position.
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
		// positions.
		player_x = 0.0f;
		player_z = 0.0f;
		player_scale = glm::mat4(1.0f);
		player_rotation = glm::mat4(1.0f);
		player_torso_rotation = glm::mat4(1.0f);
	}

	// horse transformation (scale the horse)
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		player_scale = glm::scale(player_scale, glm::vec3(1.1f, 1.1f, 1.1f));
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		player_scale = glm::scale(player_scale, glm::vec3(0.9f, 0.9f, 0.9f));
	}
	// horse torso rotation
	if ((glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (torso_angle_counter >= -18 && torso_angle_counter < 18) {
				player_torso_rotation = glm::rotate(player_torso_rotation, glm::radians(5.0f), glm::vec3(1, 0, 0));
				player_torso_rotation++;
			}
		}
		else {
			if (torso_angle_counter > -18) {
				player_torso_rotation = glm::rotate(player_torso_rotation, glm::radians(-5.0f), glm::vec3(1, 0, 0));
				player_torso_rotation--;
			}
		}
	}
	// horse head movement
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (head_angle_counter >= -5 && head_angle_counter < 5) {
				player_head_rotation = glm::translate(player_head_rotation, player_head_to_neck);
				player_head_rotation = glm::rotate(player_head_rotation, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				player_head_rotation = glm::translate(player_head_rotation, -player_head_to_neck);
				head_angle_counter++;
			}
		}
		else {
			if (head_angle_counter > -5) {
				player_head_rotation = glm::translate(player_head_rotation, player_head_to_neck);
				player_head_rotation = glm::rotate(player_head_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				player_head_rotation = glm::translate(player_head_rotation, -player_head_to_neck);
				head_angle_counter--;
			}
		}
	}
	// horse neck movement
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (neck_angle_counter >= 0 && neck_angle_counter < 15) {
				player_neck_rotation = glm::translate(player_neck_rotation, player_neck_to_torso);
				player_neck_rotation = glm::rotate(player_neck_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_neck_rotation = glm::translate(player_neck_rotation, -player_neck_to_torso);
				neck_angle_counter++;
			}
		}
		else {
			if (neck_angle_counter > 0) {
				player_neck_rotation = glm::translate(player_neck_rotation, player_neck_to_torso);
				player_neck_rotation = glm::rotate(player_neck_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_neck_rotation = glm::translate(player_neck_rotation, -player_neck_to_torso);
				neck_angle_counter--;
			}
		}
	}
	// horse front right upper leg movement.
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (furl_angle_counter >= -15 && furl_angle_counter < 15) {
				player_front_upper_right_leg_rotation = glm::translate(player_front_upper_right_leg_rotation, player_torso_to_front_upper_leg);
				player_front_upper_right_leg_rotation = glm::rotate(player_front_upper_right_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_upper_right_leg_rotation = glm::translate(player_front_upper_right_leg_rotation, -player_torso_to_front_upper_leg);
				furl_angle_counter++;
			}
		}
		else {
			if (furl_angle_counter > -15) {
				player_front_upper_right_leg_rotation = glm::translate(player_front_upper_right_leg_rotation, player_torso_to_front_upper_leg);
				player_front_upper_right_leg_rotation = glm::rotate(player_front_upper_right_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_upper_right_leg_rotation = glm::translate(player_front_upper_right_leg_rotation, -player_torso_to_front_upper_leg);
				furl_angle_counter--;
			}
		}
	}
	// horse front right lower leg movement.
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (flrl_angle_counter >= 0 && flrl_angle_counter < 15) {
				player_front_lower_right_leg_rotation = glm::translate(player_front_lower_right_leg_rotation, player_front_right_knee);
				player_front_lower_right_leg_rotation = glm::rotate(player_front_lower_right_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_lower_right_leg_rotation = glm::translate(player_front_lower_right_leg_rotation, -player_front_right_knee);
				flrl_angle_counter++;
			}
		}
		else {
			if (flrl_angle_counter > 0) {
				player_front_lower_right_leg_rotation = glm::translate(player_front_lower_right_leg_rotation, player_front_right_knee);
				player_front_lower_right_leg_rotation = glm::rotate(player_front_lower_right_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_lower_right_leg_rotation = glm::translate(player_front_lower_right_leg_rotation, -player_front_right_knee);
				flrl_angle_counter--;
			}
		}
	}
	// horse hind right upper leg movement.
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (hurl_angle_counter >= -15 && hurl_angle_counter < 15) {
				player_hind_upper_right_leg_rotation = glm::translate(player_hind_upper_right_leg_rotation, player_torso_to_hind_upper_right_leg);
				player_hind_upper_right_leg_rotation = glm::rotate(player_hind_upper_right_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_upper_right_leg_rotation = glm::translate(player_hind_upper_right_leg_rotation, -player_torso_to_hind_upper_right_leg);
				hurl_angle_counter++;
			}
		}
		else {
			if (hurl_angle_counter > -15) {
				player_hind_upper_right_leg_rotation = glm::translate(player_hind_upper_right_leg_rotation, player_torso_to_hind_upper_right_leg);
				player_hind_upper_right_leg_rotation = glm::rotate(player_hind_upper_right_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_upper_right_leg_rotation = glm::translate(player_hind_upper_right_leg_rotation, -player_torso_to_hind_upper_right_leg);
				hurl_angle_counter--;
			}
		}
	}
	// horse hind right lower leg movement.
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (hlrl_angle_counter >= 0 && hlrl_angle_counter < 15) {
				player_hind_lower_right_leg_rotation = glm::translate(player_hind_lower_right_leg_rotation, player_hind_right_knee);
				player_hind_lower_right_leg_rotation = glm::rotate(player_hind_lower_right_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_lower_right_leg_rotation = glm::translate(player_hind_lower_right_leg_rotation, -player_hind_right_knee);
				hlrl_angle_counter++;
			}
		}
		else {
			if (hlrl_angle_counter > 0) {
				player_hind_lower_right_leg_rotation = glm::translate(player_hind_lower_right_leg_rotation, player_hind_right_knee);
				player_hind_lower_right_leg_rotation = glm::rotate(player_hind_lower_right_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_lower_right_leg_rotation = glm::translate(player_hind_lower_right_leg_rotation, -player_hind_right_knee);
				hlrl_angle_counter--;
			}
		}
	}
	// horse front left upper leg movement.
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (full_angle_counter >= -15 && full_angle_counter < 15) {
				player_front_upper_left_leg_rotation = glm::translate(player_front_upper_left_leg_rotation, player_torso_to_front_upper_left_leg);
				player_front_upper_left_leg_rotation = glm::rotate(player_front_upper_left_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_upper_left_leg_rotation = glm::translate(player_front_upper_left_leg_rotation, -player_torso_to_front_upper_left_leg);
				full_angle_counter++;
			}
		}
		else {
			if (full_angle_counter > -15) {
				player_front_upper_left_leg_rotation = glm::translate(player_front_upper_left_leg_rotation, player_torso_to_front_upper_left_leg);
				player_front_upper_left_leg_rotation = glm::rotate(player_front_upper_left_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_upper_left_leg_rotation = glm::translate(player_front_upper_left_leg_rotation, -player_torso_to_front_upper_left_leg);
				full_angle_counter--;
			}
		}
	}
	// horse front left lower leg movement.
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (flll_angle_counter >= 0 && flll_angle_counter < 15) {
				player_front_lower_left_leg_rotation = glm::translate(player_front_lower_left_leg_rotation, player_front_left_knee);
				player_front_lower_left_leg_rotation = glm::rotate(player_front_lower_left_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_lower_left_leg_rotation = glm::translate(player_front_lower_left_leg_rotation, -player_front_left_knee);
				flll_angle_counter++;
			}
		}
		else {
			if (flll_angle_counter > 0) {
				player_front_lower_left_leg_rotation = glm::translate(player_front_lower_left_leg_rotation, player_front_left_knee);
				player_front_lower_left_leg_rotation = glm::rotate(player_front_lower_left_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_front_lower_left_leg_rotation = glm::translate(player_front_lower_left_leg_rotation, -player_front_left_knee);
				flll_angle_counter--;
			}
		}
	}
	// horse hind left upper leg movement.
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (hull_angle_counter >= -15 && hull_angle_counter < 15) {
				player_hind_upper_left_leg_rotation = glm::translate(player_hind_upper_left_leg_rotation, player_torso_to_hind_upper_left_leg);
				player_hind_upper_left_leg_rotation = glm::rotate(player_hind_upper_left_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_upper_left_leg_rotation = glm::translate(player_hind_upper_left_leg_rotation, -player_torso_to_hind_upper_left_leg);
				hull_angle_counter++;
			}
		}
		else {
			if (hull_angle_counter > -15) {
				player_hind_upper_left_leg_rotation = glm::translate(player_hind_upper_left_leg_rotation, player_torso_to_hind_upper_left_leg);
				player_hind_upper_left_leg_rotation = glm::rotate(player_hind_upper_left_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_upper_left_leg_rotation = glm::translate(player_hind_upper_left_leg_rotation, -player_torso_to_hind_upper_left_leg);
				hull_angle_counter--;
			}
		}
	}
	// horse hind left lowerleg movement.
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (hlll_angle_counter >= 0 && hlll_angle_counter < 15) {
				player_hind_lower_left_leg_rotation = glm::translate(player_hind_lower_left_leg_rotation, player_hind_left_knee);
				player_hind_lower_left_leg_rotation = glm::rotate(player_hind_lower_left_leg_rotation, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_lower_left_leg_rotation = glm::translate(player_hind_lower_left_leg_rotation, -player_hind_left_knee);
				hlll_angle_counter++;
			}
		}
		else {
			if (hlll_angle_counter > 0) {
				player_hind_lower_left_leg_rotation = glm::translate(player_hind_lower_left_leg_rotation, player_hind_left_knee);
				player_hind_lower_left_leg_rotation = glm::rotate(player_hind_lower_left_leg_rotation, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				player_hind_lower_left_leg_rotation = glm::translate(player_hind_lower_left_leg_rotation, -player_hind_left_knee);
				hlll_angle_counter--;
			}
		}
	}
}

Player::Player()
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
	player_horse_texture = loadTexture(texPath);
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

// this will draw the horse.
auto Player::draw(Shader shdr, glm::mat4 model) -> void
{
	glBindVertexArray(VAO);

	if (swap) {
		glEnableVertexAttribArray(1);
	}
	else {
		glDisableVertexAttribArray(1);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, player_horse_texture);
	glUniform1i(glGetUniformLocation(shdr.ID, "tex"), 0);
	draw_torso(shdr, model);
	draw_front_left_upper_leg(shdr);
	draw_front_left_lower_leg(shdr);
	draw_front_right_upper_leg(shdr);
	draw_front_right_lower_leg(shdr);
	draw_hind_left_upper_leg(shdr);
	draw_hind_left_lower_leg(shdr);
	draw_hind_right_upper_leg(shdr);
	draw_hind_right_lower_leg(shdr);
	draw_neck(shdr);
	draw_head(shdr);
}

auto Player::setSwap(bool texture_enable) -> void
{
	this->swap = texture_enable;
}

// functions to draw the horse.
auto Player::draw_horse(Shader shdr) -> void
{
	/*if (choice == LINES) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (choice == POINTS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (choice == FILL)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);*/
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(-45.0f / 2), glm::vec3(0.0f, 1.0f, 0.0f));
	model *= player_scale;
	model *= player_rotation;
	model = glm::translate(model, glm::vec3(player_x, 0.0f, player_z));
	player_horse_model = model;
	draw(shdr, player_horse_model);
}
auto Player::draw_torso(Shader shdr, glm::mat4 model) -> void
{
	glBindVertexArray(VAO);

	//create the horse torso.
	player_torso = model;
	player_torso = glm::scale(player_torso, glm::vec3(1.5f, 0.5f, 0.6f));
	player_torso = glm::translate(player_torso, glm::vec3(0.0f, 4.0f, -0.175f));
	player_torso *= player_torso_rotation;
	
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_torso));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
// left front legs
auto Player::draw_front_left_upper_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	player_front_left_upper_leg = player_torso;
	player_front_left_upper_leg = glm::translate(player_front_left_upper_leg, glm::vec3(-0.75f, -1.75f, 0.5f));
	player_front_left_upper_leg = glm::scale(player_front_left_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	player_front_left_upper_leg *= player_front_upper_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_front_left_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Player::draw_front_left_lower_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	player_front_left_lower_leg = player_front_left_upper_leg;
	player_front_left_lower_leg = glm::translate(player_front_left_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	player_front_left_lower_leg *= player_front_lower_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_front_left_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// right front legs
auto Player::draw_front_right_upper_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	player_front_right_upper_leg = player_torso;
	player_front_right_upper_leg = glm::translate(player_front_right_upper_leg, glm::vec3(-0.75f, -1.70f, -0.5f));
	player_front_right_upper_leg = glm::scale(player_front_right_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	player_front_right_upper_leg *= player_front_upper_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_front_right_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Player::draw_front_right_lower_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	player_front_right_lower_leg = player_front_right_upper_leg;
	player_front_right_lower_leg = glm::translate(player_front_right_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	player_front_right_lower_leg *= player_front_lower_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_front_right_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// left rear legs
auto Player::draw_hind_left_upper_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	player_hind_left_upper_leg = player_torso;
	player_hind_left_upper_leg = glm::translate(player_hind_left_upper_leg, glm::vec3(0.75f, -1.75f, 0.5f));
	player_hind_left_upper_leg = glm::scale(player_hind_left_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	player_hind_left_upper_leg *= player_hind_upper_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_hind_left_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Player::draw_hind_left_lower_leg(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse legs.
	player_hind_left_lower_leg = player_hind_left_upper_leg;
	player_hind_left_lower_leg = glm::translate(player_hind_left_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	player_hind_left_lower_leg *= player_hind_lower_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_hind_left_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// right rear legs
auto Player::draw_hind_right_upper_leg(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse legs.
	player_hind_right_upper_leg = player_torso;
	player_hind_right_upper_leg = glm::translate(player_hind_right_upper_leg, glm::vec3(0.75f, -1.75f, -0.5f));
	player_hind_right_upper_leg = glm::scale(player_hind_right_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	player_hind_right_upper_leg *= player_hind_upper_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_hind_right_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Player::draw_hind_right_lower_leg(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse legs.
	player_hind_right_lower_leg = player_hind_right_upper_leg;
	player_hind_right_lower_leg = glm::translate(player_hind_right_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	player_hind_right_lower_leg *= player_hind_lower_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_hind_right_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

auto Player::draw_neck(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse neck.
	player_neck = player_torso;
	player_neck = glm::translate(player_neck, glm::vec3(-1.2f, 0.0f, 0.0f));
	player_neck = glm::rotate(player_neck, glm::radians(45.0f), glm::vec3(.0f, 0.0f, 1.0f));
	player_neck = glm::scale(player_neck, glm::vec3(0.5f, 0.7f, 0.5f));
	player_neck *= player_neck_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_neck));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Player::draw_head(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse head.
	player_head = player_neck;
	player_head = glm::translate(player_head, glm::vec3(-0.5f, 1.6f, 0.0f));
	player_head = glm::rotate(player_head, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	player_head = glm::rotate(player_head, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	player_head = glm::scale(player_head, glm::vec3(1.5f, 0.60f, 1.0f));
	player_head *= player_head_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(player_head));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

auto Player::loadTexture(char const * path) -> GLuint
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
	else {
		std::cout << "failed to load horse texture " << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}

auto Player::player_horse_running(Shader shdr, GLfloat dTime) -> void
{
	dTime *= 5.0;
	//player_x -= dTime / 5;
	if (forward_running) {
		// front upper right leg movement
		player_front_upper_right_leg_rotation = glm::translate(player_front_upper_right_leg_rotation, player_torso_to_front_upper_leg);
		player_front_upper_right_leg_rotation = glm::rotate(player_front_upper_right_leg_rotation, dTime * glm::radians(player_run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_front_upper_right_leg_rotation = glm::translate(player_front_upper_right_leg_rotation, -player_torso_to_front_upper_leg);
		// front lower right leg movement
		player_front_lower_right_leg_rotation = glm::translate(player_front_lower_right_leg_rotation, player_front_right_knee);
		player_front_lower_right_leg_rotation = glm::rotate(player_front_lower_right_leg_rotation, dTime * glm::radians(player_run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_front_lower_right_leg_rotation = glm::translate(player_front_lower_right_leg_rotation, -player_front_right_knee);

		// front upper left leg movement
		player_front_upper_left_leg_rotation = glm::translate(player_front_upper_left_leg_rotation, player_torso_to_front_upper_left_leg);
		player_front_upper_left_leg_rotation = glm::rotate(player_front_upper_left_leg_rotation, dTime * glm::radians(player_run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_front_upper_left_leg_rotation = glm::translate(player_front_upper_left_leg_rotation, -player_torso_to_front_upper_left_leg);
		// front lower left leg movement
		player_front_lower_left_leg_rotation = glm::translate(player_front_lower_left_leg_rotation, player_front_left_knee);
		player_front_lower_left_leg_rotation = glm::rotate(player_front_lower_left_leg_rotation, dTime * glm::radians(player_run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_front_lower_left_leg_rotation = glm::translate(player_front_lower_left_leg_rotation, -player_front_left_knee);

		// hind upper right leg movement
		player_hind_upper_right_leg_rotation = glm::translate(player_hind_upper_right_leg_rotation, player_torso_to_hind_upper_right_leg);
		player_hind_upper_right_leg_rotation = glm::rotate(player_hind_upper_right_leg_rotation, dTime * glm::radians(player_run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_hind_upper_right_leg_rotation = glm::translate(player_hind_upper_right_leg_rotation, -player_torso_to_hind_upper_right_leg);
		// hind lower right leg movement
		player_hind_lower_right_leg_rotation = glm::translate(player_hind_lower_right_leg_rotation, player_hind_right_knee);
		player_hind_lower_right_leg_rotation = glm::rotate(player_hind_lower_right_leg_rotation, dTime * glm::radians(player_run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_hind_lower_right_leg_rotation = glm::translate(player_hind_lower_right_leg_rotation, -player_hind_right_knee);

		// hind upper left leg movement
		player_hind_upper_left_leg_rotation = glm::translate(player_hind_upper_left_leg_rotation, player_torso_to_hind_upper_left_leg);
		player_hind_upper_left_leg_rotation = glm::rotate(player_hind_upper_left_leg_rotation, dTime * glm::radians(player_run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_hind_upper_left_leg_rotation = glm::translate(player_hind_upper_left_leg_rotation, -player_torso_to_hind_upper_left_leg);
		// hind lower left leg movement
		player_hind_lower_left_leg_rotation = glm::translate(player_hind_lower_left_leg_rotation, player_hind_left_knee);
		player_hind_lower_left_leg_rotation = glm::rotate(player_hind_lower_left_leg_rotation, dTime * glm::radians(player_run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		player_hind_lower_left_leg_rotation = glm::translate(player_hind_lower_left_leg_rotation, -player_hind_left_knee);
		player_running_counter++;
		//std::cout << running_counter << std::endl;
		if (player_running_counter >= 200) {
			player_run_cycle = player_run_cycle * -1;
			player_running_counter = -150;
		}
	}
}

auto Player::player_random_horse_position() -> void
{
	player_x = (rand() % 100) - 50.0f;
	player_z = (rand() % 100) - 50.0f;
}

auto Player::player_hit_horse(Horse & horse) -> GLboolean
{
	bool collision_x = ((player_x + 1.5f) >= horse.x_pos) && ((horse.x_pos + 1.5f) >= player_x);
	bool collision_z = ((player_z + 1.5f) >= horse.z_pos) && ((horse.z_pos + 1.5f) >= player_z);
	
	return collision_x && collision_z;
}


