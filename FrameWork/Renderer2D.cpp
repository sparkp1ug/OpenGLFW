#include "Renderer2D.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

Renderer2D::Renderer2D()
{
	m_VAO = -1;
	m_VBO = -1;
	/* ---------------------------------------------------------------------------------------------- */
	const char * vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"}\0";
	const char * fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";

	/* build and compile shader program */
	/* -------------------------------- */
	/* VERTEX SHADER */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/* check for vertex shader compile errors */
	int success = GL_FALSE;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/* FRAGMENT SHADER */
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	/* check for fragment shader compile errors */
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/* link shaders */
	m_shader = glCreateProgram();
	glAttachShader(m_shader, vertexShader);
	glAttachShader(m_shader, fragmentShader);
	glLinkProgram(m_shader);
	/* check for shader linking errors */
	glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	/* ---------------------------------------------------------------------------------------------- */

	//m_vertices[1] = { 0.2f, 0.2f, 0.0f };
	//glGenBuffers(1, &m_VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
	////glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	//glDisableVertexAttribArray(0);
}

void Renderer2D::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
}

void Renderer2D::drawPoint(float x1, float y1, float z1)
{
	//m_vertices[1].posX = x1;
	//m_vertices[1].posY = y1;
	//m_vertices[1].posZ = z1;
	//glGenBuffers(1, &m_VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, 1);

	//glDisableVertexAttribArray(0);
}

void Renderer2D::begin()
{
	glUseProgram(m_shader);
}


Renderer2D::~Renderer2D()
{
	glDeleteBuffers(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shader);
}
