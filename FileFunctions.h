#include <string>
#include <vector>

#pragma once
string readFilename(bool withExtension);
string readFilename(bool withExtension, string& filename);
string rereadFilename(bool withExtension);
void writeGridToFile(std::vector<std::vector<std::string>>& vec, bool isNew);
void readGridFromFile(std::string& filename);
void readIconFile();