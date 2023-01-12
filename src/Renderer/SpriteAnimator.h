#pragma once

#include <memory>

namespace RenderEngine {

    class Sprite;
    /*!
    * \brief �����, ���������� �� �������� ��������, �.� ����� �������� ��� ����������� ������� � ��� ������� � ������������ ��������������
    */
    class SpriteAnimator {
    public:
        /*!
        * ����������� ������. � �� ������ ������������� �����-���� �������� ����� ������
        * \param pSprite - ����� ��������� �� ������ ������� 
        *                                           : 
                                                    pSprite(std::move(pSprite)),  // ���������� �� ����������� ������� ��� ������ � ������ ���� ������
                                                    currentFrame(0), // �������� �������� � ������� �����
                                                    currentFrameDuration(this->pSprite->GetFrameDuration(0)), // �������� �� ������� ������������ �����
                                                    currentAnimationTime(0) //�������� ������ � ����
        */
        SpriteAnimator(std::shared_ptr<Sprite> pSprite);
        size_t GetCurrentFrame() const 
        { 
            return currentFrame; 
        }
        
        /*!
        * �����, ����������� �������� ���������
        * \param - deltaTime ����� �������� �������� �����
        * ����������: 
        * \code
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
        * \endcode
        */
        void Update(const double deltaTime);

    private:
        std::shared_ptr<Sprite> pSprite; ///<����� ��������� �� ������ �������
        size_t currentFrame; ///<������� ����
        double currentFrameDuration; ///<������������ �����
        double currentAnimationTime; ///<����� ����� ����� ��������
    };

}