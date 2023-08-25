#pragma once

#include <iostream>
#include <mutex>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "FileController.h"

class SearchBarComponent {
public:
	static SearchBarComponent* GetInstance();
	void SearchUIComponent(int c_window_width, int c_window_height);
	SearchBarComponent(const SearchBarComponent& obj) = delete;

private:
	char input_buffer[1024] = ""; 
	static SearchBarComponent* sbc;
	SearchBarComponent() {}
};


class RepoInitializationComponent {
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