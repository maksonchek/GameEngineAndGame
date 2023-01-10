#include "SpriteAnimator.h"

#include "Sprite.h"

namespace RenderEngine {
    SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> pSprite) : 
                                                    pSprite(std::move(pSprite)), 
                                                    currentFrame(0), 
                                                    currentFrameDuration(this->pSprite->GetFrameDuration(0)), 
                                                    currentAnimationTime(0)
    {
    }

    void SpriteAnimator::Update(const double deltaTime)
    {
        currentAnimationTime += deltaTime;
        while (currentAnimationTime >= currentFrameDuration)
        {
            currentAnimationTime -= currentFrameDuration;
            ++currentFrame;
            if (currentFrame == pSprite->GetFramesCount())
            {
                currentFrame = 0;
            }
           currentFrameDuration = pSprite->GetFrameDuration(currentFrame);
        }
    }
}