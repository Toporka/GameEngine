#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "SpriteRenderer.h"
#include "Texture.h"

struct AnimationFrame
{
	Texture2D texture;
	float duration;
};

class Animation
{
public:
	bool loop;
	std::vector<AnimationFrame> frames;

	Animation() = default;
	Animation(std::vector<AnimationFrame> frames, bool loop);
	unsigned int GetFrameCount();
};

class AnimationManager
{
private:
	std::map<std::string, Animation> animations;
public:
	AnimationManager() = default;
	void AddAnimation(std::string animationName, Animation animation);
	void RemoveAnimation(std::string animationName);
	Animation* GetAnimation(std::string animationName);
};

class AnimationPlayer
{
private:
	Animation* currentAnimation = nullptr;
	unsigned int currentFrame = 0;
	float elapsed = 0.0f;
	bool isPlaying = false;
	const Texture2D& GetCurrentTexture() const;
	void DrawAnimation(SpriteRenderer* renderer, glm::vec2 position);
public:
	void Stop();
	void Pause();
	bool GetIsPlaing();
	void SetCurrentAnimation(AnimationManager* manager, std::string name);
	void PlayAnimation(float deltaTime, SpriteRenderer* renderer, glm::vec2 position);
};