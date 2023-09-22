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

	// Config Flags
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
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

	// 2nd test window
	ImGui::Begin("This should be another window");
	ImGui::Text("Hello there");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void UsingImGui::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

/* ============================================ 
	Use this helper function to read json files
	@param[in] filePath
		path to your file
	@param[in] docRef
		reference to the rapidjson document
	@return
		Returns true if successfull, false otherwise
   ============================================ */
bool Editor::ReadJSONFile(std::string filePath, rapidjson::Document &docRef) {
	// Open file
	std::ifstream file(filePath);
	// Check if file can be opened
	if (!file.is_open()) {
		std::cout << "File not found" << std::endl;
		return false;
	}
	// Read the entire file content into a string
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	// Close the file
	file.close();
	// Parse JSON data from the string
	docRef.Parse(fileContent.c_str()); 
	// Check for parsing errors
	if (docRef.HasParseError()) {
		std::cout << "Parsing error";
		return false;
	}
	return true; // Successfull
}


/* ============================================
	Use this helper function to write to json files
	@param[in] filePath
		path to your file
	@param[in] docRef
		reference to the rapidjson document
	@return
		Returns true if successfull, false otherwise
   ============================================ */
bool Editor::WriteJSONFile(std::string filePath, rapidjson::Document& docRef) {
	// Open file
	std::ofstream file(filePath);
	// Check if file can be opened
	if (!file.is_open()) {
		std::cout << "File not found" << std::endl;
		return false;
	}
	// Setup stream and writer
	rapidjson::StringBuffer stringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
	// Serialize JSON document to a string
	docRef.Accept(writer);
	// Write serialized data to output file
	file << stringBuffer.GetString() << std::endl;
	file.close();
	return true;
}

tempObjData tempObjList;
void Editor::Init() {
	// Define path
	const char* filePath = "../Editor/objekt.json";
	// Create rapidjson doc object
	rapidjson::Document objDoc;
	// Read data from file
	if (ReadJSONFile(filePath, objDoc)) { // Printing out to console to see
		tempObjList.name = objDoc["name"].GetString();
		std::cout << objDoc["name"].GetString() << std::endl;
		tempObjList.size = objDoc["size"].GetInt();
		std::cout << objDoc["size"].GetInt() << std::endl;
		tempObjList.colour = objDoc["colour"].GetString();
		std::cout << objDoc["colour"].GetString() << std::endl;
		tempObjList.smell = objDoc["smell"].GetFloat();
		std::cout << objDoc["smell"].GetFloat() << std::endl;
		tempObjList.alive = objDoc["alive"].GetBool();
		std::cout << objDoc["alive"].GetBool() << std::endl;
	}
	// Simulate size change
	int finalSize = tempObjList.size *= 2;
	objDoc["size"] = finalSize;
	
	if (WriteJSONFile(filePath, objDoc)) {
		std::cout << "If you open the file again and see the size double then Yay everything works\n";
	}
}

