#include "Application.h"
#include "RenderUI.h"
#include "Components.h"



void Application::Init(GLFWwindow* &window, int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "CodeSearch", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		std::cout << "ERROR:: CREATING WINDOW" << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);
}

void Application::Render(GLFWwindow* &window, WindowColor &w_color, RenderUI* render) {
	if (window == NULL) {
		std::cout << "ERROR:: PROBLEM IN RENDERING" << std::endl;
		return;
	}
	int currentWindowWidth, currentWindowHeight = 0;
	//Components* ui = new Components();
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(w_color.r, w_color.g, w_color.b, w_color.alpha);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwGetWindowSize(window, &currentWindowWidth, &currentWindowHeight);

		render->UIFrameUpdate();
		
		render->DisplayUI(currentWindowWidth, currentWindowHeight);
		
		render->UIRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Destroy(GLFWwindow* &window) {
	if (window == NULL) {
		std::cout << "ERROR:: PROBLEM IN TERMINATING" << std::endl;
		return;
	}
	glfwTerminate();
}

void Application::Run() 
{
	Application* app = new Application();
	
	GLFWwindow* window = NULL;
	
	WindowColor w_color = { 0.0f, 0.0f, 0.0f, 1.0f };

	RenderUI* r = new RenderUI();

	app->Init(window, 800, 800);
	
	r->Setup(window);

	app->Render(window, w_color, r);

	r->DestroyimGUI();

	delete(r);

	app->Destroy(window);

	delete(app);
}


