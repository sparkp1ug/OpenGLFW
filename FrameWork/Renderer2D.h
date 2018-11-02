#pragma once
class Renderer2D
{
public:
	Renderer2D();
	// draw a triangle on the screen
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	// draw a point on the screen
	void drawPoint(float x1, float y1, float z1);
	void begin();
	~Renderer2D();

protected:
	unsigned int m_shader;
	

	unsigned int m_VBO, m_VAO;
	struct Vertex
	{
		float posX;
		float posY;
		float posZ;
	};
	Vertex m_vertices[1];
};

