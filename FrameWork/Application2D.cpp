#include "Application2D.h"
#include <GLFW/glfw3.h>


Application2D::Application2D() : m_gameOver(false), m_window(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


bool Application2D::createWindow(int width, int height, const char * title, bool fullscreen)
{
	m_window = glfwCreateWindow(width, height, title, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, int w, int h) {glViewport(0, 0, w, h); });
	glfwMakeContextCurrent(m_window);
	return true;
}

void Application2D::quit(GLFWwindow * window)
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_gameOver = true;
		glfwSetWindowShouldClose(window, true);
	}
}



void Application2D::runApp(const char * title, int width, int height, bool fullscreen)
{
	if (createWindow(width, height, title, fullscreen))
	{
		while (!m_gameOver)
		{
			quit(m_window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

Application2D::~Application2D()
{
}

