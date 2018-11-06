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

class Renderer2D
{
public:
	Renderer2D();

	// draw a triangle on the screen
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	// draw a point on the screen
	void drawPoint(float x1, float y1, float size = 1.0f);

	// use the shader program
	void begin();

	~Renderer2D();

protected:
	enum { MAX_SPRITES = 512 };

	unsigned int m_shader;
	
	unsigned int m_VBO, m_VAO;

	struct Vertex
	{
		float pos[3];
	};

	Vertex m_vertices[1024];
};

#endif // !RENDERER2D_H_
