#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

class Point {
   public:
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

std::vector<Point> low_point(int& part1, std::vector<Point> part2, char value,
                             std::vector<std::vector<char>> inputs, int x,
                             int y, bool recursion = false) {
    auto row = inputs[y];
    if (!recursion) {
        if (y > 0 && inputs[y - 1][x] <= value) return part2;
        if (y < inputs.size() - 1 && inputs[y + 1][x] <= value) return part2;
        if (x > 0 && row[x - 1] <= value) return part2;
        if (x < row.size() - 1 && row[x + 1] <= value) return part2;
        part1 += value - '0' + 1;
    }
    if (inputs[y][x] - '0' == 9) return part2;
    if (y > 0 && inputs[y - 1][x] > value)
        part2 = low_point(part1, part2, value + 1, inputs, x, y - 1, true);
    if (y < inputs.size() - 1 && inputs[y + 1][x] > value)
        part2 = low_point(part1, part2, value + 1, inputs, x, y + 1, true);
    if (x > 0 && row[x - 1] > value)
        part2 = low_point(part1, part2, value + 1, inputs, x - 1, y, true);
    if (x < row.size() - 1 && row[x + 1] > value)
        part2 = low_point(part1, part2, value + 1, inputs, x + 1, y, true);
    if (x < 0 || x > row.size() - 1 || y < 0 || y > inputs.size() - 1)
        return part2;
    for (Point point : part2)
        if (point.x == x && point.y == y) return part2;
    part2.push_back(*new Point(x, y));
    return part2;
}

int main() {
    auto rows = split(read_inputs(), "\n");

    std::vector<std::vector<char>> inputs{};
    for (auto row : rows) {
        std::vector<char> v(row.begin(), row.end());
        inputs.push_back(v);
    }

    int part1 = 0;
    std::vector<int> basins = {};
    for (int y = 0; y < inputs.size(); ++y)
        for (int x = 0; x < inputs[y].size(); ++x) {
            int part2 = 0;
            std::vector<Point> lowPoint =
                low_point(part1, {}, inputs[y][x], inputs, x, y);
            part2 = lowPoint.size();
            if (part2 != 0)
                basins.push_back(part2);
        }
    int highest = 0;
    int secondHighest = 0;
    int thirdHighest = 0;

    for (auto basin : basins) {
        if (basin >= highest) {
            thirdHighest = secondHighest;
            secondHighest = highest;
            highest = basin;
            continue;
        }
        if (basin >= secondHighest) {
            thirdHighest = secondHighest;
            secondHighest = basin;
            continue;
        }
        if (basin >= thirdHighest) {
            thirdHighest = basin;
        }
    }
    std::cout << "Part 1: " << part1
              << "\nPart 2: " << highest * secondHighest * thirdHighest
              << std::endl;
}