#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "GameObjectInterface.h"

namespace RenderEngine
{
	class SpriteAnimator;
}

class SpaceShip : public GameObjectInterface
{
public:

	SpaceShip(std::shared_ptr<RenderEngine::SpriteAnimator> pSprie, const float velocity, const glm::vec2& position, const glm::vec2& size);
	
	void Render() const override;


	enum class ObjectOrientation
	{
		Top,
		Right,
		Left,
		Bottom
	};

	void SetOrientation(const ObjectOrientation orientation);

	void Move(const bool isMoving);

	void UpdateFrame(const uint64_t delta) override;

private:
	ObjectOrientation objectOrientation;

	std::shared_ptr<RenderEngine::SpriteAnimator> pSprite;

	bool isMoving;

	float velocity;

	glm::vec2 moveOffset;
};