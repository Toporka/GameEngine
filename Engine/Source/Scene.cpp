#include "Scene.h"

//SpriteRenderer* Renderer;

std::vector<Scene*> Scene::listScenes;
using Creator = std::unique_ptr<Scene>(*)();

Scene::Scene() : State(SCENE_ACTIVE)
{
    Scene::listScenes.push_back(this);
}
Scene::~Scene()
{
    auto it = std::find(listScenes.begin(), listScenes.end(), this);
    if (it != listScenes.end()) listScenes.erase(it);

    //delete Renderer;
}

void Scene::callAllInit()
{
    for (auto scene : Scene::listScenes) scene->Init();
}
void Scene::callAllUpdate(float delta)
{
    for (auto scene : Scene::listScenes) scene->Update(delta);
}
void SceneRegistry::Register(Creator creator)
{
    GetCreators().emplace_back(creator);
}
std::vector<std::unique_ptr<Scene>> SceneRegistry::CreateAll()
{
    std::vector<std::unique_ptr<Scene>> scenes;
    for (const auto& creator : GetCreators())
        scenes.push_back(creator());

    return scenes;
}
std::vector<Creator>& SceneRegistry::GetCreators()
{
    static std::vector<Creator> creators;
    return creators;
}

//void Scene::Init()
//{
//    // Load shader
//    Shader spriteShader = ResourceManager::GetShader("Sprite");
//    Renderer = new SpriteRenderer(spriteShader);
//}
//
//void Scene::Update(float dt)
//{
//    
//}