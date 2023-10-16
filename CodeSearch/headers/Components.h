#pragma once

#include <iostream>
#include <mutex>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "FileController.h"



class ComponentManager {
public:
	void AppendTextToBuffer(ImGuiTextBuffer& outputBuffer, const char* text)
	{
		outputBuffer.append(text);
		outputBuffer.append("\n");
	}
	void ClearOutputBuffer(ImGuiTextBuffer& outputBuffer) {
		outputBuffer.clear();
	}
};

class OutputWindowComponent:ComponentManager {
public:
	static OutputWindowComponent* GetInstance();
	void UpdateOutputBuffer(ImGuiTextBuffer* obuff);
	void OutputWindowUICompoent(int c_window_width, int c_window_height);
	OutputWindowComponent(const OutputWindowComponent& obj) = delete;
private:
	ImGuiTextBuffer outputBuffer;
	static OutputWindowComponent* owc;
	OutputWindowComponent() {}
};


class SearchBarComponent:ComponentManager {
public:
	static SearchBarComponent* GetInstance();
	void SearchUIComponent(int c_window_width, int c_window_height);
	SearchBarComponent(const SearchBarComponent& obj) = delete;

private:
	char input_buffer[1024] = ""; 
	static SearchBarComponent* sbc;
	SearchBarComponent() {}
};


class RepoInitializationComponent:ComponentManager {
public:
	static RepoInitializationComponent* GetInstance();
	void RepoInit(int c_window_width, int c_window_height);
	RepoInitializationComponent(const RepoInitializationComponent& obj) = delete;

private:
	char repo_path[1024] = "";
	unsigned int files_read = 0;

	static RepoInitializationComponent* ri;
	RepoInitializationComponent() {}

};