#include "SpriteAnimator.h"
#include "TextureManager.h"
#include <iostream>

namespace RenderEngine 
{
	SpriteAnimator::SpriteAnimator(std::shared_ptr<TextureManager> pTexture, 
									 std::string initTile, 
		                                std::shared_ptr<ShaderManager> pShaderManager) : 
											Sprite(std::move(pTexture), std::move(initTile), std::move(pShaderManager))
	{
		pCurrentAnimateDurations = statesMap.end();
	}

	void SpriteAnimator::InsertState(std::string state, std::vector<std::pair<std::string, uint64_t>> tilesFrameDuration)
	{
		statesMap.emplace(std::move(state), std::move(tilesFrameDuration));
	}

	void SpriteAnimator::UpdateFrame(const uint64_t deltaFrame)
	{
		if (pCurrentAnimateDurations != statesMap.end())
		{
			currentAnimationFrame += deltaFrame;

			while (currentAnimationFrame >= pCurrentAnimateDurations->second[currentFrame].second)
			{
				currentAnimationFrame -= pCurrentAnimateDurations->second[currentFrame].second;
				++currentFrame;
				isNormalCondition = true;
				if (currentFrame == pCurrentAnimateDurations->second.size())
				{
					currentFrame = 0;
				}
			}
		}
	}

	void SpriteAnimator::SetState(const std::string &newState)
	{
		auto iter = statesMap.find(newState);
		if (iter == statesMap.end())
		{
			std::cerr << "Can't find state of animation :-( " << newState << std::endl;
		}
		if (iter != pCurrentAnimateDurations)
		{
			currentAnimationFrame = 0;
			currentFrame = 0;
			isNormalCondition = true;
			pCurrentAnimateDurations = iter;
		}
	}

	void SpriteAnimator::Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const
	{
		if (isNormalCondition)
		{
			auto tile = pTexture->GetTile(pCurrentAnimateDurations->second[currentFrame].first);

			const GLfloat textureCoords[] = {

				tile.leftBottom.x, tile.leftBottom.y,
				tile.leftBottom.x, tile.rightTop.y,
				tile.rightTop.x, tile.rightTop.y,
				tile.rightTop.x, tile.leftBottom.y,
			};

			textureBuffer.UpdateBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
			isNormalCondition = false;
		}
		Sprite::Render(position, size, rotation);
	}

}
