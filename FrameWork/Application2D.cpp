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
	}
	// set it true if the escape key or close button is pressed
	m_gameOver = m_gameOver || glfwWindowShouldClose(window) == true;
}



void Application2D::runApp(const char * title, int width, int height, bool fullscreen)
{
	// check if the window has been successfully created
	if (createWindow(width, height, title, fullscreen))
	{
		// render loop
		while (!m_gameOver)
		{
			// input from the user to close the window
			quit(m_window);

			// render the window with the following color
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// swap the buffers 
			glfwSwapBuffers(m_window);
			// check for any keys or mouse movements
			glfwPollEvents();
		}
	}
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

Application2D::~Application2D()
{
}

