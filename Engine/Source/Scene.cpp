#include "Scene.h"

//SpriteRenderer* Renderer;

using Creator = std::unique_ptr<Scene>(*)();

Scene::Scene() : State(SCENE_ACTIVE) {}
Scene::~Scene() {}

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