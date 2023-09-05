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
	ImGui::Begin("Fk this shit");                          // Create a window called "fk this shit"
	ImGui::Text("This is some useful text.");              // Display some text
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void UsingImGui::Exit() {

}