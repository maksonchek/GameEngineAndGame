#include "SpaceShip.h"
#include "../../Renderer/Sprite.h"

SpaceShip::SpaceShip(std::shared_ptr<RenderEngine::Sprite> Sprite_top,
						std::shared_ptr<RenderEngine::Sprite> Sprite_bottom,
							std::shared_ptr<RenderEngine::Sprite> Sprite_left,
								std::shared_ptr<RenderEngine::Sprite> Sprite_right,
									const float velocity,
										const glm::vec2& position,
											const glm::vec2& size) 
	: GameObjectInterface(position, size, 0.f)
	, objectOrientation(ObjectOrientation::Top)
	, pSprite_top(std::move(Sprite_top))
	, pSprite_bottom(std::move(Sprite_bottom))
	, pSprite_left(std::move(Sprite_left))
	, pSprite_right(std::move(Sprite_right))
	, spriteAnimator_top(pSprite_top)
	, spriteAnimator_bottom(pSprite_bottom)
	, spriteAnimator_left(pSprite_left)
	, spriteAnimator_right(pSprite_right)
	, isMoving(false)
	, velocity(velocity)
	, moveOffset(glm::vec2(0.f, 1.f))
{
}

void SpaceShip::Render() const
{
	switch (objectOrientation)
	{
	case SpaceShip::ObjectOrientation::Top:
		pSprite_top->Render(position, size, rotation, spriteAnimator_top.GetCurrentFrame());
		break;
	case SpaceShip::ObjectOrientation::Bottom:
		pSprite_bottom->Render(position, size, rotation, spriteAnimator_bottom.GetCurrentFrame());
		break;
	case SpaceShip::ObjectOrientation::Left:
		pSprite_left->Render(position, size, rotation, spriteAnimator_left.GetCurrentFrame());
		break;
	case SpaceShip::ObjectOrientation::Right:
		pSprite_right->Render(position, size, rotation, spriteAnimator_right.GetCurrentFrame());
		break;
	}
}

void SpaceShip::SetOrientation(const ObjectOrientation orientation)
{
	if (objectOrientation == orientation)
	{
		return;
	}
	else
	{
		objectOrientation = orientation;
		switch (objectOrientation)
		{
		case SpaceShip::ObjectOrientation::Top:
			moveOffset.x = 0.f;
			moveOffset.y = 1.f;
			break;
		case SpaceShip::ObjectOrientation::Left:
			moveOffset.x = -1.f;
			moveOffset.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Right:
			moveOffset.x = 1.f;
			moveOffset.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Bottom:
			moveOffset.x = 0.f;
			moveOffset.y = -1.f;
			break;
		}
	}
}

void SpaceShip::Move(const bool isMoving)
{
	this->isMoving = isMoving;
}

void SpaceShip::UpdateFrame(const uint64_t deltaTime)
{
	if (isMoving)
	{
		position += deltaTime * velocity * moveOffset;
		switch (objectOrientation)
		{
		case SpaceShip::ObjectOrientation::Top:
			spriteAnimator_top.Update(deltaTime);
			break;
		case SpaceShip::ObjectOrientation::Bottom:
			spriteAnimator_bottom.Update(deltaTime);
			break;
		case SpaceShip::ObjectOrientation::Left:
			spriteAnimator_left.Update(deltaTime);
			break;
		case SpaceShip::ObjectOrientation::Right:
			spriteAnimator_right.Update(deltaTime);
			break;
		}
	}
}
