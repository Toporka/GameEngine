#pragma once
#include "Scene.h"
#include "SceneMacros.h"
#include <iostream>

class MainScene : public Scene
{
public:
	void Init() override;
	void Update(float delta) override;
};