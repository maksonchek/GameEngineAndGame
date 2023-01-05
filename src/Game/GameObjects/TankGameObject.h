#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "GameObjectInterface.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../EngineSystem/Timer.h"

namespace RenderEngine
{
	class Sprite;
}
class Bullet;

class TankGameObject : public GameObjectInterface
{
public:

	TankGameObject(const double maxVelocity, const glm::vec2& position, const glm::vec2& size, const float layer);
	
	void Render() const override;


	enum class ObjectOrientation : uint8_t
	{
		Top,
		Right,
		Left,
		Bottom
	};

	void SetOrientation(const ObjectOrientation orientation);

	void UpdateFrame(const double delta) override;

	double GetMaxVelocity() const;

	void SetVelocity(const double velocity) override;

	void Fire();

private:
	ObjectOrientation objectOrientation;

	std::shared_ptr<Bullet> pCurrentBullet;
	std::shared_ptr<RenderEngine::Sprite> pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> pSprite_right;
	RenderEngine::SpriteAnimator spriteAnimator_top;
	RenderEngine::SpriteAnimator spriteAnimator_bottom;
	RenderEngine::SpriteAnimator spriteAnimator_left;
	RenderEngine::SpriteAnimator spriteAnimator_right;

	std::shared_ptr<RenderEngine::Sprite> pSprite_respawn;
	RenderEngine::SpriteAnimator spriteAnimator_respawn;

	Timer respawnTimer;
	double maxVelocity;
	bool isSpawning;
};