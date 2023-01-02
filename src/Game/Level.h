#pragma once

#include <vector>
#include <string>
#include <memory>

class GameObjectInterface;

class Level {
public:
    Level(const std::vector<std::string>& levelMarkup);
    void Render() const;
    void Update(const uint64_t delta);
    size_t GetLevelWidth() const;
    size_t GetLevelHeight() const;

private:
    size_t width = 0;
    size_t height = 0;

    std::vector<std::shared_ptr<GameObjectInterface>> levelObjects;
};