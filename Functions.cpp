#include <conio.h> // For _kbhit and _getch on Windows
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream> 
#include <Windows.h> // For Sleep function
#include "ColorFunctions.h"
#include "FileFunctions.h"
using namespace std;
namespace fs = std::filesystem;

void createNewIcon();
void generateGrid(int size);
void displayGrid(vector<vector<string>>& grid, bool isNew);
void processKeystroke(char key, bool& LETTERS_ON, bool& running, int& cursor_x, int& cursor_y, vector<vector<string>>& grid, bool isNew);


static string toUppercase(string input) {
    string res;
    for (char c : input) res.push_back(toupper(c));
    return res;
}

void initializeMenu() {
    bool exited = false; // exit flag

    while (!exited) {
        // print the main menu
        std::cout << endl;
        print_string_with_background_color("P", "------------------------------");
        std::cout << endl;
        print_string_with_background_color("P", "|  ");
        print_string_with_background_color("B", "      MAIN MENU     ");
        print_string_with_background_color("P", "  |");
        std::cout << endl;
        print_string_with_background_color("P", "------------------------------");
        std::cout << endl << endl;
        std::cout << "1. Create new icon\n";
        std::cout << "2. Open existing icon\n";
        std::cout << "Type 'DONE' to exit.\n";
        std::cout << endl << "------------------------------" << endl;
        std::cout << "Select: ";
        string input;
        cin >> input;
        system("CLS"); // clear screen after selection for terminal clarity
        if (toUppercase(input) == "DONE") {
            std::cout << "Goodbye!" << endl;
            exited = true; // exit if done is entered
        }
        else if (toUppercase(input) == "1") {
            createNewIcon();
        }
        else if (toUppercase(input) == "2") {
            readIconFile();
        }
        else {
            print_string_with_background_color("R", "Invalid choice. Please try again.");
            std::cout << endl;
        }
    }
}

void createNewIcon() { // Print the menu to create a new icon

    int size = 0;
    bool inputIsValid = false;
    while (!inputIsValid) {
        std::cout << "Please enter the height of the icon in pixels: ";
        cin >> size;
        if (cin.fail()) { // if the input was not a integer, handle error appropriately (clear error state, ignore invalid input, print message to user)
            inputIsValid = false;
            cin.clear();
            cin.ignore(1000, '\n');
            std::cout << "Invalid choice. Please input a number." << endl;
        }
        else {
            inputIsValid = true;
            std::cout << "Created icon with dimensions of " << size << " x " << size << "!" << endl << endl;
            std::cout << "Press any key to enter Edit Mode..." << endl;
            generateGrid(size);
        }
    }
}


void generateGrid(int size) { // Generate the grid 2D vector data structure
    vector<vector<string>> grid(size, vector<string>(size));
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            grid[i][j] = "*"; // Fill every element with "*"
        }
    }
    displayGrid(grid, true);
}

void displayGrid(vector<vector<string>>& grid, bool isNew) {
    char key;
    bool running = true;
    bool LETTERS_ON = false;
    int cursor_x = 0;
    int cursor_y = 0;
    bool first = true;

    while (running) {
        if (_kbhit()) {
            // Get the pressed key
            system("CLS");
            key = _getch();
            // Perform actions based on the pressed key
            if (first) first = !first;
            else {
                processKeystroke(key, LETTERS_ON, running, cursor_x, cursor_y, grid, isNew);
                if (key == 27 || key == 13) break;
            }
            
            // PRINT GRID
            for (int i = 0; i < grid.size(); ++i) {
                for (int j = 0; j < grid[i].size(); ++j) {

                    string element = grid[i][j]; // Access the element at index [i][j]
                    if (i == cursor_x && j == cursor_y) {
                        // If the element under the cursor is empty, print lightgray, otherwise print hover color
                        element == ""
                            ? (LETTERS_ON ? print_string_with_background_color("LIGHTGRAY", "*") : print_string_with_background_color("LIGHTGRAY", " "))
                            : print_hover_color(element, element);
                    }
                    // For all other elements, print their corresponding color 
                    else if (element == "R") (LETTERS_ON ? print_string_with_background_color("R", "R") : print_string_with_background_color("R", " "));
                    else if (element == "O") (LETTERS_ON ? print_string_with_background_color("O", "O") : print_string_with_background_color("O", " "));
                    else if (element == "Y") (LETTERS_ON ? print_string_with_background_color("Y", "Y") : print_string_with_background_color("Y", " "));
                    else if (element == "G") (LETTERS_ON ? print_string_with_background_color("G", "G") : print_string_with_background_color("G", " "));
                    else if (element == "B") (LETTERS_ON ? print_string_with_background_color("B", "B") : print_string_with_background_color("B", " "));
                    else if (element == "V") (LETTERS_ON ? print_string_with_background_color("V", "V") : print_string_with_background_color("V", " "));
                    else if (element == "P") (LETTERS_ON ? print_string_with_background_color("P", "P") : print_string_with_background_color("P", " "));
                    else {
                        LETTERS_ON ? print_string_with_background_color("GRAY", "*") : print_string_with_background_color("GRAY", " ");
                    }
                }
                std::cout << endl;
            }
            // PRINT INSTRUCTIONS
            std::cout << endl << endl << endl;
            print_string_with_background_color("R", "1 - Red");
            print_string_with_background_color("O", "2 - Orange");
            print_string_with_background_color("Y", "3 - Yellow");
            print_string_with_background_color("G", "4 - Green");
            print_string_with_background_color("B", "5 - Blue");
            print_string_with_background_color("V", "6 - Violet");
            print_string_with_background_color("P", "7 - Pink");
            std::cout << endl << endl;
            std::cout << "Arrow keys: Move cursor" << endl;
            std::cout << "       1-7: Color selected pixel" << endl;
            std::cout << " BACKSPACE: Remove color" << endl;
            std::cout << "       TAB: Toggle letters" << endl;
            std::cout << "     ENTER: Save icon to file" << endl;
            std::cout << "       ESC: Exit without saving" << endl;
        }
        Sleep(10); // Sleep for 100 milliseconds
    }
}

void processKeystroke(char key, bool& LETTERS_ON, bool& running, int& cursor_x, int& cursor_y, vector<vector<string>>& grid, bool isNew) {
    switch (key) {
    case 27: // ESC key
        running = false; // Break the loop
        break;
        // Add cases for other specific keys you want to handle
    case 9: // TAB key
        LETTERS_ON = !LETTERS_ON; // Toggle Letter mode
        break;
    case 13: // Enter key
        running = false;
        writeGridToFile(grid, isNew);
        //cout << "Saving file..." << endl;
        break;
    case 8: // BACKSPACE key
        grid[cursor_x][cursor_y] = "*"; // Delete color
        break;
    case 72:
        //cout << "Up arrow is pressed" << endl;
        if (cursor_x > 0) cursor_x--;
        break;
    case 75:
        //cout << "Left arrow is pressed" << endl;
        if (cursor_y > 0) cursor_y--;
        break;
    case 80:
        //cout << "Down arrow is pressed" << endl;
        if (cursor_x < grid.size() - 1) cursor_x++;
        break;
    case 77:
        //cout << "Right arrow is pressed" << endl;
        if (cursor_y < grid.size() - 1) cursor_y++;
        break;
    case 49: // Key "1"
        grid[cursor_x][cursor_y] = "R";
        break;
    case 50: // Key "2"
        grid[cursor_x][cursor_y] = "O";
        break;
    case 51: // Key "3"
        grid[cursor_x][cursor_y] = "Y";
        break;
    case 52: // Key "4"
        grid[cursor_x][cursor_y] = "G";
        break;
    case 53: // Key "5"
        grid[cursor_x][cursor_y] = "B";
        break;
    case 54: // Key "6"
        grid[cursor_x][cursor_y] = "V";
        break;
    case 55: // Key "7"
        grid[cursor_x][cursor_y] = "P";
        break;
    default: // On any other key, do nothing
        break;
    }
}