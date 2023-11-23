/**************************************************************************
 * @file Editor.cpp
 * @author LOW Wang Chun, Mark
 * @par DP email: l.wangchunmark@digipen.edu
 * @par Course: CSD 2401
 * @par Software Engineering Project 3
 * @date 13-09-2023
 * @brief This source file contains the code to setup and run the editor
 *************************************************************************/

#include <Windows.h>
#include <iostream>
#include "Editor.h"
#include "Collision.h"
#define PI 3.141592653589793
 // Defining static variables
Editor::SystemTime Editor::timeRecorder;
std::vector<float> Editor::fpsData;
std::pair<int, int> Editor::gameWindowOrigin;
std::pair<int, int> Editor::gameWindowSize;
std::vector<std::string> prefabList;
std::string Editor::browserInputPath;
bool Editor::browserDoubleClicked;
std::string Editor::browserSelectedItem;
GameObject* Editor::selected;

OpenGLObject Editor::selectedOutline;
// Editor settings
int Editor::iconSize{ 128 };
int Editor::iconPadding{ 16 };

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

	// Set filepath to imgui.ini file
	io.IniFilename = FILEPATH_IMGUI;

	// Load fonts for editor
	LoadFonts();

	io.FontDefault = io.Fonts->Fonts[0];

	// Config Flags
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Setup bindins
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init(glsl_vers);
	std::cout << "ImGui Successfully initialized" << std::endl;
}


void UsingImGui::LoadFonts() {
	ImGuiIO& io = ImGui::GetIO();
	for (const auto& entry : std::filesystem::directory_iterator(FILEPATH_FONTS)) {
		io.Fonts->AddFontFromFileTTF(entry.path().string().c_str(), 20.0f);
	}
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

	// Create the menu bar
	Editor::CreateMenuBar();

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

	//Editor::selectedOutline.Draw(std::string(""), true);
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
	browserDoubleClicked = false;
	browserInputPath = FILEPATH_MASTER;
	Editor::selectedOutline.InitObjects();
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
	double mouseX; // = io.MousePos.x;
	double mouseY; // = io.MousePos.y;

	glfwGetCursorPos(windowNew, &mouseX, &mouseY);

	OpenGLObject::FrameBufferMouseCoords(windowNew, &mouseX, &mouseY, OpenGLObject::cameraObject);

	double ogMouseX; 
	double ogMouseY;

	glfwGetCursorPos(windowNew, &ogMouseX, &ogMouseY);

	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::pair<int, int> xBounds = std::pair<int, int>(Editor::gameWindowOrigin.first, Editor::gameWindowSize.first);
	std::pair<int, int> yBounds = std::pair<int, int>(Editor::gameWindowOrigin.second, (Editor::gameWindowSize.second));
	for (std::pair<size_t, GameObject*> gObj : objectFactory->GetGameObjectIDMap()) {
		Transform* tx = GET_COMPONENT(gObj.second, Transform, ComponentType::TRANSFORM);
		if ((ogMouseX > xBounds.first && ogMouseX < xBounds.second) && (ogMouseY > yBounds.first && ogMouseY < yBounds.second)) {
			if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1)) {
				if (CollisionMouseRect(tx->position, tx->scale.x * 1.1, tx->scale.y * 1.1, mouseX, mouseY)) {
					selected = gObj.second;
					break;
				}
			}
		}
	}
	static bool translateMode = false;
	static bool scaleMode = false;
	static bool scaleMode2 = false;
	if (selected != nullptr) {
		Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
		if ((ogMouseX > xBounds.first && ogMouseX < xBounds.second) && (ogMouseY > yBounds.first && ogMouseY < yBounds.second)) {
			if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1)) {
				if (translateMode != true && scaleMode != true && scaleMode2 != true) {
					if (CollisionMouseRect(tx->position, tx->scale.x, tx->scale.y, mouseX, mouseY)) {
						translateMode = true;
						//	tx->position = Vec2(mouseX, mouseY);
					}
					else if (CollisionMouseRect(Vec2(tx->position.x + tx->scale.x / 2.f, tx->position.y), tx->scale.x * 0.1f, tx->scale.y * 1.1, mouseX, mouseY)) {
						scaleMode = true;
						/*tx->scale.x += mouseX - (tx->position.x + tx->scale.x / 2);
						tx->position += Vec2(mouseX - (tx->position.x + tx->scale.x / 2), 0);		*/
					}
					else if (CollisionMouseRect(Vec2(tx->position.x - tx->scale.x / 2.f, tx->position.y), tx->scale.x * 0.1f, tx->scale.y * 1.1, mouseX, mouseY)) {
						scaleMode2 = true;
					}
				}
				
			}
		}
		if (tx != nullptr) {
			Matrix3x3 scale = Matrix3x3(tx->scale.x * 1.1f, 0.f, 0.f,
				0.f, tx->scale.y * 1.1f, 0.f,
				0.f, 0.0f, 1.0f);
			float radRot = tx->rotation * (static_cast<float>(PI) / 180.0f);
			Matrix3x3 rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
				-sinf(radRot), cosf(radRot), 0.f,
				0.f, 0.f, 1.0f);
			Matrix3x3 translate = Matrix3x3(1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				tx->position.x, tx->position.y, 1.0f);
			selectedOutline.Update(scale, rotate, translate);
		}
		
	}
	static bool buttonDown = false;
	if (translateMode) {
		if (selected != nullptr) {
			Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
					buttonDown = true;
				}
				else {
					buttonDown = false;
					translateMode = false;
				}

				if (buttonDown) {
					tx->position = Vec2(mouseX, mouseY);
				}
			}
		}
	}
	if (scaleMode) {
		if (selected != nullptr) {
			Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
					buttonDown = true;
				}
				else {
					buttonDown = false;
					scaleMode = false;
				}

				if (buttonDown) {
					tx->scale.x += mouseX - (tx->position.x + tx->scale.x / 2);
					tx->position += Vec2(mouseX - (tx->position.x + tx->scale.x / 2), 0);
				}
			}
		}
	}

	if (scaleMode2) {
		if (selected != nullptr) {
			Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
					buttonDown = true;
				}
				else {
					buttonDown = false;
					scaleMode2 = false;
				}

				if (buttonDown) {
					if (mouseX < (tx->position.x - tx->scale.x / 2)) {
						tx->scale.x += abs((mouseX)-((tx->position.x - tx->scale.x / 2)));
						tx->position -= Vec2(abs((mouseX)-((tx->position.x - tx->scale.x / 2))), 0);
					}
					else {
						tx->scale.x -= abs((mouseX)-((tx->position.x - tx->scale.x / 2)));
						tx->position += Vec2(abs((mouseX)-((tx->position.x - tx->scale.x / 2))), 0);
					}
					
				}
			}
		}
	}
	if (inputSystem.GetKeyState(GLFW_KEY_DELETE)) {
		if (selected != nullptr) {
			objectFactory->DestroyObject(objectFactory->GetGameObjectByID(selected->GetGameObjectID()));
			selected = nullptr;
		}
	}

	
}

/* ============================================
	CREATING INDIVIDUAL DOCKABLE IMGUI PANELS
   ============================================ */

void Editor::CreateMenuBar() {
	static bool showAssBrowserSettings = false;
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Create")) {}
			if (ImGui::MenuItem("Save")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings")) {
			if (ImGui::MenuItem("AssBrowser##1")) {
				showAssBrowserSettings = true;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (showAssBrowserSettings) {
		static int exp1 = 7, exp2 = 4;
		ImGui::Begin("Asset Browser Settings", &showAssBrowserSettings);
		//ImGui::SliderFloat("Icon Size", &iconSize, 32, 2048);
		//ImGui::SliderFloat("Icon Padding", &iconPadding, 0, 128);
		if (ImGui::SliderInt("Icon Size", &exp1, 5, 10)) {
			iconSize = std::powf(2.0f, exp1);
		}
		if (ImGui::SliderInt("Icon Padding", &exp2, 0, 10)) {
			iconPadding = std::powf(2.0f, exp2);
		}
		ImGui::End();
	}
}


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
	ImGui::Checkbox("Asset Browser", &panelList.assetBrowserPanel); // Checkbox for asset browser
	ImGui::Checkbox("Debug Panel", &panelList.debugPanel); // Checkbox for debug panel

	if (ImGui::Button("Do Something")) {

	}


	ImGui::SeparatorText("Scene controls");
	static int selectedScene = 0;
	static std::string sceneFileName;
	// Render drop menu for scene file selector
	if (ImGui::BeginCombo("Scene File", assetManager.GetScene(selectedScene).c_str())) {
		for (int i = 0; i < assetManager.GetNumberOfScenes(); i++) {
			bool isSelected = (i == selectedScene);
			if (ImGui::Selectable(assetManager.GetScene(i).c_str(), isSelected)) {
				selectedScene = i;
				sceneFileName = "assets/scenes/" + assetManager.GetScene(i);
			}
			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	//std::cout << sceneFileName << std::endl;
	// Save level to file
	if (ImGui::Button("Save scene")) {
		rapidjson::Document tilemapDoc = tilemapLoader->SaveTilemap(sceneFileName);
		const rapidjson::Document& objectDoc = objectFactory->GetObjectDocSaving(sceneFileName);

		rapidjson::Document::AllocatorType& allocator = tilemapDoc.GetAllocator();
		
		for (auto& member : objectDoc.GetObj()) {
			// Check for conflicts or handle them based on your needs
			if (!tilemapDoc.HasMember(member.name)) {
				rapidjson::Value key(member.name, allocator);
				rapidjson::Value value;
				value.CopyFrom(member.value, allocator);
				tilemapDoc.AddMember(key, value, allocator);
			}
		}
		JsonSerializer serializer;
		if (serializer.WriteJSONFile(sceneFileName, tilemapDoc)) {
			std::cout << "Successfully saved objects to file." << std::endl;
		}
		//objectFactory->SaveObjectsToFile(sceneFileName);
	}
	ImGui::SameLine();
	// Load level from file
	if (ImGui::Button("Load scene")) {
		objectFactory->DestroyAllObjects();
		tilemapLoader->LoadTilemap(sceneFileName);
		objectFactory->BuildObjectFromFile(sceneFileName);
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
		gameWindowOrigin.first = static_cast<int>(ImGui::GetWindowPos().x);
		gameWindowOrigin.second = static_cast<int>(ImGui::GetWindowPos().y);
		gameWindowSize.first = static_cast<int>(ImGui::GetWindowSize().x);
		gameWindowSize.second = static_cast<int>(ImGui::GetWindowSize().y);
		// Get draw size of window
		ImVec2 wsize = ImGui::GetWindowSize();
		// Invert V from openGL
		//ImGui::Image(reinterpret_cast<ImTextureID>(0), wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(OpenGLObject::FrameTexture)), wsize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // Replace thirdTexture with handle to FBO when graphics done rendering to FBO	
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
	static float phyRotSpeed, phySpeed, phyMass, phyFriction, transXpos, transYpos, transRot, transScaleX, transScaleY, colScaleX, colScaleY, colRot;
	static bool phyIsStatic, physicsFlag, transformFlag, logicFlag, colliderFlag, saveFlag, loadedFlag = false;

	static int currentScriptIndex;
	static std::set<unsigned int> tempLogicSet;
	static std::string currentScriptName;
	static bool initialized, deleteFlag = false;


	static std::string newPrefabName{}, newPrefabType{};

	std::map<std::string, Prefab*> copy = objectFactory->GetPrefabMap();
	std::map<std::string, Prefab*>::iterator it = copy.begin();
	static std::string selectedName = it->first;

	// Refresh list of prefabs from file directory
	//if (ImGui::Button("Refresh")) {
	//	std::filesystem::path prefabPath{ FILEPATH_PREFAB };
	//	if (std::filesystem::is_directory(prefabPath)) {
	//		for (const auto& entry : std::filesystem::directory_iterator(prefabPath)) {
	//			
	//		}
	//	}
	//}
	if (ImGui::Button("Spawn Objects")) {
		size_t highestNumber = 0; // Initialize with the lowest possible ID

		if (!objectFactory->GetGameObjectIDMap().empty()) {
			// Find the highest assigned ID in the existing objects
			for (const auto& pair : objectFactory->GetGameObjectIDMap()) {
				const std::string& objName = pair.second->GetName();
				size_t pos = objName.find(selectedName);
				if (pos != std::string::npos) {
					size_t number = std::stoi(objName.substr(pos + selectedName.size())); // Extract and parse the number part
					highestNumber = std::max(highestNumber, number);
				}
			}
		}
		Prefab* prefabObj = objectFactory->GetPrefabByName(selectedName);
		std::string name = selectedName + std::to_string(highestNumber + 1);
		GameObject* objFromPrefab = objectFactory->BuildObjectFromPrefab(prefabObj->GetName(), prefabObj->GetType());
		objFromPrefab->SetName(name);

	}

	if (ImGui::Button("Add Prefab")) {
		size_t highestNumber = 0; // Initialize with the lowest possible ID
		std::string defaultPrefabName = "NewPrefab";
		if (!objectFactory->GetPrefabMap().empty()) {
			// Find the highest assigned ID in the existing objects
			for (const auto& pair : objectFactory->GetPrefabMap()) {
				const std::string& objName = pair.second->GetName();
				size_t pos = objName.find(defaultPrefabName);
				if (pos != std::string::npos) {
					size_t number = std::stoi(objName.substr(pos + defaultPrefabName.size())); // Extract and parse the number part
					highestNumber = std::max(highestNumber, number);
				}

			}
		}
		std::string name = defaultPrefabName + std::to_string(highestNumber + 1);
		Prefab* prefab{ new Prefab(name, "Temp") };
		objectFactory->AddPrefabToMap(prefab, prefab->GetName());
		saveFlag = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Prefab")) {
		objectFactory->RemovePrefabFromMap(selectedName);
		selectedName = it->first;
		saveFlag = true;

	}
	if (saveFlag) {
		ImGui::SameLine();
		bool physicsUpdateFlag = false;
		bool transformUpdateFlag = false;
		bool logicUpdateFlag = false;
		bool colliderUpdateFlag = false;
		
		ImGui::SameLine();
		std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
		if (ImGui::Button("Save")) {
			// Handle saving/deleteion for physics body component
			if (physicsFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::PHYSICS_BODY) == -1) {
				objectFactory->GetPrefabByName(selectedName)->AddComponent(new PhysicsBody(), ComponentType::PHYSICS_BODY);
			}
			if (objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::PHYSICS_BODY) != -1) {
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed = phyRotSpeed;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->speed = phySpeed;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->mass = phyMass;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->frictionForce = phyFriction;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->isStatic = phyIsStatic;
				physicsUpdateFlag = true;
			}
			if (!physicsFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::PHYSICS_BODY) != -1) {
				objectFactory->GetPrefabByName(selectedName)->RemoveComponent(GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY));
			}

			// Handle saving for transform component
			if (transformFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::TRANSFORM) == -1) {
				objectFactory->GetPrefabByName(selectedName)->AddComponent(new Transform(), ComponentType::TRANSFORM);
			}
			if (objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::TRANSFORM) != -1) {
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->position.x = transXpos;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->position.y = transYpos;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->rotation = transRot;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->scale.x = transScaleX;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->scale.y = transScaleY;
				transformUpdateFlag = true;

			}
			if (!transformFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::TRANSFORM) != -1) {
				objectFactory->GetPrefabByName(selectedName)->RemoveComponent(GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM));
			}
			//Handle saving/deletion for logic component
			if (logicFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::LOGICCOMPONENT) == -1) {
				objectFactory->GetPrefabByName(selectedName)->AddComponent(new LogicComponent(), ComponentType::LOGICCOMPONENT);
			}
			if (objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::LOGICCOMPONENT) != -1) {
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), LogicComponent, ComponentType::LOGICCOMPONENT)->scriptIndexSet = tempLogicSet;
				logicUpdateFlag = true;
			}
			if (!logicFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::LOGICCOMPONENT) == -1) {
				objectFactory->GetPrefabByName(selectedName)->RemoveComponent
				(GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), LogicComponent, ComponentType::LOGICCOMPONENT));
			}

			// Handle saving/deletion for collider component
			if (colliderFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::COLLIDER) == -1) {
				objectFactory->GetPrefabByName(selectedName)->AddComponent(new Collider(), ComponentType::COLLIDER);
			}
			if (objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::COLLIDER) != -1) {
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER)->tx->rotation = colRot;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER)->tx->scale.x = colScaleX;
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER)->tx->scale.y = colScaleY;
				colliderUpdateFlag = true;
			}
			if (!colliderFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::COLLIDER) != -1) {
				objectFactory->GetPrefabByName(selectedName)->RemoveComponent(GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER));
			}
			for (std::map<size_t, GameObject*>::iterator it = copyMap.begin(); it != copyMap.end(); it++) {
				if ((*it).second->GetType() == objectFactory->GetPrefabByName(selectedName)->GetType()) {

				
					Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Transform, ComponentType::TRANSFORM);
					if (objTX != nullptr) {
						Transform* prefabTX = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM);
						Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Transform, ComponentType::TRANSFORM);
						objTX->scale = prefabTX->scale;
						objTX->position = prefabTX->position;
						objTX->rotation = prefabTX->rotation;
					}


					
					PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), PhysicsBody, ComponentType::PHYSICS_BODY);
					if (objBody != nullptr) {
						PhysicsBody* prefabBody = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY);
						PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), PhysicsBody, ComponentType::PHYSICS_BODY);
						objBody->rotationSpeed = prefabBody->rotationSpeed;
						objBody->mass = prefabBody->mass;
						objBody->frictionForce = prefabBody->frictionForce;
						objBody->speed = prefabBody->speed;
						objBody->isStatic = prefabBody->isStatic;
					}


					
					LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), LogicComponent, ComponentType::LOGICCOMPONENT);
					if (objLogic != nullptr) {
						LogicComponent* prefabLogic = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), LogicComponent, ComponentType::LOGICCOMPONENT);
						LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), LogicComponent, ComponentType::LOGICCOMPONENT);
						objLogic->scriptIndexSet = prefabLogic->scriptIndexSet;
					}


					
					Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Collider, ComponentType::COLLIDER);
					if (objCollider != nullptr) {
						Collider* prefabCollider = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER);
						Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Collider, ComponentType::COLLIDER);
						objCollider->tx->scale = prefabCollider->tx->scale;
						objCollider->tx->rotation = prefabCollider->tx->rotation;
					}

				}
			}
			objectFactory->SavePrefabsToFile(FILEPATH_PREFAB);
			saveFlag = false;
		}
		if (ImGui::Button("Preview Changes")) {
			
			for (std::map<size_t, GameObject*>::iterator it = copyMap.begin(); it != copyMap.end(); it++) {
				if ((*it).second->GetType() == objectFactory->GetPrefabByName(selectedName)->GetType()) {
				
					/*	Transform* prefabTX = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM);
						Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Transform, ComponentType::TRANSFORM);
						objTX->scale = prefabTX->scale;
						objTX->position = prefabTX->position;
						objTX->rotation = prefabTX->rotation;*/
					Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Transform, ComponentType::TRANSFORM);
					if (objTX != nullptr) {
						objTX->scale.x = transScaleX;
						objTX->scale.y = transScaleY;
						objTX->position = Vec2(transXpos, transYpos);
						objTX->rotation = transRot;
					}
					
					
					/*	PhysicsBody* prefabBody = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY);
						PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), PhysicsBody, ComponentType::PHYSICS_BODY);
						objBody->rotationSpeed = prefabBody->rotationSpeed;
						objBody->mass = prefabBody->mass;
						objBody->frictionForce = prefabBody->frictionForce;
						objBody->speed = prefabBody->speed;
						objBody->isStatic = prefabBody->isStatic;*/
					PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), PhysicsBody, ComponentType::PHYSICS_BODY);
					if (objBody != nullptr) {
						objBody->rotationSpeed = phyRotSpeed;
						objBody->speed = phySpeed;
						objBody->mass = phyMass;
						objBody->frictionForce = phyFriction;
						objBody->isStatic = phyIsStatic;
					}
					
					
					/*	LogicComponent* prefabLogic = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), LogicComponent, ComponentType::LOGICCOMPONENT);
						LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), LogicComponent, ComponentType::LOGICCOMPONENT);
						objLogic->scriptIndexSet = prefabLogic->scriptIndexSet;*/
					LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), LogicComponent, ComponentType::LOGICCOMPONENT);
					if (objLogic != nullptr) {
						objLogic->scriptIndexSet = tempLogicSet;
					}
					
					
					/*Collider* prefabCollider = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER);
					Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Collider, ComponentType::COLLIDER);
					objCollider->tx->scale = prefabCollider->tx->scale;
					objCollider->tx->rotation = prefabCollider->tx->rotation;*/
					Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID((*it).second->GetGameObjectID()), Collider, ComponentType::COLLIDER);
					if (objCollider != nullptr) {
						objCollider->tx->scale.x = colScaleX;
						objCollider->tx->scale.y = colScaleY;
						objCollider->tx->rotation = colRot;
					}
					
				}
			}
			// Save and serialize prefabs
		}
	}




	// Left Plane
	{
		ImGui::BeginChild("left pane", ImVec2(150, 0), true);
		for (; it != copy.end(); it++) {
			std::string prefabName = it->first;
			if (ImGui::Selectable(prefabName.c_str(), prefabName == selectedName) || !loadedFlag) {
				selectedName = prefabName;
				initialized = false;
				// Update states
				physicsFlag = (copy[selectedName]->Has(ComponentType::PHYSICS_BODY) != -1);
				transformFlag = (copy[selectedName]->Has(ComponentType::TRANSFORM) != -1);
				logicFlag = (copy[selectedName]->Has(ComponentType::LOGICCOMPONENT) != -1);
				colliderFlag = (copy[selectedName]->Has(ComponentType::COLLIDER) != -1);
				loadedFlag = true;

				if (copy[selectedName]->Has(ComponentType::PHYSICS_BODY) != -1) {
					phyRotSpeed = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->rotationSpeed;
					phySpeed = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->speed;
					phyMass = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->mass;
					phyFriction = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->frictionForce;
					phyIsStatic = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY)->isStatic;
				}
				if (copy[selectedName]->Has(ComponentType::TRANSFORM) != -1) {
					transXpos = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->position.x;
					transYpos = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->position.y;
					transRot = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->rotation;
					transScaleX = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->scale.x;
					transScaleY = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM)->scale.y;
				}
				if (copy[selectedName]->Has(ComponentType::COLLIDER) != -1) {
					colRot = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER)->tx->rotation;
					colScaleX = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER)->tx->scale.x;
					colScaleY = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER)->tx->scale.y;
				}
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
		ImGui::Text("Prefab Type: %s", copy[selectedName]->GetType().c_str());
		ImGui::PushStyleColor(ImGuiCol_Text, greenColour);
		ImGui::Text("Active Components:");
		ImGui::PopStyleColor();
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

		// Render Physics
		if (ImGui::Checkbox("##Physics", &physicsFlag)) {
			saveFlag = true;
		}
		ImGui::SameLine();
		if (ImGui::CollapsingHeader("Physics Body")) {
			ImGui::Indent();
			if (ImGui::SliderFloat("Rotation Speed", &phyRotSpeed, 0.0f, 1000.0f)) saveFlag = true;
			if (ImGui::SliderFloat("Speed", &phySpeed, 0.0f, 1000.0f)) saveFlag = true;
			if (ImGui::SliderFloat("Mass", &phyMass, 0.0f, 1000.0f)) saveFlag = true;
			if (ImGui::SliderFloat("Friction", &phyFriction, 0.0f, 100.0f)) saveFlag = true;
			if (ImGui::Checkbox("Is Static", &phyIsStatic)) saveFlag = true;
			ImGui::Unindent();
		}
		// Render Transform
		if (ImGui::Checkbox("##Transform", &transformFlag)) {
			saveFlag = true;
		}
		ImGui::SameLine();
		if (ImGui::CollapsingHeader("Transform")) {
			ImGui::Indent();
			if (ImGui::InputFloat("X-Position", &transXpos)) saveFlag = true;
			if (ImGui::InputFloat("Y-Position", &transYpos)) saveFlag = true;
			if (ImGui::InputFloat("Rotation", &transRot)) saveFlag = true;
			if (ImGui::InputFloat("ScaleX", &transScaleX)) saveFlag = true;
			if (ImGui::InputFloat("ScaleY", &transScaleY)) saveFlag = true;
			ImGui::Unindent();
		}
		// Render Logic
		if (ImGui::Checkbox("##Logic", &logicFlag)) {
			saveFlag = true;
		}
		ImGui::SameLine();
		if (ImGui::CollapsingHeader("Logic") && logicFlag) {
			if (ImGui::BeginCombo("Scripts", currentScriptName.c_str())) {
				for (int i = 0; i < logicSystem->scriptVec.size(); i++) {
					bool isSelected = (i == currentScriptIndex);
					if (ImGui::Selectable(logicSystem->scriptVec[i]->name.c_str(), isSelected)) {
						currentScriptIndex = i;
						currentScriptName = logicSystem->scriptVec[i]->name;
					}

					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Button("Add Script")) {
				tempLogicSet.insert(currentScriptIndex);
				saveFlag = true;
			}
			if (ImGui::Button("Delete Script")) {
				tempLogicSet.erase(currentScriptIndex);
				saveFlag = true;
			}

			ImGui::BeginChild("Script List");
			LogicComponent* prefabLogic = GET_PREFAB_COMPONENT(copy[selectedName], LogicComponent, ComponentType::LOGICCOMPONENT);
			if (prefabLogic != nullptr) {
				if (initialized == false) {
					tempLogicSet = prefabLogic->scriptIndexSet;
					initialized = true;
				}

				for (std::set<unsigned int>::iterator it = tempLogicSet.begin(); it != tempLogicSet.end(); it++) {
					ImGui::Text(logicSystem->scriptVec[*it]->name.c_str());
				}
			}

			ImGui::EndChild();

		}
		// Render Collider
		if (ImGui::Checkbox("##Collider", &colliderFlag)) {
			saveFlag = true;
		}
		ImGui::SameLine();
		if (ImGui::CollapsingHeader("Collider")) {
			ImGui::Indent();
			if (ImGui::InputFloat("ScaleX##", &colScaleX)) saveFlag = true;
			if (ImGui::InputFloat("ScaleY##", &colScaleY)) saveFlag = true;
			if (ImGui::InputFloat("Rotation##", &colRot)) saveFlag = true;
			ImGui::Unindent();
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
	static bool transformFlag, physicsFlag, logicFlag, colliderFlag;
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
				selected = objectFactory->GetGameObjectByID(gameobjID);
			}

			count++;
		}
		if (selected != nullptr) {
			int count2 = 0;
			if (selected->GetGameObjectID() != gameobjID) {
				gameobjID = selected->GetGameObjectID();
				std::map<size_t, GameObject*>::iterator it2 = copyMap.begin();
				for (; it2 != copyMap.end(); it2++) {
					if (it2->second->GetGameObjectID() == gameobjID) {
						selectedID = count2;
					}
					count2++;
				}
			}
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
			static float xPos = 0, yPos = 0, scaleX = 0, scaleY = 0, speed = 0, angle = 0, rotSpeed = 0;
			if (objectFactory->GetGameObjectIDMap().empty()) {
				ImGui::Text("No objects");
			}
			else {
				if (objectFactory->GetGameObjectByID(gameobjID) != nullptr) {
					ImGui::Text("Object ID: %d", objectFactory->GetGameObjectByID(gameobjID)->GetGameObjectID());
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::TRANSFORM) != -1) {

						xPos = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x;
						yPos = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y;
						scaleX = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale.x;
						scaleY = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale.y;
						angle = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->rotation;

					}
					else {
						xPos = yPos = scaleX = scaleY = angle = 0;
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
				ImGui::Text("ScaleX: %.2f", scaleX);
				ImGui::Text("ScaleY: %.2f", scaleY);
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
					objectFactory->AddComponent(ComponentType::PHYSICS_BODY, objectFactory->GetGameObjectByID(startIndex + i));
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
				if (objectFactory->GetGameObjectByID(gameobjID) != nullptr) {
					static float xPos2 = 0, yPos2 = 0, scale2 = 0, scaleY2 = 0, speed2 = 0, angle2 = 0, rotSpeed2 = 0;
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::TRANSFORM) != -1) {
						transformFlag = true;
					}
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::PHYSICS_BODY) != -1) {
						physicsFlag = true;
					}
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::LOGICCOMPONENT) != -1) {
						logicFlag = true;
					}
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::COLLIDER) != -1) {
						colliderFlag = true;
					}
					ImGui::Indent();
					if (ImGui::Checkbox("##Transform", &transformFlag)) {
						Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM);
						if (objTX != nullptr) {
							objectFactory->GetGameObjectByID(gameobjID)->RemoveComponent(objTX);
							transformFlag = false;
						}
						else {
							objectFactory->GetGameObjectByID(gameobjID)->AddComponent(new Transform(), ComponentType::TRANSFORM);
							objectFactory->GetGameObjectByID(gameobjID)->Initialize();
							transformFlag = true;
						}
					}
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Transform")) {
						if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::TRANSFORM) != -1) {
							xPos2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x;
							if (ImGui::SliderFloat("X-Position", &xPos2, static_cast<float>(-(windowSize.first / 2)), static_cast<float>(windowSize.first / 2), "%.2f")) { // Slider for X-Position
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.x = xPos2;
							}

							yPos2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y;
							if (ImGui::SliderFloat("Y-Position", &yPos2, static_cast<float>(-(windowSize.second / 2)), static_cast<float>(windowSize.second / 2), "%.2f")) { // Slider for Y-Position
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->position.y = yPos2;
							}

							scale2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale.x;
							if (ImGui::SliderFloat("Scale X %", &scale2, 0.0f, 500.0f, "%.2f")) { // Slider for Scale
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale.x = scale2;
							}

							scaleY2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale.y;
							if (ImGui::SliderFloat("Scale Y %", &scaleY2, 0.0f, 500.0f, "%.2f")) { // Slider for Scale
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->scale.y = scaleY2;
							}

							angle2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->rotation;
							if (ImGui::SliderFloat("Angle", &angle2, 0.0f, 360.0f, "%.2f")) { // Slider for true angle
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Transform, ComponentType::TRANSFORM)->rotation = angle2;
							}
						}
						else {
							ImGui::Text("Selected Object has no TRANSFORM component");
						}
					}


					ImGui::Unindent();



					ImGui::Indent();
					if (ImGui::Checkbox("##Physics", &physicsFlag)) {
						PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), PhysicsBody, ComponentType::PHYSICS_BODY);
						if (objBody != nullptr) {
							objectFactory->GetGameObjectByID(gameobjID)->RemoveComponent(objBody);
							physicsFlag = false;
						}
						else {
							objectFactory->GetGameObjectByID(gameobjID)->AddComponent(new PhysicsBody(), ComponentType::PHYSICS_BODY);
							objectFactory->GetGameObjectByID(gameobjID)->Initialize();
							physicsFlag = true;
						}
					}
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Physics Body")) {
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
					ImGui::Unindent();


					static std::string currentScriptName;
					static int currentScriptIndex;
					ImGui::Indent();
					if (ImGui::Checkbox("##Logic", &logicFlag)) {
						LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), LogicComponent, ComponentType::LOGICCOMPONENT);
						if (objLogic != nullptr) {
							objectFactory->GetGameObjectByID(gameobjID)->RemoveComponent(objLogic);
							logicFlag = false;
						}
						else {
							objectFactory->GetGameObjectByID(gameobjID)->AddComponent(new LogicComponent(), ComponentType::LOGICCOMPONENT);
							objectFactory->GetGameObjectByID(gameobjID)->Initialize();
							logicFlag = true;
						}


					}
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Logic")) {
						if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::LOGICCOMPONENT) != -1) {
							logicFlag = true;
							if (ImGui::BeginCombo("Scripts", currentScriptName.c_str())) {
								for (int i = 0; i < logicSystem->scriptVec.size(); i++) {
									bool isSelected = (i == currentScriptIndex);
									if (ImGui::Selectable(logicSystem->scriptVec[i]->name.c_str(), isSelected)) {
										currentScriptIndex = i;
										currentScriptName = logicSystem->scriptVec[i]->name;
									}

									if (isSelected) {
										ImGui::SetItemDefaultFocus();
									}
								}
								ImGui::EndCombo();
							}
							ImGui::SameLine();
							LogicComponent* objectLogic = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), LogicComponent, ComponentType::LOGICCOMPONENT);
							if (ImGui::Button("Add Script")) {
								objectLogic->scriptIndexSet.insert(currentScriptIndex);
							}
							ImGui::SameLine();
							if (ImGui::Button("Delete Script")) {
								objectLogic->scriptIndexSet.erase(currentScriptIndex);
							}

							if (objectLogic != nullptr) {
								for (std::set<unsigned int>::iterator it = objectLogic->scriptIndexSet.begin(); it != objectLogic->scriptIndexSet.end(); it++) {
									ImGui::Text(logicSystem->scriptVec[*it]->name.c_str());
								}
							}
						}
						else {
							ImGui::Text("Selected Object has no LOGIC component");
						}
					}
					ImGui::Unindent();


					ImGui::Indent();
					if (ImGui::Checkbox("##Collider", &colliderFlag)) {
						Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Collider, ComponentType::COLLIDER);
						if (objCollider != nullptr) {
							objectFactory->GetGameObjectByID(gameobjID)->RemoveComponent(objCollider);
							colliderFlag = false;
						}
						else {
							objectFactory->GetGameObjectByID(gameobjID)->AddComponent(new Collider(), ComponentType::COLLIDER);
							objectFactory->GetGameObjectByID(gameobjID)->Initialize();
							colliderFlag = true;
						}
					}
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Collider")) {
						static float colliderScaleX, colliderScaleY;
						if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::COLLIDER) != -1) {
							colliderScaleX = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Collider, ComponentType::COLLIDER)->tx->scale.x;
							if (ImGui::SliderFloat("Collider Scale X", &colliderScaleX, 0.0f, 1000.0f, "%.2f")) { // Slider for Speed
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Collider, ComponentType::COLLIDER)->tx->scale.x = colliderScaleX;
							}


							colliderScaleY = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Collider, ComponentType::COLLIDER)->tx->scale.y;
							if (ImGui::SliderFloat("Collider Scale Y", &colliderScaleY, 0.0f, 1000.0f, "%.2f")) { // Slider for Speed
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), Collider, ComponentType::COLLIDER)->tx->scale.y = colliderScaleY;
							}
						}
						else {
							ImGui::Text("Selected Object has no COLLIDER component");
						}
					}
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
	ImVec2 panelSize = ImGui::GetContentRegionAvail();

	static std::string currFilePath = FILEPATH_MASTER;
	static bool validPath = true;

	if (ImGui::InputText("##FilePath", &browserInputPath, ImGuiInputTextFlags_EnterReturnsTrue) || (ImGui::SameLine(), ImGui::Button("Go")) || browserDoubleClicked) {  // Enter if "enter" is pressed
		browserSelectedItem = "";
		if (std::filesystem::exists(browserInputPath) && std::filesystem::is_directory(browserInputPath)) {
			currFilePath = browserInputPath;
			validPath = true;
			std::cout << currFilePath << std::endl;
		}
		else {
			validPath = false;
			std::cout << "invalid path" << std::endl;

		}
		browserDoubleClicked = false;
	}

	ImGui::SameLine();
	if (ImGui::Button("Back")) {
		browserSelectedItem = "";
		std::filesystem::path temp = currFilePath;
		if (std::filesystem::exists(temp) && temp.string() != FILEPATH_MASTER) {
			browserInputPath = temp.parent_path().string();
			currFilePath = browserInputPath;
			validPath = true;
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Home")) {
		browserInputPath = FILEPATH_MASTER;
		currFilePath = browserInputPath;
		browserSelectedItem = "";
		validPath = true;
	}

	ImGui::SameLine();
	ImGui::Spacing();
	if (ImGui::Button("Add File")) {
		// Get absolute path of working directory
		std::filesystem::path exePath = std::filesystem::current_path();
		std::filesystem::path addToPath = exePath / currFilePath;
		// Windows API to handle dialog box
		HWND hwnd = GetActiveWindow();
		OPENFILENAME ofn;
		wchar_t szFile[MAX_PATH] = L"";
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		// Open dialog box
		if (GetOpenFileName(&ofn)) {
			std::wstring selectedFilePath(szFile);
			// Construct the destination path
			std::wstring destinationPath = addToPath.wstring() + L"\\" + std::filesystem::path(selectedFilePath).filename().wstring();

			// Check if the source file exists
			if (std::filesystem::exists(selectedFilePath)) {
				// Copy file to destination directory
				std::filesystem::copy(selectedFilePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
				// Construct and display message
				std::wstring test(currFilePath.begin(), currFilePath.end());
				LPCWSTR boxMessage = (L"File added to \"" + test + L"\" folder!").c_str();
				MessageBox(hwnd, boxMessage, L"Success", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hwnd, L"Error adding file to folder: Souce file does not exist!", L"Failure", MB_OK | MB_ICONERROR);
			}
		}
		// Rset working directory to the project folder
		std::filesystem::current_path(exePath);
	}

	ImGui::SameLine();
	if (ImGui::Button("Delete Selected") && browserSelectedItem != "") {
		ImGui::OpenPopup("NO TAKEBACKS");
	}
	if (ImGui::BeginPopupModal("NO TAKEBACKS", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		static std::string msg("Are you sure you want to delete the selected item:\n\n" + browserSelectedItem + "\n\nIf u fk everything up by deleting a prefab etc., go settle yourself!");
		ImGui::TextWrapped(msg.c_str());
		ImGui::Separator();

		// Show confirm button
		ImGui::PushStyleColor(ImGuiCol_Button, redColour);
		if (ImGui::Button("Confirm Deletion")) {
			if (!browserSelectedItem.empty()) { // Double check for non selection
				// Concat deletion path
				std::filesystem::path pathToDelete = std::filesystem::current_path() / browserInputPath / browserSelectedItem;
				if (std::filesystem::exists(pathToDelete)) {
					if (std::filesystem::is_directory(pathToDelete)) {
						std::filesystem::remove_all(pathToDelete); // remove_all for directories
					}
					else {
						std::filesystem::remove(pathToDelete); // remove for individual files
					}
					ImGui::CloseCurrentPopup(); // Close the popup when done					
				}
				else {
					std::cout << "File does not exist!";
				}
			}
		}
		ImGui::PopStyleColor();
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	ImGui::BeginChild("BrowserPane", ImVec2(panelSize.x, 0), true);
	if (validPath) {
		RenderDirectoryV2(currFilePath);
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Text, redColour);
		ImGui::Text("INVALID PATH");
		ImGui::PopStyleColor();
	}
	ImGui::EndChild();


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
			ImGui::PushStyleColor(ImGuiCol_Text, bananaColour);
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
		static const char* chartLabels[] = { "Physics", "Graphics" , "Sound", "Particles", "Scene Manager", "Collider", "Transform" };
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

//// Recursive helper function to render the file directory for the asset browser	
//void Editor::RenderDirectory(const std::string& filePath) {
//	std::filesystem::path dirPath(filePath);
//	if (std::filesystem::exists(dirPath)) {
//		// Render folder directories
//		for (auto& entry : std::filesystem::directory_iterator(dirPath)) {
//			if (entry.is_directory()) {
//				if (ImGui::TreeNode(entry.path().filename().string().c_str())) {
//					RenderDirectory(entry.path().string());
//					ImGui::TreePop();
//				}
//			}
//		}
//		// Render individual files
//		for (auto& entry : std::filesystem::directory_iterator(filePath)) {
//			if (!entry.is_directory()) {
//				ImGui::Selectable(entry.path().filename().string().c_str());
//			}
//		}
//	}
//	else {
//		std::cout << "File path does not exist. Maybe check the working directory" << std::endl;
//	}
//}

void Editor::RenderDirectoryV2(const std::string& filePath) {
	// Calculate how many icons per column
	float gridSize = iconSize + iconPadding;
	ImVec2 panelSize = ImGui::GetContentRegionAvail();
	int colCount = static_cast<int>(panelSize.x / gridSize);
	if (colCount < 1) {
		colCount = 1;
	}
	// Set render columns
	ImGui::Columns(colCount, 0, false);

	for (auto& entry : std::filesystem::directory_iterator(filePath)) {
		const std::string entryName = entry.path().filename().string();
		const bool isDirectory = entry.is_directory();

		// Use folder or file icon texture
		ImTextureID iconTexture = isDirectory ? reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture(TEST1))) : reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture(TEST2)));

		// Change button style if entry is selected
		if (browserSelectedItem == entryName) {
			// Yellow with opacity differences for visuals
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 0.0f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 0.0f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 0.0f, 0.8f));
		}

		// Render button
		ImGui::ImageButton(iconTexture, ImVec2(iconSize, iconSize));

		// Reset button style
		if (browserSelectedItem == entryName) {
			ImGui::PopStyleColor(3);
		}

		if (ImGui::IsItemHovered()) {
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) { // On double click
				if (isDirectory) {
					// Handle directory click
					browserInputPath = entry.path().string();
					browserDoubleClicked = true;
					browserSelectedItem = "";
				}
				else {
					// Handle file click

				}
			}
			else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) { // On single click
				// Handle single click on any item
				browserSelectedItem = entryName;
			}

		}
		ImGui::TextWrapped(entryName.c_str());
		ImGui::NextColumn();
	}
	ImGui::Columns(1);
}