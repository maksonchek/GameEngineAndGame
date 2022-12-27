#pragma once

#include <memory>

namespace RenderEngine {

    class Sprite;

    class SpriteAnimator {
    public:
        SpriteAnimator(std::shared_ptr<Sprite> pSprite);
        size_t GetCurrentFrame() const 
        { 
            return currentFrame; 
        }
        void Update(const uint64_t deltaTime);

    private:
        std::shared_ptr<Sprite> pSprite;
        size_t currentFrame;
        uint64_t currentFrameDuration;
        uint64_t currentAnimationTime;
    };

}