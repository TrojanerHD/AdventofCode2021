#include <iostream>

#include "../common/common.h"

class Octopus {
   public:
    int value;
    bool marked = false;
    Octopus(int value) { this->value = value; }
};

void check_adjacent(std::vector<std::vector<Octopus>>& rows, int x, int y) {
    rows[y][x].marked = true;
    if (x - 1 >= 0 && !rows[y][x - 1].marked)
        if (++rows[y][x - 1].value > 9) check_adjacent(rows, x - 1, y);

    if (x + 1 < rows[y].size() && !rows[y][x + 1].marked)
        if (++rows[y][x + 1].value > 9) check_adjacent(rows, x + 1, y);

    if (y - 1 >= 0 && !rows[y - 1][x].marked)
        if (++rows[y - 1][x].value > 9) check_adjacent(rows, x, y - 1);

    if (y + 1 < rows.size() && !rows[y + 1][x].marked)
        if (++rows[y + 1][x].value > 9) check_adjacent(rows, x, y + 1);

    if (x - 1 >= 0 && y - 1 >= 0 && !rows[y - 1][x - 1].marked)
        if (++rows[y - 1][x - 1].value > 9) check_adjacent(rows, x - 1, y - 1);

    if (x + 1 < rows[y].size() && y - 1 >= 0 && !rows[y - 1][x + 1].marked)
        if (++rows[y - 1][x + 1].value > 9) check_adjacent(rows, x + 1, y - 1);

    if (x - 1 >= 0 && y + 1 < rows.size() && !rows[y + 1][x - 1].marked)
        if (++rows[y + 1][x - 1].value > 9) check_adjacent(rows, x - 1, y + 1);

    if (x + 1 < rows[y].size() && y + 1 < rows.size() &&
        !rows[y + 1][x + 1].marked)
        if (++rows[y + 1][x + 1].value > 9) check_adjacent(rows, x + 1, y + 1);
}

int main() {
    std::vector<std::string> inputsVector = split(read_inputs(), "\n");
    std::vector<std::vector<Octopus>> rows;
    int flashes = 0;
    int part1 = 0;
    int part2 = 0;

    for (auto string : inputsVector) {
        std::vector<char> v(string.begin(), string.end());
        std::vector<Octopus> row;
        for (auto number : v) row.push_back(*new Octopus(number - '0'));
        rows.push_back(row);
    }
    for (int i = 0;; ++i) {
        for (int y = 0; y < rows.size(); ++y)
            for (int x = 0; x < rows[y].size(); ++x)
                if (++rows[y][x].value > 9 && !rows[y][x].marked)
                    check_adjacent(rows, x, y);
        for (int y = 0; y < rows.size(); ++y)
            for (int x = 0; x < rows[y].size(); ++x)
                if (rows[y][x].marked) {
                    rows[y][x].value = 0;
                    rows[y][x].marked = false;
                    ++flashes;
                }
        if (i == 99) part1 = flashes;
        if (part2 != 0 && i >= 99) break;
        if (part2 != 0) continue;
        bool simultaneously = true;
        for (auto row : rows) {
            for (auto octopus : row) {
                if (octopus.value != 0) {
                    simultaneously = false;
                    break;
                }
            }
            if (!simultaneously) break;
        }
        if (simultaneously) part2 = i + 1;
    }
    std::cout << "Part 1: " << part1 << "\nPart 2: " << part2 << std::endl;
}