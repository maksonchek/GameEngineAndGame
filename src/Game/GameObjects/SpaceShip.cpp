#include "SpaceShip.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

SpaceShip::SpaceShip(const double maxVelocity,
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
																	, maxVelocity(maxVelocity)
																	, isSpawning(true)
{
	respawnTimer.SetCallback([&]()
		{
			isSpawning = false;
		}
	);
	respawnTimer.Start(1500);

	boxColliders.emplace_back(glm::vec2(0), GOIsize);
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
			GOIdirection.x = 0.f;
			GOIdirection.y = 1.f;
			break;
		case SpaceShip::ObjectOrientation::Left:
			GOIdirection.x = -1.f;
			GOIdirection.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Right:
			GOIdirection.x = 1.f;
			GOIdirection.y = 0.f;
			break;
		case SpaceShip::ObjectOrientation::Bottom:
			GOIdirection.x = 0.f;
			GOIdirection.y = -1.f;
			break;
		}
	}
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
		if (GOIvelocity>0)
		{
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

double SpaceShip::GetMaxVelocity() const
{
	return maxVelocity;
}

void SpaceShip::SetVelocity(const double velocity)
{

	if (!isSpawning)
	{
		GOIvelocity = velocity;
	}
}
