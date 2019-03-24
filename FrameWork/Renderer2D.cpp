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
#include <glm/ext.hpp>
#include <iostream>

Renderer2D::Renderer2D() {
	m_cameraScale = 1.0f;

	SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_currentVertex = 0;
	m_currentIndex = 0;
	/* ------------------------------------------------------------------------- */
	/* build and compile shader program */
	const char * vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 color;\n"

		"out vec4 vertexColor;\n"
		
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"

		"void main()\n"
		"{\n"
		"	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0f);\n"
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
	// reset the current vertex
	m_currentVertex = 0;
	// reset the current index
	m_currentIndex = 0;
	// set the startindex to 0
	int startIndex = m_currentVertex;

	// first point
	// pos
	m_vertices[m_currentVertex].pos[0] = x1;
	m_vertices[m_currentVertex].pos[1] = y1;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	// second point
	// pos
	m_vertices[m_currentVertex].pos[0] = x2;
	m_vertices[m_currentVertex].pos[1] = y2;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	//color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	// third point
	// pos
	m_vertices[m_currentVertex].pos[0] = x3;
	m_vertices[m_currentVertex].pos[1] = y3;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	m_indices[m_currentIndex++] = startIndex;
	m_indices[m_currentIndex++] = startIndex + 1;
	m_indices[m_currentIndex++] = startIndex + 2;


	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_currentVertex, m_vertices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * m_currentIndex, m_indices);

	glDrawElements(GL_TRIANGLES, m_currentIndex, GL_UNSIGNED_INT, 0);
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
	// reset the current index
	m_currentIndex = 0;
	// set the startindex to 0
	int startIndex = m_currentVertex;

	// pos
	m_vertices[m_currentVertex].pos[0] = x1;
	m_vertices[m_currentVertex].pos[1] = y1;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	// pos
	m_vertices[m_currentVertex].pos[0] = x2;
	m_vertices[m_currentVertex].pos[1] = y2;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	// pos
	m_vertices[m_currentVertex].pos[0] = x3;
	m_vertices[m_currentVertex].pos[1] = y3;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	// pos
	m_vertices[m_currentVertex].pos[0] = x4;
	m_vertices[m_currentVertex].pos[1] = y4;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
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

	glDrawElements(GL_TRIANGLES, m_currentIndex, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer2D::drawCircle(float x1, float y1, float radius) {
	// reset the current vertex
	m_currentVertex = 0;
	m_currentIndex = 0;
	// set the startindex to 0
	int startIndex = m_currentVertex;

	float r = radius;
	// set p to 0 and Q to radius
	float p = 0.0f;
	float q = r;
	// set the decision parameter
	float d = 3 - (2 * r);

	// plot the center point
	// pos
	m_vertices[m_currentVertex].pos[0] = x1;
	m_vertices[m_currentVertex].pos[1] = y1;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	float rotDelta = glm::pi<float>() * 2 / 32;

	for (int i = 0; i < 32; ++i) {
		// pos
		m_vertices[m_currentVertex].pos[0] = glm::sin(rotDelta * i) * radius + x1;
		m_vertices[m_currentVertex].pos[1] = glm::cos(rotDelta * i) * radius + y1;
		m_vertices[m_currentVertex].pos[2] = 0.0f;
		// color
		m_vertices[m_currentVertex].color[0] = m_r;
		m_vertices[m_currentVertex].color[1] = m_g;
		m_vertices[m_currentVertex].color[2] = m_b;
		m_vertices[m_currentVertex].color[3] = m_a;
		m_currentVertex++;

		if (i == (32 - 1)) {
			m_indices[m_currentIndex++] = startIndex;
			m_indices[m_currentIndex++] = startIndex + 1;
			m_indices[m_currentIndex++] = m_currentVertex - 1;
		}
		else {
			m_indices[m_currentIndex++] = startIndex;
			m_indices[m_currentIndex++] = m_currentVertex;
			m_indices[m_currentIndex++] = m_currentVertex - 1;
		}
	}

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_currentVertex, m_vertices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * m_currentIndex, m_indices);

	glDrawElements(GL_TRIANGLES, m_currentIndex, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer2D::drawLine(float x1, float y1, float x2, float y2, float width) {
	// reset the current vertex
	m_currentVertex = 0;
	m_currentIndex = 0;
	// set the startindex to 0
	int startIndex = m_currentVertex;
	
	// plot the points
	// pos
	m_vertices[m_currentVertex].pos[0] = x1;
	m_vertices[m_currentVertex].pos[1] = y1;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	// plot the points
	// pos
	m_vertices[m_currentVertex].pos[0] = x2;
	m_vertices[m_currentVertex].pos[1] = y2;
	m_vertices[m_currentVertex].pos[2] = 0.0f;
	// color
	m_vertices[m_currentVertex].color[0] = m_r;
	m_vertices[m_currentVertex].color[1] = m_g;
	m_vertices[m_currentVertex].color[2] = m_b;
	m_vertices[m_currentVertex].color[3] = m_a;
	m_currentVertex++;

	glLineWidth(width);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_currentVertex, m_vertices);

	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Renderer2D::SetColor(float r, float g, float b, float a) {
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void Renderer2D::begin() {
	// get the window window width and height
	int width = 0;
	int height = 0;
	GLFWwindow* window = glfwGetCurrentContext();
	glfwGetWindowSize(window, &width, &height);

	glUseProgram(m_shader);

	// initializing model identity matrix
	glm::mat4 model = glm::mat4(1.0f);
	// initializing view identity matrix
	glm::mat4 view = glm::mat4(1.0f);
	// initializing projection identity matrix
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
	projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 1.0f, -101.0f);

	// pass the matrices into shader
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Renderer2D::end() {
	glDeleteProgram(m_shader);
}

Renderer2D::~Renderer2D() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}
