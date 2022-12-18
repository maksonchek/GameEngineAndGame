#include "SpaceShip.h"
#include "../../Renderer/SpriteAnimator.h"

SpaceShip::SpaceShip(std::shared_ptr<RenderEngine::SpriteAnimator> pSprite, const float velocity, const glm::vec2& position, const glm::vec2& size) : GameObjectInterface(position, size, 0.f),
					objectOrientation(ObjectOrientation::Top), pSprite(std::move(pSprite)), isMoving(false), velocity(velocity), moveOffset(glm::vec2(0.f, 1.f))
{
}

void SpaceShip::Render() const
{
	pSprite->Render(position, size, rotation);
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
			pSprite->SetState("GameObjectTopState");
			moveOffset.x = 0.f;
			moveOffset.y = 1.f;
			break;
		case SpaceShip::ObjectOrientation::Left:
			pSprite->SetState("GameObjectLeftState");
			moveOffset.x = -1.f;
			moveOffset.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Right:
			pSprite->SetState("GameObjectRightState");
			moveOffset.x = 1.f;
			moveOffset.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Bottom:
			pSprite->SetState("GameObjectBottomState");
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

void SpaceShip::UpdateFrame(const uint64_t delta)
{
	if (isMoving)
	{
		position += delta * velocity * moveOffset;
		pSprite->UpdateFrame(delta);
	}
}
