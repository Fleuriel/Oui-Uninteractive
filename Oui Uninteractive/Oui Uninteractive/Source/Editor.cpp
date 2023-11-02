/**************************************************************************
 * @file Editor.cpp
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 13-09-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/

#include <iostream>
#include "Editor.h"

// Defining static containers
Editor::SystemTime Editor::timeRecorder;
std::vector<float> Editor::fpsData;
std::pair<int, int> Editor::gameWindowOrigin;
std::pair<int, int> Editor::gameWindowSize;
std::vector<std::string> prefabList;


/**************************************************************************
* @brief Helper function to build a custom tooltip with description
* @param desc - String to put into the tooltip
* @return void
*************************************************************************/
static void HelpMarker(std::string desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip()) {
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc.c_str());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}


/**************************************************************************
* @brief Initialization function for ImGui
* @param window - Pointer to the GFLW window
* @param glsl_vers - C-string containing the GLSL version used 
* @return void
*************************************************************************/
void UsingImGui::Init(GLFWwindow* glfwWindow, const char* glsl_vers) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.IniFilename = FILEPATH_IMGUI;

	// Config Flags
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Setup bindins
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init(glsl_vers);
	std::cout << "ImGui Successfully initialized" << std::endl;
}


/**************************************************************************
* @brief Creates the ImGui frame
* @return void
*************************************************************************/
void UsingImGui::CreateFrame() {
	// Start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}


/**************************************************************************
* @brief Update function for ImGui
* @return void
*************************************************************************/
void UsingImGui::Update() {
	

}



/**************************************************************************
* @brief Draw function for ImGui windows
* @return void
*************************************************************************/
void UsingImGui::Draw() {
	// Create the master panel to control other panels
	Editor::CreateMasterPanel();

	if (panelList.gamePanel) {
		Editor::CreateRenderWindow();
	}
	if (panelList.prefabPanel) {
		Editor::CreatePrefabPanel();
	}
	if (panelList.soundPanel) {
		Editor::CreateSoundPanel();
	}
	if (panelList.objectPanel) {
		Editor::CreateObjectList();
	}
	if (panelList.assetBrowserPanel) {
		Editor::CreateAssetBrowser();
	}
	if (panelList.debugPanel) {
		Editor::CreateDebugPanel();
	}
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}


/**************************************************************************
* @brief Exit function for ImGui
* @return void
*************************************************************************/
void UsingImGui::Exit() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}


/**************************************************************************
* @brief This function initializes the editor
* @return void
*************************************************************************/
void Editor::Init() {
	// Set max data points
	maxFPSdata = 2000;

}


/**************************************************************************
* @brief This function updates the editor
* @return void
*************************************************************************/
void Editor::Update() {
	ImGuiIO& io = ImGui::GetIO();
	// Add FPS data point to vector
	fpsData.push_back(io.Framerate);
	// Flush out data points when max limit reached
	if (fpsData.size() > maxFPSdata) {
		fpsData.erase(fpsData.begin());
	}
}


/* ============================================
	CREATING INDIVIDUAL DOCKABLE IMGUI PANELS
   ============================================ */

/**************************************************************************
* @brief This function creates the Master Panel used to control the other sub panels
* @return void
*************************************************************************/
void Editor::CreateMasterPanel() {
	ImGui::Begin("Master Control Panel");
	ImGui::Text("Show panels:");
	ImGui::Checkbox("Game Window", &panelList.gamePanel); // Checkbox for sound panel
	ImGui::Checkbox("Prefab Editor", &panelList.prefabPanel); // Checkbox for prefab editor panel
	ImGui::Checkbox("Sound Panel", &panelList.soundPanel); // Checkbox for sound panel
	ImGui::Checkbox("Objects Panel", &panelList.objectPanel); // Checkbox for object manager panel
	ImGui::Checkbox("Asset Browser", & panelList.assetBrowserPanel); // Checkbox for asset browser
	ImGui::Checkbox("Debug Panel", &panelList.debugPanel); // Checkbox for debug panel
	// The "do smth" button. Interchangable quick access button used for quick testing of features
	if (ImGui::Button("Do Something")) {
		objectFactory->DestroyAllObjects();
		objectFactory->BuildObjectFromFile(FILEPATH_SCENES_TESTWALLS);
	}
	ImGui::End();
}


/**************************************************************************
* @brief This function creates the window to the game world
* @return void
*************************************************************************/
void Editor::CreateRenderWindow() {
	ImGui::Begin("Game Window");
	
	if (ImGui::BeginChild("GameWindow")) {
		gameWindowOrigin.first = ImGui::GetWindowPos().x;
		gameWindowOrigin.second = ImGui::GetWindowPos().y;
		gameWindowSize.first = ImGui::GetWindowSize().x;
		gameWindowSize.second = ImGui::GetWindowSize().y;
		// Get draw size of window
		ImVec2 wsize = ImGui::GetWindowSize();
		// Invert V from openGL
		//ImGui::Image(reinterpret_cast<ImTextureID>(0), wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image(reinterpret_cast<ImTextureID>(OpenGLObject::FrameTexture), wsize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // Replace thirdTexture with handle to FBO when graphics done rendering to FBO	
	}
	ImGui::EndChild();
	ImGui::End();
}



/**************************************************************************
* @brief This function creates the prefab editor window
* @return void
*************************************************************************/
void Editor::CreatePrefabPanel() {
	ImGui::Begin("Prefab Editor");
	static bool physics, transform, logic, collider;
	// Refresh list of prefabs from file directory
	if (ImGui::Button("Refresh")) {
		std::filesystem::path prefabPath{ FILEPATH_PREFAB };
		if (std::filesystem::is_directory(prefabPath)) {
			for (const auto& entry : std::filesystem::directory_iterator(prefabPath)) {
				
			}
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Save")) {
		objectFactory->SavePrefabsToFile(FILEPATH_PREFAB);
	}

	std::map<std::string, Prefab*> copy = objectFactory->GetPrefabMap();
	std::map<std::string, Prefab*>::iterator it = copy.begin();
	static std::string selectedName = it->first;
	
	// Left Plane
	{	
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		for (; it != copy.end(); it++) {
			std::string prefabName = it->first;
			
			if (ImGui::Selectable(prefabName.c_str(), prefabName == selectedName)) {
				selectedName = prefabName;
			}
		}

		ImGui::EndChild();
	}
	ImGui::SameLine();

	// Right Plane
	{
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below
		ImGui::SeparatorText("Details");
		ImGui::Text("Prefab Type: %s", copy[selectedName]->GetType());
		ImGui::Text("Active Components:");
		// If selected prefab has no components
		if (copy[selectedName]->GetPrefabComponentList().empty()) {
			ImGui::Text("Selected Prefab has no components");
		}
		else {
			for (auto& x : copy[selectedName]->GetPrefabComponentList()) {
				ImGui::Text(objectFactory->EnumToString(x->componentType).c_str());
			}
		}
		ImGui::SeparatorText("Components List");

		// Render all the components
		ImGui::Checkbox("##Physics", &physics); ImGui::SameLine();		
		if (ImGui::CollapsingHeader("Physics Body")) {
		/*	if (ImGui::SliderFloat()) {
				
			}*/
			
		}
		ImGui::Checkbox("##Transform", &transform); ImGui::SameLine();
		if (ImGui::CollapsingHeader("Transform")) {

		}
		ImGui::Checkbox("##Logic", &logic); ImGui::SameLine();
		if (ImGui::CollapsingHeader("Logic")) {

		}
		ImGui::Checkbox("##Collider", &collider); ImGui::SameLine();
		if (ImGui::CollapsingHeader("Collider")) {

		}
		

		ImGui::EndChild();
		ImGui::EndGroup();
	}
	ImGui::End();
}


/**************************************************************************
* @brief This function creates the sound panel used to control sound functionality
* @return void
*************************************************************************/
void Editor::CreateSoundPanel() {
	ImGui::Begin("Sound Control Panel");
	if (ImGui::TreeNode("Tracks")) {
		ImGui::SeparatorText("BGM");
		static int bgmChoice = 0;
		static float volValue = 1.0f, bgmVol1 = 1.0f, bgmVol2 = 1.0f;
		bool pauseStatus1 = true, pauseStatus2 = true;

		// Check pause status for bgmch1	
		soundManager->bgmChannels[0]->getPaused(&pauseStatus1);
		if (pauseStatus1) {
			ImGui::PushStyleColor(ImGuiCol_Text, redColour); // Red if not playing	
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, greenColour); // Green if playing
		}
		if (ImGui::RadioButton("BGM 1", &bgmChoice, 0)) { // On radio button 1 click
			volValue = bgmVol1;
		} ImGui::SameLine();
		ImGui::PopStyleColor();

		// Check pause status for bgmch2
		soundManager->bgmChannels[1]->getPaused(&pauseStatus2);
		if (pauseStatus2) { 
			ImGui::PushStyleColor(ImGuiCol_Text, redColour); // Red if not playing
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, greenColour); // Green if playing
		}
		if (ImGui::RadioButton("BGM 2", &bgmChoice, 1)) { // On radio button 2 click
			volValue = bgmVol2;
		}
		ImGui::PopStyleColor();

		// On Volume slider click
		if (ImGui::SliderFloat("Volume", &volValue, 0.0f, 1.0f, "%.2f")) {
			if (bgmChoice == 0) {
				bgmVol1 = volValue;
			}
			else if (bgmChoice == 1) {
				bgmVol2 = volValue;
			}
			soundManager->bgmChannels[bgmChoice]->setVolume(volValue);
		}
		// On play button click
		if (ImGui::Button("Play/Pause")) {
			soundManager->PlayBGMSounds();
			soundManager->TogglePlayChannel(soundManager->bgmChannels[bgmChoice]);
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


/**************************************************************************
* @brief This function creates the object list used to modify objects
* @return void
*************************************************************************/
void Editor::CreateObjectList() {
	ImGui::Begin("Pretty objects here");
	static size_t gameobjID = 0;
	
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::map<size_t, GameObject*>::iterator it = copyMap.begin();
	// Left Plane
	static size_t selectedID = 0;
	{
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
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
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below
		// Detail Tab
		if (ImGui::CollapsingHeader("Details")) {
			static float xPos = 0, yPos = 0, scale = 0, speed = 0, angle = 0, rotSpeed = 0;
			if (objectFactory->GetGameObjectIDMap().empty()) {
				ImGui::Text("No objects");
			}
			else {
				if (objectFactory->GetGameObjectByID(gameobjID) != nullptr) {
					ImGui::Text("Object ID: %d", objectFactory->GetGameObjectByID(gameobjID)->GetGameObjectID());
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
				}
				
				ImGui::Text("X-Position: %.2f | Y-Position: %.2f", xPos, yPos);
				ImGui::Text("Scale: %.2f", scale);
				ImGui::Text("Angle: %.2f", angle);
				ImGui::Text("speed: %.2f", speed);
				ImGui::Text("Rotation Speed: %.2f", rotSpeed);
				ImGui::Separator();
			}
			
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

					objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(highestNumber));
					objectFactory->GetGameObjectByID(highestNumber)->Initialize();
					int randX, randY;
					randX = rand() % ((windowSize.first / 2) - (-(windowSize.first / 2)) + 1) + (-(windowSize.first / 2));
					randY = rand() % ((windowSize.second / 2) - (-(windowSize.second / 2)) + 1) + (-(windowSize.second / 2));
					GET_COMPONENT(objectFactory->GetGameObjectByID(highestNumber), Transform, ComponentType::TRANSFORM)->position.x = static_cast<float>(randX);
					GET_COMPONENT(objectFactory->GetGameObjectByID(highestNumber), Transform, ComponentType::TRANSFORM)->position.y = static_cast<float>(randY);

					highestNumber++; // Increment the highest assigned ID
				}
				gameobjID = objectFactory->GetGameObjectIDMap().begin()->first;
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
				for (std::map<size_t, GameObject*>::iterator it2 = copyMap.begin(); it2 != copyMap.end(); it2++) {
					//set to next record if not the end
					if (getNext) {
						gameobjID = it2->first;
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
			size_t startIndex = 0;
			if (!copyMap.empty()) {
				startIndex = copyMap.rbegin()->first;
			}
			else {
				startIndex = 0;
			}
			if (startIndex > 1) {
				startIndex++;
			}
			if (ImGui::Button("Spawn 2500 Objects")) {
				for (size_t i{}; i < 2500; ++i) {
					std::string goName{ "ObjectRunTime" + std::to_string(startIndex + i + 1) };
					objectFactory->BuildObjectRunTime(goName, "Enemy");
					objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(startIndex+ i));
					objectFactory->AddComponent(ComponentType::TRANSFORM, objectFactory->GetGameObjectByID(startIndex + i));
					objectFactory->AddComponent(ComponentType::COLLIDER, objectFactory->GetGameObjectByID(startIndex + i));
					objectFactory->GetGameObjectByID(startIndex + i)->Initialize();
					GET_COMPONENT(objectFactory->GetGameObjectByID(startIndex + i), Transform, ComponentType::TRANSFORM)->position.x = static_cast<float>(rand() % 800);
					GET_COMPONENT(objectFactory->GetGameObjectByID(startIndex + i), Transform, ComponentType::TRANSFORM)->position.y = static_cast<float>(rand() % 600);
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
					if (ImGui::SliderFloat("X-Position", &xPos2, static_cast<float>(-(windowSize.first / 2)), static_cast<float>(windowSize.first / 2), "%.2f")) { // Slider for X-Position
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x = xPos2;
					}

					yPos2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y;
					if (ImGui::SliderFloat("Y-Position", &yPos2, static_cast<float>(-(windowSize.second / 2)), static_cast<float>(windowSize.second / 2), "%.2f")) { // Slider for Y-Position
						GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y = yPos2;
					}

					scale2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale;
					if (ImGui::SliderFloat("Scale %", &scale2, 0.0f, 500.0f, "%.2f")) { // Slider for Scale
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


/*************************************************************************
* @brief This function creates the asset browser panel used to peruse content
* @return void
*************************************************************************/
void Editor::CreateAssetBrowser() {
	ImGui::Begin("Asset Browser");
	if (ImGui::Button("Refresh")) {

	}
	ImGui::BeginChild("LeftPane", ImVec2(200, 0), true);  // Use 200 width first, can change later. Dynamically size height for now
	RenderDirectory(FILEPATH_MASTER);
	ImGui::EndChild();

	ImGui::SameLine();

	// Right Pane
	{
		ImGui::Text("Teest2");

	}
	
	ImGui::End();
}


/*************************************************************************
* @brief This function creates debug panel used to troubleshoot issues
* @return void
*************************************************************************/
void Editor::CreateDebugPanel() {
	ImGui::Begin("Debug Panel");
	ImGuiIO& io = ImGui::GetIO();

	if (ImGui::CollapsingHeader("Perfomance")) {
		// FPS DATA	
		if (io.Framerate < 60) {
			ImGui::PushStyleColor(ImGuiCol_Text, redColour);
		}
		else if (io.Framerate >= 60 && io.Framerate < 100) {
			ImGui::PushStyleColor(ImGuiCol_Text, yellowColour);
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, greenColour);		
		}
		ImGui::Text("Program FPS: %.2f", io.Framerate); // Display program FPS in "Performance" tab
		ImGui::PopStyleColor();
		
		ImGui::PushStyleColor(ImGuiCol_PlotLines, pinkColour);
		ImGui::PlotLines("Current FPS", fpsData.data(), static_cast<int>(fpsData.size()), 0, "FPS", 0.0f, 300.0f, ImVec2(0, 80));
		ImGui::PopStyleColor();
		// FRAME TIME DATA
		ImGui::Text("Frame time: %.2f ms", 1000.0f / GetFrames());// Display program FPS in "Performance" tab
		ImGui::Text("Program run time: %.2f", GetGameRunTime());
		ImGui::Separator();

		// SYSTEM TIME DATA
		ImGui::Text("System Time Percentage");
		float physicsPercentage = static_cast<float>(timeRecorder.physicsTime / GetDT());
		float grpahicsPercentage = static_cast<float>(timeRecorder.graphicsTime / GetDT());
		float soundPercentage = static_cast<float>(timeRecorder.soundTime / GetDT());
		float particlesPercentage = static_cast<float>(timeRecorder.particlesTime / GetDT());
		float scenemanagerPercentage = static_cast<float>(timeRecorder.scenemanagerTime / GetDT());
		float colliderPercentage = static_cast<float>(timeRecorder.colliderTime / GetDT());
		float transformPercentage = static_cast<float>(timeRecorder.transformTime / GetDT());
		static const char* chartLabels[] = { "Physics", "Graphics" , "Sound", "Particles", "Scene Manager", "Collider", "Transform"};
		float data[] = {
			physicsPercentage, grpahicsPercentage, soundPercentage, particlesPercentage, scenemanagerPercentage, colliderPercentage, transformPercentage
		};
		static ImPlotPieChartFlags flags = 0;
		// Draw pie chart
		ImPlot::BeginPlot("##PieSystemTime", ImVec2(250, 250), ImPlotFlags_Equal | ImPlotFlags_NoMouseText);
		ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
		ImPlot::SetupAxesLimits(0, 1, 0, 1);
		ImPlot::PlotPieChart(chartLabels, data, sizeof(data) / sizeof(float), 0.5, 0.5, 0.4, "%.2f", 90, flags);
		ImPlot::EndPlot();
	}

	if (ImGui::CollapsingHeader("Tools")) {

		static bool drawBB = false;
		static size_t gameobjID = 0;
		ImGui::Checkbox("Display bounding box", &drawBB);
		
		if (drawBB) {

			OpenGLObject::renderBoundingBox = true;
		}
		else
		{
			OpenGLObject::renderBoundingBox = false;
		}

		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Inputs")) {
		// Mouse input checks
		if (io.MousePos.x < 0 || io.MousePos.x > windowSize.first || io.MousePos.y < 0 || io.MousePos.y > windowSize.second) {
			ImGui::Text("Mouse position: Out of window");
		}
		else {
			ImGui::Text("Mouse position: (%g, %g)", io.MousePos.x, io.MousePos.y);
		}
		ImGui::Text("Click duration:");
		for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDown(i)) { 
			ImGui::SameLine(); ImGui::Text("M%d (%.2f secs)", i + 1, io.MouseDownDuration[i]); 
		}

		ImGui::Separator();
		// Keyboard input checks
		struct funcs {
			static bool IsLegacyNativeDupe(ImGuiKey key) {
				if (key < 0 || key >= ImGuiKey_COUNT) {					
					return false; // Handle  key is out of bounds
				}
				return key < 512 && ImGui::GetIO().KeyMap[key] != -1;
			}
		};
		ImGuiKey start_key = (ImGuiKey)0;
		ImGui::Text("Keys down:");
		for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) { // Check Keydowns
			if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue;
			ImGui::SameLine();
			ImGui::Text("\"%s\"", ImGui::GetKeyName(key));
		}
		ImGui::Text("Keys modifiers: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");		
	}
	ImGui::End();
}
	
// Recursive helper function to render the file directory for the asset browser	
void Editor::RenderDirectory(const std::string& filePath) {
	// Render folder directories
	for (auto& entry : std::filesystem::directory_iterator(filePath)) {
		if (entry.is_directory()) {
			if (ImGui::TreeNode(entry.path().filename().string().c_str())) {
				RenderDirectory(entry.path().string());
				ImGui::TreePop();
			}
		}
	}
	// Render individual files
	for (auto& entry : std::filesystem::directory_iterator(filePath)) {
		if (!entry.is_directory()) {
			ImGui::Selectable(entry.path().filename().string().c_str());
		}
	}
}