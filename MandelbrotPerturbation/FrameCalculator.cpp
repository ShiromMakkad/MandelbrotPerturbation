#include "pch.h"
#include "FrameCalculator.h"

using namespace cimg_library;
using namespace std;

namespace FrameCalculator {
	void calculateFrame::initializeCalculateFrame(int WIDTHin, int HEIGHTin, int MAX_ITERATIONin, const char* xZoomPointin, const char* yZoomPointin, double ZOOM_RATEin, const char* palette) {
		WIDTH = WIDTHin;
		HEIGHT = HEIGHTin;
		MAX_ITERATION = MAX_ITERATIONin;
		ZOOM_RATE = ZOOM_RATEin;

		//Set the precision to the precision needed to contain the string. For more information, see http://www.exploringbinary.com/number-of-bits-in-a-decimal-integer/
		xZoomPoint = atof(xZoomPointin);
		yZoomPoint = atof(yZoomPointin);

		ColorPalette::ColorPalette colorPaletteCreator;
		colorPaletteCreator.ColorChooser(palette, colors);
	}

	//This code was found here: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
	void calculateFrame::DisplayPercent(double progress) {
		int barWidth = 70;

		cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) cout << "=";
			else if (i == pos) cout << ">";
			else cout << " ";
		}
		cout << "] " << int(progress * 100.0) << " %\r";
		cout.flush();
	}

	void calculateFrame::calculateOneFrame(const int frame, const char* bufferLocation) {
		string saveLocation(bufferLocation);
		saveLocation = saveLocation + "\\frame" + to_string(frame) + ".bmp";

		string glitchSave(bufferLocation);
		glitchSave = glitchSave + "\\glitch.bmp";

		string infoLocation(bufferLocation);
		infoLocation = infoLocation + "\\info" + to_string(frame) + ".txt";

		chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

		referencePoints = 0;

		CImg<unsigned char> image(WIDTH, HEIGHT, 1, 3, 0);

		vector<Point> pointsRemaining;
		vector<Point> allPoints;

		//Fill the list of points with all points in the image.
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				Point pt(x, y);
				pointsRemaining.push_back(pt);
			}
		}

		double magnifiedRadius = radius / pow(ZOOM_RATE, frame);
		int window_radius = (WIDTH < HEIGHT) ? WIDTH : HEIGHT;

		while (pointsRemaining.size() > (WIDTH * HEIGHT) * (percentGlitchTolerance / 100)) {
			referencePoints++;

			//Determine the reference point to calculate
			//Check whether this is the first time running the loop. 
			if (referencePoints == 1) {
				referenceCoordinateReal = xZoomPoint;
				referenceCoordinateImaginary = yZoomPoint;

				calculatedRealDelta = 0;
				calculatedImaginaryDelta = 0;

				ReferenceZoomPoint(referenceCoordinateReal, referenceCoordinateImaginary, MAX_ITERATION);
				if (seriesApproximation) {
					skippedIterations = calculateSeries(frame, magnifiedRadius, window_radius);
				}

				cout << "Iterations Skipped: " << skippedIterations << endl;
			}
			else {
				if (calculateGlitches == false) {
					break;
				}

				CImg<unsigned char> glitchImage(WIDTH, HEIGHT, 1, 3, 0);

				vector<vector<int>> glitch2DArray;

				glitch2DArray.resize(WIDTH, vector<int>(HEIGHT, -1));
				for (int i = 0; i < pointsRemaining.size(); i++) {
					glitch2DArray[pointsRemaining[i].getX()][pointsRemaining[i].getY()] = pointsRemaining[i].getIteration();
					unsigned char white[3] = { 255,255,255 };
					glitchImage.draw_point(pointsRemaining[i].getX(), pointsRemaining[i].getY(), white, 255);
				}

				int referencePointIndex = 0;
				random_device rand_dev;
				mt19937 generator(rand_dev());
				uniform_int_distribution<int> distribution(0, pointsRemaining.size() - 1);
				referencePointIndex = distribution(generator);

				cout << referencePointIndex << endl;
				cout << pointsRemaining.size() << endl;

				unsigned char red[3] = { 255,0,0 };
				glitchImage.draw_point(pointsRemaining[referencePointIndex].getX(), pointsRemaining[referencePointIndex].getY(), red, 255);

				glitchImage.save(glitchSave.c_str());

				//Get the complex point at the chosen reference point
				double deltaReal = ((magnifiedRadius * (2 * pointsRemaining[referencePointIndex].getX() - WIDTH)) / window_radius);
				double deltaImaginary = ((-magnifiedRadius * (2 * pointsRemaining[referencePointIndex].getY() - HEIGHT)) / window_radius);

				/* We need to store this offset because the formula we use to convert pixels into a complex point does so relative to the center of the image.
				* We need to offset that calculation when our reference point isn't in the center. The actual offsetting is done in calculate point.
				*/
				calculatedRealDelta = deltaReal;
				calculatedImaginaryDelta = deltaImaginary;

				referenceCoordinateReal = xZoomPoint + deltaReal;

				referenceCoordinateImaginary = yZoomPoint + deltaImaginary;
				ReferenceZoomPoint(referenceCoordinateReal, referenceCoordinateImaginary, MAX_ITERATION);
			}

			vector<Point> glitchPoints;

			int lastChecked = -1;
			for (unsigned int i = 0; i < pointsRemaining.size(); i++) {
				calculatePoint(pointsRemaining[i].getX(), pointsRemaining[i].getY(), magnifiedRadius, window_radius, image, glitchPoints, allPoints);
				//Everything else in this loop is just for updating the progress counter. 
				double progress = (double)i / pointsRemaining.size();
				if (int(progress * 100) != lastChecked) {
					DisplayPercent(progress);
					lastChecked = int(progress * 100);
				}
			}

			//These points are glitched, so we need to mark them for recalculation. We need to recalculate them using Pauldelbrot's glitch fixing method (see calculate point).
			pointsRemaining = glitchPoints;

			cout << "Points left: " << pointsRemaining.size() << endl;
			cout << "Reference Points: " << referencePoints << endl;
		}

		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

		cout << "Done!" << endl;
		cout << "C++ Perterbation Render Time: " << duration << endl;
		cout << xZoomPoint << endl;
		cout << yZoomPoint << endl;

		image.save(saveLocation.c_str());
		CImg<unsigned char> glitchImage(WIDTH, HEIGHT, 1, 3, 0);
		vector<vector<int>> glitch2DArray;

		glitch2DArray.resize(WIDTH, vector<int>(HEIGHT, -1));
		for (int i = 0; i < pointsRemaining.size(); i++) {
			glitch2DArray[pointsRemaining[i].getX()][pointsRemaining[i].getY()] = pointsRemaining[i].getIteration();
			unsigned char white[3] = { 255,255,255 };
			glitchImage.draw_point(pointsRemaining[i].getX(), pointsRemaining[i].getY(), white, 255);
		}
		glitchImage.save(glitchSave.c_str());

		ofstream info(infoLocation.c_str());
		info << "C++ Perterbation Render Time: " << duration << endl;
		info << "Iterations Skipped: " << skippedIterations << endl;
		info << "Reference Points: " << referencePoints << endl;
		info.close();
	}

	void calculateFrame::calculatePoint(int x, int y, double magnifiedRadius, int window_radius, CImg<unsigned char>& image, vector<Point>& glitchPoints, vector<Point>& allPoints) {
		/*Get the complex number at this pixel.
		*This calculates the number relative to the reference point, so we need to translate that to the center when the reference point isn't in the center.
		*That's why for the first reference, calculatedRealDelta and calculatedImaginaryDelta are 0: it's calculating relative to the center.
		*/
		double deltaReal = ((magnifiedRadius * (2 * x - WIDTH)) / window_radius) - calculatedRealDelta;
		double deltaImaginary = ((-magnifiedRadius * (2 * y - HEIGHT)) / window_radius) - calculatedImaginaryDelta;
		complex<double> DeltaSub0(deltaReal, deltaImaginary);

		int iteration = skippedIterations;
		complex<double> DeltaSubN;
		//If we are doing series approximation and this isn't a glitched point. Series approximation messes up glitch correction and detection. The risk is minimal for the whole image, but if we know the point is glitched, it's a bad idea.
		if (seriesApproximation && referencePoints == 1) {
			//Series approximation didn't work. Set this equal to the point. 
			if (iteration == 0) {
				DeltaSubN = DeltaSub0;
			}
			else {
				//Use equation 2 from the orginal paper to get the delta. 
				mantexpComplex DeltaSubNMant;

				vector<mantexpComplex> DeltaSub0ToThe;
				DeltaSub0ToThe.resize(numCoefficients + 1);
				DeltaSub0ToThe[1] = mantexpComplex(deltaReal, deltaImaginary);
				for (int i = 2; i <= numCoefficients; i++) {
					DeltaSub0ToThe[i] = DeltaSub0ToThe[i - 1] * DeltaSub0ToThe[1];
					DeltaSub0ToThe[i].Reduce();
				}

				for (int i = 0; i < numCoefficients; i++) {
					DeltaSubNMant = DeltaSubNMant + (coefficients[i][iteration] * DeltaSub0ToThe[i + 1]);
				}
				DeltaSubN = DeltaSubNMant.toComplex();
			}
		}
		else {
			DeltaSubN = DeltaSub0;
			iteration = 0;
		}

		boolean glitched = false;
		//Iteration loop
		do
		{
			DeltaSubN *= XSubNTimes2[iteration] + DeltaSubN;
			DeltaSubN += DeltaSub0;
			iteration++;
			ZCoordinateMagnitudeSquared = norm(XSubN[iteration] + DeltaSubN);

			/*This is Pauldelbrot's glitch detection method. You can see it here: http://www.fractalforums.com/announcements-and-news/pertubation-theory-glitches-improvement/.
			* As for why it looks so weird, it's because I've squared both sides of his equation and moved the |ZsubN| to the other side to be precalculated.
			* For more information, look at where the reference point is calculated.
			* I also only want to store this point once.
			*/
			if (calculateGlitches == true && glitched == false && ZCoordinateMagnitudeSquared < PerturbationToleranceCheck[iteration]) {
				Point pt(x, y, iteration);
				glitchPoints.push_back(pt);
				glitched = true;
				break;
			}

			//Bailout radius of 256 for smooth coloring.
		} while (ZCoordinateMagnitudeSquared < 256 && iteration < MAX_ITERATION);

		if (glitched == false) {
			if (iteration == MAX_ITERATION) {
				unsigned char black[3] = { 0,0,0 };
				image.draw_point(x, y, black, 255);
			}
			else {
				int index = (int)((iteration - log2(log2(ZCoordinateMagnitudeSquared))) * 5) % colors.size(); //Get the index of the color array that we are going to read from. 
				//int index = (int) (iteration - (log(0.5*(ZCoordinateMagnitudeSquared)) - log(0.5*log(256))) / log(2)) % colors.size();
				//int index = iteration % colors.size();
				unsigned char color[3] = { colors[index][0], colors[index][1] , colors[index][2] };
				image.draw_point(x, y, color, 255);
			}
			Point pt(x, y, iteration);

			allPoints.push_back(pt);
		}
	}

	void calculateFrame::ReferenceZoomPoint(const long double& centerReal, const long double& centerImaginary, int maxIteration) {
		//Raising this number makes more calculations, but less variation between each calculation (less chance of mis-identifying a glitched point).
		double glitchTolerancy = 1e-6;

		XSubN.clear();
		XSubNTimes2.clear();
		PerturbationToleranceCheck.clear();

		ZCoordinateReal = centerReal;
		ZCoordinateImaginary = centerImaginary;

		for (int i = 0; i <= maxIteration; i++)
		{
			// pre multiply by two
			ZCoordinateRealTimes2 = ZCoordinateReal * 2;
			ZCoordinateImaginaryTimes2 = ZCoordinateImaginary * 2;

			complex<double> c(ZCoordinateReal, ZCoordinateImaginary);
			complex<double> TwoC(ZCoordinateRealTimes2, ZCoordinateImaginaryTimes2);
			/* The reason we are storing the same value times two is that we can precalculate this value here because multiplying this value by two is needed many times in the program.
			* Also, for some reason, we can't multiply complex numbers by anything greater than 1 using std::complex, so we have to multiply the individual terms each time.
			* This is expensive to do above, so we are just doing it here.
			*/
			XSubN.push_back(c);
			XSubNTimes2.push_back(TwoC);
			/*Norm is the squared version of abs and 0.000001 is 10^-3 squared.
			* The reason we are storing this into an array is that we need to check the magnitude against this value to see if the value is glitched.
			* We are leaving it squared because otherwise we'd need to do a square root operation, which is expensive, so we'll just compare this to the squared magnitude.
			*/

			double tolerancyReal = ZCoordinateReal * glitchTolerancy;
			double tolerancyImag = ZCoordinateImaginary * glitchTolerancy;
			complex<double> tolerancy(tolerancyReal, tolerancyImag);
			PerturbationToleranceCheck.push_back(norm(tolerancy));

			//Calculate the set
			ZCoordinateReal = (ZCoordinateReal * ZCoordinateReal) - (ZCoordinateImaginary * ZCoordinateImaginary) + centerReal;

			ZCoordinateImaginary = (ZCoordinateRealTimes2 * ZCoordinateImaginary) + centerImaginary;
		}
	}

	/* This method simply calculates the A, B, and C coefficients (as well as the others I've found) as described in the original paper.
	* Here is the link to a formula for more coefficients: http://mathr.co.uk/blog/2016-03-06_simpler_series_approximation.html
	* Here is a thread I opened on this topic: https://fractalforums.org/fractal-mathematics-and-new-theories/28/how-to-get-more-than-3-series-approximation-terms/571/
	* ASubI is each coefficient (don't worry about b) i.e. ASub1 is A, ASub2 is B, etc.
	*/
	int calculateFrame::calculateSeries(double frame, double magnifiedRadius, int window_radius) {
		if (numCoefficients < 2) {
			return 0;
		}
		if (numCoefficients > 5) {
			numCoefficients = 5;
		}

		double deltaReal = ((magnifiedRadius * ((2 * WIDTH) - WIDTH)) / window_radius) - calculatedRealDelta;
		double deltaImaginary = ((-magnifiedRadius * ((2 * HEIGHT) - HEIGHT)) / window_radius) - calculatedImaginaryDelta;

		vector<mantexpComplex> DeltaSub0ToThe;
		DeltaSub0ToThe.resize(numCoefficients + 1);
		DeltaSub0ToThe[1] = mantexpComplex(deltaReal, deltaImaginary);

		for (int i = 2; i <= numCoefficients; i++) {
			DeltaSub0ToThe[i] = DeltaSub0ToThe[i - 1] * DeltaSub0ToThe[1];
			DeltaSub0ToThe[i].Reduce();
		}

		coefficients.resize(numCoefficients, vector<mantexpComplex>(XSubN.size()));

		coefficients[0][0] = mantexpComplex(1, 0);

		double tolerancy = pow(2, -64);

		for (int i = 1; i < XSubN.size(); i++) {
			if (numCoefficients >= 1) {
				//A
				coefficients[0][i] = (coefficients[0][i - 1] * XSubN[i - 1] * (double)2) + (double)1;
			}
			if (numCoefficients >= 2) {
				//B
				coefficients[1][i] = (coefficients[1][i - 1] * XSubN[i - 1] * (double)2) + coefficients[0][i - 1].square();
			}
			if (numCoefficients >= 3) {
				//C
				coefficients[2][i] = (coefficients[2][i - 1] * XSubN[i - 1] * (double)2) + (coefficients[1][i - 1] * coefficients[0][i - 1] * (double)2);
			}
			if (numCoefficients >= 4) {
				//D
				coefficients[3][i] = (coefficients[3][i - 1] * XSubN[i - 1] * (double)2) + (coefficients[0][i - 1] * coefficients[2][i - 1] * (double)2) + coefficients[1][i - 1].square();
			}
			if (numCoefficients >= 5) {
				//E
				coefficients[4][i] = (coefficients[4][i - 1] * XSubN[i - 1] * (double)2) + (coefficients[0][i - 1] * coefficients[3][i - 1] * (double)2) + (coefficients[1][i - 1] * coefficients[2][i - 1] * (double)2);
			}

			for (int j = 0; j < numCoefficients; j++) {
				coefficients[j][i].Reduce();
			}

			//Check to see if the approximation is no longer valid. The validity is checked if an arbritary point we approximated differs from the point it should be by too much. That is the tolerancy which scales with the depth. 
			if (((coefficients[numCoefficients - 2][i] * DeltaSub0ToThe[numCoefficients - 1]).normMant() * tolerancy) < (coefficients[numCoefficients - 1][i] * DeltaSub0ToThe[numCoefficients]).normMant()) {
				if (i <= 3) {
					for (int j = 0; j < numCoefficients; j++) {
						coefficients[j].resize(0);
					}

					return 0;
				}
				else {
					//When we're breaking here, it means that we've found a point where the approximation no longer works. Returning that would create a messed up image. We should move a little further back to get an approximation that is good. 
					for (int j = 0; j < numCoefficients; j++) {
						coefficients[j].resize(i - 3);
					}

					return i - 3;
				}
			}
		}
		for (int j = 0; j < numCoefficients; j++) {
			coefficients[j].resize(XSubN.size() - 1);
		}

		return XSubN.size() - 1;
	}
}