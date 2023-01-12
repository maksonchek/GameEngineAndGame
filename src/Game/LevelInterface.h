#pragma once 

#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <algorithm>

class GameObjectInterface;

/*!
* \brief Виртуальный класс, создержащий в себе поля и методы, общие для всех создаваемых уровней.
Наследование от этого класса при срздании уровня обязательно!
*/
class LevelInterface {
public:
	LevelInterface();
	static constexpr unsigned int BLOCK_SIZE = 16; ///<Размер в пикселях единицы уровня (например блок бетонной стены имеет данный размер)
	/*!
	* Функция, отвечающая за отрисовку уровня
	* Реализация:
	* \code
			for (const auto & currentLevelObject : levelObjects)
			{
				if (currentLevelObject)
				{
					currentLevelObject->Render();
				}
			}
    * \endcode
	*/
	virtual void Render() const;

	/*!
	* Метод, отвечающий за обмновление даныых об объектах на текущем уровне за единицу времени кадра
	*/
	virtual void Update(const double delta);
	
	/*!
	* Возвращает ширину уровня 
	*/
	virtual size_t GetLevelWidth() const;

	/*!
	* Возващает высоту уровня
	*/
	virtual size_t GetLevelHeight() const;

	/*!
	* Возвращает объекты, находящиеся рябом с игроком. Метод нужен для получения тех не многих объектов, с которыми рядом находится объект, относительно которого требуется найти объекты. Чтобы обработать предполагаемые взаимодействия этих объектов
	* \param bottomLeft - координаты левого нижнего угла игрового объекта, относительно которого ищется объекты рядом.
	* \param topRight - координаты правого верхнего угла игрового объекта, относительно которого ищется объекты рядом.
	* \return вектор указателей на игровые объекты, с которыми находится рядом объект, относительно которого требуется найти объекты поблизости
	* Реализация:
	* \code
	
				std::vector<std::shared_ptr<GameObjectInterface>> returnLevelObjects;
				returnLevelObjects.reserve(9);

				glm::vec2 newBottomLeft(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(widthPixels)), std::clamp(heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(heightPixels)));
				glm::vec2 newTopRight(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(widthPixels)), std::clamp(heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(heightPixels)));

				size_t startX = static_cast<size_t>(floor(newBottomLeft.x / BLOCK_SIZE));
				size_t endX = static_cast<size_t>(ceil(newTopRight.x / BLOCK_SIZE));

				size_t startY = static_cast<size_t>(floor(newTopRight.y / BLOCK_SIZE));
				size_t endY = static_cast<size_t>(ceil(newBottomLeft.y / BLOCK_SIZE));

				for (size_t currentColumn = startX; currentColumn < endX; currentColumn++)
				{
					for (size_t currentRow = startY; currentRow < endY; currentRow++)
					{
						auto& currentObject = levelObjects[currentRow * width + currentColumn];
						if (currentObject)
						{
							returnLevelObjects.push_back(currentObject);
						}
					}
				}

				if (endX >= width)
				{
					returnLevelObjects.push_back(levelObjects[levelObjects.size() - 1]);
				}
				if (startX <= 1)
				{
					returnLevelObjects.push_back(levelObjects[levelObjects.size() - 2]);
				}
				if (startY <= 1)
				{
					returnLevelObjects.push_back(levelObjects[levelObjects.size() - 3]);
				}
				if (endY >= height)
				{
					returnLevelObjects.push_back(levelObjects[levelObjects.size() - 4]);
				}

				return returnLevelObjects;
	* \endcode
	*/
	virtual std::vector<std::shared_ptr<GameObjectInterface>> GetLevelObjects(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;

protected:
	size_t width = 0; //Ширина уровня
	size_t height = 0; //Высота уровня
	unsigned int widthPixels = 0; //Ширина уровня в пикселях
	unsigned int heightPixels = 0; //Высота уровня в пикселях
	std::vector<std::shared_ptr<GameObjectInterface>> levelObjects; //Объекты, находящиеся на текущем уровне.
};