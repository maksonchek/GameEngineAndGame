#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace Renderer
{
	class SpriteAnimator;
}

class SpaceShip
{
public:

	SpaceShip(std::shared_ptr<Renderer::SpriteAnimator> pSprie, const float velocity, const glm::vec2& position);
	
	void Render() const;


	enum class ObjectOrientation
	{
		Top,
		Right,
		Left,
		Bottom
	};

	void SetOrientation(const ObjectOrientation orientation);

	void Move(const bool isMoving);

	void UpdateFrame(const uint64_t delta);

private:
	ObjectOrientation objectOrientation;

	std::shared_ptr<Renderer::SpriteAnimator> pSprite;

	bool isMoving;

	float velocity;

	glm::vec2 position;

	glm::vec2 moveOffset;
};