#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// Stolen from https://stackoverflow.com/a/40699396/9634099
std::vector<std::string> split(std::string target, std::string delim) {
    std::vector<std::string> v;
    if (!target.empty()) {
        size_t start = 0;
        do {
            size_t x = target.find(delim, start);
            if (x == std::string::npos) break;

            v.push_back(target.substr(start, x - start));
            start = x + 1;
        } while (true);

        v.push_back(target.substr(start));
    }
    return v;
}

std::string read_inputs() {
    std::ifstream file("values.txt");
    if (file.is_open()) {
        std::string line;
        std::string values;
        auto firstIteration = true;
        while (getline(file, line)) {
            if (!firstIteration)
                values += "\n";
            else
                firstIteration = false;
            values += line;
        }
        return values;
    }
    return nullptr;
}

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