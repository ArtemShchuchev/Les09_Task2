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
	if (fr.numerator_ == 0) throw std::domain_error("��������� = 0, ������� �� ����������.");
	if (fr.denominator_ == 0) throw std::overflow_error("�������� = 0, ������� ��������� � �������������.");
}

Fraction::Fraction(int numerator, int denominator)
{
	numerator_ = numerator;
	denominator_ = denominator;
	exception(*this); // �������� ����������
}

Fraction::Fraction(int num)
{
	numerator_ = num;
	denominator_ = num;
	exception(*this); // �������� ����������
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
	// ���������� �������� ������ ���� ������
	// �������������� �������� �������
	return (div() == fr.div());
}
bool Fraction::operator != (Fraction fr)
{
	// ���������� ������� ������� � ������� �������������� ==
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
	if (denominator_ != fr.denominator_) // ���������� � ���. �����������
	{
		tempFr.numerator_ *= denominator_;
		tempFr.numerator_ += numerator_ * fr.denominator_;
		tempFr.denominator_ *= denominator_;
	}
	else tempFr.numerator_ += numerator_; // ����� �����������

	reductFract(tempFr); // ���������� �����
	exception(tempFr); // �������� ����������

	return tempFr;
}

Fraction Fraction::operator - (const Fraction& fr)
{
	Fraction tempFr = fr;
	if (denominator_ != fr.denominator_) // ���������� � ���. �����������
	{
		tempFr.numerator_ *= denominator_;
		tempFr.numerator_ = numerator_ * fr.denominator_ - tempFr.numerator_;
		tempFr.denominator_ *= denominator_;
	}
	else tempFr.numerator_ = numerator_ - tempFr.numerator_; // ����� �����������

	reductFract(tempFr); // ���������� �����
	exception(tempFr); // �������� ����������

	return tempFr;
}

Fraction Fraction::operator * (const Fraction& fr)
{
	Fraction tempFr = fr;
	
	tempFr.numerator_ *= numerator_;
	tempFr.denominator_ *= denominator_;

	reductFract(tempFr); // ���������� �����

	return tempFr;
}

Fraction Fraction::operator / (const Fraction& fr)
{
	Fraction tempFr = fr;
	
	tempFr.numerator_ = numerator_ * fr.denominator_;
	tempFr.denominator_ = denominator_ * fr.numerator_;

	reductFract(tempFr); // ���������� �����

	return tempFr;
}

// ���������� ++
Fraction Fraction::operator++()
{
	*this = (*this) + 1;
	exception(*this); // �������� ����������
	return *this;
}

// ����������� ++
Fraction Fraction::operator++(int num)
{
	Fraction temp = (*this);
	++(*this);	// ��������� ���������� ����������
	exception(*this); // �������� ����������
	return temp;
}

// ���������� --
Fraction Fraction::operator--()
{
	*this = (*this) - 1;
	exception(*this); // �������� ����������
	return *this;
}

// ����������� --
Fraction Fraction::operator--(int num)
{
	Fraction retThis = (*this);
	--(*this);	// ��������� ���������� ����������
	exception(*this); // �������� ����������
	return retThis;
}

// ������� -
Fraction Fraction::operator-()
{
	this->numerator_ *= -1;
	return (*this);
}
