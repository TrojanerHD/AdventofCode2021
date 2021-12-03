#include "common.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Stolen from https://stackoverflow.com/a/40699396/9634099
std::string read_inputs() {
    std::ifstream file("values.txt");
    if (!file.is_open()) return nullptr;
    std::string line;
    std::string values;
    auto firstIteration = true;
    while (getline(file, line)) {
        if (!firstIteration)
            values += "\n";
        else
            firstIteration = false;
        values += line;
    }
    return values;
}

// Stolen from https://stackoverflow.com/a/40699396/9634099
std::vector<std::string> split(std::string target, std::string delim) {
    std::vector<std::string> v;
    if (!target.empty()) {
        size_t start = 0;
        do {
            size_t x = target.find(delim, start);
            if (x == std::string::npos) break;

            v.push_back(target.substr(start, x - start));
            start = x + 1;
        } while (true);

        v.push_back(target.substr(start));
    }
    return v;
}