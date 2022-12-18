#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "Sprite.h"

namespace RenderEngine {

    class SpriteAnimator : public Sprite{
    public:

        SpriteAnimator(const std::shared_ptr<TextureManager> pTexture,
                 const std::string initTile,
                   const std::shared_ptr<ShaderManager> pShaderManager);

        void InsertState(std::string state, std::vector<std::pair<std::string, uint64_t>> tilesFrameDuration);

        void UpdateFrame(const uint64_t deltaFrame);

        void SetState(const std::string &newState);

        void Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
       
    private:

        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> statesMap;

        uint64_t currentFrame = 0;

        uint64_t currentAnimationFrame = 0;

        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator pCurrentAnimateDurations;

        mutable bool isNormalCondition = false;
    };

}