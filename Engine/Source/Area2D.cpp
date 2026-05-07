#include "Area2D.h"

AreaRect::AreaRect(glm::vec2 position, glm::vec2 size) : position(position), size(size) {}

glm::vec2 AreaRect::GetCollision(const Area2D& area) const
{
    return area.GetCollision(*this);
}

glm::vec2 AreaRect::GetCollision(const AreaRect& area) const
{
    float oneLeft = position.x;
    float oneRight = position.x + size.x;
    float oneTop = position.y;
    float oneBottom = position.y + size.y;
    float twoLeft = area.position.x;
    float twoRight = area.position.x + area.size.x;
    float twoTop = area.position.y;
    float twoBottom = area.position.y + area.size.y;
    float overlapX = std::min(oneRight, twoRight) - std::max(oneLeft, twoLeft);
    float overlapY = std::min(oneBottom, twoBottom) - std::max(oneTop, twoTop);
    glm::vec2 difference(overlapX, overlapY);
    if (overlapX <= 0.0f || overlapY <= 0.0f)
        return glm::vec2(0.0f, 0.0f);
    else
        return glm::vec2(overlapX, overlapY);
}

glm::vec2 AreaRect::GetCollision(const AreaCircle& area) const
{
    glm::vec2 center(area.position + area.radius);
    glm::vec2 aabb_half_extents(size.x / 2.0f, size.y / 2.0f);
    glm::vec2 aabb_center(
        position.x + aabb_half_extents.x,
        position.y + aabb_half_extents.y
    );
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    if (glm::length(difference) >= area.radius)
        return glm::vec2(0.0f, 0.0f);
    else
        return difference;
}

AreaCircle::AreaCircle(glm::vec2 position, float radius) : position(position), radius(radius) {}

glm::vec2 AreaCircle::GetCollision(const Area2D& area) const
{
    return area.GetCollision(*this);
}

glm::vec2 AreaCircle::GetCollision(const AreaRect& area) const
{
    glm::vec2 center(position + radius);
    glm::vec2 aabb_half_extents(area.size.x / 2.0f, area.size.y / 2.0f);
    glm::vec2 aabb_center(
        area.position.x + aabb_half_extents.x,
        area.position.y + aabb_half_extents.y
    );
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    if (glm::length(difference) >= radius)
        return glm::vec2(0.0f, 0.0f);
    else
        return difference;
}

glm::vec2 AreaCircle::GetCollision(const AreaCircle& area) const
{
    glm::vec2 difference = area.position - position;
    float distance = glm::length(difference);
    if (distance < radius + area.radius)
        return difference;
    else
        return glm::vec2(0.0f, 0.0f);
}