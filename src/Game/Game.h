#pragma once

#include <array>
#include <glm/vec2.hpp>
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
};