#include "Game.h"

/*
    -Coorigur a aba de cenas
    - adicionar funcionalidades e propriedades pra cena
    -Adiccionar objeco e salvar em scenes manager
*/

#include "../engine/Time.h"
#include "../engine/Mesh.h"
#include "../engine/Light.h"
#include "../engine/Engine.h"
#include "../engine/Screen.h"
#include "../engine/Object.h"
#include "../engine/Camera.h"
#include "../engine/Command.h"
#include "../engine/Texture.h"
#include "../engine/Material.h"
#include "../engine/Resources.h"
#include "../engine/GameObject.h"
#include "../engine/FrameBuffer.h"

#include "../engine/ECS.h"

#include "../engine/component/Transform.h"
#include "../engine/component/MeshRender.h"
#include "../engine/component/SunComponent.h"

#include "../engine/ui/main/Template.h"

#include "../engine/core/scene/SceneManager.h"
#include "../engine/core/scene/Scene.h"

Camera* camera;

std::unordered_map<ImageType, std::unique_ptr<Texture>> textures;

SceneManager mSceneManager;
std::mutex myMutex;

void Game::Start() {
    try {
		textures.emplace(ImageType::ICON_FILE,       &Resources::Load<Texture>("src/assets/icon/icons8-file-30.png"));
		textures.emplace(ImageType::ICON_FOLDER,     &Resources::Load<Texture>("src/assets/icon/icons8-folder-50.png"));
		textures.emplace(ImageType::ICON_BACK_FILE,  &Resources::Load<Texture>("src/assets/icon/icons8-go-back-50.png"));
		textures.emplace(ImageType::ICON_GAMEOBJECT, &Resources::Load<Texture>("src/assets/icon/icons8-3d-object-50.png"));
		textures.emplace(ImageType::ICON_PENCIL,     &Resources::Load<Texture>("src/assets/icon/icons8-lápis-30.png"));
		textures.emplace(ImageType::ICON_LIGHT,     &Resources::Load<Texture>("src/assets/icon/icons8-lâmpada-globular-64.png"));
    } catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
    camera = &Camera::MainCamera();

    try {
         mSceneManager.loadAllScenes();
        if (mSceneManager.m_scenes.empty()) {
              mSceneManager.createScenes("This_is_your_scene");
            // mSceneManager.saveScenes();
        } else {
           // auto& back = mSceneManager.m_scenes.back();
           // GameObject* gameObject = back->add("Sphere");
           // gameObject->AddComponent<SunComponent>();
        }
    } catch (Exception e) {
        Log.Write(e.getMessage());
    }
    
}

Game::~Game() {
   // mSceneManager.saveAllScenes();
}

void Game::Update() {
    manager.Update();
    /*
    Light& sun = Light::GetSun();
    sun.position.z += 10.0f * Time::deltaTime;
    if (sun.position.z > 360) {
        sun.position.z = 0.0;
    }
    */
}

void Game::Render() {
    manager.Render();
}

template <typename ...Argv>
bool GameObjectButton(const char* fmt, int id, Argv... arg) {
    ImVec2 buttonSize(100, ImGui::CalcTextSize(fmt).y);
    ImVec2 buttonPosition(50, ImGui::GetCursorPos().y - buttonSize.y);

    ImGui::SetCursorPos(buttonPosition);

    ImGui::InvisibleButton(std::string("##" + std::to_string(id)).c_str(), buttonSize);

    ImGui::Image(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_GAMEOBJECT]->textureID), ImVec2(16, 16));
    ImGui::SameLine();
    
    ImGui::Text(fmt, arg...);

    return ImGui::IsItemClicked();
}

void Game::Gui() {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGuiIO& io = ImGui::GetIO();
    
    if (ImGui::Begin("DockSpace Demo", nullptr, window_flags)) {
        ImGui::PopStyleVar(2);

        // DockSpace
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit"))
                    glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }
    
    
    static bool isRenameScene, isRenameGameObject, isgameObjectSelect, canDelete;
    static int sceneID, gameObjectID;

    if (ImGui::Begin("Cenas", nullptr, ImGuiWindowFlags_NoResize)) {
        for (std::size_t i = 0; i < mSceneManager.m_scenes.size(); ++i) {
            const auto& scenes = mSceneManager.m_scenes[i];
            ImGui::PushID(i);

            bool collapseScenes = ImGui::CollapsingHeader(scenes->name.c_str(), ImGuiTreeNodeFlags_DefaultOpen);
            if (ImGui::IsItemHovered() && ImGui::IsKeyDown(ImGuiKey_F2) && !isRenameScene) {
                isRenameScene = true;
                sceneID = i;
            }
            if (collapseScenes) {
                for (std::size_t j = 0; j < scenes->m_gameObjects.size(); ++j) {
                    GameObject* gameObject = scenes->m_gameObjects[j];

                    ImGui::Image(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_GAMEOBJECT]->textureID), ImVec2(16, 16));
                    ImGui::SameLine();

                    ImGui::Selectable(gameObject->name.c_str(), gameObjectID == j);

                    if (ImGui::IsItemClicked()) {
                        gameObjectID = j;
                        sceneID = i;
                        isgameObjectSelect = true;
                    }
                    if (ImGui::IsItemHovered() && ImGui::IsKeyReleased(ImGuiKey_Delete) || ImGui::IsKeyReleased(ImGuiKey_X)) {
                        scenes->remove(scenes->m_gameObjects[gameObjectID]);
                        isgameObjectSelect = false;
                        continue;
                    }
                    if (ImGui::IsItemHovered() && ImGui::IsKeyReleased(ImGuiKey_F2) && !isRenameGameObject) {
                        isRenameGameObject = true;
                        gameObjectID = j;
                        sceneID = i;
                    }
                }
            }
            ImGui::PopID();
        }
        if (isRenameScene) {
            auto& scene = mSceneManager.m_scenes[sceneID];

            ImGui::OpenPopup("#popup_scene_rename");
            if (ImGui::BeginPopup("#popup_scene_rename")) {
                static std::string newName(scene->name.begin() , scene->name.end());
                newName.resize(32);

                ImGui::InputText("Nome", newName.data(), newName.size());
                if (ImGui::Button("Fecha")) {
                    newName.erase(std::find(newName.begin(), newName.end(), '\0'), newName.end());
                    mSceneManager.renamescene(newName);
                    
                    newName.clear();
                    isRenameScene = false;
                }
                ImGui::EndPopup();
            }
        }
        if (isRenameGameObject) {
            auto& gameObject = mSceneManager.m_scenes[sceneID]->m_gameObjects[gameObjectID];

            ImGui::OpenPopup("#popup_gameobject_rename");
            if (ImGui::BeginPopup("#popup_gameobject_rename")) {
                static std::string newName(gameObject->name.begin() , gameObject->name.end());
                newName.resize(32);
                
                ImGui::InputText("Nome", newName.data(), newName.size());
                if (ImGui::Button("Fecha")) {
                    newName.erase(std::find(newName.begin(), newName.end(), '\0'), newName.end());

                    gameObject->name = newName;
                    
                    newName.clear();
                    isRenameGameObject = false;
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }
    
    if (ImGui::Begin("Renderização", nullptr, ImGuiWindowFlags_NoResize)) {
        ImGui::Image(reinterpret_cast<ImTextureID>(mFrameBuffer->postTextureID), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* pPayload = ImGui::AcceptDragDropPayload(FILE_OBJ, ImGuiDragDropFlags_None)) {
                const char* path = (const char*)pPayload->Data;
                if (path != nullptr) {
                    try {
                        auto& scene = mSceneManager.m_scenes[sceneID];
                        scene->add(path);
                    } catch (Exception e) {
                        std::cout << e.getMessage() << std::endl;
                    }
                }
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::End();
    }

    if (ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoResize)) {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem("Console")) {
            }
            if (ImGui::MenuItem("Files")) {
            }
            ImGui::EndMenuBar();
        }
        
        // TODO: FIX ME
        static std::filesystem::path currentPath("./");

        ImGui::Columns(5, "#Collums1", false);
        if (textures[ImageType::ICON_BACK_FILE] && ImGui::ImageButton(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_BACK_FILE]->textureID), ImVec2(32, 32))) {
            if (currentPath != std::filesystem::path("./")) {
                currentPath = currentPath.parent_path();
            }
        }
        ImGui::Text("Voltar");

        int id;

        for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
            ImGui::PushID(++id);
            ImGui::NextColumn();

            if (entry.is_directory() && textures[ImageType::ICON_FOLDER]) {
                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_FOLDER]->textureID), ImVec2(32, 32))) {
                    currentPath = entry.path();
                }
            } else {
                std::string path = entry.path();

                if (entry.path().extension() == std::filesystem::path(".obj") && textures[ImageType::ICON_GAMEOBJECT]) {
                    ImGui::ImageButton(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_GAMEOBJECT]->textureID), ImVec2(32, 32));
                
                    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID) && textures[ImageType::ICON_GAMEOBJECT]) {
                        ImGui::SetDragDropPayload(FILE_OBJ, path.c_str(), path.size() + 1);
                        ImGui::ImageButton(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_GAMEOBJECT]->textureID), ImVec2(32, 32));
                
                        ImGui::EndDragDropSource();
                    }
                } else {
                    // ImGui::ImageButton(reinterpret_cast<ImTextureID>(textures[ImageType::ICON_FILE]->textureID), ImVec2(32, 32));
                }
            }
            ImGui::Text("%s", entry.path().filename().c_str());
            ImGui::PopID();
        }
        ImGui::Columns(1);

        ImGui::End();
    }
    
    if (ImGui::Begin("Propriedades", nullptr, ImGuiWindowFlags_NoResize)) {
        if (ImGui::CollapsingHeader("Status do jogo")) {
            ImGui::Text("Application average\n%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            
            ImGui::Text("Total de objetos: %ld", gameObjectList.size());

            ImGui::Text("Total de vertices: %ld", gameStatics.vertices);

            ImGui::Text("Total de entitades: %ld", gameStatics.entities);
        }

        if (ImGui::CollapsingHeader("Cameras")) {
            ///ImGui::Text("Camera editor", gameObjectList.size());
        }
        
        if (isgameObjectSelect) {
            if (ImGui::CollapsingHeader("Propriedades", ImGuiTreeNodeFlags_NoTreePushOnOpen)) {
                auto& gameObject = mSceneManager.m_scenes[sceneID]->m_gameObjects[gameObjectID];

                MeshRender& meshRender = gameObject->GetComponent<MeshRender>();

                Transform* transform = &gameObject->GetComponent<Transform>();

                ImGui::Text("GameObject: %s", gameObject->name.c_str());

                ImGui::Text("Positição: ");
                ImGui::DragFloat("posX", &transform->position.x);
                ImGui::DragFloat("posY", &transform->position.y);
                ImGui::DragFloat("posZ", &transform->position.z);

                ImGui::Text("Escala: ");
                ImGui::DragFloat("scaleX", &transform->scale.x);
                ImGui::DragFloat("scaleY", &transform->scale.y);
                ImGui::DragFloat("scaleZ", &transform->scale.z);

                auto& material = meshRender.material;

                ImGui::Separator();

                ImGui::Text("Material: %s", material->name.c_str());

                ImGui::ColorPicker3("M Ambiente", material->ambient.data);

                ImGui::ColorPicker3("M Diffuse", material->diffuse.data);

                ImGui::ColorPicker3("M Specular", material->specular.data);

                ImGui::SliderFloat("M Shiness", &material->shininess, 0, 150);

                ImGui::SliderFloat("M Scale", &material->scale, 0, 20);

            }
        }
        
        if (ImGui::CollapsingHeader("Sol")) {
            Light& sun = Light::GetSun();

            

            ImGui::InputFloat("Direção X", &sun.position.x);
            ImGui::InputFloat("Direção Y", &sun.position.y);
            ImGui::InputFloat("Direção Z", &sun.position.z);

            ImGui::ColorPicker3("S Ambiente", sun.ambient.data, 0);

            ImGui::ColorPicker3("S Diffusa", sun.diffuse.data, 0);

            ImGui::ColorPicker3("S Especular", sun.specular.data, 0);
        }
        ImGui::End();
    }
}

void Global::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    ImGuiIO& io = ImGui::GetIO();

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        io.MouseDrawCursor = !io.MouseDrawCursor;
        //glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if ((action == GLFW_PRESS || action == GLFW_REPEAT)) {
        camera->processKeyboardInput(key, Time::deltaTime);
    }
}

void Global::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    ImGuiIO& io = ImGui::GetIO();
    if (!io.MouseDrawCursor) {
        return;
    }
    static Vector2 lastMousePos(xpos, ypos);
    const Vector2 offset = Vector2(xpos, ypos) - lastMousePos;

    camera->processMouseMovement(offset);

    lastMousePos = Screen::GetResolution() / 2;

    if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) {
        glfwSetCursorPos(window, lastMousePos.x, lastMousePos.y);
    }
}

void Global::DropCallback(GLFWwindow* window, int numFiles, const char** fileNames) {
    for (int i{};i<numFiles;++i) {
        std::string filePath = fileNames[i];
        if (filePath.find(".obj") == std::string::npos) {
            std::cout << "File not .Obj" << std::endl;
            return;
        }
        GameObject& gameObject = Resources::Load<GameObject>(filePath);
        gameObject.Instantiate();
    }
    
}

