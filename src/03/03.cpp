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

int numberOfZeros(std::vector<std::string>& inputs, size_t i) {
    int zeros = 0;
    for (std::vector<std::string>::iterator iterator = inputs.begin();
         iterator != inputs.end(); ++iterator) {
        std::vector<char> inputVector((*iterator).begin(), (*iterator).end());
        if (inputVector[i] == '0') zeros++;
    }
    return zeros;
}

void applyBitCriteria(std::vector<std::string>& inputs, bool reversed,
                      size_t i) {
    int zeros = numberOfZeros(inputs, i);
    bool moreZeros = zeros > inputs.size() / 2;
    for (std::vector<std::string>::iterator iterator = inputs.begin();
         iterator != inputs.end(); ++iterator) {
        std::vector<char> inputVector((*iterator).begin(), (*iterator).end());
        if (moreZeros) {
            if ((!reversed && inputVector[i] == '1') ||
                (reversed && inputVector[i] == '0')) {
                inputs.erase(iterator);
                iterator--;
            }
        } else if ((!reversed && inputVector[i] == '0') ||
                   (reversed && inputVector[i] == '1')) {
            inputs.erase(iterator);
            iterator--;
        }
    }
}

int main() {
    std::vector<std::string> inputs = split(read_inputs(), "\n");
    std::vector<std::string> oxygenInputs = inputs;
    std::vector<std::string> co2Inputs = inputs;
    std::string gamma = "";
    std::string epsilon = "";
    for (size_t i = 0; i < inputs[0].length(); i++) {
        int zeros = numberOfZeros(inputs, i);
        gamma += zeros > inputs.size() / 2 ? "0" : "1";
        epsilon += zeros > inputs.size() / 2 ? "1" : "0";
        if (oxygenInputs.size() > 1) applyBitCriteria(oxygenInputs, false, i);
        if (co2Inputs.size() > 1) applyBitCriteria(co2Inputs, true, i);
    }
    std::cout << "Part 1: " << binaryToDecimal(gamma) * binaryToDecimal(epsilon)
              << "\nPart 2: "
              << binaryToDecimal(oxygenInputs[0]) *
                     binaryToDecimal(co2Inputs[0])
              << std::endl;
}