#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

// Stolen from
// https://www.programiz.com/cpp-programming/examples/binary-decimal-convert
int binaryToDecimal(std::string binary) {
    int dec = 0, i = 0, rem;

    while (binary.length() != 0) {
        rem = stol(binary) % 10;
				binary.pop_back();
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}

int main() {
    std::vector<std::string> inputs = split(read_inputs(), "\n");
    std::vector<char> firstInputs(inputs[0].begin(), inputs[0].end());
    std::string gamma = "";
		std::string epsilon = "";
    for (size_t i = 0; i < firstInputs.size(); i++) {
        auto zeros = 0;
        for (size_t j = 0; j < inputs.size(); j++) {
            std::vector<char> inputVector(inputs[j].begin(), inputs[j].end());
            if (inputVector[i] == '0') zeros++;
        }
        gamma += zeros > inputs.size() / 2 ? "0" : "1";
				epsilon += zeros > inputs.size() / 2 ? "1" : "0";
    }
    std::cout << "Part 1: " << binaryToDecimal(gamma) * binaryToDecimal(epsilon) << std::endl;
}