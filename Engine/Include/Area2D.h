#pragma once

#include <glm/glm.hpp>

class AreaRect;
class AreaCircle;

class Area2D
{
public:
	virtual ~Area2D() = default;
	virtual glm::vec2 GetCollision(const Area2D& area) const = 0;
	virtual glm::vec2 GetCollision(const AreaRect& area) const = 0;
	virtual glm::vec2 GetCollision(const AreaCircle& area) const = 0;
};

class AreaRect : public Area2D
{
public:
    glm::vec2 position;
    glm::vec2 size;
    AreaRect(glm::vec2 position, glm::vec2 size);

    virtual glm::vec2 GetCollision(const Area2D& area) const override;
    virtual glm::vec2 GetCollision(const AreaRect& area) const override;
    virtual glm::vec2 GetCollision(const AreaCircle& area) const override;
};

class AreaCircle : public Area2D
{
public:
    glm::vec2 position;
    float radius;
    AreaCircle(glm::vec2 position, float radius);

    virtual glm::vec2 GetCollision(const Area2D& area) const override;
    virtual glm::vec2 GetCollision(const AreaRect& area) const override;
    virtual glm::vec2 GetCollision(const AreaCircle& area) const override;
};