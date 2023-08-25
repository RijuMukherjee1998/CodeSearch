#pragma once

#include <iostream>
#include "RenderUI.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowColor {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float alpha = 1.0f;
};

class Application 
{
public:
	void Init(GLFWwindow* &window, int width, int height);

	void Render(GLFWwindow* &window, WindowColor &w_color, RenderUI* ui);

	void Destroy(GLFWwindow* &window);

	static void Run();
};
