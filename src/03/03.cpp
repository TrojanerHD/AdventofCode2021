#include <iostream>

#include "../common/common.h"

int number_of_zeros(std::vector<std::string>& inputs, size_t i) {
    int zeros = 0;
    for (std::vector<std::string>::iterator iterator = inputs.begin();
         iterator != inputs.end(); ++iterator) {
        std::vector<char> inputVector(iterator->begin(), iterator->end());
        if (inputVector[i] == '0') zeros++;
    }
    return zeros;
}

void apply_bit_criteria(std::vector<std::string>& inputs, bool reversed,
                        size_t i) {
    int zeros = number_of_zeros(inputs, i);
    bool moreZeros = zeros > inputs.size() / 2;
    for (std::vector<std::string>::iterator iterator = inputs.begin();
         iterator != inputs.end(); ++iterator) {
        std::vector<char> inputVector(iterator->begin(), iterator->end());
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
        int zeros = number_of_zeros(inputs, i);
        gamma += zeros > inputs.size() / 2 ? "0" : "1";
        epsilon += zeros > inputs.size() / 2 ? "1" : "0";
        if (oxygenInputs.size() > 1) apply_bit_criteria(oxygenInputs, false, i);
        if (co2Inputs.size() > 1) apply_bit_criteria(co2Inputs, true, i);
    }
    std::cout << "Part 1: "
              << binary_to_decimal(gamma) * binary_to_decimal(epsilon)
              << "\nPart 2: "
              << binary_to_decimal(oxygenInputs[0]) *
                     binary_to_decimal(co2Inputs[0])
              << std::endl;
}