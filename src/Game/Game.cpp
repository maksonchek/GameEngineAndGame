#include "Game.h"
#include "../Renderer/ShaderManager.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/TextureManager.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/SpriteAnimator.h" 
#include "../Game/GameObjects/TankGameObject.h" //Инклудируем созданный танк
#include "../Game/GameObjects/Bullet.h" //Инклудируем созданную пулю
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Level.h" //Инклудируем созданный уровень
#include "../PhysicsEngine/PhysicsEngine.h"

	Game::Game(const glm::vec2 windowSize) : gameState(GameState::Active), windowSize(windowSize)
	{
		keysForClick.fill(false); //Это разработчик трогать не должен
	}

	Game::~Game()
	{

	}
      
	void Game::Render() //У созданных уровней и персонажей разработчик вызывает функцию рендеринга, которые нужнно отрисовать при запуске игры
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
            pLevel->Update(deltaTime); //Вызов функции покадровой обработки у уровня
        }
        if (pGameObject) {

            if (keysForClick[GLFW_KEY_W]) //Обработка нажатий на кнопки для управления танком
            {
                pGameObject->SetOrientation(TankGameObject::ObjectOrientation::Top);
                pGameObject->SetVelocity(pGameObject->GetMaxVelocity());
            }
            else if (keysForClick[GLFW_KEY_A])
            {
                pGameObject->SetOrientation(TankGameObject::ObjectOrientation::Left);
                pGameObject->SetVelocity(pGameObject->GetMaxVelocity());
            }
            else if (keysForClick[GLFW_KEY_S])
            {
                pGameObject->SetOrientation(TankGameObject::ObjectOrientation::Bottom);
                pGameObject->SetVelocity(pGameObject->GetMaxVelocity());
            }
            else if (keysForClick[GLFW_KEY_D])
            {
                pGameObject->SetOrientation(TankGameObject::ObjectOrientation::Right);
                pGameObject->SetVelocity(pGameObject->GetMaxVelocity());
            }
            else
            {
                pGameObject->SetVelocity(0);
            }
            if (pGameObject && keysForClick[GLFW_KEY_SPACE])
            {
                pGameObject->Fire();
            }
            pGameObject->UpdateFrame(deltaTime);  //Вызов функции покадровой обработки у танка
        }
	}

	void Game::SetClick(const int key, const int action)
	{
		keysForClick[key] = action;  //Это разработчик трогать не должен
	}

	bool Game::InitGame()
	{
        ResourceManager::LoadResourcesFromJSON("res/gameResources.json"); //Это разработчик трогать не должен

        auto pSpriteShaderProgram = ResourceManager::GetShaderManager("SpriteShader");

        if (!pSpriteShaderProgram) //Это разработчик трогать не должен
        {
            std::cerr << "Didn't found shaders :-( " << "SpriteShader" << std::endl;
        }

        pLevel = std::make_shared<Level>(ResourceManager::GetLevels()[0]); //Устанавливаем уровень который хотим запустить. Их может быть много, если в gameResources, они были размечены
        windowSize.x = static_cast<int>(pLevel->GetLevelWidth()); //Это разработчик трогать не должен
        windowSize.y = static_cast<int>(pLevel->GetLevelHeight()); //Это разработчик трогать не должен
        PhysicsEngineManager::PhysicsEngine::SetCurrentLevel(pLevel); //Это разработчик трогать не должен

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f); //Это разработчик трогать не должен


        pSpriteShaderProgram->UseShader(); //Это разработчик трогать не должен
        pSpriteShaderProgram->SetInt("textures", 0); //Это разработчик трогать не должен
        pSpriteShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix); //Это разработчик трогать не должен


        pGameObject = std::make_shared<TankGameObject>(0.05, pLevel->GetPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f); //Инициализация танке по координатам респавна
        PhysicsEngineManager::PhysicsEngine::AddDynamicGameObject(pGameObject); //Придание танку физических свойств
         
        return true; 
	}

    size_t Game::GetCurrentLevelWidth() const
    {
        return pLevel->GetLevelWidth();  //Это разработчик трогать не должен
    } 

    size_t Game::GetCurrentLevelHeight() const
    { 
        return pLevel->GetLevelHeight();  //Это разработчик трогать не должен
    }