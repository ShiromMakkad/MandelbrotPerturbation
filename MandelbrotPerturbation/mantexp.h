#pragma once
#include <iostream>

using namespace std;

class mantexp
{
friend class mantexpComplex;
private:
	
protected:
	
public:
	void Reduce();
	double mantissa = 0;
	int exp = 0;

	mantexp() {}
	mantexp(double mantissa, int exp) { setMantexp(mantissa, exp); };
	mantexp(double number) { setDouble(number); };

	mantexp operator*(double factor);
	bool operator<(mantexp compareTo);
	bool operator<(double compareTo);
	friend ostream &operator<<(ostream &os, mantexp &in);

	double toDouble();
	void setDouble(double number);
	void setMantexp(double mantissa, int exp);
	void mulDouble(double factor);
	void mulMantexp(mantexp factor);
	void addDouble(double addend);
	void addMantexp(mantexp addend);
};