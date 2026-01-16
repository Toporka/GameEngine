#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // Load shader
    Shader spriteShader = ResourceManager::GetShader("Sprite");
    Renderer = new SpriteRenderer(spriteShader);
}

void Game::ProcessInput(float dt)
{

}

void Game::Update(float dt)
{
    
}

void Game::Render()
{
    
}