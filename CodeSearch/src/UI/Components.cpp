#include "Components.h" 

void OutputWindowComponent::UpdateOutputBuffer(ImGuiTextBuffer& out_buff) {
	if (!out_buff.empty()) {
		outputBuffer.clear();
		outputBuffer.append(out_buff.begin(), out_buff.end());
	}
}

void OutputWindowComponent::OutputWindowUICompoent(int currentWindowWidth, int currentWindowHeight) {
	ImGui::Begin("Output Window", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::SetWindowPos(ImVec2(0.0f, 2 * currentWindowHeight / 10.0f), ImGuiCond_Always);

	ImGui::SetWindowSize(ImVec2(currentWindowWidth / 1.0f, 8.0f * currentWindowHeight / 10.0f));

	ImGui::Text("%s", outputBuffer.begin());

	ImGui::End();
}

OutputWindowComponent* OutputWindowComponent::owc = nullptr;

OutputWindowComponent* OutputWindowComponent::GetInstance() {
	if (owc == NULL) {
		owc = new OutputWindowComponent();
		return owc;
	}
	return owc;
}

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
static void Init(char* repo_path, ImGuiTextBuffer& out_buff, bool& done) {

	FileController fc;

	std::filesystem::path dir_path(repo_path);
	
	std::vector<std::string> allFiles = fc.FileCount_Iterator(repo_path,out_buff);
	
	std::cout << allFiles.size()<< std::endl;

	done = true;
}


void RepoInitializationComponent::RepoInit(int currentWindowWidth, int currentWindowHeight) {
	static bool start = false;
	static bool done = false;
	static ImGuiTextBuffer output_buff;
	ImGui::Begin("Initialization", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(currentWindowWidth / 1.0f, currentWindowHeight / 10.0f));
	ImGui::InputTextWithHint("##NoLabel", "Path of your Repo to initialize ... ", repo_path, sizeof(repo_path));
	
	OutputWindowComponent* owc = OutputWindowComponent::GetInstance();

	ImGui::SameLine();
	if (ImGui::Button("Initialize") && repo_path != "" && start == false) {
		start = true;
		done = false;
		std::lock_guard<std::mutex> lock(rinit_mutex);
		std::cout << "Initiating new thread" << std::endl;
		std::thread(Init, repo_path, std::ref(output_buff), std::ref(done)).detach();
	}
	
	owc->UpdateOutputBuffer(output_buff);

	if (done == true) {
		ImGui::Text("Initialization Done");
		start = false;
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