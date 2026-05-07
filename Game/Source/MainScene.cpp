#include "MainScene.h"

void MainScene::Init()
{
	std::cout << "Init\n";
}
void MainScene::Update(float delta)
{
	std::cout << "Update\n";
}

REGISTER_SCENE(MainScene);