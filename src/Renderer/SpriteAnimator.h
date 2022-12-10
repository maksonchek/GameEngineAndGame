#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "Sprite.h"

namespace Renderer {

    class SpriteAnimator : public Sprite{
    public:

        SpriteAnimator(const std::shared_ptr<TextureManager> pTexture,
                 const std::string initTile,
                   const std::shared_ptr<ShaderManager> pShaderManager,
                      const glm::vec2& position = glm::vec2(0.f),
                        const glm::vec2& size = glm::vec2(1.f),
                          const float rotation = 0.f);

        void InsertState(std::string state, std::vector<std::pair<std::string, uint64_t>> tilesFrameDuration);

        void UpdateFrame(const size_t deltaFrame);

        void SetState(const std::string &newState);

        void Render() const override;
       
    private:

        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> statesMap;

        uint64_t currentFrame = 0;

        uint64_t currentAnimationFrame = 0;

        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator pCurrentAnimateDurations;

        mutable bool isNormalCondition = false;
    };

}