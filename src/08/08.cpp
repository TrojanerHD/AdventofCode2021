#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

bool lines_match(std::vector<char> line1, std::vector<char> line2) {
    for (char c : line1)
        if (std::find(line2.begin(), line2.end(), c) == line2.end())
            return false;
    return true;
}

std::vector<char> string_to_char_vector(std::string string) {
    std::vector<char> v(string.begin(), string.end());
    return v;
}

int main() {
    std::vector<std::string> ios = split(read_inputs(), "\n");
    int easyDigits = 0;
    int part2 = 0;
    for (std::string ioString : ios) {
        std::vector<std::string> io = split(ioString, " \\| ");
        std::vector<std::string> inputs = split(io[0], " ");
        std::vector<std::string> outputs = split(io[1], " ");

        std::vector<char> zero(6);   // Hard
        std::vector<char> one(2);    // Easy
        std::vector<char> two(5);    // Hard
        std::vector<char> three(5);  // Hard
        std::vector<char> four(4);   // Easy
        std::vector<char> five(5);   // Hard
        std::vector<char> six(6);    // Hard
        std::vector<char> seven(3);  // Easy
        std::vector<char> nine(6);   // Hard

        for (auto input : inputs) {
            if (input.length() == 2)
                one = string_to_char_vector(input);
            else if (input.length() == 4)
                four = string_to_char_vector(input);
            else if (input.length() == 3)
                seven = string_to_char_vector(input);
            else if (input.length() == 6)
                six = string_to_char_vector(input);
        }
        for (auto input : inputs) {
            if (input.length() == 2 || input.length() == 3 ||
                input.length() == 4 || input.length() == 7)
                continue;

            std::vector<char> lanes = string_to_char_vector(input);
            int overlappings = 0;
            if (input.length() == 6) {
                for (char lane : lanes)
                    for (char fourChar : four)
                        if (fourChar == lane) ++overlappings;
                if (overlappings == 4) {
                    nine = lanes;
                    continue;
                }
                overlappings = 0;
                for (char lane : lanes)
                    for (char oneChar : one)
                        if (oneChar == lane) ++overlappings;
                if (overlappings == 2)
                    zero = lanes;
                else
                    six = lanes;
                continue;
            }
            for (char lane : lanes)
                for (char oneChar : one)
                    if (oneChar == lane) ++overlappings;

            if (overlappings == 2) {
                three = lanes;
                continue;
            }

            overlappings = 0;
            for (char lane : lanes)
                for (char fourChar : four)
                    if (fourChar == lane) ++overlappings;

            if (overlappings == 2)
                two = lanes;
            else
                five = lanes;
        }

        std::string display("");
        for (std::string output : outputs) {
            if (output.length() == 2) {
                ++easyDigits;
                display += "1";
            } else if (output.length() == 3) {
                ++easyDigits;
                display += "7";
            } else if (output.length() == 4) {
                ++easyDigits;
                display += "4";
            } else if (output.length() == 7) {
                ++easyDigits;
                display += "8";
            } else {
                std::vector<char> outputVector(output.begin(), output.end());
                if (output.length() == 6) {
                    if (lines_match(outputVector, nine))
                        display += "9";
                    else if (lines_match(outputVector, six))
                        display += "6";
                    else
                        display += "0";
                } else {
                    if (lines_match(outputVector, two))
                        display += "2";
                    else if (lines_match(outputVector, three))
                        display += "3";
                    else
                        display += "5";
                }
            }
        }
        part2 += stoi(display);
    }

    std::cout << "Part 1: " << easyDigits << "\nPart 2: " << part2 << std::endl;
}