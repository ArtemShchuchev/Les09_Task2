#include "Fraction.h"


double Fraction::div()
{
	exception(*this); // проверка исключений
	toImproperFract(*this);	// в неправильную дробь

	double temp = static_cast<double>(numerator_) / denominator_;

	toProperFract(*this);	// в правильную дробь
	return temp;
}

//	ѕривожу к правильной дроби
//		105		  3		  1
//		---	->	17-	->	17-
//		 6		  6		  2
void Fraction::toProperFract(Fraction& f)
{
	exception(f); // проверка исключений

	if (f.numerator_ / f.denominator_)	// если дробь неправильна€
	{
		int znak = 1;	// предположу, что число положительное
		if (f.whole_ < 0)
		{
			f.whole_ *= -1;		// модуль числа
			znak = -1;			// число отрицательное
		}
		if (f.numerator_ < 0)
		{
			f.numerator_ *= -1;	// модуль числа
			znak = -1;			// число отрицательное
		}

		f.whole_ += f.numerator_ / f.denominator_;
		f.numerator_ %= f.denominator_;
		f.whole_ *= znak;		// вернул знак
	}

	// упрощаю дробь (ищу общий множитель)
	int multiplier = f.numerator_ < 0 ? f.numerator_ * -1 : f.numerator_;
	while (multiplier > 1)
	{
		// если знаменатель делитс€ на multiplier без остатка
		// и числитель делитс€ на multiplier без остатка
		if (!(f.denominator_ % multiplier) && !(f.numerator_ % multiplier))
		{
			f.numerator_ /= multiplier;
			f.denominator_ /= multiplier;
			break;
		}
		--multiplier;
	};
}

//	ѕривожу к Ќ≈правильной дроби
//		 1		7
//		2-	->	-
//		 3		3
void Fraction::toImproperFract(Fraction& f)
{
	if (f.whole_)	// если дробь правильна€
	{
		int znak = 1;	// предположу, что число положительное
		if (f.whole_ < 0)
		{
			f.whole_ *= -1;		// модуль числа
			znak = -1;			// число отрицательное
		}
		if (f.numerator_ < 0)
		{
			f.numerator_ *= -1;	// модуль числа
			znak = -1;			// число отрицательное
		}

		f.numerator_ += f.whole_ * f.denominator_;
		f.whole_ = 0;
		f.numerator_ *= znak;	// вернул знак
	}
}

void Fraction::exception(Fraction& fr)
{
	if ( !(fr.whole_ || fr.numerator_) && fr.denominator_ == 0 )
	{
		throw std::domain_error("„ислитель и знаменатель = 0, решени€ не существует.");
	}
	if (fr.denominator_ == 0) throw std::overflow_error("ƒелитель = 0, решение стремитс€ к бесконечности.");
}

Fraction::Fraction(int numerator, int denominator)
{
	numerator_ = numerator;
	denominator_ = denominator;
	whole_ = 0;
	if (denominator_ < 0) // проверка/правка знаков
	{
		denominator_ *= -1;
		numerator_ *= -1;
	}
	exception(*this);		// проверка исключений
	toProperFract(*this);	// в правильную дробь
}

Fraction::Fraction(int whole)
{
	numerator_ = 0;
	denominator_ = 1;
	whole_ = whole;
	exception(*this); // проверка исключений
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

Fraction Fraction::operator + (Fraction second)
{
	Fraction first = *this;
	
	// в неправильные дроби
	toImproperFract(first);
	toImproperFract(second);
	
	// приведение к общ. знаменателю
	if (first.denominator_ != second.denominator_)
	{
		first.numerator_ *= second.denominator_;
		second.numerator_ *= first.denominator_;
		// второй знаменатель - не важен
		first.denominator_ *= second.denominator_;
		//second.denominator_ = first.denominator_;
	}
	
	// при общем знаменателе
	first.numerator_ += second.numerator_;
	
	// в правильную дробь
	toProperFract(first);

	return first;
}

Fraction Fraction::operator - (Fraction second)
{
	Fraction first = *this;

	// в неправильные дроби
	toImproperFract(first);
	toImproperFract(second);

	// приведение к общ. знаменателю
	if (first.denominator_ != second.denominator_)
	{
		first.numerator_ *= second.denominator_;
		second.numerator_ *= first.denominator_;
		// второй знаменатель - не важен
		first.denominator_ *= second.denominator_;
		//second.denominator_ = first.denominator_;
	}

	// при общем знаменателе
	first.numerator_ -= second.numerator_;

	// в правильную дробь
	toProperFract(first);

	return first;
}

Fraction Fraction::operator * (Fraction fr)
{
	// в неправильные дроби
	toImproperFract(*this);
	toImproperFract(fr);

	fr.numerator_ *= this->numerator_;
	fr.denominator_ *= this->denominator_;

	// в правильную дробь
	toProperFract(*this);
	toProperFract(fr);

	return fr;
}

Fraction Fraction::operator / (Fraction fr)
{
	// в неправильные дроби
	toImproperFract(*this);
	toImproperFract(fr);

	int znak = 1;	// предположу, что число положительное
	int tempDenom = fr.denominator_; // сохранаю делитель

	// знаменатель = числитель_2 * знаменатель_1
	fr.denominator_ = fr.numerator_ * this->denominator_;
	if (fr.numerator_ < 0) // провер€ю знак числител€_2
	{
		fr.denominator_ *= -1;	// модуль числа
		znak *= -1;					// помен€л знак
	}
	// числитель = числитель_1 * знаменатель_2
	fr.numerator_ = this->numerator_ * tempDenom;
	// числитель 1, на знак провер€ть не надо
	fr.numerator_ *= znak;		// восстановил знак

	// в правильную дробь
	toProperFract(*this);
	toProperFract(fr);

	return fr;
}

// префиксный ++
Fraction Fraction::operator++()
{
	*this = (*this) + 1;
	return *this;
}

// постфиксный ++
Fraction Fraction::operator++(int num)
{
	Fraction temp = (*this);
	++(*this);	// использую префиксную перегрузку
	return temp;
}

// префиксный --
Fraction Fraction::operator--()
{
	*this = (*this) - 1;
	return *this;
}

// постфиксный --
Fraction Fraction::operator--(int num)
{
	Fraction retThis = (*this);
	--(*this);	// использую префиксную перегрузку
	return retThis;
}

// унарный -
Fraction Fraction::operator-()
{
	*this = *this * -1;
	return (*this);
}
