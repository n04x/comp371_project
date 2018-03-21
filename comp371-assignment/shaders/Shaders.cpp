#include "Shaders.h"

Shader::Shader(std::string vs_path, std::string fs_path)
{
	// creating the shaders.
	GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the vertex shader code from the file.
	std::string vs_code;
	std::ifstream vs_stream(vs_path, std::ios::in);
	if (vs_stream.is_open()) {
		std::string Line = "";
		while (getline(vs_stream, Line)) {
			vs_code += "\n" + Line;
		}
		vs_stream.close();
	}
	else {
		printf("can't open %s. Check your file path...\n", vs_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the fragment shader code from the file.
	std::string fs_code;
	std::ifstream fs_stream(fs_path, std::ios::in);
	if (fs_stream.is_open()) {
		std::string Line = "";
		while (getline(fs_stream, Line))
			fs_code += "\n" + Line;
		fs_stream.close();
	}
	else {
		printf("can't open %s. Check your file path...\n", fs_path.c_str());
		getchar();
		exit(-1);
	}
	GLint result = GL_FALSE;
	int infoLog;

	// Compile the vertex shader.
	printf("compiling shader: %s...\n", vs_path.c_str());
	char const * vs_ptr = vs_code.c_str();
	glShaderSource(vs_id, 1, &vs_ptr, nullptr);
	glCompileShader(vs_id);

	// check vertex shader.
	glGetShaderiv(vs_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vs_id, GL_INFO_LOG_LENGTH, &infoLog);
	if (infoLog > 0) {
		std::vector<char> vs_error(infoLog + 1);
		glGetShaderInfoLog(vs_id, infoLog, nullptr, &vs_error[0]);
		printf("%s\n", &vs_error[0]);
	}

	// compile the fragment shader.
	printf("compiling shader: %s...\n", fs_path.c_str());
	char const * fs_ptr = fs_code.c_str();
	glShaderSource(fs_id, 1, &fs_ptr, nullptr);
	glCompileShader(fs_id);

	// check fragment shader.
	glGetShaderiv(fs_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fs_id, GL_INFO_LOG_LENGTH, &infoLog);
	if (infoLog > 0) {
		std::vector<char> fs_error(infoLog + 1);
		glGetShaderInfoLog(fs_id, infoLog, nullptr, &fs_error[0]);
		printf("%s\n", &fs_error[0]);
	}

	// linking the program.
	printf("linking both shader into program...\n");
	ID = glCreateProgram();
	glAttachShader(ID, vs_id);
	glAttachShader(ID, fs_id);
	glBindAttribLocation(ID, 0, "in_Position");
	glLinkProgram(ID);

	// check the program.
	glGetProgramiv(ID, GL_LINK_STATUS, &result);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &result);
	if (infoLog > 0) {
		std::vector<char> p_error(infoLog + 1);
		glGetProgramInfoLog(ID, infoLog, nullptr, &p_error[0]);
		printf("%s\n", &p_error[0]);
	}

	// free up the memory.
	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
}
// activation of the shader.
auto Shader::useID() -> const void
{
	glUseProgram(ID);
}
auto Shader::programID() -> GLuint {
	return ID;
}