#include <iostream> // консоль - cout
#include "Fraction.h"
#include "myFunk.h"

void printFraction(Fraction&);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");   // задаём русский текст
	system("chcp 1251");            // настраиваем кодировку консоли
	std::system("cls");

	std::cout << "Задача 2. Остальные операции с дробями\n";
	std::cout << "--------------------------------------\n" << std::endl;

	try
	{
		int numerator = 0, denominator = 0;

		numerator = userInput("Введите числитель дроби 1: ");
		denominator = userInput("Введите знаменатель дроби 1: ");
		Fraction f1(numerator, denominator);

		numerator = userInput("Введите числитель дроби 2: ");
		denominator = userInput("Введите знаменатель дроби 2: ");
		Fraction f2(numerator, denominator);

		printFraction(f1); std::cout << " + "; printFraction(f2);
		std::cout << " = ";
		Fraction temp = f1 + f2;
		printFraction(temp); std::cout << std::endl;
		
		printFraction(f1); std::cout << " - "; printFraction(f2);
		std::cout << " = ";
		temp = f1 - f2;
		printFraction(temp); std::cout << std::endl;

		printFraction(f1); std::cout << " * "; printFraction(f2);
		std::cout << " = ";
		temp = f1 * f2;
		printFraction(temp); std::cout << std::endl;

		printFraction(f1); std::cout << " / "; printFraction(f2);
		std::cout << " = ";
		temp = f1 / f2;
		printFraction(temp); std::cout << std::endl << std::endl;

		std::cout << "++"; printFraction(f1);
		std::cout << " * "; printFraction(f2);
		std::cout << " = ";
		temp = ++f1 * f2;
		printFraction(temp); std::cout << std::endl;
		std::cout << "Значение дроби 1 = ";
		printFraction(f1); std::cout << std::endl << std::endl;

		printFraction(f1); std::cout << "--";
		std::cout << " * "; printFraction(f2);
		std::cout << " = ";
		temp = f1-- * f2;
		printFraction(temp); std::cout << std::endl;
		std::cout << "Значение дроби 1 = ";
		printFraction(f1); std::cout << std::endl << std::endl;
		
		printFraction(f1); std::cout << "++";
		std::cout << " * "; printFraction(f2);
		std::cout << " = ";
		temp = f1++ * f2;
		printFraction(temp); std::cout << std::endl;
		std::cout << "Значение дроби 1 = ";
		printFraction(f1); std::cout << std::endl << std::endl;

		std::cout << "--"; printFraction(f1);
		std::cout << " * "; printFraction(f2);
		std::cout << " = ";
		temp = --f1 * f2;
		printFraction(temp); std::cout << std::endl;
		std::cout << "Значение дроби 1 = ";
		printFraction(f1); std::cout << std::endl << std::endl;

		temp = -f1;
		printFraction(temp); std::cout << std::endl;


		/*
		std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
		std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
		std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
		std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
		std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
		std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
		*/
	}
	catch (std::domain_error& err)
	{
		std::cout << "Ошибка: " << err.what() << std::endl;
	}
	catch (std::overflow_error& err)
	{
		std::cout << "Ошибка: " << err.what() << std::endl;
	}

	return 0;
}

/*
Задача 2. Остальные операции с дробями
В этом задании вы переопределите остальные операторы для класса дроби.

Необходимо переопределить операторы для класса Fraction из предыдущего задания:

сложение;
вычитание;
умножение;
деление;
унарный минус;
инкремент постфиксный и префиксный;
декремент постфиксный и префиксный.
Продемонстрируйте работу ваших операторов. Попросите пользователя ввести две дроби и покажите результат каждой операции. Операции декремента и инкремента отнимают и прибавляют к дроби 1 соответственно.

Составьте выражения, содержащие постфиксный и префиксный инкремент и декремент, чтобы продемонстрировать разницу между постфиксной и префиксной версиями.

Пример работы программы
Консоль
Введите числитель дроби 1: 3
Введите знаменатель дроби 1: 4
Введите числитель дроби 2: 4
Введите знаменатель дроби 2: 5
3/4 + 4/5 = 31/20
3/4 - 4/5 = -1/20
3/4 * 4/5 = 3/5
3/4 / 4/5 = 15/16
++3/4 * 4/5 = 7/5
Значение дроби 1 = 7/4
7/4-- * 4/5 = 7/5
Значени дроби 1 = 3/4
*/

void printFraction(Fraction& fr)
{
	using namespace std;

	cout << fr.getNumer() << "/" << fr.getDenom();
}
