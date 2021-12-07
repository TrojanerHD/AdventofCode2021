#include "common.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// Stolen from https://stackoverflow.com/a/40699396/9634099
std::string read_inputs() {
    std::ifstream file("values.txt");
    if (!file.good()) {
        std::cout << "Values file not found" << std::endl;
        return "";
    }
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
    std::regex rx("(.*?)" + delim);
    target += delim;
    std::vector<std::string> v;
    if (!target.empty()) {
        std::smatch res;
        std::string::const_iterator searchStart(target.begin());
        while (std::regex_search(searchStart, target.cend(), res, rx)) {
            v.push_back(res[1]);
            searchStart = res.suffix().first;
        }
    }
    return v;
}
// Stolen from https://stackoverflow.com/a/15619863/9634099
std::vector<int> string_vector_to_int_vector(std::vector<std::string> input) {
    std::vector<int> output;
    std::transform(input.begin(), input.end(),
                   std::back_inserter(output),
                   [](const std::string& str) { return stoi(str); });
}