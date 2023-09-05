/**************************************************************************
 * @file Editor.cpp
 * @author
 * @par DP email:
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/

#include <Editor.h>
#include <iostream>

void UsingImGui::Init(GLFWwindow* window, const char* glsl_vers) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup bindins
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_vers);
	std::cout << "ImGui Successfully initialized" << std::endl;
}

void UsingImGui::CreateFrame() {
	// Start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UsingImGui::Update() {
	

}

void UsingImGui::Draw() {
	bool loltest;
	static int clickCounter = 0;
	ImGui::Begin("Fk this shit");                          // Create a window called "fk this shit"
	ImGui::Text("Why do we live just to suffer :(");              // Display some text
	ImGui::Checkbox("This is cool", &loltest);
	if (ImGui::Button("Click me!")) {
		++clickCounter;
	}
	ImGui::SameLine();
	ImGui::Text("You clicked %d times", clickCounter);
	if (clickCounter > 4) {
		ImGui::Text("Please stop wasting time here");
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void UsingImGui::Exit() {

}