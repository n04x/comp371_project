#ifndef HORSE_H
#define HORSE_H
#include "..\stdinclude.h"
#include "..\shaders\Shaders.h"
#include "..\stb_image.h"
#include "BoundingBox.h"

enum modes { POINTS, LINES, FILL };

// joints
auto const head_to_neck = glm::vec3(1.2f, 0.0f, 0.0f);					// 1. key binding: 1.
auto const neck_to_torso = glm::vec3(0.5f, 0.0f, 0.0f);					// 2. key binding: 2.
auto const torso_to_front_upper_leg = glm::vec3(0.0f, 1.0f, 0.0f);		// 3. Key binding: 3.
auto const front_right_knee = glm::vec3(0.0f, 1.0f, 0.0f);				// 4. key binding: 4.
auto const torso_to_hind_upper_right_leg = glm::vec3(0.0f, 1.5f, 0.0f); // 5. key binding: 5.
auto const hind_right_knee = glm::vec3(0.0f, 1.0f, 0.0f);				// 6. key binding: 6.
auto const torso_to_front_upper_left_leg = glm::vec3(0.0f, 1.5f, 0.0f); // 7. key binding: 7.
auto const front_left_knee = glm::vec3(0.0f, 1.0f, 0.0f);				// 8. key binding: 8.
auto const torso_to_hind_upper_left_leg = glm::vec3(0.0f, 1.5f, 0.0f);	// 9. key binding: 9.
auto const hind_left_knee = glm::vec3(0.0f, 1.0f, 0.0f);				// 0. key binding: 0.


class Horse
{
public:
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normal;
	std::vector<GLuint> indices;
	std::vector<glm::vec2> texture_coordinates;
	auto horse_callback_input(GLFWwindow* window) -> void;
	// bounding boxes
	auto setBBWorld(BoudingBox bb) -> void;
	// horse transformation
	glm::mat4 horse_rotation = glm::mat4(1.0f);
	glm::mat4 horse_scale = glm::mat4(1.0f);
	glm::mat4 torso_rotation = glm::mat4(1.0f);
	glm::mat4 head_rotation = glm::mat4(1.0f);
	glm::mat4 neck_rotation = glm::mat4(1.0f);
	glm::mat4 front_upper_right_leg_rotation = glm::mat4(1.0f);
	glm::mat4 front_lower_right_leg_rotation = glm::mat4(1.0f);
	glm::mat4 hind_upper_right_leg_rotation = glm::mat4(1.0f);
	glm::mat4 hind_lower_right_leg_rotation = glm::mat4(1.0f);
	glm::mat4 front_upper_left_leg_rotation = glm::mat4(1.0f);
	glm::mat4 front_lower_left_leg_rotation = glm::mat4(1.0f);
	glm::mat4 hind_upper_left_leg_rotation = glm::mat4(1.0f);
	glm::mat4 hind_lower_left_leg_rotation = glm::mat4(1.0f);
	

	modes choice = FILL;
	GLfloat x_pos = 0.0f, z_pos = 0.0f;

	Horse();
	// functions to draw the horse.
	auto draw(Shader shdr, glm::mat4 model) -> void;
	auto setSwap(bool texture_enable) -> void;
	// functions to draw the body parts.
	auto draw_horse(Shader shdr, modes choice) -> void;
	auto draw_torso(Shader shdr, glm::mat4 model) -> void;
	// Create the legs
	auto draw_front_left_upper_leg(Shader shdr) -> void;
	auto draw_front_left_lower_leg(Shader shdr) -> void;
	auto draw_front_right_upper_leg(Shader shdr) -> void;
	auto draw_front_right_lower_leg(Shader shdr) -> void;
	auto draw_hind_left_upper_leg(Shader shdr) -> void;
	auto draw_hind_left_lower_leg(Shader shdr) -> void;
	auto draw_hind_right_upper_leg(Shader shdr) -> void;
	auto draw_hind_right_lower_leg(Shader shdr) -> void;
	auto draw_neck(Shader shdr) -> void;
	auto draw_head(Shader shdr) -> void;
	auto loadTexture(char const *path)->GLuint;

	// the automatization of horse movement for the troop.
	auto horse_running(GLfloat dTime) -> void;
	auto horse_eating_grass(GLfloat dTime) -> void;
	auto horse_movement(GLfloat dTime, int horseNumber) -> void;
	auto random_horse_position() -> void;

	// the horse texture
	GLuint horse_texture;

protected:
	GLuint VAO;
	GLuint VBO, VBOtx, VBOnorm;
	GLuint EBO;
	BoudingBox horse_bounding_box;
	bool swap = true;
	
	// list of body part model for the horse.
	glm::mat4 horse_model = glm::mat4(1.0f);
	glm::mat4 head = glm::mat4(1.0f);
	glm::mat4 neck = glm::mat4(1.0f);
	glm::mat4 torso = glm::mat4(1.0f);
	glm::mat4 front_left_upper_leg = glm::mat4(1.0f);
	glm::mat4 front_left_lower_leg = glm::mat4(1.0f);
	glm::mat4 front_right_upper_leg = glm::mat4(1.0f);
	glm::mat4 front_right_lower_leg = glm::mat4(1.0f);
	glm::mat4 hind_left_upper_leg = glm::mat4(1.0f);
	glm::mat4 hind_left_lower_leg = glm::mat4(1.0f);
	glm::mat4 hind_right_upper_leg = glm::mat4(1.0f);
	glm::mat4 hind_right_lower_leg = glm::mat4(1.0f);
	
	// path for the horse texture
	const char * texPath = "..\\comp371-assignment\\textures\\horse.jpg";

};
#endif // !HORSE_H
