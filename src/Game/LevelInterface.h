#pragma once 

#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <algorithm>

class GameObjectInterface;

class LevelInterface {
public:
	LevelInterface();
	static constexpr unsigned int BLOCK_SIZE = 16;
	virtual void Render() const;
	virtual void Update(const double delta);
	virtual size_t GetLevelWidth() const;
	virtual size_t GetLevelHeight() const;
	virtual std::vector<std::shared_ptr<GameObjectInterface>> GetLevelObjects(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;

protected:
	size_t width = 0;
	size_t height = 0;
	unsigned int widthPixels = 0;
	unsigned int heightPixels = 0;
	std::vector<std::shared_ptr<GameObjectInterface>> levelObjects;
};