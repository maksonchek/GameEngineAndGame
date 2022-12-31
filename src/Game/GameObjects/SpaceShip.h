#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "GameObjectInterface.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine
{
	class Sprite;
}

class SpaceShip : public GameObjectInterface
{
public:

	SpaceShip(const float velocity, const glm::vec2& position, const glm::vec2& size);
	
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

	std::shared_ptr<RenderEngine::Sprite> pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> pSprite_right;
	RenderEngine::SpriteAnimator spriteAnimator_top;
	RenderEngine::SpriteAnimator spriteAnimator_bottom;
	RenderEngine::SpriteAnimator spriteAnimator_left;
	RenderEngine::SpriteAnimator spriteAnimator_right;

	bool isMoving;

	float velocity;

	glm::vec2 moveOffset;
};