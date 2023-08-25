#include "Components.h" 



void SearchBarComponent::SearchUIComponent(int currentWindowWidth, int currentWindowHeight) {
	static bool enterPressed = false;
	static char output_buff[1024] = "";

	ImGui::Begin("Search", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	
	ImGui::SetWindowPos(ImVec2(0.0f, currentWindowHeight/10.0f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(currentWindowWidth / 1.0f, currentWindowHeight / 10.0f));
	ImGui::InputTextWithHint("##NoLabel", "Search your code for this repo ... ", input_buffer, sizeof(input_buffer));
	
	ImGui::SameLine();
	
	enterPressed = ImGui::Button("Search");
	
	ImGui::End();

	ImGui::Begin("Output Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(0.0f, 2 * currentWindowHeight / 10.0f), ImGuiCond_Always);
	
	ImGui::SetWindowSize(ImVec2(currentWindowWidth / 1.0f, 8.0f * currentWindowHeight / 10.0f));

	if (ImGui::IsKeyPressed(ImGuiKey_Enter)) {
		enterPressed = true;
	}

	if (enterPressed) {
		if (strlen(input_buffer) <= 1024)
		{
			strcpy_s(output_buff, sizeof(output_buff), input_buffer);
		}
	}
	
	ImGui::Text("%s",output_buff);

	if (ImGui::IsKeyReleased(ImGuiKey_Enter) || enterPressed == true) {
			enterPressed = false; 
	}
	ImGui::End();
	
}

SearchBarComponent* SearchBarComponent::sbc = nullptr;

SearchBarComponent* SearchBarComponent::GetInstance() {
	if (sbc == NULL){
		sbc = new SearchBarComponent();
		return sbc;
	}
	return sbc;
}


std::mutex rinit_mutex;
static void Init(char* repo_path, bool& update, float& progress_counter) {

	FileController fc;

	std::filesystem::path dir_path(repo_path);
	
	unsigned int total_files = fc.FileCount_Iterator(repo_path);
	
	std::cout << total_files << std::endl;

	progress_counter = 1.0f / (float)total_files;

	update = true;	
}


void RepoInitializationComponent::RepoInit(int currentWindowWidth, int currentWindowHeight) {
	static float progress = 0.0f;
	static float progress_counter = 0.0f;
	static bool start = false;
	static bool update = false;
	static bool done = false;

	ImGui::Begin("Initialization", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(currentWindowWidth / 1.0f, currentWindowHeight / 10.0f));
	ImGui::InputTextWithHint("##NoLabel", "Path of your Repo to initialize ... ", repo_path, sizeof(repo_path));

	ImGui::SameLine();
	if (ImGui::Button("Initialize") && repo_path != "") {
		start = true;
		std::lock_guard<std::mutex> lock(rinit_mutex);
		std::thread(Init, repo_path, std::ref(update), std::ref(progress_counter)).detach();
	}

	if (progress >= 1.0f) {
		progress = 0.0f;
		progress_counter = 0.0f;
		update = false;
		start = false;
		ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
	}
	else if(progress < 1.0f && update == true){
		start = false;
		ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
		progress = progress + progress_counter;
	}
	else if(start == true) {
		ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
	}
	if (done == true) {
		ImGui::Text("Init Done");
	}
	ImGui::End();
}



RepoInitializationComponent* RepoInitializationComponent::ri = nullptr;

RepoInitializationComponent* RepoInitializationComponent::GetInstance() {
	if (ri == NULL) {
		ri = new RepoInitializationComponent();
		return ri;
	}
	return ri;
}