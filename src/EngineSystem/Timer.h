#pragma once

#include <functional>

/*!
* \brief �����, ����������� ��� �������/�������� � ����, ������� ����������� � �� ������ ����������. ����� �� ����� ���� ����������
*/
class Timer {
public:
    Timer();

    /*!
    * ������� �������������, ������ �� ����� �������. ��������
    * \param delta -������� ������� �����
    * ����������:
    * \code
             if (isRunning)
            {
                timeLeft -= delta;
                if (timeLeft <= 0)
                {
                    isRunning = false;
                    callback();
                }
            }
    * \endcode
    */
    void Update(const double delta);

    /*!
    * �������, ����������� ������
    * \param duration - ������������ �������
    * \code
        timeLeft = duration;
        isRunning = true;
    * \endcode
    */
    void Start(const double duration);

    /*!
    * �������� � ������������� � ������� ������� ��������� �������
    */
    void SetCallback(std::function<void()> callback);

private:
    std::function<void()> callback; ///< ������� ��������� ������, ������ ��� ���������/���������� �������
    double timeLeft; ///< ����� ������������ ������������� �� ������� �������
    bool isRunning; ///< ������� �� ������ ��� ���
};
