#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../common/common.h"

typedef std::vector<std::vector<int>> bingoBoard;

// Stolen from https://stackoverflow.com/a/20659156/9634099
std::vector<int> string_to_int_vector(std::string input) {
    std::stringstream iss(input);

    int number;
    std::vector<int> result;
    while (iss >> number) result.push_back(number);
    return result;
}

void add_board(std::vector<int>& bingoBoards, std::vector<bingoBoard>& bingos,
              bingoBoard foundBoard,
              std::vector<bingoBoard>::iterator& bingoBoardIterator,
              std::vector<int> enteredNumbers) {
    int sum = 0;
    for (std::vector<int> row : foundBoard)
        for (int number : row)
            if (std::find(enteredNumbers.begin(), enteredNumbers.end(),
                          number) == enteredNumbers.end())
                sum += number;
    bingoBoards.push_back(sum * *enteredNumbers.rbegin());
    bingos.erase(bingoBoardIterator);
    --bingoBoardIterator;
}

std::vector<int> find_board(std::vector<bingoBoard> bingos,
                           std::vector<std::string> inputs,
                           std::vector<int>& enteredNumbers) {
    std::vector<int> bingoBoards = {};
    for (std::string input : inputs) {
        enteredNumbers.push_back(stoi(input));
        for (std::vector<bingoBoard>::iterator bingoBoardIterator =
                 bingos.begin();
             bingoBoardIterator != bingos.end(); ++bingoBoardIterator) {
            bingoBoard bingoBoard = *bingoBoardIterator;
            bool bingo = true;
            for (std::vector<int> row : bingoBoard) {
                bingo = true;
                for (int number : row)
                    if (std::find(enteredNumbers.begin(), enteredNumbers.end(),
                                  number) == enteredNumbers.end()) {
                        bingo = false;
                        break;
                    }
                if (bingo) {
                    add_board(bingoBoards, bingos, bingoBoard,
                             bingoBoardIterator, enteredNumbers);
                    break;
                }
            }
            if (bingo) continue;

            for (size_t i = 0; i < bingoBoard[0].size(); ++i) {
                bingo = true;
                for (std::vector<int> row : bingoBoard) {
                    if (std::find(enteredNumbers.begin(), enteredNumbers.end(),
                                  row[i]) == enteredNumbers.end()) {
                        bingo = false;
                        break;
                    }
                }
                if (bingo) {
                    add_board(bingoBoards, bingos, bingoBoard,
                             bingoBoardIterator, enteredNumbers);
                    break;
                }
            }
        }
    }
    return bingoBoards;
}

int main() {
    const std::vector<std::string> values = split(read_inputs(), "\n");
    std::vector<bingoBoard> bingos = {{}};
    const std::vector<std::string> inputs = split(values[0], ",");

    for (std::vector<std::string>::const_iterator iterator = values.begin() + 2;
         iterator != values.end(); ++iterator) {
        if (*iterator == "") {
            bingos.push_back({});
            continue;
        }
        bingos[bingos.size() - 1].push_back(string_to_int_vector(*iterator));
    }
    std::vector<int> enteredNumbers;
    std::vector<int> foundBoards = find_board(bingos, inputs, enteredNumbers);

    std::cout << "Part 1: " << foundBoards[0]
              << "\nPart 2: " << *foundBoards.rbegin() << std::endl;
}