#include "glm/glm.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "ResourceManager.h"
#include "EngineProperties.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

EngineProperties* engineProperties = EngineProperties::GetEngineProperties();

int main(int argc, char* argv[])
{
    // The Width of the screen
    engineProperties->screenWidth = 800;
    // The height of the screen
    engineProperties->screenHeight = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);

    GLFWwindow* window = glfwCreateWindow(engineProperties->screenWidth, engineProperties->screenHeight, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    glViewport(0, 0, engineProperties->screenWidth, engineProperties->screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load shaders
    ResourceManager::LoadShader("Engine/Shaders/Vertex.shader", "Engine/Shaders/Fragment.shader", nullptr, "Sprite");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(engineProperties->screenWidth),
        static_cast<float>(engineProperties->screenHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("Sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("Sprite").SetMatrix4("projection", projection);

    // Create list scenes
    std::vector<std::unique_ptr<Scene>> listScenes = SceneRegistry::CreateAll();
    // Call All Init
    for (std::unique_ptr<Scene>& scene : listScenes)
        scene->Init();

    // deltaTime variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Call All Update
        for (std::unique_ptr<Scene>& scene : listScenes)
            scene->Update(deltaTime);

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
       if (action == GLFW_PRESS)
           engineProperties->keys[key] = true;
        else if (action == GLFW_RELEASE)
           engineProperties->keys[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}