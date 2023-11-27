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
#include "Collision.h"
#include "Cheats.h"
#include "HealthSystem.h"
#define PI 3.141592653589793

 // Defining static variables
bool Editor::editorOn;
bool Editor::fileBrowserOpen;
bool Editor::consoleEntered;
bool Editor::itemDrag;
bool Editor::gameWindowHover;
bool Editor::mismatchPayload;
Editor::SystemTime Editor::timeRecorder;

std::vector<float> Editor::fpsData;
std::pair<int, int> Editor::gameWindowOrigin;
std::pair<int, int> Editor::gameWindowSize;
std::vector<std::string> prefabList;
std::string Editor::browserInputPath;
std::string Editor::consoleTextInput;
bool Editor::browserDoubleClicked;
std::string Editor::browserSelectedItem;
GameObject* Editor::selected;
std::map<std::string, LPCWSTR> Editor::fileFilterList;
std::map<std::string, std::string> Editor::iconExtList;

OpenGLObject Editor::selectedOutline;
OpenGLObject Editor::selectedOutline1;
OpenGLObject Editor::selectedOutline2;
OpenGLObject Editor::selectedOutline3;
OpenGLObject Editor::selectedOutline4;
OpenGLObject Editor::rotatedWidget;

// Editor settings
int Editor::EditorSettings::iconSize{ 128 };
int Editor::EditorSettings::iconPadding{ 16 };
int Editor::EditorSettings::pieChartDisplayCount{ 5 };
int Editor::EditorSettings::dataAvgPeriod{ 1 };
float scaleOutline = 30.f;

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
 
	if (!io.Fonts->Fonts.empty()) {
		io.FontDefault = io.Fonts->Fonts[0];
	}
	
	// Config Flags
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup bindins
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init(glsl_vers);
	std::cout << "ImGui Successfully initialized" << std::endl;
}


/**************************************************************************
* @brief This function loads fonts for use with ImGui Editor
* @return void
*************************************************************************/
void UsingImGui::LoadFonts() {
	ImGuiIO& io = ImGui::GetIO();
	for (const auto& entry : std::filesystem::directory_iterator(FILEPATH_FONTS)) {
		std::string extName = entry.path().extension().string();
		std::transform(extName.begin(), extName.end(), extName.begin(), ::tolower);
		if (extName == ".ttf" || extName == ".otf") {
			io.Fonts->AddFontFromFileTTF(entry.path().string().c_str(), 20.0f);
		}
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
	
	if (panelList.consolePanel && !inputSystem.cheater) {
		inputSystem.cheater = panelList.consolePanel;
	}
	else
		panelList.consolePanel = inputSystem.cheater;

	if (panelList.consolePanel) {
		Editor::CreateConsolePanel();
	}

	//Editor::selectedOutline.Draw(std::string(""), true);
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backupContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupContext);
	}
	
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
	fileBrowserOpen = false;
	Editor::selectedOutline.InitObjects();
	SetFileFilters();
	SetIconExtList();
}


/**************************************************************************
* @brief This function loads fonts for use with ImGui Editor
* @return void
*************************************************************************/
void Editor::SetFileFilters() {
	fileFilterList.clear();
	fileFilterList.insert(std::make_pair(FILEPATH_MASTER, L"All Files (*.*)\0*.*\0"));
	fileFilterList.insert(std::make_pair(FILEPATH_FONTS, L"Font Files (*.ttf; *.otf)\0*.ttf;*.otf\0"));
	fileFilterList.insert(std::make_pair(FILEPATH_TEXTURES, L"Image Files (*.jpg; *.jpeg; *.png; *.gif)\0*.jpg;*.jpeg;*.png;*.gif\0"));
	fileFilterList.insert(std::make_pair(FILEPATH_SPRITES, fileFilterList[FILEPATH_TEXTURES]));
	fileFilterList.insert(std::make_pair(FILEPATH_SOUNDS_BGM, L"Audio Files (*.mp3; *.wav; *.ogg; *.FLAC)\0*.mp3; *.wav; *.ogg; *.FLAC\0"));
	fileFilterList.insert(std::make_pair(FILEPATH_SOUNDS_SFX, fileFilterList[FILEPATH_SOUNDS_BGM]));
	fileFilterList.insert(std::make_pair(FILEPATH_SCENES, L"Text Files (*.JSON)\0*.JSON\0"));
	fileFilterList.insert(std::make_pair(FILEPATH_PREFABS, L"Text Files (*.JSON)\0*.JSON\0"));
}


/**************************************************************************
* @brief This function sets up the different file icons to be used with the various extension types
* @return void
*************************************************************************/
void Editor::SetIconExtList() {
	iconExtList.clear();
	iconExtList.insert(std::make_pair(".ttf", "font_icon"));
	iconExtList.insert(std::make_pair(".otf", "font_icon"));
	iconExtList.insert(std::make_pair(".frag", "frag_icon"));
	iconExtList.insert(std::make_pair(".vert", "vert_icon"));
	iconExtList.insert(std::make_pair(".JSON", "json_icon"));
	iconExtList.insert(std::make_pair(".mp3", "audio_icon"));
	iconExtList.insert(std::make_pair(".wav", "audio_icon"));
	iconExtList.insert(std::make_pair(".ogg", "audio_icon"));
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

	static bool translateMode = false;
	static bool scaleMode = false;
	static bool scaleMode2 = false;
	static bool scaleMode3 = false;
	static bool scaleMode4 = false;
	static bool rotateMode = false;
	std::map<size_t, GameObject*> copyMap = objectFactory->GetGameObjectIDMap();
	std::pair<int, int> xBounds = std::pair<int, int>(Editor::gameWindowOrigin.first, Editor::gameWindowSize.first);
	std::pair<int, int> yBounds = std::pair<int, int>(Editor::gameWindowOrigin.second, (Editor::gameWindowSize.second));
	if ((ogMouseX > xBounds.first && ogMouseX < xBounds.second) && (ogMouseY > yBounds.first && ogMouseY < yBounds.second)) {
		for (std::pair<size_t, GameObject*> gObj : objectFactory->GetGameObjectIDMap()) {
			Transform* tx = GET_COMPONENT(gObj.second, Transform, ComponentType::TRANSFORM);
			if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1)) {
				if (tx != nullptr) {
					if (CollisionPointRotateRect(tx->position, tx->scale.x, tx->scale.y, mouseX, mouseY, tx->rotation)) {
						if (translateMode != true && scaleMode != true && scaleMode2 != true && scaleMode3 != true && scaleMode4 != true && rotateMode != true && itemDrag != true) {
							selected = gObj.second;
						}
						break;
					}
				}
			}

		}
	}
	Vec2 rightGizmoPos = Vec2(0, 0);
	Vec2 leftGizmoPos = Vec2(0, 0);
	Vec2 topGizmoPos = Vec2(0, 0);
	Vec2 botGizmoPos = Vec2(0, 0);
	Vec2 rotateGizmoPos = Vec2(0, 0);
	//detecting what action the user wants to take
	static bool buttonDown = false;
	static bool holdDown = false;
	static bool canReleaseSelect = false;
	if (selected != nullptr) {
		Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
		if (tx != nullptr && (ogMouseX > xBounds.first && ogMouseX < xBounds.second) && (ogMouseY > yBounds.first && ogMouseY < yBounds.second)) {		
			rightGizmoPos = tx->position + Vector2DRotate(Vec2(tx->scale.x / 2.f + scaleOutline, 0), tx->rotation, Vec2(0, 0));
			leftGizmoPos = tx->position - Vector2DRotate(Vec2((tx->scale.x / 2.f) + scaleOutline, 0), tx->rotation, Vec2(0, 0));
			topGizmoPos = tx->position + Vector2DRotate(Vec2(0, (tx->scale.y / 2.f) + scaleOutline), tx->rotation, Vec2(0, 0));
			botGizmoPos = tx->position - Vector2DRotate(Vec2(0, (tx->scale.y / 2.f) + scaleOutline), tx->rotation, Vec2(0, 0));
			rotateGizmoPos = tx->position + Vector2DRotate(Vec2(0, (tx->scale.y / 2.f) + (3 * scaleOutline)), tx->rotation, Vec2(0, 0));
			if (canReleaseSelect && holdDown && inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
				holdDown = false;
				canReleaseSelect = false;
				selected = nullptr;
			}
			if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) && gameWindowHover) {
				holdDown = true;
				if (translateMode != true && scaleMode != true && scaleMode2 != true && scaleMode3 != true && scaleMode4 != true && rotateMode != true && itemDrag != true){
					if (CollisionPointRotateRect(tx->position, tx->scale.x + scaleOutline, tx->scale.y + scaleOutline, mouseX, mouseY, tx->rotation)) {
						translateMode = true;
					}
					else if (CollisionPointRotateRect(rightGizmoPos, scaleOutline, tx->scale.y + scaleOutline, mouseX, mouseY, tx->rotation)) {
						scaleMode = true;
					}
					else if (CollisionPointRotateRect(leftGizmoPos, scaleOutline, tx->scale.y + scaleOutline, mouseX, mouseY, tx->rotation)) {
						scaleMode2 = true;
					}
					else if (CollisionPointRotateRect(topGizmoPos, tx->scale.x + scaleOutline, scaleOutline, mouseX, mouseY, tx->rotation)) {
						scaleMode3 = true;
					
					}
					else if (CollisionPointRotateRect(botGizmoPos, tx->scale.x + scaleOutline, scaleOutline, mouseX, mouseY, tx->rotation)) {
						scaleMode4 = true;
					}
					else if (CollisionPointRotateRect(rotateGizmoPos, scaleOutline, scaleOutline, mouseX, mouseY, tx->rotation)) {
						rotateMode = true;
					}
					else {
						canReleaseSelect = true;
					}
				}	
			}
			else {
				holdDown = false;
			}
		}
		if (tx != nullptr) {
			DrawGizmos(tx->scale.x, tx->scale.y, tx->position, tx->rotation);
		}	
	}
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
					tx->position = Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
				}
			}
		}
	}
	//scale x
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
					Vec2 edgePt = tx->position + Vec2(tx->scale.x / 2.f, 0);
					edgePt = Vector2DRotate(edgePt, tx->rotation, Vec2(0,0));
					Vec2 dir = edgePt - tx->position;
					Vector2DNormalize(dir, dir);

					float dp = Vector2DDotProduct(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position, Vec2(1, 0));
					float mags = Vector2DLength(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position) * Vector2DLength(Vec2(1, 0));
					float angle = acosf(dp / mags);
					angle = angle * static_cast<float>((180.f / PI));
					if (tx->rotation > 180.f) {
						angle = 360.f - angle;
					}
					Vec2 mouseVec = Vector2DRotate(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)), -angle, Vec2(0,0));
					
					float displacement = (mouseVec.x - (tx->position.x + tx->scale.x / 2));
					tx->scale.x += displacement;
					if (tx->scale.x < 0) {
						tx->scale.x = 0;
					}
				}
			}
		}
	}
	//scale x
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
					Vec2 edgePt = tx->position - Vec2(tx->scale.x / 2.f, 0);
					edgePt = Vector2DRotate(edgePt, tx->rotation, Vec2(0, 0));
					Vec2 dir = edgePt - tx->position;
					Vector2DNormalize(dir, dir);

					float dp = Vector2DDotProduct(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position, Vec2(1, 0));
					float mags = Vector2DLength(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position) * Vector2DLength(Vec2(1, 0));
					float angle = acosf(dp / mags);
					angle = angle * static_cast<float>((180.f / PI));
					if (tx->rotation < 180.f) {
						angle = 360.f - angle;
					}
					Vec2 mouseVec = Vector2DRotate(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)), 180 - angle, Vec2(0, 0));

					if (mouseVec.x < (tx->position.x - tx->scale.x / 2)) {
						tx->scale.x += abs((mouseVec.x - (tx->position.x - tx->scale.x / 2)));
					}
					else {
						tx->scale.x -= abs((mouseVec.x - (tx->position.x - tx->scale.x / 2)));
					}
					if (tx->scale.x < 0) {
						tx->scale.x = 0;
					}
				}
			}
		}
	}
	//scale left
	if (scaleMode3) {
		if (selected != nullptr) {
			Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
					buttonDown = true;
				}
				else {
					buttonDown = false;
					scaleMode3 = false;
				}

				if (buttonDown) {
					Vec2 edgePt = tx->position + Vec2(0, tx->scale.y / 2.f);
					edgePt = Vector2DRotate(edgePt, tx->rotation, Vec2(0, 0));
					Vec2 dir = edgePt - tx->position;
					Vector2DNormalize(dir, dir);

					float dp = Vector2DDotProduct(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position, Vec2(0, 1));
					float mags = Vector2DLength(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position) * Vector2DLength(Vec2(0, 1));
					float angle = acosf(dp / mags);
					angle = angle * static_cast<float>((180 / PI));
					if (tx->rotation > 180.f) {
						angle = 360.f - angle;
					}
					Vec2 mouseVec = Vector2DRotate(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)), -angle, Vec2(0, 0));
					tx->scale.y += (mouseVec.y - (tx->position.y + tx->scale.y / 2));
					if (tx->scale.y < 0) {
						tx->scale.y = 0;
					}
				}
			}
		}
	}
	//scale left
	if (scaleMode4) {
		if (selected != nullptr) {
			Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
					buttonDown = true;
				}
				else {
					buttonDown = false;
					scaleMode4 = false;
				}
				if (buttonDown) {
					Vec2 edgePt = tx->position - Vec2(0, tx->scale.y / 2.f);
					edgePt = Vector2DRotate(edgePt, tx->rotation, Vec2(0, 0));
					Vec2 dir = edgePt - tx->position;
					Vector2DNormalize(dir, dir);

					float dp = Vector2DDotProduct(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position, Vec2(0, 1));
					float mags = Vector2DLength(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position) * Vector2DLength(Vec2(0, 1));
					float angle = acosf(dp / mags);
					angle = angle * static_cast<float>((180.f / PI));
					if (tx->rotation < 180.f) {
						angle = 360.f - angle;
					}
					Vec2 mouseVec = Vector2DRotate(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)),180 - angle, Vec2(0, 0));
					if (mouseVec.y < (tx->position.y - tx->scale.y / 2)) {
						tx->scale.y += abs((mouseVec.y - (tx->position.y - tx->scale.y / 2)));
					}
					else {
						tx->scale.y -= abs((mouseVec.y - (tx->position.y - tx->scale.y / 2)));
					}
					if (tx->scale.y < 0) {
						tx->scale.y = 0;
					}
				}
			}
		}
	}
	if (rotateMode) {
		if (selected != nullptr) {
			Transform* tx = GET_COMPONENT(selected, Transform, ComponentType::TRANSFORM);
			if (tx != nullptr) {
				if (inputSystem.GetMouseState(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
					buttonDown = true;
				}
				else {
					buttonDown = false;
					rotateMode = false;
				}
				if (buttonDown) {
						float dp = Vector2DDotProduct(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position, Vec2(0,1));
					float mags = Vector2DLength(Vec2(static_cast<float>(mouseX), static_cast<float>(mouseY)) - tx->position) * Vector2DLength(Vec2(0,1));
					float angle = acosf(dp / mags);
					angle = angle * static_cast<float>((180.f / PI));
					if (mouseX > tx->position.x) {
						angle = 360.f - angle;
					}
					tx->rotation = angle;
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
	itemDrag = false;
}

/* ============================================
	CREATING INDIVIDUAL DOCKABLE IMGUI PANELS
   ============================================ */
/**************************************************************************
* @brief This function renders the menu bar at the top of the window
* @return void
*************************************************************************/
void Editor::CreateMenuBar() {
	static bool showAssBrowserSettings = false;
	static bool showPerformanceSettings = false;
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Create")) {}
			if (ImGui::MenuItem("Save")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings")) {
			if (ImGui::MenuItem("Asset Browser##1")) {
				showAssBrowserSettings = true;
			}
			if (ImGui::MenuItem("Performance Info")) {
				showPerformanceSettings = true;
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
			EditorSettings::iconSize = static_cast<int>(std::powf(2.0f, static_cast<float>(exp1)));
		}
		if (ImGui::SliderInt("Icon Padding", &exp2, 0, 10)) {
			EditorSettings::iconPadding = static_cast<int>(std::powf(2.0f, static_cast<float>(exp2)));
		}
		ImGui::End();
	}
	if (showPerformanceSettings) {
		ImGui::Begin("Performance Viewer Settings", &showPerformanceSettings);
		ImGui::PushItemWidth(ImGui::GetWindowWidth() / 3);
		ImGui::SliderInt("Pie Chart Item Count", &EditorSettings::pieChartDisplayCount, 0, 10);
		ImGui::SliderInt("Data AVG period", &EditorSettings::dataAvgPeriod, 0, 5);
		ImGui::PopItemWidth();
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
	ImGui::Checkbox("Console Panel", &panelList.consolePanel); // Checkbox for console panel

	if (ImGui::Button("Do Something")) {

	}


	ImGui::SeparatorText("Scene Controls");
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
	// Save level to file
	if (ImGui::Button("Save scene")) {
		// Get rapidjson documents of tilemap and game objects
		rapidjson::Document tilemapDoc = tilemapLoader->SaveTilemap(sceneFileName);
		rapidjson::Document const& objectDoc = objectFactory->GetObjectDocSaving(sceneFileName);
		rapidjson::Document::AllocatorType& allocator = tilemapDoc.GetAllocator();
		
		// Merge game objects document into tilemap document
		for (auto& member : objectDoc.GetObj()) {
			if (!tilemapDoc.HasMember(member.name)) {
				rapidjson::Value key(member.name, allocator);
				rapidjson::Value value;
				value.CopyFrom(member.value, allocator);
				tilemapDoc.AddMember(key, value, allocator);
			}
		}

		// Save data to JSON file
		JsonSerializer serializer;
		if (serializer.WriteJSONFile(sceneFileName, tilemapDoc)) {
			std::cout << "Successfully saved objects to file." << std::endl;
		}
	}
	ImGui::SameLine();
	// Load level from file
	if (ImGui::Button("Load scene")) {
		sysManager->isPaused = false;
		objectFactory->DestroyAllObjects();
		tilemapLoader->LoadTilemap(sceneFileName);
		objectFactory->BuildObjectFromFile(sceneFileName);
		tilemapLoader->CreateGrid();
		healthSys->ClearHealthbar();
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
		ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) ? gameWindowHover = true : gameWindowHover = false;
		gameWindowOrigin.first = static_cast<int>(ImGui::GetWindowPos().x);
		gameWindowOrigin.second = static_cast<int>(ImGui::GetWindowPos().y);
		gameWindowSize.first = static_cast<int>(ImGui::GetWindowSize().x);
		gameWindowSize.second = static_cast<int>(ImGui::GetWindowSize().y);

		// Get draw size of window
		ImVec2 wsize = ImGui::GetWindowSize();
		// Invert V from openGL
		ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(OpenGLObject::FrameTexture)), wsize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f)); // Replace thirdTexture with handle to FBO when graphics done rendering to FBO	

		// Setup drag and drop checks within window
		if (ImGui::BeginDragDropTarget()) {
			const ImGuiPayload* payload = ImGui::GetDragDropPayload();
			// OBJECT IS SELECTED
			if (selected != nullptr) {
				if (!selected->IsUsingSprite()) { // Selected object utilizes textures
					// Payload matches object type (Texture onto a texture)
					if (payload->IsDataType("PAYLOAD_TEXTURE")) {
						mismatchPayload = false;
						if (const ImGuiPayload* droppedPayload = ImGui::AcceptDragDropPayload("PAYLOAD_TEXTURE")) {
							std::string dropTextureName = static_cast<const char*>(droppedPayload->Data);
							selected->SetTexture(dropTextureName);
						}
					} // Payload mismatch object type (Anything else onto a texture)
					else {
						// ERROR ICON IMPLEMENTATION
						mismatchPayload = true;
					}
				}
				else if (selected->IsUsingSprite()) { // Selected object utilizes sprites
					// Payload matchers object type (Sprite onto a sprite)
					if (payload->IsDataType("PAYLOAD_SPRITE")) {
						mismatchPayload = false;
						if (const ImGuiPayload* droppedPayload = ImGui::AcceptDragDropPayload("PAYLOAD_SPRITE")) {
							std::string dropSpriteName = static_cast<const char*>(droppedPayload->Data);
							selected->SetTexture(dropSpriteName);
						}
					} // Payload mismatch object type (Anything else onto a sprite)
					else {
						// ERROR ICON IMPLEMENTATION
						mismatchPayload = true;
					}
				}
				else if (payload->IsDataType("PAYLOAD_UNKNOWN")) {
					mismatchPayload = true;					
				}
			}
			else { // NO OBJECT SELECTED
				if (payload->IsDataType("PAYLOAD_AUDIO_BGM")) {
					mismatchPayload = false;
					if (const ImGuiPayload* droppedPayload = ImGui::AcceptDragDropPayload("PAYLOAD_AUDIO_BGM")) {
						std::string dropBGMName = static_cast<const char*>(droppedPayload->Data);
						soundManager->StopAll();
						soundManager->PlayBGM(dropBGMName);
					}				
				}
				else if (payload->IsDataType("PAYLOAD_AUDIO_SFX")) {
					mismatchPayload = false;
					if (const ImGuiPayload* droppedPayload = ImGui::AcceptDragDropPayload("PAYLOAD_AUDIO_SFX")) {
						std::string dropSFXName = static_cast<const char*>(droppedPayload->Data);
						soundManager->PlaySFX(dropSFXName);
					}
				}
				else if (payload->IsDataType("PAYLOAD_SCENE")) {
					mismatchPayload = false;
					if (const ImGuiPayload* droppedPayload = ImGui::AcceptDragDropPayload("PAYLOAD_SCENE")) {
						std::string dropSceneName = static_cast<const char*>(droppedPayload->Data);
						sysManager->isPaused = false;
						dropSceneName = FILEPATH_SCENES + "\\" + dropSceneName;
						objectFactory->DestroyAllObjects();
						tilemapLoader->LoadTilemap(dropSceneName);
						objectFactory->BuildObjectFromFile(dropSceneName);
						tilemapLoader->CreateGrid();
					}
				}
			}
			itemDrag = false;
			ImGui::EndDragDropTarget();

		}
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
	static float phyRotSpeed, phySpeed, phyMass, phyFriction, transXpos, transYpos, transRot, transScaleX, transScaleY, colScaleX, colScaleY, colRot, aggRange;
	static int maxHp;
	static bool phyIsStatic, physicsFlag, transformFlag, logicFlag, colliderFlag, enemyfsmFlag, hpFlag, saveFlag, loadedFlag = false;

	static int currentScriptIndex;
	static std::set<unsigned int> tempLogicSet;
	static std::string currentScriptName;
	static bool initialized, deleteFlag = false;


	static std::string newPrefabName{}, newPrefabType{};

	std::map<std::string, Prefab*> copy = objectFactory->GetPrefabMap();
	std::map<std::string, Prefab*>::iterator it = copy.begin();
	static std::string selectedName = it->first;


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
		if (objFromPrefab != nullptr) {
			objFromPrefab->SetName(name);
		}
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
		Prefab* prefab{ new Prefab(name, name) };
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
		bool enemyfsmUpdateFlag = false; 
		bool hpUpdateFlag = false;
		
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

			// Handle saving/deleteion for enemy FSM component
			if (enemyfsmFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::ENEMY_FSM) == -1) {
				objectFactory->GetPrefabByName(selectedName)->AddComponent(new EnemyFSM(), ComponentType::ENEMY_FSM);
			}
			if (objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::ENEMY_FSM) != -1) {
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), EnemyFSM, ComponentType::ENEMY_FSM)->aggroRange = aggRange;
				enemyfsmUpdateFlag = true;
			}
			if (!enemyfsmFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::ENEMY_FSM) != -1) {
				objectFactory->GetPrefabByName(selectedName)->RemoveComponent(GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), EnemyFSM, ComponentType::ENEMY_FSM));
			}

			// Handle saving/deleteion for health component
			if (hpFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::HEALTH) == -1) {
				objectFactory->GetPrefabByName(selectedName)->AddComponent(new HealthComponent(), ComponentType::HEALTH);
			}
			if (objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::HEALTH) != -1) {
				GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), HealthComponent, ComponentType::HEALTH)->maxHealth = maxHp;
				hpUpdateFlag = true;
			}
			if (!hpFlag && objectFactory->GetPrefabByName(selectedName)->Has(ComponentType::HEALTH) != -1) {
				objectFactory->GetPrefabByName(selectedName)->RemoveComponent(GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), HealthComponent, ComponentType::HEALTH));
			}

			for (std::map<size_t, GameObject*>::iterator itGameObject = copyMap.begin(); itGameObject != copyMap.end(); itGameObject++) {
				if ((*itGameObject).second->GetType() == objectFactory->GetPrefabByName(selectedName)->GetType()) {
					Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID((*itGameObject).second->GetGameObjectID()), Transform, ComponentType::TRANSFORM);
					if (objTX != nullptr) {
						Transform* prefabTX = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Transform, ComponentType::TRANSFORM);

						objTX->scale = prefabTX->scale;
						objTX->position = prefabTX->position;
						objTX->rotation = prefabTX->rotation;
					}
					PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID((*itGameObject).second->GetGameObjectID()), PhysicsBody, ComponentType::PHYSICS_BODY);
					if (objBody != nullptr) {
						PhysicsBody* prefabBody = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), PhysicsBody, ComponentType::PHYSICS_BODY);
						objBody->rotationSpeed = prefabBody->rotationSpeed;
						objBody->mass = prefabBody->mass;
						objBody->frictionForce = prefabBody->frictionForce;
						objBody->speed = prefabBody->speed;
						objBody->isStatic = prefabBody->isStatic;
					}
					LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID((*itGameObject).second->GetGameObjectID()), LogicComponent, ComponentType::LOGICCOMPONENT);
					if (objLogic != nullptr) {
						LogicComponent* prefabLogic = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), LogicComponent, ComponentType::LOGICCOMPONENT);
						objLogic->scriptIndexSet = prefabLogic->scriptIndexSet;
					}
					Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID((*itGameObject).second->GetGameObjectID()), Collider, ComponentType::COLLIDER);
					if (objCollider != nullptr) {
						Collider* prefabCollider = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), Collider, ComponentType::COLLIDER);
						objCollider->tx->scale = prefabCollider->tx->scale;
						objCollider->tx->rotation = prefabCollider->tx->rotation;
					}
					EnemyFSM* objEnemyFSM = GET_COMPONENT(objectFactory->GetGameObjectByID((*itGameObject).second->GetGameObjectID()), EnemyFSM, ComponentType::ENEMY_FSM);
					if (objEnemyFSM != nullptr) {
						EnemyFSM* prefabFSM = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), EnemyFSM, ComponentType::ENEMY_FSM);
						objEnemyFSM->aggroRange = prefabFSM->aggroRange;
					}
					HealthComponent* objMaxHp = GET_COMPONENT(objectFactory->GetGameObjectByID((*itGameObject).second->GetGameObjectID()), HealthComponent, ComponentType::HEALTH);
					if (objMaxHp != nullptr) {
						HealthComponent* prefabMaxHp = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), HealthComponent, ComponentType::HEALTH);
						objMaxHp->maxHealth = prefabMaxHp->maxHealth;
					}

				}
			}
			objectFactory->SavePrefabsToFile(FILEPATH_PREFAB_DEFAULT);
			saveFlag = false;
			
		}
		if (ImGui::Button("Preview Changes")) {
			
			for (std::map<size_t, GameObject*>::iterator itPreview = copyMap.begin(); itPreview != copyMap.end(); itPreview++) {
				if ((*itPreview).second->GetType() == objectFactory->GetPrefabByName(selectedName)->GetType()) {
				
					Transform* objTX = GET_COMPONENT(objectFactory->GetGameObjectByID((*itPreview).second->GetGameObjectID()), Transform, ComponentType::TRANSFORM);
					if (objTX != nullptr) {
						objTX->scale.x = transScaleX;
						objTX->scale.y = transScaleY;
						objTX->position = Vec2(transXpos, transYpos);
						objTX->rotation = transRot;
					}
					PhysicsBody* objBody = GET_COMPONENT(objectFactory->GetGameObjectByID((*itPreview).second->GetGameObjectID()), PhysicsBody, ComponentType::PHYSICS_BODY);
					if (objBody != nullptr) {
						objBody->rotationSpeed = phyRotSpeed;
						objBody->speed = phySpeed;
						objBody->mass = phyMass;
						objBody->frictionForce = phyFriction;
						objBody->isStatic = phyIsStatic;
					}
					LogicComponent* objLogic = GET_COMPONENT(objectFactory->GetGameObjectByID((*itPreview).second->GetGameObjectID()), LogicComponent, ComponentType::LOGICCOMPONENT);
					if (objLogic != nullptr) {
						objLogic->scriptIndexSet = tempLogicSet;
					}
					Collider* objCollider = GET_COMPONENT(objectFactory->GetGameObjectByID((*itPreview).second->GetGameObjectID()), Collider, ComponentType::COLLIDER);
					if (objCollider != nullptr) {
						objCollider->tx->scale.x = colScaleX;
						objCollider->tx->scale.y = colScaleY;
						objCollider->tx->rotation = colRot;
					}
					EnemyFSM* objEnemyFSM = GET_COMPONENT(objectFactory->GetGameObjectByID((*itPreview).second->GetGameObjectID()), EnemyFSM, ComponentType::ENEMY_FSM);
					if (objEnemyFSM != nullptr) {
						objEnemyFSM->aggroRange = aggRange;
					}
					HealthComponent* objMaxHp = GET_COMPONENT(objectFactory->GetGameObjectByID((*itPreview).second->GetGameObjectID()), HealthComponent, ComponentType::HEALTH);
					if (objMaxHp != nullptr) {
						objMaxHp->maxHealth = maxHp;
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
				enemyfsmFlag = (copy[selectedName]->Has(ComponentType::ENEMY_FSM) != -1);
				hpFlag = (copy[selectedName]->Has(ComponentType::HEALTH) != -1);
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
				if (copy[selectedName]->Has(ComponentType::ENEMY_FSM) != -1) {
					aggRange = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), EnemyFSM, ComponentType::ENEMY_FSM)->aggroRange;
				}
				if (copy[selectedName]->Has(ComponentType::HEALTH) != -1) {
					maxHp = GET_PREFAB_COMPONENT(objectFactory->GetPrefabByName(selectedName), HealthComponent, ComponentType::HEALTH)->maxHealth;
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
			LogicComponent* prefabLogic = GET_PREFAB_COMPONENT(copy[selectedName], LogicComponent, ComponentType::LOGICCOMPONENT);
			if (prefabLogic != nullptr) {
				if (initialized == false) {
					tempLogicSet = prefabLogic->scriptIndexSet;
					initialized = true;
				}
				for (std::set<unsigned int>::iterator itLogic = tempLogicSet.begin(); itLogic != tempLogicSet.end(); itLogic++) {
					ImGui::Text(logicSystem->scriptVec[*itLogic]->name.c_str());
				}
			}
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
		// Render EnemyFSM
		if (ImGui::Checkbox("##EnemyFSM", &enemyfsmFlag)) {
			saveFlag = true;
		}
		ImGui::SameLine();
		if (ImGui::CollapsingHeader("Enemy FSM")) {
			ImGui::Indent();
			if (ImGui::InputFloat("Aggro Range", &aggRange)) saveFlag = true;
			ImGui::Unindent();
		}
		// Render HealthComponent
		if (ImGui::Checkbox("##HealthComponent", &hpFlag)) {
			saveFlag = true;
		}
		ImGui::SameLine();
		if (ImGui::CollapsingHeader("Health Component")) {
			ImGui::Indent();
			if (ImGui::InputInt("Max Health", &maxHp)) saveFlag = true;
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
	// Get copy of sound map
	auto soundMap = assetManager.GetSoundMap();
	// Do SFX stuff
	auto& sfxSounds = soundMap[SoundManager::SoundType::SFX];
	static std::string currSelectedSFX; 
	if (ImGui::BeginCombo("SFX Sounds", currSelectedSFX.c_str())) {
		for (const auto& soundPair : sfxSounds) {
			bool isSelected = (currSelectedSFX == soundPair.first);
			if (ImGui::Selectable(soundPair.first.c_str(), isSelected)) {
				currSelectedSFX = soundPair.first;
			}
			// Set focus
			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	if (ImGui::Button("Start##SFX")) {
		if (!currSelectedSFX.empty()) {
			soundManager->PlayAdvanced(currSelectedSFX, SoundManager::SoundType::SFX, 0.7f, false, SoundManager::SG2);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause##SFX")) {
		soundManager->PauseGroup(SoundManager::SG2);
	}
	ImGui::SameLine();
	if (ImGui::Button("Resume##SFX")) {
		soundManager->ResumeGroup(SoundManager::SG2);
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop##SFX")) {
		soundManager->StopGroup(SoundManager::SG2);
	}
	
	// Do BGM stuff
	auto& bgmSounds = soundMap[SoundManager::SoundType::BGM];
	static std::string currSelectedBGM;
	if (ImGui::BeginCombo("BGM Sounds", currSelectedBGM.c_str())) {
		for (const auto& soundPair : bgmSounds) {
			bool isSelected = (currSelectedBGM == soundPair.first);
			if (ImGui::Selectable(soundPair.first.c_str(), isSelected)) {
				currSelectedBGM = soundPair.first;
			}
			// Set focus
			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	if (ImGui::Button("Start##BGM")) {
		if (!currSelectedBGM.empty()) {
			soundManager->PlayAdvanced(currSelectedBGM, SoundManager::SoundType::BGM, 1.0f, true, SoundManager::SG3);
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause##BGM")) {
		soundManager->PauseGroup(SoundManager::SG3);
	}
	ImGui::SameLine();
	if (ImGui::Button("Resume##BGM")) {
		soundManager->ResumeGroup(SoundManager::SG3);
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop##BGM")) {
		soundManager->StopGroup(SoundManager::SG3);
	}
	if (ImGui::Button("Stop All")) {
		soundManager->StopAll();
	}
	ImGui::End();
}


/**************************************************************************
* @brief This function creates the object list used to modify objects
* @return void
*************************************************************************/
void Editor::CreateObjectList() {
	static bool transformFlag, physicsFlag, logicFlag, colliderFlag, enemyfsmFlag, hpFlag;
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
				if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::TRANSFORM) != -1) {
					selected = objectFactory->GetGameObjectByID(gameobjID);
				}
				
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
					ImGui::Text("Object Type: %s", objectFactory->GetGameObjectByID(gameobjID)->GetType().c_str());
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
					static float xPos2 = 0, yPos2 = 0, scale2 = 0, scaleY2 = 0, speed2 = 0, angle2 = 0, rotSpeed2 = 0, aggRange2 = 0;
					static int currentHp2= 0, maxHp2 = 0;
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
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::ENEMY_FSM) != -1) {
						enemyfsmFlag = true;
					}
					if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::HEALTH) != -1) {
						hpFlag = true;
					}

					// Transform Controls
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

					// Physics Controls
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

					// Logic Controls
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
								for (std::set<unsigned int>::iterator itScript = objectLogic->scriptIndexSet.begin(); itScript != objectLogic->scriptIndexSet.end(); itScript++) {
									ImGui::Text(logicSystem->scriptVec[*itScript]->name.c_str());
								}
							}
						}
						else {
							ImGui::Text("Selected Object has no LOGIC component");
						}
					}
					ImGui::Unindent();

					// Collider Controls
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
					ImGui::Unindent();

					// FSM Controls
					ImGui::Indent();
					if (ImGui::Checkbox("##EnemyFSM", &enemyfsmFlag)) {
						EnemyFSM* objEnemyFSM = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), EnemyFSM, ComponentType::ENEMY_FSM);
						if (objEnemyFSM != nullptr) {
							objectFactory->GetGameObjectByID(gameobjID)->RemoveComponent(objEnemyFSM);
							enemyfsmFlag = false;
						}
						else {
							objectFactory->GetGameObjectByID(gameobjID)->AddComponent(new EnemyFSM(), ComponentType::ENEMY_FSM);
							objectFactory->GetGameObjectByID(gameobjID)->Initialize();
							enemyfsmFlag = true;
						}
					}
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Enemy FSM")) {
						if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::ENEMY_FSM) != -1) {
							aggRange2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), EnemyFSM, ComponentType::ENEMY_FSM)->aggroRange;
							if (ImGui::SliderFloat("AggroRange", &aggRange2, 0.f, 500.f, "%.2f")) { // Slider for Aggro Range
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), EnemyFSM, ComponentType::ENEMY_FSM)->aggroRange = aggRange2;
							}
						}
						else {
							ImGui::Text("Selected Object has no ENEMY FSM component");
						}
					}
					ImGui::Unindent();

					// Health Component Controls
					ImGui::Indent();
					if (ImGui::Checkbox("##HealthComponent", &hpFlag)) {
						HealthComponent* objHp = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), HealthComponent, ComponentType::HEALTH);
						if (objHp != nullptr) {
							objectFactory->GetGameObjectByID(gameobjID)->RemoveComponent(objHp);
							hpFlag = false;
						}
						else {
							objectFactory->GetGameObjectByID(gameobjID)->AddComponent(new HealthComponent(), ComponentType::HEALTH);
							objectFactory->GetGameObjectByID(gameobjID)->Initialize();
							hpFlag = true;
						}
					}
					ImGui::SameLine();
					if (ImGui::CollapsingHeader("Health Component")) {
						if (objectFactory->GetGameObjectByID(gameobjID)->Has(ComponentType::HEALTH) != -1) {
							currentHp2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), HealthComponent, ComponentType::HEALTH)->currentHealth;
							if (ImGui::SliderInt("Current Health", &currentHp2, 0, maxHp2, "%d")) { // Slider for Current Health
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), HealthComponent, ComponentType::HEALTH)->currentHealth = currentHp2;
							}
							maxHp2 = GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), HealthComponent, ComponentType::HEALTH)->maxHealth;
							if (ImGui::SliderInt("Max Health", &maxHp2, 0, 10, "%d")) { // Slider for Max Health
								GET_COMPONENT(objectFactory->GetGameObjectByID(gameobjID), HealthComponent, ComponentType::HEALTH)->maxHealth = maxHp2;
							}
						}
						else {
							ImGui::Text("Selected Object has no HEALTH component");
						}
					}
					ImGui::Unindent();
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
		mismatchPayload = false;
		if (std::filesystem::exists(browserInputPath) && std::filesystem::is_directory(browserInputPath)) {
			currFilePath = browserInputPath;
			validPath = true;
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
		mismatchPayload = false;
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
		mismatchPayload = false;
		validPath = true;
	}

	ImGui::SameLine();
	if (ImGui::Button("Reload")) {
		assetManager.ReloadAll();
	}

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
		ofn.lpstrFilter = fileFilterList[currFilePath];
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		// Open dialog box
		fileBrowserOpen = true;
		if (GetOpenFileName(&ofn)) {
			std::wstring selectedFilePath(szFile);
			// Construct the destination path
			std::wstring destinationPath = addToPath.wstring() + L"\\" + std::filesystem::path(selectedFilePath).filename().wstring();

			// Check if the source file exists
			if (std::filesystem::exists(selectedFilePath)) {
				// Copy file to destination directory
				std::filesystem::copy(selectedFilePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
				// Construct and display message
				std::wstring temp(currFilePath.begin(), currFilePath.end());
				LPCWSTR boxMessage = (L"File added to \"" + temp + L"\" folder!").c_str();
				MessageBox(hwnd, boxMessage, L"Success", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hwnd, L"Error adding file to folder: Souce file does not exist!", L"Failure", MB_OK | MB_ICONERROR);
			}	
			// Rset working directory to the project folder
			std::filesystem::current_path(exePath);
			assetManager.ReloadAll();
		}
		fileBrowserOpen = false;	
	}

	ImGui::SameLine();
	if (ImGui::Button("Delete Selected") && browserSelectedItem != "") {
		ImGui::OpenPopup("NO TAKEBACKS");
	}

	if (currFilePath == FILEPATH_TEXTURES || currFilePath == FILEPATH_SPRITES) {
		ImGui::SameLine();
		HelpMarker("Drag and drop assets to load onto selected object");
	}

	if (ImGui::BeginPopupModal("NO TAKEBACKS", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		static std::string msg("Are you sure you want to delete the selected item:\n\n" + browserSelectedItem);
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
		static std::map<std::string, float> sysTimeAccumulators;
		static std::vector<std::pair<std::string, float>> avgSysTimes;
		static int sysTimeSampleCount = 0;
		//int sampleCounter = EditorSettings::dataAvgPeriod * 60;
		static std::vector<float> fpsSamples;
		static float timeAccumulator = 0.0f;
		// Record system times
		sysTimeAccumulators["Physics"] += timeRecorder.physicsTime / io.DeltaTime;
		sysTimeAccumulators["Graphics"] += timeRecorder.graphicsTime / io.DeltaTime;
		sysTimeAccumulators["Sound"] += timeRecorder.soundTime / io.DeltaTime;
		sysTimeAccumulators["Particles"] += timeRecorder.particlesTime / io.DeltaTime;
		sysTimeAccumulators["Scene Manager"] += timeRecorder.scenemanagerTime / io.DeltaTime;
		sysTimeAccumulators["Collider"] += timeRecorder.colliderTime / io.DeltaTime;
		sysTimeAccumulators["Transform"] += timeRecorder.transformTime / io.DeltaTime;
		sysTimeSampleCount++;
		std::vector<const char*> chartLabels;
		std::vector<float> data;
		// Record FPS
		fpsSamples.push_back(io.Framerate);
		timeAccumulator += io.DeltaTime;
		// Average out FPS
		static float avgFPS;
		// On avg period
		if (timeAccumulator >= EditorSettings::dataAvgPeriod) {
			avgFPS = std::accumulate(fpsSamples.begin(), fpsSamples.end(), 0.0f) / static_cast<float>(fpsSamples.size());
			avgSysTimes.clear();
			fpsSamples.clear();

			for (auto& [system, accumulatedTime] : sysTimeAccumulators) {
				float averageTime = accumulatedTime / static_cast<float>(sysTimeSampleCount);
				avgSysTimes.emplace_back(system, averageTime);
				sysTimeAccumulators[system] = 0.0f; // Reset accumulator for each system
			}
			// Sort times in descending order for pie chart
			std::sort(avgSysTimes.begin(), avgSysTimes.end(),
				[](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
					return a.second > b.second;
				});	

			size_t countToDisplay = std::min(static_cast<size_t>(EditorSettings::pieChartDisplayCount), avgSysTimes.size());
			for (size_t i = 0; i < countToDisplay; i++) {
				std::cout << avgSysTimes[i].second << std::endl;

			}
			sysTimeSampleCount = 0;
			timeAccumulator = 0.0f;
		}
		
		// FPS DATA	
		if (avgFPS < 60) {
			ImGui::PushStyleColor(ImGuiCol_Text, redColour);
		}
		else if (avgFPS >= 60 && avgFPS < 100) {
			ImGui::PushStyleColor(ImGuiCol_Text, bananaColour);
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, greenColour);
		}
		ImGui::Text("Program FPS: %.2f", avgFPS); // Display program FPS in "Performance" tab
		ImGui::PopStyleColor();
		ImGui::PushItemWidth(ImGui::GetWindowWidth() / 2);
		ImGui::PushStyleColor(ImGuiCol_PlotLines, pinkColour);
		ImGui::PlotLines("Average FPS", fpsData.data(), static_cast<int>(fpsData.size()), 0, "FPS", 0.0f, 300.0f, ImVec2(0, 80));
		ImGui::PopItemWidth();
		ImGui::PopStyleColor();
		// FRAME TIME DATA
		ImGui::Text("Frame time: %.2f ms", 1000.0f / GetFrames());// Display program FPS in "Performance" tab
		ImGui::Text("Program run time: %.2f", GetGameRunTime());
		ImGui::Separator();

		ImGui::Text("System Time Percentage");		

		if (!avgSysTimes.empty()) {
			chartLabels.clear();
			data.clear();
			size_t countToDisplay = std::min(static_cast<size_t>(EditorSettings::pieChartDisplayCount), avgSysTimes.size());
			for (size_t i = 0; i < countToDisplay; i++) {
				//std::cout << avgSysTimes[i].second << std::endl;
				chartLabels.push_back(avgSysTimes[i].first.c_str());
				data.push_back(avgSysTimes[i].second);
			}
		}

		static ImPlotPieChartFlags flags = 0;
		// Draw pie chart	
		if (ImPlot::BeginPlot("##PieSystemTime", ImVec2(ImGui::GetWindowWidth(), 250), ImPlotFlags_Equal | ImPlotFlags_NoMouseText)) {
			ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
			ImPlot::SetupAxesLimits(0, 1, 0, 1);
			ImPlot::PlotPieChart(chartLabels.data(), data.data(), static_cast<int>(data.size()), 0.5, 0.5, 0.4, "%.2f", 90, flags);
			ImPlot::EndPlot();
		}	

		if (ImGui::CollapsingHeader("Tools")) {

			static bool drawBB = false;
			static size_t gameobjID = 0;
			ImGui::Checkbox("Display bounding box", &drawBB);

			if (drawBB) {

				OpenGLObject::renderBoundingBox = true;
			}
			else {
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
	}
		ImGui::End();
}


/**************************************************************************
* @brief This function renders file directories
* @param[in] filePath - Current file path of the asset browser
* @return void
*************************************************************************/
void Editor::RenderDirectoryV2(const std::string& filePath) {
	// Calculate how many icons per column
	float gridSize = static_cast<float>(EditorSettings::iconSize + EditorSettings::iconPadding);
	ImVec2 panelSize = ImGui::GetContentRegionAvail();
	int colCount = static_cast<int>(panelSize.x / gridSize);
	if (colCount < 1) {
		colCount = 1;
	}
	// Set render columns
	ImGui::Columns(colCount, 0, false);
	
	for (auto& entry : std::filesystem::directory_iterator(filePath)) {
		const bool isDirectory = entry.is_directory();
		const std::string entryName = entry.path().filename().string();			
		const std::string entryExt = entry.path().extension().string();
		std::string texNameWithoutExt = entry.path().stem().string();
		// Set correct icons
		ImTextureID iconTexture = nullptr;
		if (isDirectory && entry.path().string() != FILEPATH_TRASHBIN) { // For folders
			iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture("folder_icon")));
		}
		else if (isDirectory && entry.path().string() == FILEPATH_TRASHBIN) { // For trash folder
			iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture("trash_icon")));
		}
		else { // Non-folder icons
			// For image files
			if (entryExt == ".jpg" || entryExt == ".jpeg" || entryExt == ".png" || entryExt == ".gif") {
				// For Spites
				if (filePath == FILEPATH_SPRITES) {
					size_t bracketPos = texNameWithoutExt.find('('); // Cutout size for accessing
					if (bracketPos != std::string::npos) {
						texNameWithoutExt = texNameWithoutExt.substr(0, bracketPos);
					}
					iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetSpriteTexture(texNameWithoutExt)));
					
					// Trim everything except name
					size_t underscorePos = texNameWithoutExt.find("_");
					if (underscorePos != std::string::npos) {
						texNameWithoutExt = texNameWithoutExt.substr(0, underscorePos);
					}
				}
				// For Textures
				else {
					iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture(texNameWithoutExt)));
				}			
			} // For everything else
			else {
				auto it = iconExtList.find(entryExt);
				if (it != iconExtList.end()) { // Use corresponding texture
					iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture(it->second))); 
				}
				else { // Use default texture
					iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture("others_icon")));
				}
			}		
		}
		
		// Change button style if entry is selected
		if (browserSelectedItem == entryName) {
			// Yellow with opacity differences for visuals
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 0.0f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 0.0f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 0.0f, 0.8f));
		}

		// Render button
		ImGui::ImageButton(iconTexture, ImVec2(static_cast<float>(EditorSettings::iconSize), static_cast<float>(EditorSettings::iconSize)));

		
		// Set Drag Source
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
			itemDrag = true;
			if (filePath == FILEPATH_TEXTURES) {
				// Set payload type
				ImGui::SetDragDropPayload("PAYLOAD_TEXTURE", texNameWithoutExt.c_str(), texNameWithoutExt.size() + 1);
			}
			else if (filePath == FILEPATH_SPRITES) {
				// Set payload type
				ImGui::SetDragDropPayload("PAYLOAD_SPRITE", texNameWithoutExt.c_str(), texNameWithoutExt.size() + 1);
			}
			else if (filePath == FILEPATH_SOUNDS_BGM) {
				ImGui::SetDragDropPayload("PAYLOAD_AUDIO_BGM", browserSelectedItem.c_str(), browserSelectedItem.size() + 1);
			}
			else if (filePath == FILEPATH_SOUNDS_SFX) {
				ImGui::SetDragDropPayload("PAYLOAD_AUDIO_SFX", browserSelectedItem.c_str(), browserSelectedItem.size() + 1);
			}
			/*else if (filePath == FILEPATH_SCENES) {
				ImGui::SetDragDropPayload("PAYLOAD_SCENE", browserSelectedItem.c_str(), browserSelectedItem.size() + 1);
			}*/
			else if (filePath == FILEPATH_FONTS) {
				ImGui::SetDragDropPayload("PAYLOAD_FONT", browserSelectedItem.c_str(), browserSelectedItem.size() + 1);
			}
			else {
				ImGui::SetDragDropPayload("PAYLOAD_UNKNOWN", browserSelectedItem.c_str(), browserSelectedItem.size() + 1);
			}
			// Display held item
			if (mismatchPayload) {
				iconTexture = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(assetManager.GetTexture("error_icon")));
			}
			ImGui::Image(iconTexture, ImVec2(static_cast<float>(EditorSettings::iconSize / 4), static_cast<float>(EditorSettings::iconSize / 4)));
			ImGui::EndDragDropSource();
		}
			
		

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

/**************************************************************************
* @brief This function renders console panel used to enter commands and cheat codes
* @return void
*************************************************************************/
void Editor::CreateConsolePanel() {
	ImGui::Begin("Console");

	if (ImGui::InputText("####", &consoleTextInput, ImGuiInputTextFlags_EnterReturnsTrue) || (ImGui::SameLine(), ImGui::Button("Enter"))) {
		if (CheckCheatCode(consoleTextInput))
			Cheat(consoleTextInput);
		if (consoleTextInput == "developermodeoff") {
			panelList.consolePanel = false;
			inputSystem.cheater = false;
		}
		consoleTextInput.clear();
	}

	// Action to be taken on Enter press
	ImGui::Text((CheckCheatCode(consoleTextInput) || consoleTextInput == "developermodeoff") ? "Command Check: Command Found" : "Command Check: Command Not Found");

	ImGui::End();
}

/**************************************************************************
* @brief This function calculates and updates the matrix for the shapes used 
		 in a basic gizmo for scaling/rotating/moving a game object in the Editor
* @param float scaleX - X scale of Game Object
* @param float scaleY - Y scale of Game Object
* @param Vec2 pos - position of Game Object
* @param float rot - rotation of Game Object
* @return void
*************************************************************************/
void Editor::DrawGizmos(float scaleX, float scaleY, Vec2 pos, float rot) {
	Matrix3x3 scale = Matrix3x3(scaleX + scaleOutline, 0.f, 0.f,
								0.f, scaleY + scaleOutline, 0.f,
								0.f, 0.0f, 1.0f);
	float radRot = rot * (static_cast<float>(PI) / 180.0f);
	Matrix3x3 rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
								-sinf(radRot), cosf(radRot), 0.f,
								0.f, 0.f, 1.0f);
	Matrix3x3 translate = Matrix3x3(1.f, 0.f, 0.f,
									0.f, 1.f, 0.f,
									pos.x, pos.y, 1.0f);

	selectedOutline.Update(scale, rotate, translate);

	scale = Matrix3x3(scaleOutline, 0.f, 0.f,
		0.f,scaleY + scaleOutline, 0.f,
		0.f, 0.0f, 1.0f);
	 radRot = rot * (static_cast<float>(PI) / 180.0f);
	rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
		-sinf(radRot), cosf(radRot), 0.f,
		0.f, 0.f, 1.0f);
	Vec2 translateVec = pos + Vector2DRotate(Vec2(scaleX / 2.f, 0) + Vec2(scaleOutline, 0), rot, Vec2(0, 0));
	translate = Matrix3x3(1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		translateVec.x, translateVec.y, 1.0f);
	selectedOutline1.Update(scale, rotate, translate);

	scale = Matrix3x3(scaleOutline, 0.f, 0.f,
		0.f, scaleY + scaleOutline, 0.f,
		0.f, 0.0f, 1.0f);
	radRot = rot * (static_cast<float>(PI) / 180.0f);
	rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
		-sinf(radRot), cosf(radRot), 0.f,
		0.f, 0.f, 1.0f);
	translateVec = pos - Vector2DRotate(Vec2(scaleX / 2.f, 0) + Vec2(scaleOutline, 0), rot, Vec2(0, 0));
	translate = Matrix3x3(1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		translateVec.x, translateVec.y, 1.0f);
	selectedOutline2.Update(scale, rotate, translate);

	scale = Matrix3x3(scaleX + scaleOutline, 0.f, 0.f,
		0.f, scaleOutline, 0.f,
		0.f, 0.0f, 1.0f);
	radRot = rot * (static_cast<float>(PI) / 180.0f);
	rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
		-sinf(radRot), cosf(radRot), 0.f,
		0.f, 0.f, 1.0f);
	translateVec = pos + Vector2DRotate(Vec2(0, (scaleY / 2.f) + scaleOutline), rot, Vec2(0, 0));
	translate = Matrix3x3(1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		translateVec.x, translateVec.y, 1.0f);
	selectedOutline3.Update(scale, rotate, translate);

	scale = Matrix3x3(scaleX + scaleOutline, 0.f, 0.f,
		0.f, scaleOutline, 0.f,
		0.f, 0.0f, 1.0f);
	radRot = rot * (static_cast<float>(PI) / 180.0f);
	rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
		-sinf(radRot), cosf(radRot), 0.f,
		0.f, 0.f, 1.0f);
	translateVec = pos - Vector2DRotate(Vec2(0, (scaleY / 2.f) + scaleOutline), rot, Vec2(0, 0));
	translate = Matrix3x3(1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		translateVec.x, translateVec.y, 1.0f);
	selectedOutline4.Update(scale, rotate, translate);

	scale = Matrix3x3(scaleOutline, 0.f, 0.f,
		0.f, scaleOutline, 0.f,
		0.f, 0.0f, 1.0f);
	radRot = rot * (static_cast<float>(PI) / 180.0f);
	rotate = Matrix3x3(cosf(radRot), sinf(radRot), 0,
		-sinf(radRot), cosf(radRot), 0.f,
		0.f, 0.f, 1.0f);
	translateVec = pos + Vector2DRotate(Vec2(0, (scaleY / 2.f) + (3 * scaleOutline)), rot, Vec2(0, 0));
	translate = Matrix3x3(1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		translateVec.x, translateVec.y, 1.0f);
	rotatedWidget.Update(scale, rotate, translate);
}