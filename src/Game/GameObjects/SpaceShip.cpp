#include "SpaceShip.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

SpaceShip::SpaceShip(const float velocity,
						const glm::vec2& position,
							const glm::vec2& size) 
												: GameObjectInterface(position, size, 0.f)
												, objectOrientation(ObjectOrientation::Top)
											    , pSprite_top(ResourceManager::GetSprite("tankSprite_top"))
												, pSprite_bottom(ResourceManager::GetSprite("tankSprite_bottom"))
												, pSprite_left(ResourceManager::GetSprite("tankSprite_left"))
												, pSprite_right(ResourceManager::GetSprite("tankSprite_right"))
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
		pSprite_top->Render(GOIposition, GOIsize, GOIrotation, spriteAnimator_top.GetCurrentFrame());
		break;
	case SpaceShip::ObjectOrientation::Bottom:
		pSprite_bottom->Render(GOIposition, GOIsize, GOIrotation, spriteAnimator_bottom.GetCurrentFrame());
		break;
	case SpaceShip::ObjectOrientation::Left:
		pSprite_left->Render(GOIposition, GOIsize, GOIrotation, spriteAnimator_left.GetCurrentFrame());
		break;
	case SpaceShip::ObjectOrientation::Right:
		pSprite_right->Render(GOIposition, GOIsize, GOIrotation, spriteAnimator_right.GetCurrentFrame());
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
		GOIposition += deltaTime * velocity * moveOffset;
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
