#pragma once

#include <iostream> // std

class Fraction
{
private:
	int whole_;			// ����� �����
	int numerator_;		// ���������
	int denominator_;	// �����������
	double div();
	void toProperFract(Fraction&);		// � ���������� �����
	void toImproperFract(Fraction&);	// � ������������ �����
	void exception(Fraction&);			// �������� ����������

public:
	Fraction(int numerator, int denominator);
	Fraction(int whole);

	int getWhole();
	int getNumer();
	int getDenom();

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