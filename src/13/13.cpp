#include <iostream>

#include "../common/common.h"

class Instruction {
   public:
    int value;
    bool horizontal;
    Instruction(int value, bool horizontal) {
        this->value = value;
        this->horizontal = horizontal;
    }
};

class Coordinate {
   public:
    int x;
    int y;
    Coordinate(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int main() {
    auto inputs = split(read_inputs(), "\n");
    bool foldInstructions = false;
    std::vector<Instruction> instructions;
    std::vector<Coordinate> coordinates;
    for (auto input : inputs) {
        if (input == "") {
            foldInstructions = true;
            continue;
        }
        if (!foldInstructions) {
            auto coordinate = split(input, ",");
            coordinates.push_back(
                *new Coordinate(stoi(coordinate[0]), stoi(coordinate[1])));
            continue;
        }
        auto important = split(input, " ")[2];
        auto instruction = split(important, "=");
        instructions.push_back(
            *new Instruction(stoi(instruction[1]), instruction[0] == "x"));
    }

    int part1;
    std::string part2;
    int maxX = 0;
    int maxY = 0;
    for (int i = 0; i < instructions.size(); ++i) {
        auto instruction = instructions[i];
        for (int j = 0; j < coordinates.size(); ++j) {
            if (instruction.horizontal) {
                if (coordinates[j].x > instruction.value)
                    coordinates[j].x = instruction.value * 2 - coordinates[j].x;
                continue;
            }
            if (coordinates[j].y > instruction.value)
                coordinates[j].y = instruction.value * 2 - coordinates[j].y;

            // Determining the size of the output field
            if (i == instructions.size() - 1) {
                if (coordinates[j].x > maxX) maxX = coordinates[j].x + 1;
                if (coordinates[j].y > maxY) maxY = coordinates[j].y + 1;
            }
        }

        // Deleting all duplicates
        for (std::vector<Coordinate>::iterator j = coordinates.begin();
             j < coordinates.end() - 1; ++j) {
            for (std::vector<Coordinate>::iterator k = j + 1;
                 k < coordinates.end(); ++k) {
                if (j->x == k->x && j->y == k->y) {
                    coordinates.erase(k);
                    --k;
                    --j;
                }
            }
        }
        // Part 1 (number of points after one iteration)
        if (i == 0) part1 = coordinates.size();
    }

    // Visual output (part 2)
    for (int y = 0; y < maxY; ++y) {
        for (int x = 0; x < maxX; ++x) {
            bool found = false;
            for (auto coordinate : coordinates)
                if (coordinate.x == x && coordinate.y == y) {
                    part2 += "#";
                    found = true;
                    continue;
                }
            if (!found) part2 += ".";
        }
        part2 += "\n";
    }
    std::cout << "Part 1: " << part1 << "\nPart 2:\n" << part2 << std::endl;
}