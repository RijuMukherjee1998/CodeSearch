#pragma once

#include "Components.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class RenderUI {
public:
	void Setup(GLFWwindow* &window);
	
	void UIFrameUpdate();
	
	void DisplayUI(int cww, int cwh);
	
	void UIRender();

	void DestroyimGUI();

};