#pragma once
#include <complex>
//This allows me to easily store points and assosciate values with them. 

using namespace std;

class Point
{
private:
	int x, y;
	int iteration = -1;
	double index = 1.5;
	complex<double> DeltaSubN;
	bool glitched = false;
public:
	Point() {}
	Point(int xIn, int Yin) : x(xIn), y(Yin) {}
	Point(int xIn, int yIn, int iterationIn) : x(xIn), y(yIn), iteration(iterationIn) {}
	Point(int xIn, int yIn, int iterationIn, double indexin) : x(xIn), y(yIn), iteration(iterationIn), index(indexin) {}

	void setIteration(int iterationIn) { iteration = iterationIn; };
	void setIndex(double indexIn) { index = indexIn; };
	void setDeltaSubN(complex<double> DeltaSubNIn) { DeltaSubN = DeltaSubNIn; };
	void setGlitched(bool glitchedIn) { glitched = glitchedIn; };

	int getX() { return x; };
	int getY() { return y; };
	int getIteration() { return iteration; };
	double getIndex() { return index; };
	complex<double> getDeltaSubN() { return DeltaSubN; };
	bool isGlitched() { return glitched; };

	bool operator==(Point in) { return (x == in.getX() && y == in.getY()); };
};