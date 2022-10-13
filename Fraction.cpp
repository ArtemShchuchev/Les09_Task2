#include "Fraction.h"


double Fraction::div()
{
	exception(*this); // �������� ����������
	toImproperFract(*this);	// � ������������ �����

	double temp = static_cast<double>(numerator_) / denominator_;

	toProperFract(*this);	// � ���������� �����
	return temp;
}

//	������� � ���������� �����
//		105		  3		  1
//		---	->	17-	->	17-
//		 6		  6		  2
void Fraction::toProperFract(Fraction& f)
{
	exception(f); // �������� ����������

	if (f.numerator_ / f.denominator_)	// ���� ����� ������������
	{
		int znak = 1;	// ����������, ��� ����� �������������
		if (f.whole_ < 0)
		{
			f.whole_ *= -1;		// ������ �����
			znak = -1;			// ����� �������������
		}
		if (f.numerator_ < 0)
		{
			f.numerator_ *= -1;	// ������ �����
			znak = -1;			// ����� �������������
		}

		f.whole_ += f.numerator_ / f.denominator_;
		f.numerator_ %= f.denominator_;
		f.whole_ *= znak;		// ������ ����
	}

	// ������� ����� (��� ����� ���������)
	int multiplier = f.numerator_ < 0 ? f.numerator_ * -1 : f.numerator_;
	while (multiplier > 1)
	{
		// ���� ����������� ������� �� multiplier ��� �������
		// � ��������� ������� �� multiplier ��� �������
		if (!(f.denominator_ % multiplier) && !(f.numerator_ % multiplier))
		{
			f.numerator_ /= multiplier;
			f.denominator_ /= multiplier;
			break;
		}
		--multiplier;
	};
}

//	������� � ������������ �����
//		 1		7
//		2-	->	-
//		 3		3
void Fraction::toImproperFract(Fraction& f)
{
	if (f.whole_)	// ���� ����� ����������
	{
		int znak = 1;	// ����������, ��� ����� �������������
		if (f.whole_ < 0)
		{
			f.whole_ *= -1;		// ������ �����
			znak = -1;			// ����� �������������
		}
		if (f.numerator_ < 0)
		{
			f.numerator_ *= -1;	// ������ �����
			znak = -1;			// ����� �������������
		}

		f.numerator_ += f.whole_ * f.denominator_;
		f.whole_ = 0;
		f.numerator_ *= znak;	// ������ ����
	}
}

void Fraction::exception(Fraction& fr)
{
	if ( !(fr.whole_ || fr.numerator_) && fr.denominator_ == 0 )
	{
		throw std::domain_error("��������� � ����������� = 0, ������� �� ����������.");
	}
	if (fr.denominator_ == 0) throw std::overflow_error("�������� = 0, ������� ��������� � �������������.");
}

Fraction::Fraction(int numerator, int denominator)
{
	numerator_ = numerator;
	denominator_ = denominator;
	whole_ = 0;
	if (denominator_ < 0) // ��������/������ ������
	{
		denominator_ *= -1;
		numerator_ *= -1;
	}
	exception(*this);		// �������� ����������
	toProperFract(*this);	// � ���������� �����
}

Fraction::Fraction(int whole)
{
	numerator_ = 0;
	denominator_ = 1;
	whole_ = whole;
	exception(*this); // �������� ����������
}

int Fraction::getWhole()
{
	return whole_;
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

Fraction Fraction::operator + (Fraction second)
{
	Fraction first = *this;
	
	// � ������������ �����
	toImproperFract(first);
	toImproperFract(second);
	
	// ���������� � ���. �����������
	if (first.denominator_ != second.denominator_)
	{
		first.numerator_ *= second.denominator_;
		second.numerator_ *= first.denominator_;
		// ������ ����������� - �� �����
		first.denominator_ *= second.denominator_;
		//second.denominator_ = first.denominator_;
	}
	
	// ��� ����� �����������
	first.numerator_ += second.numerator_;
	
	// � ���������� �����
	toProperFract(first);

	return first;
}

Fraction Fraction::operator - (Fraction second)
{
	Fraction first = *this;

	// � ������������ �����
	toImproperFract(first);
	toImproperFract(second);

	// ���������� � ���. �����������
	if (first.denominator_ != second.denominator_)
	{
		first.numerator_ *= second.denominator_;
		second.numerator_ *= first.denominator_;
		// ������ ����������� - �� �����
		first.denominator_ *= second.denominator_;
		//second.denominator_ = first.denominator_;
	}

	// ��� ����� �����������
	first.numerator_ -= second.numerator_;

	// � ���������� �����
	toProperFract(first);

	return first;
}

Fraction Fraction::operator * (Fraction fr)
{
	// � ������������ �����
	toImproperFract(*this);
	toImproperFract(fr);

	fr.numerator_ *= this->numerator_;
	fr.denominator_ *= this->denominator_;

	// � ���������� �����
	toProperFract(*this);
	toProperFract(fr);

	return fr;
}

Fraction Fraction::operator / (Fraction fr)
{
	// � ������������ �����
	toImproperFract(*this);
	toImproperFract(fr);

	int znak = 1;	// ����������, ��� ����� �������������
	int tempDenom = fr.denominator_; // �������� ��������

	// ����������� = ���������_2 * �����������_1
	fr.denominator_ = fr.numerator_ * this->denominator_;
	if (fr.numerator_ < 0) // �������� ���� ���������_2
	{
		fr.denominator_ *= -1;	// ������ �����
		znak *= -1;					// ������� ����
	}
	// ��������� = ���������_1 * �����������_2
	fr.numerator_ = this->numerator_ * tempDenom;
	// ��������� 1, �� ���� ��������� �� ����
	fr.numerator_ *= znak;		// ����������� ����

	// � ���������� �����
	toProperFract(*this);
	toProperFract(fr);

	return fr;
}

// ���������� ++
Fraction Fraction::operator++()
{
	*this = (*this) + 1;
	return *this;
}

// ����������� ++
Fraction Fraction::operator++(int num)
{
	Fraction temp = (*this);
	++(*this);	// ��������� ���������� ����������
	return temp;
}

// ���������� --
Fraction Fraction::operator--()
{
	*this = (*this) - 1;
	return *this;
}

// ����������� --
Fraction Fraction::operator--(int num)
{
	Fraction retThis = (*this);
	--(*this);	// ��������� ���������� ����������
	return retThis;
}

// ������� -
Fraction Fraction::operator-()
{
	*this = *this * -1;
	return (*this);
}
