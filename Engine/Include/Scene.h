#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

enum SceneState {
    SCENE_ACTIVE,
    SCENE_MENU,
    SCENE_WIN
};

class Scene
{
private:
    static std::vector<Scene*> listScenes;
public:
    SceneState    State;

    Scene();
    ~Scene();

    virtual void Init() = 0;
    virtual void Update(float delta) = 0;

    static void callAllInit();
    static void callAllUpdate(float delta);
};

class SceneRegistry 
{
public:
    using Creator = std::unique_ptr<Scene>(*)();
    static void Register(Creator creator);
    static std::vector<std::unique_ptr<Scene>> CreateAll();
private:
    static std::vector<Creator>& GetCreators();
};