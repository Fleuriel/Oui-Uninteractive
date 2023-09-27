/**************************************************************************
 * @file Editor.cpp
 * @author Mark Low
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 13-09-2023
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
	if (panelList.debugPanel) {
		Editor::CreateDebugPanel();
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


}


/* ============================================
	CREATING INDIVIDUAL DOCKABLE IMGUI PANELS
   ============================================ */

void Editor::CreateMasterPanel() {
	ImGui::Begin("Master Control Panel");
	ImGui::Text("Show panels:");
	ImGui::Checkbox("Sound Panel", &panelList.soundPanel); // Checkbox for sound panel
	ImGui::Checkbox("Objects Panel", &panelList.objectPanel); // Checkbox for sound panel
	ImGui::Checkbox("Debug Panel", &panelList.debugPanel); // Checkbox for debug panel
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
	static size_t gameobjID = 0;
	
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();
	// Left Plane
	static size_t selectedID = 0;
	{
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		int objCount = objectFactory->GetGameObjectIDMap().size();
		std::string prevName;	
		
		
		int count = 0;
		for (; it != copyMap.end(); it++) {

			std::string objName = it->second->GetName();
			size_t objID = it->second->GetGameObjectID();
			
			if (ImGui::Selectable(objName.c_str(), selectedID == count)) {
				gameobjID = objID;
				selectedID = count;
			}
			count++;
		}
		
		ImGui::EndChild();
	}
	ImGui::SameLine();


	// Right Plane
	{
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
		// Detail Tab
		if (ImGui::CollapsingHeader("Details")) {
			if (objectFactory->GetGameObjectByID(gameobjID) != nullptr) {
				ImGui::Text("Object ID: %d", objectFactory->GetGameObjectByID(gameobjID)->GetGameObjectID());
			}
			static float xPos = 0, yPos = 0, scale = 0, speed = 0, angle = 0, rotSpeed = 0;
			if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::TRANSFORM) != -1) {
				xPos = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x;
				yPos = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y;
				scale = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale;
				angle = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->rotation;
			}
			else {
				xPos = yPos = scale = angle = 0;
			}
			if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::PHYSICS_BODY) != -1) {
				speed = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY)->speed;
				rotSpeed = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed;
			}
			else {
				speed = rotSpeed = 0;
			}
			ImGui::Text("X-Position: %.2f | Y-Position: %.2f", xPos, yPos);
			ImGui::Text("Scale: %.2f", scale);
			ImGui::Text("Angle: %.2f", angle);
			ImGui::Text("speed: %.2f", speed);
			ImGui::Text("Rotation Speed: %.2f", rotSpeed);
			ImGui::Separator();
		}
		// Master object controller
		if (ImGui::CollapsingHeader("Master Object Manager")) {
			static int addCount = 0;
			static int cloneCount = 0;

			// Adding objects
			ImGui::InputInt("Add Count", &addCount);
			ImGui::SameLine(); 

			if (ImGui::Button("Add")) {
				size_t highestNumber = 0; // Initialize with the lowest possible ID

				if (!objectFactory->GetGameObjectIDMap().empty()) {
					// Find the highest assigned ID in the existing objects
					for (const auto& pair : objectFactory->GetGameObjectIDMap()) {
						const std::string& objName = pair.second->GetName();
						size_t pos = objName.find("Object");
						if (pos != std::string::npos) {
							size_t number = std::stoi(objName.substr(pos + 6)); // Extract and parse the number part
							highestNumber = std::max(highestNumber, number);
						}
					}
				}

				for (int i = 0; i < addCount; i++) {
					std::string newName = "Object" + std::to_string(highestNumber + 1);
					objectFactory->BuildObjectRunTime(newName, "");
					highestNumber++; // Increment the highest assigned ID
				}
			}

			ImGui::SameLine(); 
			HelpMarker("Use this to add as many objects as you want");
			
			// Cloning objects
			ImGui::InputInt("Clone Count", &cloneCount);
			ImGui::SameLine();
			if (ImGui::Button("Clone")) {
				for (int i = 0; i < cloneCount; i++) {
					objectFactory->CloneObject(gameobjID);
				}					
			}
			ImGui::SameLine(); 
			HelpMarker("Use this to clone as many objects as you want");
			
			// Deleting objects
			if (ImGui::Button("Delete")) {
				if (objectFactory->GetGameObjectByID(gameobjID) != nullptr) {
					objectFactory->DestroyObject(objectFactory->GetGameObjectByID(gameobjID));
				}
				size_t counter = 0;
				bool getNext = false;
				for (std::map<size_t, GameObject*>::iterator it = copyMap.begin(); it != copyMap.end(); it++) {
					//set to next record if not the end
					if (getNext) {
						gameobjID = it->first;
						getNext = false;
						break;
					}
					//trigger to get ready to read next record
					if (counter == selectedID) {
						getNext = true;
					}
					
					counter++;
				}
				//edge case if deleted object is the last one
				if (getNext) {
					selectedID = 0;
					gameobjID = copyMap.begin()->first;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete All")) {
				objectFactory->DestroyAllObjects();
				selectedID = 0;
			}
			ImGui::SameLine();
			// Used for testing M1 Rubric: Have 2.5k Objects with FPS >60
			if (ImGui::Button("Spawn 2500 Objects")) {
				for (size_t i{}; i < 2500; ++i) {
					std::string goName{ "ObjectRunTime" + std::to_string(i + 1) };
					objectFactory->BuildObjectRunTime(goName, "Enemy");
					objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(i));
					objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(i));
					objectFactory->GetGameObjectByID(i)->Initialize();

					GET_COMPONENT(objectFactory->GetGameObjectByID(i), Transform, ComponentType::TRANSFORM)->position.x = rand() % 800;
					GET_COMPONENT(objectFactory->GetGameObjectByID(i), Transform, ComponentType::TRANSFORM)->position.y = rand() % 600;
				}
			}
		
			ImGui::Separator();
		}
		// Individual Object Controls
		if (ImGui::CollapsingHeader("Object Modifier")) {
			if (objectFactory->GetGameObjectIDMap().empty()) {
				ImGui::Text("No Objects, Add some objects above");
			}
			else {
				static float xPos2 = 0, yPos2 = 0, scale2 = 0, speed2 = 0, angle2 = 0, rotSpeed2 = 0;
				if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::TRANSFORM) != -1) {
					xPos2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x;
					if (ImGui::SliderFloat("X-Position", &xPos2, 0.0f, 1000.0f, "%.2f")) { // Slider for X-Position
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x = xPos2;
					}

					yPos2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y;
					if (ImGui::SliderFloat("Y-Position", &yPos2, 0.0f, 100.0f, "%.2f")) { // Slider for Y-Position
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y = yPos2;
					}

					scale2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale;
					if (ImGui::SliderFloat("Scale", &scale2, 0.0f, 100.0f, "%.2f")) { // Slider for Scale
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale = scale2;
					}

					angle2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->rotation;
					if (ImGui::SliderFloat("Angle", &angle2, 0.0f, 360.0f, "%.2f")) { // Slider for true angle
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->rotation = angle2;
					}
				}
				else {
					ImGui::Text("Selected Object has no TRANSFORM component");
				}
				if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::PHYSICS_BODY) != -1) {
					speed2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY)->speed;
					if (ImGui::SliderFloat("Speed", &speed2, 0.0f, 100.0f, "%.2f")) { // Slider for Speed
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY)->speed = speed2;
					}


					rotSpeed2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed;
					if (ImGui::SliderFloat("Rotation Speed", &rotSpeed2, 0.0f, 500.0f, "%.2f")) {// Slider for rotation speed
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed = rotSpeed2;
					}
				}
				else {
					ImGui::Text("Selected Object has no PHYSICSBODY component");
				}
				
			}
			
			ImGui::Separator();
		}
		
		
		ImGui::EndChild();

		ImGui::EndGroup();
	}
	ImGui::End();
}

void Editor::CreateDebugPanel() {
	ImGui::Begin("Debug Panel");

	if (ImGui::CollapsingHeader("Perfomance")) {
		ImGui::Text("Program FPS: %.2f", GetFrames()); // Display program FPS in "Performance" tab

		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Tools")) {
		ImGui::Text("Program FPS: %.2f", GetFrames()); // Display program FPS in "Performance" tab
		ImGui::Checkbox("Display bounding box", &panelList.soundPanel); // Checkbox for sound panel
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Inputs")) {
		double mouseXPos, mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		ImGui::Text("Mouse position: (%d, %d)", static_cast<int>(mouseXPos), static_cast<int>(mouseYPos));
		ImGui::Separator();
	}
	ImGui::End();
}
	
	
