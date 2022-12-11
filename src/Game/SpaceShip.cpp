#include "SpaceShip.h"
#include "../Renderer/SpriteAnimator.h"

SpaceShip::SpaceShip(std::shared_ptr<Renderer::SpriteAnimator> pSprite, const float velocity, const glm::vec2& position) :
					objectOrientation(ObjectOrientation::Top), pSprite(std::move(pSprite)), isMoving(false), velocity(velocity), position(position), moveOffset(glm::vec2(0.f, 1.f))
{
	this->pSprite->SetPosition(position);
}

void SpaceShip::Render() const
{
	pSprite->Render();
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
			pSprite->SetState("objectTopState");
			moveOffset.x = 0.f;
			moveOffset.y = 1.f;
			break;
		case SpaceShip::ObjectOrientation::Left:
			pSprite->SetState("objectLeftState");
			moveOffset.x = -1.f;
			moveOffset.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Right:
			pSprite->SetState("objectRightState");
			moveOffset.x = 1.f;
			moveOffset.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Bottom:
			pSprite->SetState("objectBottomState");
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
		pSprite->SetPosition(position);
		pSprite->UpdateFrame(delta);
	}
}
