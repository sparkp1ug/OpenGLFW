#pragma once
struct GLFWwindow;
class Application2D
{
public:
	/* GLFW - Initialize and Configure */
	Application2D();

	/* GLFW - window creation */
	bool createWindow(int width, int height, const char* title, bool fullscreen = false);

	~Application2D();

protected:
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window;
};

