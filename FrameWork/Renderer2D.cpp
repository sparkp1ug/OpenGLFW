/**
*************************************************************************************************
* OpenGL-Framework
* Copyright (c) 2018 Ramkumar Thiyagarajan
*************************************************************************************************
* File: Renderer2D.cpp
*
* Description:	Drawing primitive shapes, and renders the sprites.
*				Vertex Shader and Fragment Shader is implemented
*
* Author: Ramkumar Thiyagarajan
*
* Date: 6/11/2018
*************************************************************************************************
*/

#include "Renderer2D.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <iostream>

Renderer2D::Renderer2D() {
	SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_currentVertex = 0;
	m_currentIndex = 0;
	/* ------------------------------------------------------------------------- */
	/* build and compile shader program */
	const char * vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 color;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
		"	vertexColor = color;\n"
		"}\0";
	const char * fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"in vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vertexColor;\n"
		"}\0";
	/* VERTEX SHADER */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for vertex shader compile errors
	int success = GL_FALSE;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	/* FRAGMENT SHADER */
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for fragment shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders 
	m_shader = glCreateProgram();
	glAttachShader(m_shader, vertexShader);
	glAttachShader(m_shader, fragmentShader);
	glLinkProgram(m_shader);

	// check for shader linking errors 
	glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	/* ------------------------------------------------------------------------- */

	// use of vertex array object
	m_VAO = -1;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Create a Vertex Buffer Object that will store the vertices on video memory */
	m_VBO = -1;
	glGenBuffers(1, &m_VBO);
	m_EBO = -1;
	glGenBuffers(1, &m_EBO);

	// Allocate space and upload data from CPU to GPU 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * (MAX_SPRITES * 4), m_vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

	// position attribute - Specify how the data for position can be accessed 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0);
	// enable the position attribute
	glEnableVertexAttribArray(0);
	// color attribute - Specify how the data for position can be accessed 
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)12);
	// enable the color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Renderer2D::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	m_vertices[0].pos[0] = x1;
	m_vertices[0].pos[1] = y1;
	m_vertices[0].pos[2] = 0.0f;

	m_vertices[1].pos[0] = x2;
	m_vertices[1].pos[1] = y2;
	m_vertices[1].pos[2] = 0.0f;

	m_vertices[2].pos[0] = x3;
	m_vertices[2].pos[1] = y3;
	m_vertices[2].pos[2] = 0.0f;

	// color
	m_vertices[0].color[0] = m_r;
	m_vertices[0].color[1] = m_g;
	m_vertices[0].color[2] = m_b;
	m_vertices[0].color[3] = m_a;

	m_vertices[1].color[0] = m_r;
	m_vertices[1].color[1] = m_g;
	m_vertices[1].color[2] = m_b;
	m_vertices[1].color[3] = m_a;

	m_vertices[2].color[0] = m_r;
	m_vertices[2].color[1] = m_g;
	m_vertices[2].color[2] = m_b;
	m_vertices[2].color[3] = m_a;

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;


	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 3, m_vertices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * 3, m_indices);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer2D::drawPoint(float x1, float y1, float size) {
	m_vertices[0].pos[0] = x1;
	m_vertices[0].pos[1] = y1;
	m_vertices[0].pos[2] = 0.0f;

	m_vertices[0].color[0] = m_r;
	m_vertices[0].color[1] = m_g;
	m_vertices[0].color[2] = m_b;
	m_vertices[0].color[3] = m_a;

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex), m_vertices);

	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(size);
	glBindVertexArray(0);
}

void Renderer2D::drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	// reset the current vertex
	m_currentVertex = 0;
	m_currentIndex = 0;
	// set the startindex to 0
	int startIndex = m_currentVertex;

	// pos
	m_vertices[0].pos[0] = x1;
	m_vertices[0].pos[1] = y1;
	m_vertices[0].pos[2] = 0.0f;
	// color
	m_vertices[0].color[0] = m_r;
	m_vertices[0].color[1] = m_g;
	m_vertices[0].color[2] = m_b;
	m_vertices[0].color[3] = m_a;
	m_currentVertex++;

	// pos
	m_vertices[1].pos[0] = x2;
	m_vertices[1].pos[1] = y2;
	m_vertices[1].pos[2] = 0.0f;
	// color
	m_vertices[1].color[0] = m_r;
	m_vertices[1].color[1] = m_g;
	m_vertices[1].color[2] = m_b;
	m_vertices[1].color[3] = m_a;
	m_currentVertex++;

	// pos
	m_vertices[2].pos[0] = x3;
	m_vertices[2].pos[1] = y3;
	m_vertices[2].pos[2] = 0.0f;
	// color
	m_vertices[2].color[0] = m_r;
	m_vertices[2].color[1] = m_g;
	m_vertices[2].color[2] = m_b;
	m_vertices[2].color[3] = m_a;
	m_currentVertex++;

	// pos
	m_vertices[3].pos[0] = x4;
	m_vertices[3].pos[1] = y4;
	m_vertices[3].pos[2] = 0.0f;
	// color
	m_vertices[3].color[0] = m_r;
	m_vertices[3].color[1] = m_g;
	m_vertices[3].color[2] = m_b;
	m_vertices[3].color[3] = m_a;
	m_currentVertex++;

	m_indices[m_currentIndex++] = startIndex + 0;
	m_indices[m_currentIndex++] = startIndex + 1;
	m_indices[m_currentIndex++] = startIndex + 2;

	m_indices[m_currentIndex++] = startIndex + 0;
	m_indices[m_currentIndex++] = startIndex + 2;
	m_indices[m_currentIndex++] = startIndex + 3;

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_currentVertex, m_vertices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * m_currentIndex, m_indices);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer2D::drawCircle(float x1, float y1, float radius) {
}

void Renderer2D::SetColor(float r, float g, float b, float a) {
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void Renderer2D::begin() {
	glUseProgram(m_shader);
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

Renderer2D::~Renderer2D() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteProgram(m_shader);
}
