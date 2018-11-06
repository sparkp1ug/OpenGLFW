/**
*************************************************************************************************
* OpenGL-Framework
* Copyright (c) 2018 Ramkumar Thiyagarajan
*************************************************************************************************
* File: Application2D.h
*
* Description:	Create an OpenGL window and render the sprites drawn on the screen.
*				The scripts for the game should be added in this class.
*
* Author: Ramkumar Thiyagarajan
*
* Date: 6/11/2018
*************************************************************************************************
*/

#ifndef APPLICATION2D_H_
#define APPLICATION2D_H_

#include "Renderer2D.h"

struct GLFWwindow;
class Application2D
{
public:
	/* GLFW - Initialize and Configure */
	Application2D();

	/* GLFW - render loop */
	void runApp(const char* title, int width, int height, bool fullscreen = false);

	void start();

	void draw();

	/* refreshes the screen */
	void clearScreen();

	~Application2D();

protected:
	/* GLFW - window creation */
	bool createWindow(int width, int height, const char* title, bool fullscreen = false);

	/* quit GLFW window upon escape key press */
	void quit(GLFWwindow* window);

	GLFWwindow* m_window;

	bool m_gameOver;

	/* Application stuff */
	Renderer2D* renderer2D;
};

#endif
