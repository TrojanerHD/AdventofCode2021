#include <cmath>
#include <iostream>

#include "../common/common.h"

int main() {
    auto input = read_inputs();
    auto finalX = split(split(split(input, "=")[1], " ")[0], "\\.\\.");
    auto lowFinalX = stoi(finalX[0]);
    auto highFinalX = stoi(finalX[1]);
    auto finalY = split(split(input, "=")[2], "\\.\\.");
    auto lowFinalY = stoi(finalY[0]);
    auto highFinalY = stoi(finalY[1]);

    std::vector<int> probePosition{0, 0};
    int minX = 0;
    for (int xSum = 1; xSum + minX < lowFinalX; ++minX) xSum += minX;
    int maxX = 0;
    for (int xSum = 1; xSum + maxX < highFinalX; ++maxX) xSum += maxX;

    --maxX;

    int minY = 0;
    int maxY = abs(lowFinalY);

    auto highY = 0;
    auto part2 = 0;

    for (int y = lowFinalY; y < maxY; ++y) {
        for (int x = minX; x <= highFinalX; ++x) {
            auto tempY = y;
            auto tempX = x;
						int highYTemp = 0;
            std::vector<int> oldPosition{0, 0};
            while (probePosition[0] <= highFinalX &&
                   probePosition[1] >= lowFinalY) {
                oldPosition = probePosition;
                probePosition[0] += tempX;
                probePosition[1] += tempY;
                if (highYTemp < probePosition[1]) highYTemp = probePosition[1];
                if (tempX > 0)
                    --tempX;
                else if (tempX < 0)
                    ++tempX;
                --tempY;
            }
            if (oldPosition[0] >= lowFinalX && oldPosition[1] <= highFinalY) {
                ++part2;
								highY = highYTemp;
						}
            probePosition = {0, 0};
        }
    }
    std::cout << "Part 1 " << highY << "\nPart 2: " << part2 << std::endl;
}