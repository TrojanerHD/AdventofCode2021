#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

int main() {
    std::vector<std::string> inputs = split(read_inputs(), "\n");
    int easyDigits = 0;
    for (std::string input : inputs) {
        std::vector<std::string> io = split(input, " \\| ");
        std::vector<std::string> outputs = split(io[1], " ");
        for (std::string output : outputs)
            if (output.length() == 2 || output.length() == 3 ||
                output.length() == 4 || output.length() == 7)
                easyDigits++;
    }

    std::cout << "Part 1: " << easyDigits << std::endl;
}