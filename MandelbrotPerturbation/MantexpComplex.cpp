#include "pch.h"
#include "mantexpComplex.h"

void mantexpComplex::Reduce() {
	int addedExpReal;
	double mantissaRealTemp = frexp(mantissaReal, &addedExpReal);
	
	int addedExpImag;
	double mantissaImagTemp = frexp(mantissaImag, &addedExpImag);

	int realExp = addedExpReal + exp;
	int imagExp = addedExpImag + exp;

	if (realExp == imagExp) {
		exp = realExp;

		mantissaImag = mantissaImagTemp;
		mantissaReal = mantissaRealTemp;
	}
	else if (realExp > imagExp) {
		//mantissaImagTemp /= pow(2, realExp - imagExp);
		//mantissaRealTemp *= pow(2, realExp - imagExp);
		mantissaRealTemp = ldexp(mantissaRealTemp, realExp - imagExp);

		exp = imagExp;
		//exp = realExp;
		mantissaReal = mantissaRealTemp;
		mantissaImag = mantissaImagTemp;
	}
	else {
		//mantissaRealTemp /= pow(2, imagExp - realExp);
		//mantissaImagTemp *= pow(2, imagExp - realExp);
		mantissaImagTemp = ldexp(mantissaImagTemp, imagExp - realExp);

		exp = realExp;
		//exp = imagExp;
		mantissaReal = mantissaRealTemp;
		mantissaImag = mantissaImagTemp;
	}
}

void mantexpComplex::setMantexp(mantexp realIn, mantexp imagIn) {
	if (realIn.exp == imagIn.exp) {
		exp = realIn.exp;
		mantissaReal = realIn.mantissa;
		mantissaImag = imagIn.mantissa;
	}
	if (realIn.exp > imagIn.exp) {
		//imagIn.mantissa /= pow(2, realIn.exp - imagIn.exp);
		//realIn.mantissa *= pow(2, realIn.exp - imagIn.exp);
		realIn.mantissa = ldexp(realIn.mantissa, realIn.exp - imagIn.exp);

		exp = imagIn.exp;
		//exp = realIn.exp;
		mantissaReal = realIn.mantissa;
		mantissaImag = imagIn.mantissa;
	}
	else {
		//realIn.mantissa /= pow(2, imagIn.exp - realIn.exp);
		//imagIn.mantissa *= pow(2, imagIn.exp - realIn.exp);
		imagIn.mantissa = ldexp(imagIn.mantissa, imagIn.exp - realIn.exp);

		exp = realIn.exp;
		//exp = imagIn.exp;
		mantissaReal = realIn.mantissa;
		mantissaImag = imagIn.mantissa;
	}
}

void mantexpComplex::setComplex(complex<double> complex) {
	setDouble(complex.real(), complex.imag());
}

void mantexpComplex::setDouble(double real, double imag) {
	mantexp realMant(real);
	mantexp imagMant(imag);

	setMantexp(realMant, imagMant);
}

double mantexpComplex::norm() {
	return ldexp(pow(mantissaReal, 2) + pow(mantissaImag, 2), exp * 2);
}

mantexp mantexpComplex::normMant() {
	mantexp out(pow(mantissaReal, 2) + pow(mantissaImag, 2), exp * 2);

	return out;
}

double mantexpComplex::abs() {
	return sqrt(ldexp(pow(mantissaReal, 2) + pow(mantissaImag, 2), exp * 2));
}

mantexpComplex mantexpComplex::square() {
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.exp *= 2;

	//This is done because otherwise we'd be using the already multiplied mantissa real which is wrong
	double tempMantissaReal = pow(newMantexpComplex.mantissaReal, 2) - pow(newMantexpComplex.mantissaImag, 2);
	newMantexpComplex.mantissaImag = 2 * newMantexpComplex.mantissaReal * newMantexpComplex.mantissaImag;
	newMantexpComplex.mantissaReal = tempMantissaReal;

	return newMantexpComplex;
}

complex<double> mantexpComplex::toComplex() {
	complex<double> out(ldexp(mantissaReal, exp), ldexp(mantissaImag, exp));

	return out;
}

void mantexpComplex::mulDouble(double factor) {
	if (factor == 2) {
		exp++;
	}
	else {
		mantissaReal *= factor;
		mantissaImag *= factor;
	}

	if (mantissaReal > 1e50 || mantissaImag > 1e50 || mantissaReal < 1e-50 || mantissaImag < 1e-50) {
		Reduce();
	}
}

void mantexpComplex::mulMantexp(mantexp factor) {
	mantissaReal *= factor.mantissa;
	mantissaImag *= factor.mantissa;
	exp += factor.exp;

	if (mantissaReal > 1e50 || mantissaImag > 1e50 || mantissaReal < 1e-50 || mantissaImag < 1e-50) {
		Reduce();
	}
}

void mantexpComplex::addDoubleReal(double addend) {
	mantexp temp(addend);

	addMantexpReal(temp);
}

void mantexpComplex::addDoubleImag(double addend) {
	mantexp temp(addend);

	addMantexpImag(temp);
}

void mantexpComplex::addMantexpReal(mantexp addend) {
	/*
	if (exp > addend.exp) {
		addend.mantissa /= pow(2, exp - addend.exp);
	}
	else if (exp < addend.exp) {
		addend.mantissa *= pow(2, addend.exp - exp);
	}
	*/
	addend.mantissa = ldexp(addend.mantissa, addend.exp - exp);

	mantissaReal += addend.mantissa;
}

void mantexpComplex::addMantexpImag(mantexp addend) {
	//addend.mantissa /= pow(2, exp - addend.exp);
	addend.mantissa = ldexp(addend.mantissa, addend.exp - exp);

	mantissaImag += addend.mantissa;
}

void mantexpComplex::mulMantexpComplex(mantexpComplex factor) {
	double tempMantissaReal = ((mantissaReal * factor.mantissaReal) - (mantissaImag * factor.mantissaImag));
	mantissaImag = ((mantissaReal * factor.mantissaImag) + (mantissaImag * factor.mantissaReal));
	mantissaReal = tempMantissaReal;

	exp += factor.exp;

	if (mantissaReal > 1e50 || mantissaImag > 1e50 || mantissaReal < 1e-50 || mantissaImag < 1e-50) {
		Reduce();
	}
}

void mantexpComplex::addMantexpComplex(mantexpComplex addend) {
	if (mantissaImag == 0 && mantissaReal == 0) {
		exp = addend.exp;
	}
	else if (addend.mantissaReal != 0 && addend.mantissaImag != 0) {
		if (exp > addend.exp) {
			//addend.mantissaReal /= pow(2, exp - addend.exp);
			//addend.mantissaImag /= pow(2, exp - addend.exp);

			//mantissaReal *= pow(2, exp - addend.exp);
			//mantissaImag *= pow(2, exp - addend.exp);

			mantissaReal = ldexp(mantissaReal, exp - addend.exp);
			mantissaImag = ldexp(mantissaImag, exp - addend.exp);
			exp = addend.exp;
		}
		else if (exp < addend.exp) {
			//addend.mantissaReal *= pow(2, addend.exp - exp);
			//addend.mantissaImag *= pow(2, addend.exp - exp);

			addend.mantissaReal = ldexp(addend.mantissaReal, addend.exp - exp);
			addend.mantissaImag = ldexp(addend.mantissaImag, addend.exp - exp);

			//mantissaReal /= pow(2, addend.exp - exp);
			//mantissaImag /= pow(2, addend.exp - exp);

			//exp = addend.exp;
		}
	}

	mantissaReal += addend.mantissaReal;
	mantissaImag += addend.mantissaImag;
}

void mantexpComplex::addComplex(complex<double> addend) {
	mantexpComplex newMantexpComplex;
	newMantexpComplex.setDouble(addend.real(), addend.imag());

	addMantexpComplex(newMantexpComplex);
}

void mantexpComplex::mulComplex(complex<double> factor) {
	mantexpComplex newMantexpComplex;
	newMantexpComplex.setDouble(factor.real(), factor.imag());

	mulMantexpComplex(newMantexpComplex);
}

mantexpComplex mantexpComplex::operator+(double addend)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.addDoubleReal(addend);

	return newMantexpComplex;
}

mantexpComplex mantexpComplex::operator+(complex<double> addend)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.setDouble(addend.real(), addend.imag());

	newMantexpComplex.addMantexpComplex(newMantexpComplex);

	return newMantexpComplex;
}

mantexpComplex mantexpComplex::operator+(mantexpComplex addend)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.addMantexpComplex(addend);

	return newMantexpComplex;
}

mantexpComplex mantexpComplex::operator*(double factor)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.mulDouble(factor);

	return newMantexpComplex;
}

mantexpComplex mantexpComplex::operator*(mantexp factor)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.mulMantexp(factor);

	return newMantexpComplex;
}

mantexpComplex mantexpComplex::operator*(complex<double> factor)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.mulComplex(factor);

	return newMantexpComplex;
}

mantexpComplex mantexpComplex::operator*(mantexpComplex factor)
{
	mantexpComplex newMantexpComplex;
	newMantexpComplex.exp = exp;
	newMantexpComplex.mantissaReal = mantissaReal;
	newMantexpComplex.mantissaImag = mantissaImag;

	newMantexpComplex.mulMantexpComplex(factor);

	return newMantexpComplex;
}

ostream &operator<<(ostream &os, mantexpComplex &in) {
	in.Reduce();

	return os << in.mantissaReal << " + " << in.mantissaImag << "i *2^" << in.exp;
}