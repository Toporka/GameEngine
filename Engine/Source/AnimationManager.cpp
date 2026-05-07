#include "AnimationManager.h"

Animation::Animation(std::vector<AnimationFrame> frames, bool loop = true) : frames(frames), loop(loop) {}

unsigned int Animation::GetFrameCount()
{
	return (unsigned int)frames.size();
}

void AnimationManager::AddAnimation(std::string animationName, Animation animation)
{
	animations[animationName] = std::move(animation);
}

void AnimationManager::RemoveAnimation(std::string animationName)
{
	animations.erase(animationName);
}

Animation* AnimationManager::GetAnimation(std::string animationName)
{
	auto iterator = animations.find(animationName);
	return iterator != animations.end() ? &iterator->second : nullptr;
}

void AnimationPlayer::Stop()
{
	isPlaying = false;
}

void AnimationPlayer::Pause()
{
	isPlaying = !isPlaying;
}

bool AnimationPlayer::GetIsPlaing()
{
	return isPlaying;
}

void AnimationPlayer::SetCurrentAnimation(AnimationManager* manager, std::string name)
{
	currentAnimation = manager->GetAnimation(name);
	currentFrame = 0;
	elapsed = 0.0f;
	isPlaying = true;
}

void AnimationPlayer::PlayAnimation(float delta, SpriteRenderer* renderer, glm::vec2 position)
{
	if (currentAnimation == nullptr || currentAnimation->frames.empty() || isPlaying == false)
		return;

	elapsed += delta;
	while (elapsed >= currentAnimation->frames[currentFrame].duration)
	{
		elapsed -= currentAnimation->frames[currentFrame].duration;
		currentFrame++;
		if (currentFrame >= currentAnimation->GetFrameCount())
		{
			if (currentAnimation->loop) currentFrame = 0;
			else
			{
				currentFrame = currentAnimation->GetFrameCount() - 1;
				isPlaying = false;
				break;
			}
		}
	}

	DrawAnimation(renderer, position);
}

const Texture2D& AnimationPlayer::GetCurrentTexture() const
{
	if (currentAnimation && currentFrame < currentAnimation->GetFrameCount())
		return currentAnimation->frames[currentFrame].texture;

	static Texture2D empty;
	return empty;
}

void AnimationPlayer::DrawAnimation(SpriteRenderer* renderer, glm::vec2 position)
{
	const Texture2D& texture = this->GetCurrentTexture();
	renderer->DrawSprite(texture, position, glm::vec2(texture.Width, texture.Height));
}