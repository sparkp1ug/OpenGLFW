#pragma once
class Renderer2D
{
public:
	Renderer2D();
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	~Renderer2D();

protected:
	unsigned int m_shader;
	

	unsigned int m_VBO;
	struct Vertex
	{
		float pos[3];
	};
	Vertex m_vertices[3];
};

