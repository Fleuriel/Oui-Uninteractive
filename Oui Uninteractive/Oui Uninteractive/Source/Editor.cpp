/**************************************************************************
 * @file Editor.cpp
 * @author
 * @par DP email:
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 09-05-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/

#include "Editor.h"
#include <iostream>

static void HelpMarker(std::string desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip()) {
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

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
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void UsingImGui::Update() {
	

}

void UsingImGui::Draw() {
	// Create the master panel to control other panels

	Editor::CreateMasterPanel();

	if (panelList.soundPanel) {
		Editor::CreateSoundPanel();
	}
	if (panelList.objectPanel) {
		Editor::CreateObjectList();
	}
	if (panelList.Panel1) {
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
	}
	

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void UsingImGui::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


void Editor::Init() {
	// Define path
	const char* filePath = "../editor/objekt.json";

}


/* ============================================
	CREATING INDIVIDUAL DOCKABLE IMGUI PANELS
   ============================================ */

void Editor::CreateMasterPanel() {
	ImGui::Begin("Master Control Panel");
	ImGui::Text("Show panels:");
	ImGui::Checkbox("Sound Panel", &panelList.soundPanel); // Checkbox for sound panel
	ImGui::Checkbox("Objects Panel", &panelList.objectPanel); // Checkbox for sound panel
	ImGui::End();
}

void Editor::CreateSoundPanel() {
	ImGui::Begin("Sound Control Panel");
	if (ImGui::TreeNode("Tracks")) {
		ImGui::SeparatorText("BGM");
		static float bgmVol = 1.0f;
		ImGui::SliderFloat("Volume", &bgmVol, 0.0f, 1.0f, "%.2f");
		soundManager->bgmChannel->setVolume(bgmVol);
		if (ImGui::Button("Play/Pause")) {
			soundManager->PlayBGMSounds();
			soundManager->TogglePlayChannel(soundManager->bgmChannel);
		}
		ImGui::SeparatorText("SFX");
		static int sfxChoice = 0;
		ImGui::RadioButton("SFX 1", &sfxChoice, 0); ImGui::SameLine();
		ImGui::RadioButton("SFX 2", &sfxChoice, 1); ImGui::SameLine();
		ImGui::RadioButton("SFX 3", &sfxChoice, 2);
		if (ImGui::Button("Play")) {
			soundManager->sfxChoice = sfxChoice;
			soundManager->PlaySFXSounds();
		}
		ImGui::TreePop();
	}
	
	ImGui::End();
}

void Editor::CreateObjectList() {
	ImGui::Begin("Pretty objects here");
	// Left Plane
	static size_t selectedID = 0;
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();
	{
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		int objCount = objectFactory->GetGameObjectIDMap().size();
		std::string prevName;
		

		int count = 0;
		for (int count = 0; it != copyMap.end(); it++, count++) {
			std::string objName = it->second->GetName();
			size_t objID = it->second->GetGameObjectID();

			if (ImGui::Selectable(objName.c_str(), selectedID == objID)) {
				selectedID = objID; // Update selected object
				std::cout << selectedID;
			}
		}

		//for (int i = 0; i < objectFactory->; i++) {
		//	if (objectFactory->GetGameObjectByID(i) == nullptr)
		//		continue;
		//	// Get the details of individual object
		//	std::string objName = objectFactory->GetGameObjectByID(i)->GetName();
		//	size_t objID = objectFactory->GetGameObjectByID(i)->GetGameObjectID();
		//	std::string newName = objName;
		//	// Check if its a copied object
		//	if (prevName == objName) {
		//		newName += "(" + std::to_string(i) + ")"; // concat copy number
		//	}
		//	// Check and set which entry is selected 
		//	if (ImGui::Selectable(newName.c_str(), selectedID == i)) {			
		//		selectedID = i;
		//	}		
		//	prevName = objName;
		//}
		
		ImGui::EndChild();
	}
	ImGui::SameLine();


	// Right Plane
	{
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
		// Detail Tab
		if (ImGui::CollapsingHeader("Details")) {		
			ImGui::Text("Object ID: %d", objectFactory->GetGameObjectByID(selectedID)->GetGameObjectID());
			ImGui::Text("Size: ");
			ImGui::Text("Rotation: ");
			ImGui::Separator();
		}
		// Master object controller
		if (ImGui::CollapsingHeader("Master Object Manager")) {
			static int addCount = 0;
			static int cloneCount = 0;

			// Adding objects
			ImGui::InputInt("Add Count", &addCount);
			ImGui::SameLine(); 
		/*	if (ImGui::Button("Add")){
				for (int i = 0; i < addCount; i++) {
					std::string startName{ "Object" };
					startName += std::to_string(objectFactory->GetGameObjectIDMap().size() + 1);
					objectFactory->BuildObjectRunTime(startName);
				}
			}*/

			if (ImGui::Button("Add")) {
				size_t highestID = 0; // Initialize with the lowest possible ID

				if (!objectFactory->GetGameObjectIDMap().empty()) {
					// Find the highest assigned ID in the existing objects
					for (const auto& pair : objectFactory->GetGameObjectIDMap()) {
						highestID = std::max(highestID, pair.first) + 1;
					}
				}

				for (int i = 0; i < addCount; i++) {
					std::string newName = "Object" + std::to_string(highestID + 1);
					objectFactory->BuildObjectRunTime(newName);
					highestID++; // Increment the highest assigned ID
				}
			}

			ImGui::SameLine(); 
			HelpMarker("Use this to add as many objects as you want");
			
			// Cloning objects
			ImGui::InputInt("Clone Count", &cloneCount);
			ImGui::SameLine();
			if (ImGui::Button("Clone")) {
				for (int i = 0; i < cloneCount; i++) {
					objectFactory->CloneObject(selectedID);
				}					
			}
			ImGui::SameLine(); 
			HelpMarker("Use this to clone as many objects as you want");
			
			// Deleting objects
			if (ImGui::Button("Delete")) {
				objectFactory->DestroyObject(objectFactory->GetGameObjectByID(selectedID));
				// Reset selected rect to first to prevent deleting the air and causing bullshit to happen
				auto iter = copyMap.begin();
				if (iter != copyMap.end()) {
					selectedID = iter->second->GetGameObjectID();
				}

			}
			ImGui::SameLine();
			if (ImGui::Button("Delete All")) {
				objectFactory->DestroyAllObjects();
			}
			ImGui::Separator();
		}
		// Individual Object Controls
		if (ImGui::CollapsingHeader("Object Modifier")) {
			static float xPos, yPos, xScale, yScale, angle, rotSpeed;
			ImGui::SliderFloat("X-Position", &xPos, 0.0f, 1.0f, "%.2f"); // Slider for X-Position
			ImGui::SliderFloat("Y-Position", &yPos, 0.0f, 1.0f, "%.2f"); // Slider for Y-Position
			ImGui::SliderFloat("X-Scale", &xScale, 0.0f, 1.0f, "%.2f"); // Slider for X-Scale
			ImGui::SliderFloat("Y-Scale", &yScale, 0.0f, 1.0f, "%.2f"); // Slider for Y-Scale
			ImGui::SliderFloat("Angle", &angle, 0.0f, 1.0f, "%.2f"); // Slider for true angle
			ImGui::SliderFloat("Rotation Speed", &rotSpeed, 0.0f, 1.0f, "%.2f"); // Slider for rotation speed
			ImGui::Separator();
		}
		
		
		ImGui::EndChild();

		if (ImGui::Button("Revert")) {}
		ImGui::SameLine();
		if (ImGui::Button("Save")) {}
		ImGui::EndGroup();
	}
	ImGui::End();
}
	
	

