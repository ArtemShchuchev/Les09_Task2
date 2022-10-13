#pragma once

#include <iostream> // std

class Fraction
{
private:
	int whole_;			// целая часть
	int numerator_;		// числитель
	int denominator_;	// знаменатель
	double div();
	void toProperFract(Fraction&);		// в правильную дробь
	void toImproperFract(Fraction&);	// в неправильную дробь
	void exception(Fraction&);			// проверка исключений

public:
	Fraction(int numerator, int denominator);
	Fraction(int whole);

	int getWhole();
	int getNumer();
	int getDenom();

	bool operator == (Fraction);
	bool operator != (Fraction);
	bool operator < (Fraction);
	bool operator > (Fraction);
	bool operator <= (Fraction);
	bool operator >= (Fraction);

	Fraction operator + (Fraction);
	Fraction operator - (Fraction);
	Fraction operator * (Fraction);
	Fraction operator / (Fraction);
	Fraction operator ++ ();
	Fraction operator ++ (int);
	Fraction operator -- ();
	Fraction operator -- (int);

	Fraction operator - ();
};