#include <cmath>
#include <iostream>

#include "../common/common.h"

class Pair {
   public:
    int x;
    int y;
    Pair* subX;
    Pair* subY;
    Pair* parent = nullptr;
    int magnitude = 0;
    Pair(int x, int y) {
        this->subX = nullptr;
        this->subY = nullptr;
        this->x = x;
        this->y = y;
    }

    Pair(Pair* subX, Pair* subY) {
        this->x = -1;
        this->y = -1;
        this->subX = subX;
        this->subY = subY;
        this->subX->parent = this;
        this->subY->parent = this;
    }

    Pair(Pair* subX, int y) {
        this->x = -1;
        this->subY = nullptr;
        this->subX = subX;
        this->y = y;
        this->subX->parent = this;
    }

    Pair(int x, Pair* subY) {
        this->y = -1;
        this->subX = nullptr;
        this->x = x;
        this->subY = subY;
        this->subY->parent = this;
    }
};

Pair* create_pair(std::string input, int& i) {
    bool firstPair = true;
    Pair* pair1 = nullptr;
    Pair* pair2 = nullptr;
    std::string x = "";
    std::string y = "";
    for (; input[i] != ']'; ++i) {
        if (input[i] == '[') {
            ++i;
            if (firstPair)
                pair1 = create_pair(input, i);
            else
                pair2 = create_pair(input, i);
        }
        if (input[i] == ',') firstPair = false;
        if (isdigit(input[i]))
            if (firstPair)
                x += input[i];
            else
                y += input[i];
    }
    if (pair1 != nullptr) {
        if (pair2 != nullptr)
            return new Pair(pair1, pair2);
        else
            return new Pair(pair1, stoi(y));
    } else if (pair2 != nullptr)
        return new Pair(stoi(x), pair2);
    else
        return new Pair(stoi(x), stoi(y));
}

bool explode(Pair* pair, int depth = 0) {
    if (depth == 4) {
        // Add x to rightmost value left from it
        auto tempPair = pair;
        bool skip = false;
        while (tempPair->parent->subX == tempPair) {
            tempPair = tempPair->parent;
            if (tempPair->parent == nullptr) {
                skip = true;
                break;
            }
        }
        if (!skip) {
            tempPair = tempPair->parent;
            if (tempPair->subX == nullptr)
                tempPair->x += pair->x;
            else {
                auto tempTempPair = tempPair->subX;
                while (tempTempPair->subY != nullptr)
                    tempTempPair = tempTempPair->subY;
                tempTempPair->y += pair->x;
            }
        }

        tempPair = pair;
        skip = false;

        // Add y to leftmost value right from it
        while (tempPair->parent->subY == tempPair) {
            tempPair = tempPair->parent;
            if (tempPair->parent == nullptr) {
                skip = true;
                break;
            }
        }
        if (!skip) {
            tempPair = tempPair->parent;
            if (tempPair->subY == nullptr)
                tempPair->y += pair->y;
            else {
                auto tempTempPair = tempPair->subY;
                while (tempTempPair->subX != nullptr)
                    tempTempPair = tempTempPair->subX;
                tempTempPair->x += pair->y;
            }
        }

        if (pair->parent->subX == pair) {
            pair->parent->x = 0;
            pair->parent->subX = nullptr;
            return true;
        }
        pair->parent->y = 0;
        pair->parent->subY = nullptr;
        return true;
    }
    if (pair->subX != nullptr)
        if (explode(pair->subX, depth + 1)) return true;
    if (pair->subY != nullptr)
        if (explode(pair->subY, depth + 1)) return true;
    return false;
}

bool split_pair(Pair* pair) {
    if (pair->x >= 10) {
        pair->subX = new Pair(pair->x / 2, std::ceil((float)pair->x / 2));
        pair->subX->parent = pair;
        pair->x = -1;
        return true;
    }

    if (pair->subX != nullptr)
        if (split_pair(pair->subX)) return true;

    if (pair->y >= 10) {
        pair->subY = new Pair(pair->y / 2, std::ceil((float)pair->y / 2));
        pair->subY->parent = pair;
        pair->y = -1;
        return true;
    }

    if (pair->subY != nullptr)
        if (split_pair(pair->subY)) return true;
    return false;
}

int set_magnitude(Pair* pair) {
    if (pair->subX != nullptr)
        pair->magnitude = 3 * set_magnitude(pair->subX);
    else
        pair->magnitude = 3 * pair->x;
    if (pair->subY != nullptr)
        pair->magnitude += 2 * set_magnitude(pair->subY);
    else
        pair->magnitude += 2 * pair->y;
    return pair->magnitude;
}

void reduce(Pair* pair) {
    bool exploded = true;
    bool split = true;
    while (exploded || split) {
        if (explode(pair)) {
            exploded = true;
            continue;
        } else
            exploded = false;
        split = split_pair(pair);
    }
}
int main() {
    auto inputs = split(read_inputs(), "\n");
    Pair* lastPair = nullptr;
    auto largest = 0;

    for (int j = 0; j < inputs.size(); ++j) {
        int i = 1;
        auto pair = create_pair(inputs[j], i);
        for (int k = 0; k < inputs.size(); ++k) {
            if (k == j) continue;
            i = 1;
            auto secondPair = create_pair(inputs[k], i);
            i = 1;
            auto tempPair = create_pair(inputs[j], i);
            auto resultPair = new Pair(tempPair, secondPair);
            reduce(resultPair);
            set_magnitude(resultPair);
            if (resultPair->magnitude > largest)
                largest = resultPair->magnitude;
        }
        if (lastPair != nullptr) {
            pair = new Pair(lastPair, pair);
            reduce(pair);
        }
        lastPair = pair;
    }
    set_magnitude(lastPair);
    std::cout << "Part 1: " << lastPair->magnitude << "\nPart 2: " << largest
              << std::endl;
}