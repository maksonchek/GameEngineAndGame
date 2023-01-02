#include "SpaceShip.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

SpaceShip::SpaceShip(const double velocity,
						const glm::vec2& position,
							const glm::vec2& size, const float layer)
												: GameObjectInterface(position, size, 0.f, layer)
												, objectOrientation(ObjectOrientation::Top)
											    , pSprite_top(ResourceManager::GetSprite("tankSprite_top"))
												, pSprite_bottom(ResourceManager::GetSprite("tankSprite_bottom"))
												, pSprite_left(ResourceManager::GetSprite("tankSprite_left"))
												, pSprite_right(ResourceManager::GetSprite("tankSprite_right"))
											    , spriteAnimator_top(pSprite_top)
												, spriteAnimator_bottom(pSprite_bottom)
												, spriteAnimator_left(pSprite_left)
											    , spriteAnimator_right(pSprite_right)
												, pSprite_respawn(ResourceManager::GetSprite("respawn"))
												, spriteAnimator_respawn(pSprite_respawn)
												, pSprite_shield(ResourceManager::GetSprite("shield"))
												, spriteAnimator_shield(pSprite_shield)
																	, isMoving(false)
																	, velocity(velocity)
																	, moveOffset(glm::vec2(0.f, 1.f))
																	, isSpawning(true)
																	, hasShield(false)
{
	respawnTimer.SetCallback([&]()
		{
			isSpawning = false;
			hasShield = true;
			shieldTimer.Start(2000);
		}
	);
	respawnTimer.Start(1500);

	shieldTimer.SetCallback([&]()
		{
			hasShield = false;
		}
	);
}

void SpaceShip::Render() const
{
	if (isSpawning)
	{
		pSprite_respawn->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_respawn.GetCurrentFrame());
	}
	else
	{
		switch (objectOrientation)
		{
		case SpaceShip::ObjectOrientation::Top:
			pSprite_top->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_top.GetCurrentFrame());
			break;
		case SpaceShip::ObjectOrientation::Bottom:
			pSprite_bottom->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_bottom.GetCurrentFrame());
			break;
		case SpaceShip::ObjectOrientation::Left:
			pSprite_left->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_left.GetCurrentFrame());
			break;
		case SpaceShip::ObjectOrientation::Right:
			pSprite_right->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_right.GetCurrentFrame());
			break;
		}

		if (hasShield)
		{
			pSprite_shield->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_shield.GetCurrentFrame());
		}
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

void SpaceShip::UpdateFrame(const double deltaTime)
{
	if (isSpawning)
	{
		spriteAnimator_respawn.Update(deltaTime);
		respawnTimer.Update(deltaTime);
	}
	else
	{
		if (hasShield)
		{
			spriteAnimator_shield.Update(deltaTime);
			shieldTimer.Update(deltaTime);
		}
		if (isMoving)
		{
			GOIposition.x += static_cast<float>(deltaTime * velocity * moveOffset.x);
			GOIposition.y += static_cast<float>(deltaTime * velocity * moveOffset.y);
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
}
