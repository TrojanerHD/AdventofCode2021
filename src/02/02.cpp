#include <iostream>

#include "../common/common.h"

int main() {
    auto inputs = read_inputs();
    auto values = split(inputs, "\n");
    // Part 1
    auto depth = 0;
    auto horizontal = 0;
    for (size_t i = 0; i < values.size(); i++) {
        auto input = values[i];
        auto instructions = split(input, " ");
        if (instructions[0] == "forward")
            horizontal += stoi(instructions[1]);
        else if (instructions[0] == "down")
            depth += stoi(instructions[1]);
        else if (instructions[0] == "up")
            depth -= stoi(instructions[1]);
    }
    std::cout << "Part 1: " << horizontal * depth << std::endl;

    // Part 2
    depth = 0;
    horizontal = 0;
    auto aim = 0;
    for (size_t i = 0; i < values.size(); i++) {
        auto input = values[i];
        auto instructions = split(input, " ");
        if (instructions[0] == "forward") {
            horizontal += stoi(instructions[1]);
            depth += aim * stoi(instructions[1]);
        } else if (instructions[0] == "down")
            aim += stoi(instructions[1]);
        else if (instructions[0] == "up")
            aim -= stoi(instructions[1]);
    }
    std::cout << "Part 2: " << horizontal * depth << std::endl;
}