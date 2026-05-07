#pragma once
class EngineProperties
{
private:
	EngineProperties();
public:
	unsigned int screenWidth = 800;
	unsigned int screenHeight = 600;
	bool keys[1024];

	static EngineProperties* GetEngineProperties();
};

