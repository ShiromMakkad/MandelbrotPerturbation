#include "pch.h"
#include "ColorPalette.h"

using namespace std;
namespace fs = std::experimental::filesystem;

namespace ColorPalette
{
	void ColorPalette::ColorChooser(string paletteIn, vector<vector<int>>& color)
	{
		palette = paletteIn;

		if (palette._Equal("Random Rainbow"))
		{
			reflect = false;
			steps = 255;
			keyColors = -1;
			RandomRainbow(color, steps);
		}
		else if (palette._Equal("Blue and White Gradient")) {
			keyColors = 5;
			reflect = true;
			steps = 255;
			BlueAndWhiteGradient(color, steps, reflect);
		}
		else if (palette._Equal("Sunset Gradient"))
		{
			keyColors = 5;
			reflect = true;
			steps = 255;
			SunsetGradient(color, steps, reflect);
		}
		else if (palette._Equal("Orange and Blue Gradient"))
		{
			keyColors = 5;
			reflect = true;
			steps = 150;
			OrangeAndBlue(color, steps, reflect);
		}
		else if (palette._Equal("Green and Blue Gradient"))
		{
			keyColors = 16;
			reflect = true;
			steps = 420;
			GreenAndBlue(color, steps, reflect);
		}
		//If nothing matches, it generates the Random Rainbow Pattern. 
		else
		{
			keyColors = -1;
			reflect = false;
			steps = 255;
			RandomRainbow(color, steps);
		}
	}

	void ColorPalette::ColorChooser(string paletteIn, vector<vector<int>>& color, int numSteps)
	{
		palette = paletteIn;
		steps = numSteps;

		if (palette._Equal("Random Rainbow"))
		{
			reflect = false;
			keyColors = -1;
			RandomRainbow(color, steps);
		}
		else if (palette._Equal("Sunset Gradient"))
		{
			keyColors = 5;
			reflect = true;
			SunsetGradient(color, steps, reflect);
		}
		else if (palette._Equal("Orange and Blue Gradient"))
		{
			keyColors = 5;
			reflect = true;
			OrangeAndBlue(color, steps, reflect);
		}
		else if (palette._Equal("Green and Blue Gradient"))
		{
			keyColors = 16;
			reflect = true;
			GreenAndBlue(color, steps, reflect);
		}
		//If nothing matches, it generates the Random Rainbow Pattern. 
		else
		{
			keyColors = -1;
			reflect = false;
			RandomRainbow(color, steps);
		}
	}

	void ColorPalette::RandomRainbow(vector<vector<int>>& input, int steps)
	{
		srand(12); //Use seed so the colors stay the same. Change the seed to whatever you want.
		input.resize(steps, vector<int>(3, 0));

		for (unsigned int i = 0; i < input.size(); i++)
		{
			for (int k = 0; k < 3; k++) {
				input[i][k] = rand() % 255; //Puts a random number between 0-255.
			}
		}
	}

	void ColorPalette::BlueAndWhiteGradient(vector<vector<int>>& input, int steps, bool reflect)
	{
		//Resizes final output vector and fills it with zeros. 
		input.resize(steps, vector<int>(3, 0));
		vector<vector<int>> blueAndWhiteGradientColors;

		//Fill the 2d array of colors with zeros. Needed to ensure that the indices below exist. The first term represents how many "key colors" are being used to create the array. 
		blueAndWhiteGradientColors.resize(5, vector<int>(3, 0));

		blueAndWhiteGradientColors[0][0] = 0;
		blueAndWhiteGradientColors[0][1] = 15;
		blueAndWhiteGradientColors[0][2] = 81;

		blueAndWhiteGradientColors[1][0] = 56;
		blueAndWhiteGradientColors[1][1] = 104;
		blueAndWhiteGradientColors[1][2] = 151;

		blueAndWhiteGradientColors[2][0] = 255;
		blueAndWhiteGradientColors[2][1] = 255;
		blueAndWhiteGradientColors[2][2] = 255;

		blueAndWhiteGradientColors[3][0] = 56;
		blueAndWhiteGradientColors[3][1] = 104;
		blueAndWhiteGradientColors[3][2] = 151;

		blueAndWhiteGradientColors[4][0] = 0;
		blueAndWhiteGradientColors[4][1] = 15;
		blueAndWhiteGradientColors[4][2] = 81;

		if (reflect)
		{
			CreateMultiGradient(input, blueAndWhiteGradientColors, steps);
			ReflectColorArray(input);
		}
		else {
			CreateMultiGradient(input, blueAndWhiteGradientColors, steps);
		}
	}

	void ColorPalette::OrangeAndBlue(vector<vector<int>>& input, int steps, bool reflect)
	{
		//Resizes final output vector and fills it with zeros. 
		input.resize(steps, vector<int>(3, 0));
		vector<vector<int>> OrangeAndBlueColors;

		//Fill the 2d array of colors with zeros. Needed to ensure that the indices below exist. The first term represents how many "key colors" are being used to create the array. 
		OrangeAndBlueColors.resize(16, vector<int>(3, 0));

		OrangeAndBlueColors[0][0] = 66;
		OrangeAndBlueColors[0][1] = 30;
		OrangeAndBlueColors[0][2] = 15;

		OrangeAndBlueColors[1][0] = 25;
		OrangeAndBlueColors[1][1] = 7;
		OrangeAndBlueColors[1][2] = 26;

		OrangeAndBlueColors[2][0] = 9;
		OrangeAndBlueColors[2][1] = 1;
		OrangeAndBlueColors[2][2] = 47;

		OrangeAndBlueColors[3][0] = 4;
		OrangeAndBlueColors[3][1] = 4;
		OrangeAndBlueColors[3][2] = 73;

		OrangeAndBlueColors[4][0] = 0;
		OrangeAndBlueColors[4][1] = 7;
		OrangeAndBlueColors[4][2] = 100;

		OrangeAndBlueColors[5][0] = 12;
		OrangeAndBlueColors[5][1] = 44;
		OrangeAndBlueColors[5][2] = 138;

		OrangeAndBlueColors[6][0] = 24;
		OrangeAndBlueColors[6][1] = 82;
		OrangeAndBlueColors[6][2] = 177;

		OrangeAndBlueColors[7][0] = 57;
		OrangeAndBlueColors[7][1] = 125;
		OrangeAndBlueColors[7][2] = 209;

		OrangeAndBlueColors[8][0] = 134;
		OrangeAndBlueColors[8][1] = 181;
		OrangeAndBlueColors[8][2] = 229;

		OrangeAndBlueColors[9][0] = 211;
		OrangeAndBlueColors[9][1] = 236;
		OrangeAndBlueColors[9][2] = 248;

		OrangeAndBlueColors[10][0] = 241;
		OrangeAndBlueColors[10][1] = 233;
		OrangeAndBlueColors[10][2] = 191;

		OrangeAndBlueColors[11][0] = 248;
		OrangeAndBlueColors[11][1] = 201;
		OrangeAndBlueColors[11][2] = 95;

		OrangeAndBlueColors[12][0] = 255;
		OrangeAndBlueColors[12][1] = 170;
		OrangeAndBlueColors[12][2] = 0;

		OrangeAndBlueColors[13][0] = 204;
		OrangeAndBlueColors[13][1] = 128;
		OrangeAndBlueColors[13][2] = 0;

		OrangeAndBlueColors[14][0] = 255;
		OrangeAndBlueColors[14][1] = 170;
		OrangeAndBlueColors[14][2] = 0;

		OrangeAndBlueColors[15][0] = 153;
		OrangeAndBlueColors[15][1] = 87;
		OrangeAndBlueColors[15][2] = 0;

		if (reflect)
		{
			CreateMultiGradient(input, OrangeAndBlueColors, steps);
			ReflectColorArray(input);
		}
		else {
			CreateMultiGradient(input, OrangeAndBlueColors, steps);
		}
	}

	void ColorPalette::GreenAndBlue(vector<vector<int>>& input, int steps, bool reflect)
	{
		//Resizes final output vector and fills it with zeros. 
		input.resize(steps, vector<int>(3, 0));
		vector<vector<int>> GreenAndBlueColors;

		//Fill the 2d array of colors with zeros. Needed to ensure that the indices below exist. The first term represents how many "key colors" are being used to create the array. 
		GreenAndBlueColors.resize(16, vector<int>(3, 0));

		GreenAndBlueColors[0][0] = 0;
		GreenAndBlueColors[0][1] = 0;
		GreenAndBlueColors[0][2] = 0;

		GreenAndBlueColors[1][0] = 0;
		GreenAndBlueColors[1][1] = 63;
		GreenAndBlueColors[1][2] = 0;

		GreenAndBlueColors[2][0] = 0;
		GreenAndBlueColors[2][1] = 0;
		GreenAndBlueColors[2][2] = 0;

		GreenAndBlueColors[3][0] = 0;
		GreenAndBlueColors[3][1] = 191;
		GreenAndBlueColors[3][2] = 0;

		GreenAndBlueColors[4][0] = 0;
		GreenAndBlueColors[4][1] = 0;
		GreenAndBlueColors[4][2] = 0;

		GreenAndBlueColors[5][0] = 0;
		GreenAndBlueColors[5][1] = 191;
		GreenAndBlueColors[5][2] = 0;

		GreenAndBlueColors[6][0] = 0;
		GreenAndBlueColors[6][1] = 0;
		GreenAndBlueColors[6][2] = 0;

		GreenAndBlueColors[7][0] = 0;
		GreenAndBlueColors[7][1] = 63;
		GreenAndBlueColors[7][2] = 0;

		GreenAndBlueColors[8][0] = 0;
		GreenAndBlueColors[8][1] = 0;
		GreenAndBlueColors[8][2] = 0;

		GreenAndBlueColors[9][0] = 9;
		GreenAndBlueColors[9][1] = 8;
		GreenAndBlueColors[9][2] = 39;

		GreenAndBlueColors[10][0] = 0;
		GreenAndBlueColors[10][1] = 0;
		GreenAndBlueColors[10][2] = 0;

		GreenAndBlueColors[11][0] = 0;
		GreenAndBlueColors[11][1] = 0;
		GreenAndBlueColors[11][2] = 255;

		GreenAndBlueColors[12][0] = 0;
		GreenAndBlueColors[12][1] = 0;
		GreenAndBlueColors[12][2] = 0;

		GreenAndBlueColors[13][0] = 28;
		GreenAndBlueColors[13][1] = 24;
		GreenAndBlueColors[13][2] = 119;

		GreenAndBlueColors[14][0] = 0;
		GreenAndBlueColors[14][1] = 0;
		GreenAndBlueColors[14][2] = 0;

		GreenAndBlueColors[15][0] = 9;
		GreenAndBlueColors[15][1] = 8;
		GreenAndBlueColors[15][2] = 24;

		if (reflect)
		{
			CreateMultiGradient(input, GreenAndBlueColors, steps);
			ReflectColorArray(input);
		}
		else {
			CreateMultiGradient(input, GreenAndBlueColors, steps);
		}
	}

	void ColorPalette::SunsetGradient(vector<vector<int>>& input, int steps, bool reflect)
	{
		vector<vector<int>> sunsetGradientColors;

		//Fill the 2d array of colors with zeros. Needed to ensure that the indices below exist. The first term represents how many "key colors" are being used to create the array. 
		sunsetGradientColors.resize(5, vector<int>(3, 0));

		sunsetGradientColors[0][0] = 12;
		sunsetGradientColors[0][1] = 1;
		sunsetGradientColors[0][2] = 41;

		sunsetGradientColors[1][0] = 219;
		sunsetGradientColors[1][1] = 19;
		sunsetGradientColors[1][2] = 38;

		sunsetGradientColors[2][0] = 251;
		sunsetGradientColors[2][1] = 165;
		sunsetGradientColors[2][2] = 34;

		sunsetGradientColors[3][0] = 219;
		sunsetGradientColors[3][1] = 19;
		sunsetGradientColors[3][2] = 38;

		sunsetGradientColors[4][0] = 12;
		sunsetGradientColors[4][1] = 1;
		sunsetGradientColors[4][2] = 41;

		if (reflect)
		{
			CreateMultiGradient(input, sunsetGradientColors, steps);
			ReflectColorArray(input);
		}
		else {
			CreateMultiGradient(input, sunsetGradientColors, steps);
		}
	}

	void ColorPalette::ReflectColorArray(vector<vector<int>>& input)
	{
		unsigned int originalSize = input.size();
		input.resize(input.size() * 2, vector<int>(3, 0));
		for (unsigned int i = 0; i < originalSize; i++)
		{
			for (int k = 0; k < 3; k++) {
				input[i + originalSize][k] = input[(originalSize - 1) - i][k];
			}
		}
	}

	//Checks which key-color the color specified is closest to. 
	int ColorPalette::Color(int index) {
		double keyColorsMinusOne = keyColors - 1;

		if (reflect) {
			//Find percentage through the gradient
			double percentThrough = (double)index / ((double)steps * 2);

			//Get the position out of the gradient
			double pos = percentThrough * keyColorsMinusOne * 4;
			pos = ceil(pos);

			//Check if it's at the beginning or end. 
			if (pos == 1 || pos == keyColorsMinusOne * 4 || pos == 0) {
				return 1;
			}
			if (pos == keyColorsMinusOne * 2 || pos == (keyColorsMinusOne * 2) + 1) {
				return keyColors;
			}

			//Shift the gradient over and solve for the middle. 
			if (pos > keyColorsMinusOne * 2) {
				pos = ((keyColorsMinusOne * 4) + 1) - pos;
			}
			pos--;
			pos = pos / 2;
			pos = ceil(pos);
			pos++;

			return pos;
		}
		else {
			//Find percentage through the gradient
			double percentThrough = (double)index / steps;

			//Get the position out of the gradient
			double pos = percentThrough * keyColorsMinusOne * 2;
			pos = ceil(pos);

			//Check if it's at the beginning or end. 
			if (pos == 0) {
				return 1;
			}
			if (pos == 1) {
				return pos;
			}
			if (pos == keyColorsMinusOne * 2) {
				return keyColorsMinusOne + 1;
			}

			//Shift the gradient over and solve for the middle. 
			pos--;
			pos = pos / 2;
			pos = ceil(pos);
			pos++;

			return pos;
		}
	}

	int ColorPalette::ColorChanges(vector<vector<Point>>& allPoints, int WIDTH, int HEIGHT) {
		/* This just draws a bunch of lines ~half way through the image to determine how many color changes happened.
		* It's fairly inconsistent because so many aspects of the lines are random and they don't consider the whole image.
		*/

		int size = steps;
		int referenceLines = 20;

		if (reflect) {
			size = size * 2;
		}

		random_device rand_dev;
		mt19937 generator(rand_dev());

		int lastColor = -1;
		int colorChanges = 0;
		int indicesSinceLastChange = 0;
		for (int i = 0; i < referenceLines; i++) {
			//Height of the line
			int height = 0;
			uniform_int_distribution<int> heightDistribution(0, HEIGHT / 2);
			//Make sure the lines are all in the middle half. 
			height = heightDistribution(generator) + (HEIGHT / 4);

			//Width of the line
			int width = 0;
			//Make sure the lines don't go more than halfway. 
			uniform_int_distribution<int> widthDistribution(WIDTH / 4, WIDTH / 2);
			width = widthDistribution(generator);

			//Whether to start scanning from the left or the right.
			int side = 0;
			uniform_int_distribution<int> sideDistribution(0, 1);
			side = sideDistribution(generator);

			int iterator = 0;
			if (side == 0) {
				iterator = WIDTH - 1;
			}
			lastColor = -1;
			indicesSinceLastChange = 0;
			while (true) {
				indicesSinceLastChange++;

				if (iterator > allPoints.size() || iterator < 0 || height > allPoints[iterator].size() || height < 0) {
					cout << iterator << endl;
					cout << height << endl;
					cout << width << endl;
					cout << side << endl;
				}

				int index = allPoints[iterator][height].getIndex();
				if (index != -1) {
					index = index % size;
					if (Color(index) != lastColor) {
						//This just checks that it's not a one-pixel change and counts a tiny change like that (which may just revert itself)
						if (indicesSinceLastChange > 2) {
							colorChanges++;
						}
						lastColor = Color(index);
						indicesSinceLastChange = 0;
					}
				}

				if (side == 0) {
					iterator--;
				}
				else {
					iterator++;
				}

				if (side == 0) {
					if (iterator == WIDTH - width) {
						break;
					}
				}
				else {
					if (iterator == width) {
						break;
					}
				}
			}
		}

		colorChanges = colorChanges / referenceLines;

		if (colorChanges == 0) {
			colorChanges++;
		}

		return colorChanges;
	}

	void ColorPalette::ShiftGradient(vector<vector<int>>& colors, vector<vector<int>> colorsTemp, vector<vector<Point>>& allPoints) {
		//Yes this number needs to be gigantic. What if the person has 10 4k screens, is on strech, and is computing an image with 1,000,000 iterations? It's ridiculous but possible. 
		unsigned long long int averageIteration = 0;
		int numPointsOutside = 0;
		for (int x = 0; x < allPoints.size(); x++) {
			for (int y = 0; y < allPoints[0].size(); y++) {
				if (allPoints[x][y].getIndex() != 1.5) {
					averageIteration += allPoints[x][y].getIteration();
					numPointsOutside++;
				}
			}
		}
		averageIteration = averageIteration / (numPointsOutside);
		cout << "Average Iteration: " << averageIteration << endl;

		double shifts = 20;
		double idealDark = 0.7;

		double idealShift = 0;
		double ClosestDark = 2;
		for (double i = 0; i < shifts; i++) {
			//Shift Gradient by 10%
			rotate(colorsTemp.begin(), colorsTemp.begin() + ((colorsTemp.size() - 1) * (1 / shifts)), colorsTemp.end());

			int numColorDark = 0;
			int numColorLight = 0;
			for (int x = 0; x < allPoints.size(); x++) {
				for (int y = 0; y < allPoints[0].size(); y++) {
					int index = (int)allPoints[x][y].getIndex() % colorsTemp.size();
					if (allPoints[x][y].getIndex() != 1.5) {
						if (isDark(colorsTemp[index])) {
							numColorDark += (allPoints[x][y].getIteration() / averageIteration);
						}
						else {
							numColorLight += (allPoints[x][y].getIteration() / averageIteration);
						}
					}
				}
			}

			double percentColorDark = numColorDark / (double)(numColorDark + numColorLight);
			//cout << "Percent Shift: " << percentColorDark << endl;
			if (abs(idealDark - percentColorDark) < ClosestDark) {
				ClosestDark = abs(idealDark - percentColorDark);
				idealShift = i / shifts;
			}
		}

		//cout << "Ideal Shift: " << idealShift * 100 << "%" << endl;
		rotate(colors.begin(), colors.begin() + ((colorsTemp.size() - 1) * idealShift), colors.end());
	}

	//I found this here: http://www.tannerhelland.com/3643/grayscale-image-algorithm-vb6/
	bool ColorPalette::isDark(vector<int>& color) {
		int r = color[0];
		int g = color[1];
		int b = color[2];

		r = r * 0.299;
		g = g * 0.587;
		b = b * 0.114;

		if (r + g + b < 130) {
			return true;
		}
		else {
			return false;
		}
	}

	void ColorPalette::CreateGradient(vector<vector<int>>& input, vector<int>& one, vector<int>& two, int numSteps)
	{
		int r1 = one[0];
		int g1 = one[1];
		int b1 = one[2];

		int r2 = two[0];
		int g2 = two[1];
		int b2 = two[2];

		int newR = 0;
		int newG = 0;
		int newB = 0;

		input.resize(numSteps, vector<int>(3, 0));
		double iNorm;
		for (int i = 0; i < numSteps; i++)
		{
			iNorm = i / static_cast<double>(numSteps); // a normalized [0:1] variable
			newR = static_cast<int>(r1 + iNorm * (r2 - r1));
			newG = static_cast<int>(g1 + iNorm * (g2 - g1));
			newB = static_cast<int>(b1 + iNorm * (b2 - b1));
			input[i][0] = newR;
			input[i][1] = newG;
			input[i][2] = newB;
		}
	}

	void ColorPalette::CreateMultiGradient(vector<vector<int>>& input, vector<vector<int>>& colors, int numSteps)
	{
		input.resize(numSteps, vector<int>(3, 0));
		// we assume a linear gradient, with equal spacing between colors
		// The final gradient will be made up of n 'sections', where n =
		// colors.length - 1
		unsigned int numSections = colors.size() - 1;
		int gradientIndex = 0; // points to the next open spot in the final
							   // gradient
		vector<vector<int>> temp;

		for (unsigned int section = 0; section < numSections; section++)
		{
			// we divide the gradient into (n - 1) sections, and do a regular
			// gradient for each
			CreateGradient(temp, colors[section], colors[section + 1], numSteps / numSections);
			for (unsigned int i = 0; i < temp.size(); i++)
			{
				// copy the sub-gradient into the overall gradient
				for (int k = 0; k < 3; k++) {
					input[gradientIndex][k] = temp[i][k];
				}
				gradientIndex++;
			}
		}

		unsigned int tempSize = temp.size();
		if (gradientIndex < numSteps)
		{
			// The rounding didn't work out in our favor, and there is at least
			// one unfilled slot in the gradient[] array.
			// We can just copy the final color there
			for (; gradientIndex < numSteps; gradientIndex++)
			{
				for (int k = 0; k < 3; k++) {
					input[gradientIndex][k] = temp[tempSize - 1][k];
				}
			}
		}
		colors.clear();
	}
}
