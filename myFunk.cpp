#include "myFunk.h"

/* 
    Будет запрашивать у пользователя ввод данных
    пока не будут введены верные данные.
    В случае успеха, вернет int.
    При ошибке ввода, сбросит и очистит cin
    и снова попросит ввести данные
*/
int userInput(const std::string userText)
{
    int uData = 0;
    bool err = true;

    do
    {
        std::cout << userText; std::cin >> uData;

        if (err = std::cin.fail()) std::cin.clear(); // ошибка ввода
        int ch; // поиск и очистка лишних введенных символов
        while ((ch = std::cin.get()) != '\n' && ch != EOF);
    } while (err);

    return uData;
}
