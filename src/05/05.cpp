#include <iostream>

#include "../common/common.h"

enum Direction { Horizontal, Vertical, Diagonal };

class Line {
   public:
    std::vector<int> x{};
    std::vector<int> y{};
    Direction direction;
    static Line all_coordinates(int x1, int x2, int y1, int y2,
                                Direction direction) {
        auto line = new Line(direction);
        if (x1 < x2)
            for (int i = x1; i <= x2; ++i) line->x.push_back(i);
        else if (x1 > x2)
            for (int i = x1; i >= x2; --i) line->x.push_back(i);
        else
            line->x.push_back(x1);

        if (y1 < y2)
            for (int i = y1; i <= y2; ++i) line->y.push_back(i);
        else if (y1 > y2)
            for (int i = y1; i >= y2; --i) line->y.push_back(i);
        else
            line->y.push_back(y1);
        return *line;
    }
    Line(Direction direction) { this->direction = direction; }
};

class Intersection {
   public:
    int x;
    int y;
    Intersection(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int main() {
    std::vector<std::string> values = split(read_inputs(), "\n");
    std::vector<Line> lines{};
    for (std::string value : values) {
        std::vector<std::string> io = split(value, " -> ");
        std::string start = io[0];
        std::string end = io[1];

        int xStart = stoi(split(start, ",")[0]);
        int yStart = stoi(split(start, ",")[1]);

        int xEnd = stoi(split(end, ",")[0]);
        int yEnd = stoi(split(end, ",")[1]);

        if (xStart == xEnd)
            lines.push_back(
                Line::all_coordinates(xStart, xEnd, yStart, yEnd, Vertical));
        else if (yStart == yEnd)
            lines.push_back(
                Line::all_coordinates(xStart, xEnd, yStart, yEnd, Horizontal));
        else
            lines.push_back(
                Line::all_coordinates(xStart, xEnd, yStart, yEnd, Diagonal));
    }
    std::vector<Intersection> straightIntersections{};
    std::vector<Intersection> allIntersections{};
    for (std::vector<Line>::iterator lineIterator = lines.begin();
         lineIterator != lines.end() - 1; ++lineIterator) {
        for (std::vector<Line>::iterator lineIterator2 = lineIterator + 1;
             lineIterator2 != lines.end(); ++lineIterator2) {
            int firstLimit = lineIterator->x.size();
            if (lineIterator->direction == Vertical)
                firstLimit = lineIterator->y.size();
            int secondLimit = lineIterator2->x.size();
            if (lineIterator2->direction == Vertical)
                secondLimit = lineIterator2->y.size();
            for (int i = 0; i < firstLimit; ++i)
                for (int j = 0; j < secondLimit; ++j) {
                    int x1 = i;
                    int x2 = j;
                    int y1 = i;
                    int y2 = j;
                    if (lineIterator->direction == Horizontal)
                        y1 = 0;
                    else if (lineIterator->direction == Vertical)
                        x1 = 0;
                    if (lineIterator2->direction == Horizontal)
                        y2 = 0;
                    else if (lineIterator2->direction == Vertical)
                        x2 = 0;

                    if (lineIterator->x[x1] == lineIterator2->x[x2] &&
                        lineIterator->y[y1] == lineIterator2->y[y2]) {
                        Intersection* tempIntersection = new Intersection(
                            lineIterator->x[x1], lineIterator->y[y1]);
                        bool skip = false;
                        for (Intersection intersection : straightIntersections)
                            if (intersection.x == tempIntersection->x &&
                                intersection.y == tempIntersection->y)
                                skip = true;

                        if (skip) continue;
                        if (lineIterator->direction != Diagonal &&
                            lineIterator2->direction != Diagonal)
                            straightIntersections.push_back(*tempIntersection);
                        for (Intersection intersection : allIntersections)
                            if (intersection.x == tempIntersection->x &&
                                intersection.y == tempIntersection->y)
                                skip = true;

                        if (skip) continue;
                        allIntersections.push_back(*tempIntersection);
                    }
                }
        }
    }

    std::cout << "Part 1: " << straightIntersections.size()
              << "\nPart 2: " << allIntersections.size() << std::endl;
}