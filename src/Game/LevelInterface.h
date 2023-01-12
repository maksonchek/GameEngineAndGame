#pragma once 

#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <algorithm>

class GameObjectInterface;

/*!
* \brief ����������� �����, ����������� � ���� ���� � ������, ����� ��� ���� ����������� �������.
������������ �� ����� ������ ��� �������� ������ �����������!
*/
class LevelInterface {
public:
	LevelInterface();
	static constexpr unsigned int BLOCK_SIZE = 16; ///<������ � �������� ������� ������ (�������� ���� �������� ����� ����� ������ ������)
	/*!
	* �������, ���������� �� ��������� ������
	* ����������:
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
	* �����, ���������� �� ����������� ������ �� �������� �� ������� ������ �� ������� ������� �����
	*/
	virtual void Update(const double delta);
	
	/*!
	* ���������� ������ ������ 
	*/
	virtual size_t GetLevelWidth() const;

	/*!
	* ��������� ������ ������
	*/
	virtual size_t GetLevelHeight() const;

	/*!
	* ���������� �������, ����������� ����� � �������. ����� ����� ��� ��������� ��� �� ������ ��������, � �������� ����� ��������� ������, ������������ �������� ��������� ����� �������. ����� ���������� �������������� �������������� ���� ��������
	* \param bottomLeft - ���������� ������ ������� ���� �������� �������, ������������ �������� ������ ������� �����.
	* \param topRight - ���������� ������� �������� ���� �������� �������, ������������ �������� ������ ������� �����.
	* \return ������ ���������� �� ������� �������, � �������� ��������� ����� ������, ������������ �������� ��������� ����� ������� ����������
	* ����������:
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
	size_t width = 0; //������ ������
	size_t height = 0; //������ ������
	unsigned int widthPixels = 0; //������ ������ � ��������
	unsigned int heightPixels = 0; //������ ������ � ��������
	std::vector<std::shared_ptr<GameObjectInterface>> levelObjects; //�������, ����������� �� ������� ������.
};