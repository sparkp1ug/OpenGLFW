/**
*************************************************************************************************
* OpenGL-Framework
* Copyright (c) 2018 Ramkumar Thiyagarajan
*************************************************************************************************
* File: Renderer2D.h
*
* Description:	Drawing primitive shapes, and renders the sprites.	
*				Vertex Shader and Fragment Shader is implemented	
*
* Author: Ramkumar Thiyagarajan
*
* Date: 6/11/2018
*************************************************************************************************
*/

#ifndef RENDERER2D_H_
#define RENDERER2D_H_

class Renderer2D {
public:
	Renderer2D();

	// draw a triangle on the screen
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	// draw a point on the screen
	void drawPoint(float x1, float y1, float size = 1.0f);

	void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	// change the color of the render screen
	void SetColor(float r, float g, float b, float a);

	// use the shader program
	void begin();

	~Renderer2D();

protected:
	enum { MAX_SPRITES = 512 };

	unsigned int m_shader;

	unsigned int m_VBO, m_VAO, m_EBO;

	struct Vertex {
		float pos[3];
		float color[4];
	};

	Vertex m_vertices[MAX_SPRITES * 4];

	unsigned int m_indices[MAX_SPRITES * 6];

	float m_r, m_g, m_b, m_a;
};

#endif // !RENDERER2D_H_
