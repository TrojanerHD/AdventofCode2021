#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"
int main() {
    std::vector<int> inputs =
        string_vector_to_int_vector(split(read_inputs(), ","));
    auto max = std::max_element(std::begin(inputs), std::end(inputs));
    auto min = std::min_element(std::begin(inputs), std::end(inputs));

    int part1 = -1;
    int part2 = -1;
    for (int i = *min; i <= *max; ++i) {
        int difference1 = 0;
        int difference2 = 0;
        for (int x : inputs) difference1 += abs(x - i);
        for (int x : inputs)
            for (int j = 1; j <= abs(x - i); ++j) difference2 += j;

        if (difference1 < part1 || part1 == -1) part1 = difference1;
        if (difference2 < part2 || part2 == -1) part2 = difference2;
    }

    std::cout << "Part 1: " << part1 << "\nPart 2: " << part2 << std::endl;
}