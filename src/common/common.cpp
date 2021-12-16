#include "common.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <cmath>

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
    std::vector<std::string> v;
    if (!target.empty()) {
        std::smatch res;
        std::string::const_iterator searchStart(target.begin());
        while (std::regex_search(searchStart, target.cend(), res, rx)) {
            v.push_back(res[1]);
            searchStart = res.suffix().first;
        }
        std::string end = "";
        for (; searchStart != target.cend(); ++searchStart) end += *searchStart;
        v.push_back(end);
    }
    return v;
}

// Stolen from https://stackoverflow.com/a/15619863/9634099
std::vector<int> string_vector_to_int_vector(std::vector<std::string> input) {
    std::vector<int> output;
    std::transform(input.begin(), input.end(),
                   std::back_inserter(output),
                   [](const std::string& str) { return stoi(str); });
    return output;
}

// Stolen from
// https://www.programiz.com/cpp-programming/examples/binary-decimal-convert
uint64_t binary_to_decimal(std::string binary) {
    uint64_t dec = 0, i = 0, rem;

    while (binary.length() != 0) {
        rem = binary[binary.length() - 1] - '0';
        binary.pop_back();
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}