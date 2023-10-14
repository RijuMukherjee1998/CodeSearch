#include "RenderUI.h"
#include "Components.h"

void RenderUI::Setup(GLFWwindow* &window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void RenderUI::UIFrameUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderUI::UIRender() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void RenderUI::DestroyimGUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

RepoInitializationComponent* ri = RepoInitializationComponent::GetInstance();
SearchBarComponent* sc = SearchBarComponent::GetInstance();
OutputWindowComponent* owc = OutputWindowComponent::GetInstance();

void RenderUI::DisplayUI(int currentWindowWidth, int currentWindowHeight) {
	
	ri->RepoInit(currentWindowWidth, currentWindowHeight);
	sc->SearchUIComponent(currentWindowWidth, currentWindowHeight);
	owc->OutputWindowUICompoent(currentWindowWidth, currentWindowHeight);
}