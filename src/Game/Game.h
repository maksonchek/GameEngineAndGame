#pragma once

#include <array>
#include <glm/vec2.hpp>
#include<memory>

class SpaceShip;
class Level;

class Game
{
public:
	Game(const glm::vec2 windowSize);
	~Game();

	void Render();

	void Update(const uint64_t deltaTime);

	void SetClick(const int key, const int action); 

	bool InitGame();

private:
	std::array<bool, 349> keysForClick;
	glm::vec2 windowSize;

	enum class GameState
	{
		Active,
		Pause
	};

	GameState gameState;

	std::unique_ptr<SpaceShip> pGameObject;
	std::unique_ptr<Level> pLevel;
};