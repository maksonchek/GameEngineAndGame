#include "Game.h"
#include "../Renderer/ShaderManager.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/TextureManager.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/SpriteAnimator.h"
#include "../Game/GameObjects/SpaceShip.h"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Level.h"

	Game::Game(const glm::vec2 windowSize) : gameState(GameState::Active), windowSize(windowSize)
	{
		keysForClick.fill(false);
	}

	Game::~Game()
	{

	}
      
	void Game::Render()
	{
        if (pGameObject) 
        {
            pGameObject->Render();
        }
        if (pLevel)
        {
            pLevel->Render();
        }
	}

	void Game::Update(const double deltaTime)
	{
        if (pLevel)
        {
            pLevel->Update(deltaTime);
        }
        if (pGameObject) {

            if (keysForClick[GLFW_KEY_W])
            {
                pGameObject->SetOrientation(SpaceShip::ObjectOrientation::Top);
                pGameObject->Move(true);
            }
            else if (keysForClick[GLFW_KEY_A])
            {
                pGameObject->SetOrientation(SpaceShip::ObjectOrientation::Left);
                pGameObject->Move(true);
            }
            else if (keysForClick[GLFW_KEY_S])
            {
                pGameObject->SetOrientation(SpaceShip::ObjectOrientation::Bottom);
                pGameObject->Move(true);
            }
            else if (keysForClick[GLFW_KEY_D])
            {
                pGameObject->SetOrientation(SpaceShip::ObjectOrientation::Right);
                pGameObject->Move(true);
            }
            else
            {
                pGameObject->Move(false);
            }
            pGameObject->UpdateFrame(deltaTime);
        }
	}

	void Game::SetClick(const int key, const int action)
	{
		keysForClick[key] = action;
	}

	bool Game::InitGame()
	{
        ResourceManager::LoadResourcesFromJSON("res/gameResources.json");

        auto pSpriteShaderProgram = ResourceManager::GetShaderManager("SpriteShader");

        if (!pSpriteShaderProgram)
        {
            std::cerr << "Didn't found shaders :-( " << "SpriteShader" << std::endl;
        }

        pLevel = std::make_unique<Level>(ResourceManager::GetLevels()[0]);
        windowSize.x = static_cast<int>(pLevel->GetLevelWidth());
        windowSize.y = static_cast<int>(pLevel->GetLevelHeight());
       
        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);


        pSpriteShaderProgram->UseShader();
        pSpriteShaderProgram->SetInt("textures", 0);
        pSpriteShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix);


        pGameObject = std::make_unique<SpaceShip>(0.05, pLevel->GetPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);

         
        return true; 
	}

    size_t Game::GetCurrentLevelWidth() const
    {
        return pLevel->GetLevelWidth();
    }

    size_t Game::GetCurrentLevelHeight() const
    {
        return pLevel->GetLevelHeight();
    }