#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

int main() {
    std::string values = read_inputs();
    std::vector<std::string> v = split(values, "\n");
    int previous = stoi(v[0]);
    int total = 0;
    for (auto i = 1; i < v.size(); i++) {
        if (stoi(v[i]) > previous) total++;
        previous = stoi(v[i]);
    }

    std::cout << "Part 1: " << total << std::endl;

    previous = 0;
    auto total2 = 0;
    for (auto i = 0; i < v.size() - 2; i++) {
        auto calculated = 0;
        calculated += stoi(v[i]);
        calculated += stoi(v[i + 1]);
        calculated += stoi(v[i + 2]);
        if (i == 0) {
            previous = calculated;
            continue;
        }
        if (calculated > previous) total2++;
        previous = calculated;
    }

    std::cout << "Part 2: " << total2 << std::endl;
}