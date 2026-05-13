#include "MainScene.h"
#include "ResourceManager.h"
#include "EngineProperties.h"
#include "TextRenderer.h"
#include <iostream>

TextRenderer* textRenderer = nullptr;

void MainScene::Init()
{
    std::cout << "MainScene Init\n";

    EngineProperties* props = EngineProperties::GetEngineProperties();
    textRenderer = new TextRenderer(props->screenWidth, props->screenHeight);

    textRenderer->Load("Assets/Fonts/PixelOperator8.ttf", 48);
}

void MainScene::Update(float delta)
{
    if (textRenderer)
    {
        textRenderer->RenderText("Hello", 300.0f, 300.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    }
}

REGISTER_SCENE(MainScene);