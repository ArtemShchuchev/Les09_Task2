#pragma once

#include <iostream> // std

class Fraction
{
private:
	int numerator_;
	int denominator_;
	double div();
	void reductFract(Fraction&); // сокращение дроби по ссылке
	void exception(Fraction&);

public:
	Fraction(int numerator, int denominator);
	Fraction(int num);

	int getNumer();
	int getDenom();

	bool operator == (Fraction);
	bool operator != (Fraction);
	bool operator < (Fraction);
	bool operator > (Fraction);
	bool operator <= (Fraction);
	bool operator >= (Fraction);

	Fraction operator + (const Fraction&);
	Fraction operator - (const Fraction&);
	Fraction operator * (const Fraction&);
	Fraction operator / (const Fraction&);
	Fraction operator ++ ();
	Fraction operator ++ (int);
	Fraction operator -- ();
	Fraction operator -- (int);

	Fraction operator - ();
};