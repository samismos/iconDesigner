// ColorFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there. 
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string, int> colorMap = { // A map which maps color strings to the numeric values needed for the terminal color printing
	// Gray for uncolored pixels
	{"GRAY", 240},
	{"LIGHTGRAY", 246},
	// Default colors 
	{"R", 1},
	{"Y", 226},
	{"O", 172},
	{"G", 10},
	{"B", 4},
	{"P", 165},
	{"V", 93},

	{"*", 0},  // Empty string case

	// Hovering colors
	{"LR", 9},
	{"LO", 214},
	{"LY", 229},
	{"LG", 46},
	{"LB", 12},
	{"LV", 99},
	{"LP", 170},
};

unordered_map<string, string> hoverColorMap = { // Intermediate map to slightly change the color when cursor is hovering over the pixel
  {"R", "LR"},
  {"Y", "LY"},
  {"O", "LO"},
  {"G", "LG"},
  {"B", "LB"},
  {"P", "LP"},
  {"V", "LV"},
  {"*", "LIGHTGRAY"},  // Empty string case
};


void print_row_length_color(int times, string color) { // Prints an entire row of length <times> with a background color of <color>
	for (int i = 0; i < times; i++) {
		printf("\033[48;5;%dm %s \033[m", colorMap.at(color), color.c_str());
	}
	std::cout << endl;
}

void print_string_with_background_color(string color, string text) { // Prints <text> with a background color of <color>
	printf("\033[48;5;%dm %s \033[m", colorMap.at(color), text.c_str());
}

void print_hover_color(string color, string text) { // Prints <text> with the corresponding hover color for <color>
	printf("\033[48;5;%dm %s \033[m", colorMap.at(hoverColorMap.at(color)), text.c_str());
}