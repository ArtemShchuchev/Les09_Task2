#include "myFunk.h"

/* 
    ����� ����������� � ������������ ���� ������
    ���� �� ����� ������� ������ ������.
    � ������ ������, ������ int.
    ��� ������ �����, ������� � ������� cin
    � ����� �������� ������ ������
*/
int userInput(const std::string userText)
{
    int uData = 0;
    bool err = true;

    do
    {
        std::cout << userText; std::cin >> uData;

        if (err = std::cin.fail()) std::cin.clear(); // ������ �����
        int ch; // ����� � ������� ������ ��������� ��������
        while ((ch = std::cin.get()) != '\n' && ch != EOF);
    } while (err);

    return uData;
}
