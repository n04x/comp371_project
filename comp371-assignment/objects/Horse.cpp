#include "Horse.h"

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
static std::vector<float> horse_xpos = { 0.0f };
static std::vector<float> horse_zpos = { 0.0f };

// horse movement related stuff
static bool forward_running = true;
int running_counter = 0;
int eating_counter = 0;
int eating_cycle = 1;
int run_cycle = 1;
int rotate_tick = 0;
bool run = true;

auto Horse::setBBWorld(BoudingBox bb) -> void
{
	horse_bounding_box = bb;
}

Horse::Horse()
{
	vertices = {
		// Square #1
		glm::vec3(-1.0f, -1.0f, -1.0f),			
		glm::vec3( 1.0f, -1.0f, -1.0f),			
		glm::vec3( 1.0f,  1.0f, -1.0f),			
		glm::vec3( 1.0f,  1.0f, -1.0f),			
		glm::vec3(-1.0f,  1.0f, -1.0f),			
		glm::vec3(-1.0f, -1.0f, -1.0f),			
		// Square #2
		glm::vec3(-1.0f, -1.0f,  1.0f),			
		glm::vec3( 1.0f, -1.0f,  1.0f),			
		glm::vec3( 1.0f,  1.0f,  1.0f),			
		glm::vec3( 1.0f,  1.0f,  1.0f),			
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
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		// Square #5
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		// Square #6
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f)
	};
	
	normal = {
		// Square #1
		glm::vec3( 0.0f, 0.0f,-1.0f),
		glm::vec3( 0.0f, 0.0f,-1.0f),
		glm::vec3( 0.0f, 0.0f,-1.0f),
		glm::vec3( 0.0f, 0.0f,-1.0f),
		glm::vec3( 0.0f, 0.0f,-1.0f),
		glm::vec3( 0.0f, 0.0f,-1.0f),
		// Square #2
		glm::vec3( 0.0f, 0.0f, 1.0f),
		glm::vec3( 0.0f, 0.0f, 1.0f),
		glm::vec3( 0.0f, 0.0f, 1.0f),
		glm::vec3( 0.0f, 0.0f, 1.0f),
		glm::vec3( 0.0f, 0.0f, 1.0f),
		glm::vec3( 0.0f, 0.0f, 1.0f),
		// Square #3
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		// Square #4
		glm::vec3( 1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, 0.0f, 0.0f),
		// Square #5
		glm::vec3( 0.0f,-1.0f, 0.0f),
		glm::vec3( 0.0f,-1.0f, 0.0f),
		glm::vec3( 0.0f,-1.0f, 0.0f),
		glm::vec3( 0.0f,-1.0f, 0.0f),
		glm::vec3( 0.0f,-1.0f, 0.0f),
		glm::vec3( 0.0f,-1.0f, 0.0f),
		// Square #6
		glm::vec3( 0.0f, 1.0f, 0.0f),
		glm::vec3( 0.0f, 1.0f, 0.0f),
		glm::vec3( 0.0f, 1.0f, 0.0f),
		glm::vec3( 0.0f, 1.0f, 0.0f),
		glm::vec3( 0.0f, 1.0f, 0.0f),
		glm::vec3( 0.0f, 1.0f, 0.0f)
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
	
	horse_texture = loadTexture(texPath);
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
auto Horse::draw(Shader shdr, glm::mat4 model) -> void
{
	glBindVertexArray(VAO);

	if (swap) {
		glEnableVertexAttribArray(1);
	}
	else {
		glDisableVertexAttribArray(1);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, horse_texture);
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

auto Horse::setSwap(bool texture_enable) -> void
{
	this->swap = texture_enable;
}

// functions to draw the horse.
auto Horse::draw_horse(Shader shdr, modes choice) -> void
{
	if (choice == LINES) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (choice == POINTS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (choice == FILL)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glm::mat4 model = glm::mat4(1.0f);
	model *= horse_scale;
	model *= horse_rotation;
	model = glm::translate(model, glm::vec3(x_pos, 0.0f, z_pos));
	horse_model = model;
	draw(shdr, horse_model);
}
auto Horse::draw_torso(Shader shdr, glm::mat4 model) -> void
{
	glBindVertexArray(VAO);

	//create the horse torso.
	torso = model;
	torso = glm::scale(torso, glm::vec3(1.5f, 0.5f, 0.6f));
	torso = glm::translate(torso, glm::vec3(0.0f, 4.0f, -0.175f));
	torso *= torso_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(torso));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
// left front legs
auto Horse::draw_front_left_upper_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	front_left_upper_leg = torso;
	front_left_upper_leg = glm::translate(front_left_upper_leg, glm::vec3(-0.75f, -1.75f, 0.5f));
	front_left_upper_leg = glm::scale(front_left_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	front_left_upper_leg *= front_upper_left_leg_rotation;

	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(front_left_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Horse::draw_front_left_lower_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	front_left_lower_leg = front_left_upper_leg;
	front_left_lower_leg = glm::translate(front_left_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	front_left_lower_leg *= front_lower_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(front_left_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// right front legs
auto Horse::draw_front_right_upper_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	front_right_upper_leg = torso;
	front_right_upper_leg = glm::translate(front_right_upper_leg, glm::vec3(-0.75f, -1.70f, -0.5f));
	front_right_upper_leg = glm::scale(front_right_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	front_right_upper_leg *= front_upper_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(front_right_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Horse::draw_front_right_lower_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	front_right_lower_leg = front_right_upper_leg;
	front_right_lower_leg = glm::translate(front_right_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	front_right_lower_leg *= front_lower_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(front_right_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// left rear legs
auto Horse::draw_hind_left_upper_leg(Shader shdr) -> void {
	glBindVertexArray(VAO);

	// create the horse legs.
	hind_left_upper_leg = torso;
	hind_left_upper_leg = glm::translate(hind_left_upper_leg, glm::vec3(0.75f, -1.75f, 0.5f));
	hind_left_upper_leg = glm::scale(hind_left_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	hind_left_upper_leg *= hind_upper_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(hind_left_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Horse::draw_hind_left_lower_leg(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse legs.
	hind_left_lower_leg = hind_left_upper_leg;
	hind_left_lower_leg = glm::translate(hind_left_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	hind_left_lower_leg *= hind_lower_left_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(hind_left_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

// right rear legs
auto Horse::draw_hind_right_upper_leg(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse legs.
	hind_right_upper_leg = torso;
	hind_right_upper_leg = glm::translate(hind_right_upper_leg, glm::vec3(0.75f, -1.75f, -0.5f));
	hind_right_upper_leg = glm::scale(hind_right_upper_leg, glm::vec3(0.20f, 0.75f, 0.40f));
	hind_right_upper_leg *= hind_upper_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(hind_right_upper_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Horse::draw_hind_right_lower_leg(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse legs.
	hind_right_lower_leg = hind_right_upper_leg;
	hind_right_lower_leg = glm::translate(hind_right_lower_leg, glm::vec3(0.0f, -2.0f, 0.0f));
	hind_right_lower_leg *= hind_lower_right_leg_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(hind_right_lower_leg));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

auto Horse::draw_neck(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse neck.
	neck = torso;
	neck = glm::translate(neck, glm::vec3(-1.2f, 0.0f, 0.0f));
	neck = glm::rotate(neck, glm::radians(45.0f), glm::vec3(.0f, 0.0f, 1.0f));
	neck = glm::scale(neck, glm::vec3(0.5f, 0.7f, 0.5f));
	neck *= neck_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(neck));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
auto Horse::draw_head(Shader shdr) -> void
{
	glBindVertexArray(VAO);

	// create the horse head.
	head = neck;
	head = glm::translate(head, glm::vec3(-0.5f, 1.6f, 0.0f));
	head = glm::rotate(head, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	head = glm::rotate(head, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	head = glm::scale(head, glm::vec3(1.5f, 0.60f, 1.0f));
	head *= head_rotation;
	glUniformMatrix4fv(glGetUniformLocation(shdr.ID, "m_m"), 1, GL_FALSE, glm::value_ptr(head));
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

auto Horse::loadTexture(char const * path) -> GLuint
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

auto Horse::horse_running(GLfloat dTime, bool collide) -> void
{
	dTime *= 30.0;
	// Check if it reaches border
	if (x_pos <= horse_bounding_box.far && x_pos >= horse_bounding_box.near && x_pos >= horse_bounding_box.left && x_pos <= horse_bounding_box.right)
		run = false;
	else
		run = true;

	if (!run) {
		if (!collide) {
			x_pos -= dTime / 5;
			// front upper right leg movement
			front_upper_right_leg_rotation = glm::translate(front_upper_right_leg_rotation, torso_to_front_upper_leg);
			front_upper_right_leg_rotation = glm::rotate(front_upper_right_leg_rotation, dTime * glm::radians(run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			front_upper_right_leg_rotation = glm::translate(front_upper_right_leg_rotation, -torso_to_front_upper_leg);
			// front lower right leg movement
			front_lower_right_leg_rotation = glm::translate(front_lower_right_leg_rotation, front_right_knee);
			front_lower_right_leg_rotation = glm::rotate(front_lower_right_leg_rotation, dTime * glm::radians(run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			front_lower_right_leg_rotation = glm::translate(front_lower_right_leg_rotation, -front_right_knee);

			// front upper left leg movement
			front_upper_left_leg_rotation = glm::translate(front_upper_left_leg_rotation, torso_to_front_upper_left_leg);
			front_upper_left_leg_rotation = glm::rotate(front_upper_left_leg_rotation, dTime * glm::radians(run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			front_upper_left_leg_rotation = glm::translate(front_upper_left_leg_rotation, -torso_to_front_upper_left_leg);
			// front lower left leg movement
			front_lower_left_leg_rotation = glm::translate(front_lower_left_leg_rotation, front_left_knee);
			front_lower_left_leg_rotation = glm::rotate(front_lower_left_leg_rotation, dTime * glm::radians(run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			front_lower_left_leg_rotation = glm::translate(front_lower_left_leg_rotation, -front_left_knee);

			// hind upper right leg movement
			hind_upper_right_leg_rotation = glm::translate(hind_upper_right_leg_rotation, torso_to_hind_upper_right_leg);
			hind_upper_right_leg_rotation = glm::rotate(hind_upper_right_leg_rotation, dTime * glm::radians(run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			hind_upper_right_leg_rotation = glm::translate(hind_upper_right_leg_rotation, -torso_to_hind_upper_right_leg);
			// hind lower right leg movement
			hind_lower_right_leg_rotation = glm::translate(hind_lower_right_leg_rotation, hind_right_knee);
			hind_lower_right_leg_rotation = glm::rotate(hind_lower_right_leg_rotation, dTime * glm::radians(run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			hind_lower_right_leg_rotation = glm::translate(hind_lower_right_leg_rotation, -hind_right_knee);

			// hind upper left leg movement
			hind_upper_left_leg_rotation = glm::translate(hind_upper_left_leg_rotation, torso_to_hind_upper_left_leg);
			hind_upper_left_leg_rotation = glm::rotate(hind_upper_left_leg_rotation, dTime * glm::radians(run_cycle * -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			hind_upper_left_leg_rotation = glm::translate(hind_upper_left_leg_rotation, -torso_to_hind_upper_left_leg);
			// hind lower left leg movement
			hind_lower_left_leg_rotation = glm::translate(hind_lower_left_leg_rotation, hind_left_knee);
			hind_lower_left_leg_rotation = glm::rotate(hind_lower_left_leg_rotation, dTime * glm::radians(run_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			hind_lower_left_leg_rotation = glm::translate(hind_lower_left_leg_rotation, -hind_left_knee);
			running_counter++;
			if (running_counter >= 150) {
				run_cycle = run_cycle * -1;
				running_counter = -150;
			}
		}
	}
	/*else if (run) {
		if (rotate_tick < 50) {
			horse_rotation = glm::translate(horse_rotation, glm::vec3(x_pos, 0.0f, z_pos));
			horse_rotation = glm::rotate(horse_rotation, glm::radians(-5.0f), glm::vec3(0, 1, 0));
			horse_rotation = glm::translate(horse_rotation, -glm::vec3(x_pos, 0.0f, z_pos));
			rotate_tick++;
		}
		else {
			x_pos -= dTime / 5;
			run = false;
			running_counter = 0;
			rotate_tick = 0;
		}
	}*/
	
}

auto Horse::horse_eating_grass(GLfloat dTime) -> void
{
	dTime *= 30.0f;
	bool sleep = true;
	neck_rotation = glm::translate(neck_rotation, neck_to_torso);
	neck_rotation = glm::rotate(neck_rotation, dTime * glm::radians( eating_cycle * 5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	neck_rotation = glm::translate(neck_rotation, -neck_to_torso);
	eating_counter++;
	std::cout << "counter: "<< eating_counter << std::endl;
	if (eating_counter >= 250) {
		eating_cycle = eating_cycle * -1;
		eating_counter = 0;
	}
}

auto Horse::random_horse_position() -> void
{
	bool overlap;
	do {
		x_pos = (rand() % 50) - 25.0f;
		z_pos = (rand() % 50) - 25.0f;
		overlap = false;
		if (x_pos == 0.0f && z_pos == 0.0f)
			overlap = true;
		else {
			for (int i = 0; i < horse_xpos.size(); i++) {
				if (x_pos == horse_xpos.at(i))
					for (int j = 0; j < horse_zpos.size(); j++)
						if (z_pos == horse_zpos.at(j))
							overlap = true;
			}
		}
	} while (overlap);
	horse_xpos.push_back(x_pos);
	horse_zpos.push_back(z_pos);
	GLfloat temp_radiant = (rand() % 360) - 180.0f;
	horse_rotation = glm::translate(horse_rotation, glm::vec3(x_pos, 0.0f, z_pos));
	horse_rotation = glm::rotate(horse_rotation, glm::radians(temp_radiant), glm::vec3(0, 1, 0));
	horse_rotation = glm::translate(horse_rotation, -glm::vec3(x_pos, 0.0f, z_pos));
}

auto Horse::check_collision(Horse &otherHorse)->GLboolean {
	bool collision_x = ((x_pos + 0.5f) >= otherHorse.x_pos) && ((x_pos + 0.5f) >= otherHorse.x_pos);
	bool collision_z = ((x_pos + 0.5f) >= otherHorse.z_pos) && ((z_pos + 0.5f) >= otherHorse.z_pos);

	return collision_x && collision_z;
};

