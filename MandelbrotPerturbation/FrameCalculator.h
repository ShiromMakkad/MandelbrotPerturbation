#pragma once
#include <fstream>
#include <vector>
#include <complex>
#include <chrono>
#include <random>
#include "mantexp.h"
#include "mantexpComplex.h"
#include "Point.h"
#include "ColorPalette.h"
#include "CImg\CImg.h"

using namespace std;
using namespace cimg_library;

namespace FrameCalculator {
	class calculateFrame {
	public:
		void initializeCalculateFrame(int WIDTHin, int HEIGHTin, int MAX_ITERATIONin, const char* xZoomPointin, const char* yZoomPointin, double ZOOM_RATEin, const char* palette);
		void calculateOneFrame(const int frame, const char* saveLocation);
	private:
		void calculatePoint(int x, int y, double tempRadius, int window_radius, CImg<unsigned char>& image, vector<Point>& glitchPoints, vector<Point>& allPoints);
		void ReferenceZoomPoint(const long double& centerReal, const long double& centerImaginary, int MAX_ITERATIONS);
		int calculateSeries(double frame, double magnifiedRadius, int window_radius);

		void DisplayPercent(double percent);

		vector<complex<double>> XSubN;
		vector<complex<double>> XSubNTimes2;
		vector<double> PerturbationToleranceCheck;

		//vector<complex<double>> A, B, C;
		vector<vector<mantexpComplex>> coefficients;

		double calculatedRealDelta, calculatedImaginaryDelta;
		double ZCoordinateMagnitudeSquared;
		int skippedIterations = 0;

		int WIDTH, HEIGHT;
		int MAX_ITERATION;
		long double xZoomPoint;
		long double yZoomPoint;
		double ZOOM_RATE;
		boolean calculateGlitches = true;
		boolean seriesApproximation = false;
		unsigned int numCoefficients = 5;
		//What percentage of the image is okay to be glitched. 
		double percentGlitchTolerance = 0.1;
		int referencePoints = 0;

		long double ZCoordinateReal, ZCoordinateImaginary;
		long double ZCoordinateRealTimes2, ZCoordinateImaginaryTimes2;
		long double referenceCoordinateReal, referenceCoordinateImaginary;

		vector<vector<int>> colors;

		double radius = 2;
	};
}