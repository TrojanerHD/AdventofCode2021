#include <iostream>

#include "../common/common.h"

int main() {
    const std::vector<std::string> stringInputs = split(read_inputs(), ",");
    std::vector<int> startValues = string_vector_to_int_vector(stringInputs);

    std::vector<long> inputs{0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i : startValues) inputs[i]++;

    int part1 = 0;
    for (int i = 0; i < 256; ++i) {
        long tempOld = 0;
        long tempNow;
        for (int j = inputs.size() - 1; j >= 0; --j) {
            if (j == 0) {
                inputs[6] += inputs[j];
                inputs[8] += inputs[j];
            }
            tempNow = inputs[j];
            inputs[j] = tempOld;
            tempOld = tempNow;
        }

        if (i == 79)
            for (long x : inputs) part1 += x;
    }

    long part2 = 0;
    for (long x : inputs) part2 += x;

    std::cout << "Part 1: " << part1 << "\nPart 2: " << part2 << std::endl;
}