#pragma once
#include "Point.h"
#include <vector>
#include <iostream>
#include <random>
#include <filesystem>

namespace ColorPalette {
	using namespace std;

	/*
	* It's very easy to add your own colors.
	*
	* You can add colors in a completely random fashion (see Random Rainbow as an example),
	* or you can make all the colors manually (this is really tough and you probably won't do it as well as the gradient maker below);
	* keep in mind that you'll want to make atleast 100 different colors for it to look nice.
	*
	* You can also add colors using a gradient, which look really nice. This has been greatly simplified using code from Matthew Beckler.
	* Credits to him for those two methods and the link to the full code is below.
	* All you have to do to use his code is either use an array with two colors by calling createGradient and passing it your two color objects.
	* You can look at the examples for details. You can also create gradients with multiple colors by creating an array with all the color objects you want.
	* Then pass that array to the createMultipleGradients. You can look up gradients online or use a gradient maker for some nice looking gradients.
	*
	* The steps value is how many steps it divides the difference between the colors into. Another way to think of it is how fast the set's color's change.
	* The more steps you have, the slower the colors change, but too few steps and the colors are wildly different from each other, causing banding.
	*
	* The reflect color array method allows you to reflect the gradient over itself. Basically the gradient goes through the colors you specify and then travels
	* back, instead of abruptly restarting and creating a very odd-looking transition.
	*
	* All the color choosing is consolidated in this class to make modification easy. To create your own color option, simply create a method for your color
	* that creates the gradient (or you can not use a gradient). Then add that inside  the if statement inside colorChooser, so you can select your method.
	*/

	class ColorPalette {
	public:
		void ColorChooser(string paletteIn, vector<vector<int>>& color);
		void ColorChooser(string palette, vector<vector<int>>& color, int steps);

		void ShiftGradient(vector<vector<int>>& colors, vector<vector<int>> colorsTemp, vector<vector<Point>>& allPoints);
		int ColorChanges(vector<vector<Point>>& allPoints, int WIDTH, int HEIGHT);

		bool reflect;
		int steps;
		int keyColors;
	private:
		string palette;

		//This is a completely random number generation that has no pattern or gradient whatsoever.
		void RandomRainbow(vector<vector<int>>& input, int steps);
		void SunsetGradient(vector<vector<int>>& input, int steps, bool reflect);
		void OrangeAndBlue(vector<vector<int>>& input, int steps, bool reflect);
		void GreenAndBlue(vector<vector<int>>& input, int steps, bool reflect);
		void BlueAndWhiteGradient(vector<vector<int>>& input, int steps, bool reflect);

		bool isDark(vector<int>& color);
		int Color(int index);

		//This allows you to reflect the array over itself, creating a smooth transition. 
		void ReflectColorArray(vector<vector<int>>& input);

		//This creates a gradient from two colors with their RGB colors in a vector int array
		void CreateGradient(vector<vector<int>>& input, vector<int>& one, vector<int>& two, int numSteps);

		//This creates a gradient from two or more colors by taking in an array of arrays with the inner array having 3 ints, each defining the R,G,and B values respectively. The outer array contains eaach of these arrays with each array at a given index in the outer array representing a color.
		void CreateMultiGradient(vector<vector<int>>& input, vector<vector<int>>& colors, int numSteps);
	};
}