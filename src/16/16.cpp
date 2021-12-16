#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

std::string hex_to_bin(std::string hex) {
    std::string result;
    for (char c : hex) {
        switch (c) {
            case '0':
                result += "0000";
                break;
            case '1':
                result += "0001";
                break;
            case '2':
                result += "0010";
                break;
            case '3':
                result += "0011";
                break;
            case '4':
                result += "0100";
                break;
            case '5':
                result += "0101";
                break;
            case '6':
                result += "0110";
                break;
            case '7':
                result += "0111";
                break;
            case '8':
                result += "1000";
                break;
            case '9':
                result += "1001";
                break;
            case 'A':
            case 'a':
                result += "1010";
                break;
            case 'B':
            case 'b':
                result += "1011";
                break;
            case 'C':
            case 'c':
                result += "1100";
                break;
            case 'D':
            case 'd':
                result += "1101";
                break;
            case 'E':
            case 'e':
                result += "1110";
                break;
            case 'F':
            case 'f':
                result += "1111";
                break;
        }
    }
    return result;
}

size_t analyze_bits(std::vector<uint64_t>& numbers, int& versions,
                    std::string bin, int start = 0) {
    auto packetVersion = binary_to_decimal(std::string() + bin[start] +
                                           bin[start + 1] + bin[start + 2]);
    versions += packetVersion;
    auto typeID = binary_to_decimal(std::string() + bin[start + 3] +
                                    bin[start + 4] + bin[start + 5]);
    switch (typeID) {
        case 4: {
            bool lastBit = false;
            std::string binNumber;
            size_t i;
            for (i = start + 6; !lastBit; i += 5) {
                if (bin[i] == '0') lastBit = true;
                binNumber += std::string() + bin[i + 1] + bin[i + 2] +
                             bin[i + 3] + bin[i + 4];
            }
            uint64_t number = binary_to_decimal(binNumber);
            numbers.push_back(number);
            return i;
        }
        default:
            auto lengthType = bin[start + 6] - '0' == 0 ? 15 : 11;
            std::vector<uint64_t> tempNumbers;
            auto newBeginning = analyze_bits(tempNumbers, versions, bin,
                                             7 + start + lengthType);
            if (bin[start + 6] - '0' == 0) {
                auto lengthSubPackets =
                    binary_to_decimal(bin.substr(start + 7, lengthType));
                while (newBeginning - start - lengthType - 1 < lengthSubPackets)
                    newBeginning =
                        analyze_bits(tempNumbers, versions, bin, newBeginning);
            } else {
                auto numberSubPackets =
                    binary_to_decimal(bin.substr(start + 7, lengthType));
                for (size_t i = 0; i < numberSubPackets - 1; ++i)
                    newBeginning =
                        analyze_bits(tempNumbers, versions, bin, newBeginning);
            }
            uint64_t total = 0;
            switch (typeID) {
                case 0:
                    for (auto number : tempNumbers) total += number;
                    break;
                case 1:
                    total = 1;
                    for (auto number : tempNumbers) total *= number;
                    break;
                case 2:
                    total = tempNumbers[0];
                    for (auto number : tempNumbers)
                        if (number < total) total = number;
                    break;
                case 3:
                    for (auto number : tempNumbers)
                        if (number > total) total = number;
                    break;
                case 5:
                    if (tempNumbers[0] > tempNumbers[1]) total = 1;
                    break;
                case 6:
                    if (tempNumbers[0] < tempNumbers[1]) total = 1;
                    break;
                case 7:
                    if (tempNumbers[0] == tempNumbers[1]) total = 1;
                    break;
            }
            numbers.push_back(total);

            return newBeginning;
    }
}

int main() {
    std::string input = read_inputs();
    auto bin = hex_to_bin(input);
    // while (bin[bin.length() - 1] == '0') bin = bin.substr(0, bin.length() -
    // 1);
    std::vector<uint64_t> numbers;
    int versions = 0;
    analyze_bits(numbers, versions, bin);
    std::cout << "Part 1: " << versions << "\nPart 2: " << numbers[0]
              << std::endl;
}