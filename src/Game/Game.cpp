#include "Game.h"
#include "../Renderer/ShaderManager.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/TextureManager.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/SpriteAnimator.h"
#include "../Game/SpaceShip.h"
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
	Game::Game(const glm::vec2 windowSize) : gameState(GameState::Active), windowSize(windowSize)
	{
		keysForClick.fill(false);
	}

	Game::~Game()
	{

	}

	void Game::Render()
	{
        //ResourceManager::GetSpriteAnimator("NewSpriteAnimator")->Render();
        if (pGameObject) {
            pGameObject->Render();
        }
	}

	void Game::Update(const uint64_t deltaTime)
	{
        //ResourceManager::GetSpriteAnimator("NewSpriteAnimator")->UpdateFrame(deltaTime);
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
        auto pDefaultShaderProgram = ResourceManager::LoadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't load shaders: " << "DefaultShader" << std::endl;
            return false;
        }

        auto pSpriteShaderProgram = ResourceManager::LoadShaders("SpriteShader", "res/shaders/vertexSprite.txt", "res/shaders/fragmentSprite.txt");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return false;
        }

        auto tex = ResourceManager::LoadTexture("DefaultTexture", "res/textures/assets.png");

        std::vector<std::string> tilesNames =
        {
            "block",
            "topBlock",
            "bottomBlock",
            "leftBlock",
            "rightBlock",
            "topLeftBlock",
            "topRightBlock",
            "bottomLeftBlock",

            "bottomRightBlock",
            "beton",
            "topBeton",
            "bottomBeton",
            "leftBeton",
            "rightBeton",
            "topLeftBeton",
            "topRightBeton",

            "bottomLeftBeton",
            "bottomRightBeton",
            "water1",
            "water2",
            "water3",
            "trees",
            "ice",
            "wall",

            "eagle",
            "deadEagle",
            "nothing",
            "respawn1",
            "respawn2",
            "respawn3",
            "respawn4"
        };
        auto pTextureAtlas = ResourceManager::LoatTextureAtlas("DefaultTextureAtlas", "res/textures/assets.png", std::move(tilesNames), 16, 16);

        auto pSpriteAnimator = ResourceManager::LoadSpriteAnimator("NewSpriteAnimator", "DefaultTextureAtlas", "SpriteShader", 50, 50, "bottomRightBlock");
        pSpriteAnimator->SetPosition(glm::vec2(300, 300));
        std::vector<std::pair<std::string, uint64_t>> spriteState;
        spriteState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
        spriteState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
        spriteState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

        pSpriteAnimator->InsertState("spriteState", std::move(spriteState));
        pSpriteAnimator->SetState("spriteState");

        pDefaultShaderProgram->UseShader();
        pDefaultShaderProgram->SetInt("textures", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);

        pDefaultShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix);

        pSpriteShaderProgram->UseShader();
        pSpriteShaderProgram->SetInt("textures", 0);
        pSpriteShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix);

        std::vector<std::string> gameObjectTilesNames =
        {
            "top1",
            "top2",
            "left1",
            "left2",
            "bottom1",
            "bottom2",
            "right1",
            "right2",
        };


        auto pObjectTextureAtlas = ResourceManager::LoatTextureAtlas("SpaceShipAtlas", "res/textures/tankAtlas.png", std::move(gameObjectTilesNames), 16, 16);
        auto pGameObjectAniomation = ResourceManager::LoadSpriteAnimator("SpaceShipAnimate", "SpaceShipAtlas", "SpriteShader", 100, 100, "top1");

        std::vector<std::pair<std::string, uint64_t>> gameObjectTopState;
        gameObjectTopState.emplace_back(std::make_pair<std::string, uint64_t>("top1", 500000000));
        gameObjectTopState.emplace_back(std::make_pair<std::string, uint64_t>("top2", 500000000));

        std::vector<std::pair<std::string, uint64_t>> gameObjectBottomState;
        gameObjectBottomState.emplace_back(std::make_pair<std::string, uint64_t>("bottom1", 500000000));
        gameObjectBottomState.emplace_back(std::make_pair<std::string, uint64_t>("bottom2", 500000000));

        std::vector<std::pair<std::string, uint64_t>> gameObjectRightState;
        gameObjectRightState.emplace_back(std::make_pair<std::string, uint64_t>("right1", 500000000));
        gameObjectRightState.emplace_back(std::make_pair<std::string, uint64_t>("right2", 500000000));

        std::vector<std::pair<std::string, uint64_t>> gameObjectLeftState;
        gameObjectLeftState.emplace_back(std::make_pair<std::string, uint64_t>("left1", 500000000));
        gameObjectLeftState.emplace_back(std::make_pair<std::string, uint64_t>("left2", 500000000));

        pGameObjectAniomation->InsertState("objectTopState", std::move(gameObjectTopState));
        pGameObjectAniomation->InsertState("objectLeftState", std::move(gameObjectLeftState));
        pGameObjectAniomation->InsertState("objectRightState", std::move(gameObjectRightState));
        pGameObjectAniomation->InsertState("objectBottomState", std::move(gameObjectBottomState));

        pGameObjectAniomation->SetState("objectTopState");

        pGameObject = std::make_unique<SpaceShip>(pGameObjectAniomation, 0.0000001f, glm::vec2(100.f, 100.f));
         
        return true; 
	}