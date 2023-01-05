#include "TankGameObject.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"
//#include "../../PhysicsEngine/PhysicsEngine.h"
#include "Bullet.h"

TankGameObject::TankGameObject(const double maxVelocity,
						const glm::vec2& position,
							const glm::vec2& size, const float layer)
												: GameObjectInterface(GameObjectInterface::ObjectType::Constant_Dynamic_Object, position, size, 0.f, layer)
												, objectOrientation(ObjectOrientation::Top)
											    , pSprite_top(ResourceManager::GetSprite("tankSprite_top"))
												, pSprite_bottom(ResourceManager::GetSprite("tankSprite_bottom"))
												, pSprite_left(ResourceManager::GetSprite("tankSprite_left"))
												, pSprite_right(ResourceManager::GetSprite("tankSprite_right"))
	                                            , pCurrentBullet(std::make_shared<Bullet>(0.1, GOIposition + GOIsize / 4.f, GOIsize / 2.f, layer))
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
	PhysicsEngineManager::PhysicsEngine::AddDynamicGameObject(pCurrentBullet);
}

void TankGameObject::Render() const
{
	if (isSpawning)
	{
		pSprite_respawn->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_respawn.GetCurrentFrame());
	}
	else
	{
		switch (objectOrientation)
		{
		case TankGameObject::ObjectOrientation::Top:
			pSprite_top->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_top.GetCurrentFrame());
			break;
		case TankGameObject::ObjectOrientation::Bottom:
			pSprite_bottom->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_bottom.GetCurrentFrame());
			break;
		case TankGameObject::ObjectOrientation::Left:
			pSprite_left->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_left.GetCurrentFrame());
			break;
		case TankGameObject::ObjectOrientation::Right:
			pSprite_right->Render(GOIposition, GOIsize, GOIrotation, GOIlayer, spriteAnimator_right.GetCurrentFrame());
			break;
		}
	}
	if (pCurrentBullet->IsActive())
	{
		pCurrentBullet->Render();
	}
}

void TankGameObject::SetOrientation(const ObjectOrientation orientation)
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
		case TankGameObject::ObjectOrientation::Top:
			GOIdirection.x = 0.f;
			GOIdirection.y = 1.f;
			break;
		case TankGameObject::ObjectOrientation::Left:
			GOIdirection.x = -1.f;
			GOIdirection.y = 0.f;
			break;
		case TankGameObject::ObjectOrientation::Right:
			GOIdirection.x = 1.f;
			GOIdirection.y = 0.f;
			break;
		case TankGameObject::ObjectOrientation::Bottom:
			GOIdirection.x = 0.f;
			GOIdirection.y = -1.f;
			break;
		}
	}
}

void TankGameObject::UpdateFrame(const double deltaTime)
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
			case TankGameObject::ObjectOrientation::Top:
				spriteAnimator_top.Update(deltaTime);
				break;
			case TankGameObject::ObjectOrientation::Bottom:
				spriteAnimator_bottom.Update(deltaTime);
				break;
			case TankGameObject::ObjectOrientation::Left:
				spriteAnimator_left.Update(deltaTime);
				break;
			case TankGameObject::ObjectOrientation::Right:
				spriteAnimator_right.Update(deltaTime);
				break;
			}
		}
	}
}

double TankGameObject::GetMaxVelocity() const
{
	return maxVelocity;
}

void TankGameObject::SetVelocity(const double velocity)
{

	if (!isSpawning)
	{
		GOIvelocity = velocity;
	}
}

void TankGameObject::Fire()
{
	if (!pCurrentBullet->IsActive())
	{
		pCurrentBullet->Fire(GOIposition + GOIsize / 4.f + GOIsize * GOIdirection / 4.f, GOIdirection);
	}
}
