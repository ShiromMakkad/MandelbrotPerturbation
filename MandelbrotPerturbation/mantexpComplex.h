#pragma once
#include "mantexp.h"
#include <complex>
#include <iostream>

using namespace std;

class mantexpComplex
{
private:
	
public:
	int exp = 0;
	double mantissaReal = 0;
	double mantissaImag = 0;

	mantexpComplex() {}
	mantexpComplex(mantexp real, mantexp imaginary) { setMantexp(real, imaginary); };
	mantexpComplex(double real, double imaginary) { setDouble(real, imaginary); };
	mantexpComplex(complex<double> complex) { setComplex(complex); };

	mantexpComplex operator+(double addend);
	mantexpComplex operator+(complex<double> addend);
	mantexpComplex operator+(mantexpComplex addend);
	mantexpComplex operator*(double factor);
	mantexpComplex operator*(mantexp factor);
	mantexpComplex operator*(complex<double> factor);
	mantexpComplex operator*(mantexpComplex factor);
	friend ostream &operator<<(ostream &os, mantexpComplex &in);

	void Reduce();

	double norm();
	mantexp normMant();
	double abs();
	mantexpComplex square();

	complex<double> toComplex();

	void setDouble(double real, double imaginary);
	void setMantexp(mantexp real, mantexp imaginary);
	void setComplex(complex<double> complex);

	void mulDouble(double factor);
	void mulMantexp(mantexp factor);

	void addDoubleReal(double addend);
	void addDoubleImag(double added);

	void addMantexpReal(mantexp addend);
	void addMantexpImag(mantexp addend);

	void addComplex(complex<double> addend);
	void mulComplex(complex<double> factor);

	void mulMantexpComplex(mantexpComplex factor);
	void addMantexpComplex(mantexpComplex addend);
};