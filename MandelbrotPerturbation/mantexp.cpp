#include "pch.h"
#include "mantexp.h"

void mantexp::Reduce() {
	int addedExp;
	double tempMantissa = frexp(mantissa, &addedExp);
	if (mantissa != tempMantissa) {
		exp += addedExp;
		mantissa = tempMantissa;
	}
}

void mantexp::setDouble(double number) {
	mantissa = frexp(number, &exp);
}

void mantexp::setMantexp(double mantissaIn, int expIn) {
	mantissa = mantissaIn;
	exp = expIn;
}

double mantexp::toDouble() {
	return ldexp(mantissa, exp);
}

void mantexp::mulMantexp(mantexp factor) {
	mantissa *= factor.mantissa;
	exp += factor.exp;

	if (mantissa > 2) {
		Reduce();
	}
}

void mantexp::mulDouble(double factor) {
	mantexp factorMant(factor);

	mulMantexp(factorMant);
}

void mantexp::addMantexp(mantexp addend) {
	if (exp == addend.exp) {
		mantissa += addend.mantissa;
	}
	else if(exp > addend.exp){
		addend.mantissa /= pow(2, exp - addend.exp);

		mantissa += addend.mantissa;
	}
	else {
		mantissa /= pow(2, addend.exp - exp);

		exp = addend.exp;
		mantissa += addend.mantissa;
	}
}

void mantexp::addDouble(double addend) {
	int doubleExp;
	double doubleMantissa = frexp(addend, &doubleExp);

	if (exp == doubleExp) {
		mantissa += doubleMantissa;
	}
	else if (exp > doubleExp) {
		doubleMantissa /= pow(2, exp - doubleExp);

		mantissa += doubleMantissa;
	}
	else {
		mantissa /= pow(2, doubleExp - exp);

		exp = doubleExp;
		mantissa += doubleMantissa;
	}
}

mantexp mantexp::operator*(double factor)
{
	mantexp newMantexp(mantissa, exp);
	newMantexp.mulDouble(factor);

	return newMantexp;
}

bool mantexp::operator<(mantexp compareTo) {
	Reduce();
	compareTo.Reduce();

	if (exp > compareTo.exp) {
		return false;
	}
	else if (exp < compareTo.exp) {
		return true;
	}
	else {
		if (mantissa >= compareTo.mantissa) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}

bool mantexp::operator<(double compareTo) {
	mantexp temp(compareTo);

	return operator<(temp);
}

ostream &operator<<(ostream &os, mantexp &in) {
	in.Reduce();
	if (in.exp < 1024 && in.exp > -1024) {
		return os << in.toDouble();
	}
	else {
		return os << in.mantissa << " *2^" << in.exp;
	}
}
