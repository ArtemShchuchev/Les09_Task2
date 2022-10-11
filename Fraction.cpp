#include "Fraction.h"


double Fraction::div() { return numerator_ / denominator_; }

void Fraction::reductFract(Fraction& fr)
{
	int temp_denom = fr.denominator_;
	while (temp_denom > 1)
	{
		if (!(fr.numerator_ % temp_denom) && !(fr.denominator_ % temp_denom))
		{
			fr.numerator_ /= temp_denom;
			fr.denominator_ /= temp_denom;
			break;
		}
		--temp_denom;
	};
}

void Fraction::exception(Fraction& fr)
{
	if (fr.numerator_ == 0) throw std::domain_error("Числитель = 0, решения не существует.");
	if (fr.denominator_ == 0) throw std::overflow_error("Делитель = 0, решение стремится к бесконечности.");
}

Fraction::Fraction(int numerator, int denominator)
{
	numerator_ = numerator;
	denominator_ = denominator;
	exception(*this); // проверка исключений
}

Fraction::Fraction(int num)
{
	numerator_ = num;
	denominator_ = num;
	exception(*this); // проверка исключений
}

int Fraction::getNumer()
{
	return numerator_;
}

int Fraction::getDenom()
{
	return denominator_;
}

bool Fraction::operator == (Fraction fr)
{
	// сравнивает отдельно каждое поле класса
	// предварительно выполнив деление
	return (div() == fr.div());
}
bool Fraction::operator != (Fraction fr)
{
	// сравнивает целиком объекты с помощью перегруженного ==
	return !(*this == fr);
}
bool Fraction::operator < (Fraction fr)
{
	return (div() < fr.div());
}
bool Fraction::operator > (Fraction fr)
{
	return (fr.div() < div());
}
bool Fraction::operator <= (Fraction fr)
{
	return !(div() > fr.div());
}
bool Fraction::operator >= (Fraction fr)
{
	return !(div() < fr.div());
}

Fraction Fraction::operator + (const Fraction& fr)
{
	Fraction tempFr = fr;
	if (denominator_ != fr.denominator_) // приведение к общ. знаменателю
	{
		tempFr.numerator_ *= denominator_;
		tempFr.numerator_ += numerator_ * fr.denominator_;
		tempFr.denominator_ *= denominator_;
	}
	else tempFr.numerator_ += numerator_; // общий знаменатель

	reductFract(tempFr); // сокращение дроби
	exception(tempFr); // проверка исключений

	return tempFr;
}

Fraction Fraction::operator - (const Fraction& fr)
{
	Fraction tempFr = fr;
	if (denominator_ != fr.denominator_) // приведение к общ. знаменателю
	{
		tempFr.numerator_ *= denominator_;
		tempFr.numerator_ = numerator_ * fr.denominator_ - tempFr.numerator_;
		tempFr.denominator_ *= denominator_;
	}
	else tempFr.numerator_ = numerator_ - tempFr.numerator_; // общий знаменатель

	reductFract(tempFr); // сокращение дроби
	exception(tempFr); // проверка исключений

	return tempFr;
}

Fraction Fraction::operator * (const Fraction& fr)
{
	Fraction tempFr = fr;
	
	tempFr.numerator_ *= numerator_;
	tempFr.denominator_ *= denominator_;

	reductFract(tempFr); // сокращение дроби

	return tempFr;
}

Fraction Fraction::operator / (const Fraction& fr)
{
	Fraction tempFr = fr;
	
	tempFr.numerator_ = numerator_ * fr.denominator_;
	tempFr.denominator_ = denominator_ * fr.numerator_;

	reductFract(tempFr); // сокращение дроби

	return tempFr;
}

// префиксный ++
Fraction Fraction::operator++()
{
	*this = (*this) + 1;
	exception(*this); // проверка исключений
	return *this;
}

// постфиксный ++
Fraction Fraction::operator++(int num)
{
	Fraction temp = (*this);
	++(*this);	// использую префиксную перегрузку
	exception(*this); // проверка исключений
	return temp;
}

// префиксный --
Fraction Fraction::operator--()
{
	*this = (*this) - 1;
	exception(*this); // проверка исключений
	return *this;
}

// постфиксный --
Fraction Fraction::operator--(int num)
{
	Fraction retThis = (*this);
	--(*this);	// использую префиксную перегрузку
	exception(*this); // проверка исключений
	return retThis;
}

// унарный -
Fraction Fraction::operator-()
{
	this->numerator_ *= -1;
	return (*this);
}
