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
        void Update(const double deltaTime);

    private:
        std::shared_ptr<Sprite> pSprite;
        size_t currentFrame;
        double currentFrameDuration;
        double currentAnimationTime;
    };

}