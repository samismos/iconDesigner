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
#include "Functions.h"
using namespace std;
namespace fs = std::filesystem;

string readFilename(bool withExtension) {
    string input;
    std::cout << "Enter filename (e.g., my_grid.txt): ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, input);
    string filename;
    filename = "icons/" + input + (withExtension ? ".txt" : "");
    std::replace(filename.begin(), filename.end(), ' ', '_');
    return filename;
}

string readFilename(bool withExtension, string& filename) {
    string input;
    filename = "icons/" + filename + (withExtension ? ".txt" : "");
    std::replace(filename.begin(), filename.end(), ' ', '_');
    return filename;
}

string rereadFilename(bool withExtension) {
    string input;
    std::cout << "Enter filename (e.g., my_grid.txt): ";
    std::getline(std::cin, input);
    string filename;
    filename = "icons/" + input + (withExtension ? ".txt" : "");
    std::replace(filename.begin(), filename.end(), ' ', '_');
    return filename;
}

void writeGridToFile(std::vector<std::vector<std::string>>& vec, bool isNew) {
    string filename;
    isNew ? filename = readFilename(true) : filename = rereadFilename(true);

    // Open the file for writing
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& row : vec) {
            for (const std::string& element : row) {
                outfile << element << ",";  // Write element with comma separator
            }
            outfile << std::endl;  // Newline after each row
        }
        outfile.close();
        std::cout << "Successfully wrote vector to file: " << filename << std::endl;

        // Get the absolute path of the saved file
        std::filesystem::path absolute_path = std::filesystem::absolute(filename);

        std::string absolute_path_str = absolute_path.string();
        std::replace(absolute_path_str.begin(), absolute_path_str.end(), '\\', '/');
        std::cout << "Icon saved successfully to absolute path: " << absolute_path_str << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    Sleep(1000);
}

void readGridFromFile(std::string& filename) {
    std::string line;
    int line_counter = 0;
    std::ifstream myfile(filename);
    std::vector<std::vector<std::string>> grid;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            line_counter++;

            // Replace commas with spaces
            std::replace(line.begin(), line.end(), ',', ' ');

            // Create a stringstream from the modified line
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> row;

            // Tokenize the line by spaces and push each token into the row vector
            while (ss >> token) {
                row.push_back(token);
            }

            // Push the row into the grid
            grid.push_back(row);
        }

        std::cout << endl << "Opening file " << filename << ", " << line_counter << " x " << line_counter << "..." << endl;
        myfile.close();
        cout << "Press any key to enter Edit Mode." << endl;
        displayGrid(grid, false);
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}




void readIconFile() {
    //string filename = readFilename();
    vector<string> files;
    unordered_map<int, string> filenames;

    try {
        // Iterate over all files in the directory
        int index = 1;
        for (const auto& entry : fs::directory_iterator("./icons/")) {
            // Check if the entry is a regular file
            if (fs::is_regular_file(entry.path())) {
                // Print the filename
                std::cout << index << ". " << entry.path().filename().string() << std::endl;
                filenames.emplace(index++, entry.path().filename().string());
            }
        }
        cout << endl;
        cout << "Select number from " << "1" << " to " << filenames.size() << ": ";
        int choice;
        std::cin >> choice;
        if (cin.fail()) { // if the input was not a integer, handle error appropriately (clear error state, ignore invalid input, print message to user)
            cin.clear();
            cin.ignore(1000, '\n');
            std::cout << "Choice was not a number. Returning to main menu..." << endl;
        }
        else {
            string file = filenames.at(choice);
            //cout << file << endl;
            string filename = readFilename(false, file);
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            readGridFromFile(filename);
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
