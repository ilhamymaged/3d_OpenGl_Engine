#include <shader.h>
#include <stdlib.h>
#include <stdio.h>
#include <utility.h>

void set_mat4(shader* shader, const char* name, mat4 value) {
    int loc = glGetUniformLocation(shader->id, name);
    if(loc == -1) printf("couldn't find: %s\n", name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

shader* create_shader(char* vertex_shader_path, char* fragment_shader_path)
{
    shader* m_shader = malloc(sizeof(shader));
    if(!m_shader) return NULL;

	char* vertexShaderSource = read_file(vertex_shader_path);
	char* fragmentShaderSource = read_file(fragment_shader_path);

    if (!vertexShaderSource || !fragmentShaderSource) {
        printf("ERROR::SHADER::FAILED_TO_READ_FILES\n");
        free(vertexShaderSource);
        free(fragmentShaderSource);
        free(m_shader);
        return NULL;
    }

    const char* vsrc = vertexShaderSource;
    const char* fsrc = fragmentShaderSource;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsrc, NULL);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED::%s::%s", vertex_shader_path, infoLog); 
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED::%s::%s", fragment_shader_path, infoLog); 
	}

	m_shader->id = glCreateProgram();
	glAttachShader(m_shader->id, vertexShader);
	glAttachShader(m_shader->id, fragmentShader);
	glLinkProgram(m_shader->id);

	glGetProgramiv(m_shader->id, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(m_shader->id, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED::%s",infoLog); 
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    free(vertexShaderSource);
    free(fragmentShaderSource);

    return m_shader;
}

void set_vec3(shader* shader, const char* name, vec3 value) {
	int loc = glGetUniformLocation(shader->id, name);
    if(loc == -1) printf("couldn't find: %s\n", name);
	glUniform3fv(loc, 1, value);
}

void set_int(shader* shader, const char* name, int value) {
	int loc = glGetUniformLocation(shader->id, name);
    if(loc == -1) printf("couldn't find: %s\n", name);
	glUniform1i(loc, value);
}



void destroy_shader(shader* shader) {
    glDeleteProgram(shader->id);
	free(shader);
}

void use_shader(shader* shader) {
    glUseProgram(shader->id);
}
