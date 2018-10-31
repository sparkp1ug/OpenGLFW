#include "Application2D.h"
#include <GLFW/glfw3.h>


Application2D::Application2D()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


bool Application2D::createWindow(int width, int height, const char * title, bool fullscreen)
{
	
	GLFWwindow* window = glfwCreateWindow(width, height, title, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {glViewport(0, 0, w, h); });
	glfwMakeContextCurrent(window);
	return true;
}



Application2D::~Application2D()
{
}

