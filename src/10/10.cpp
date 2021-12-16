#include <iostream>
#include <regex>

#include "../common/common.h"

int main() {
    const auto lines = split(read_inputs(), "\n");
    std::stack<char> brackets;
    int points1 = 0;
    std::vector<long> points2{};
    for (auto line : lines) {
        bool corrupted = false;
        for (auto character : line) {
            std::regex r("[{\\(\\[<]");
            std::string characterString(1, character);
            if (std::regex_match(characterString, r))
                brackets.push(character);
            else if (character == '}') {
                if (brackets.top() == '{')
                    brackets.pop();
                else {
                    corrupted = true;
                    points1 += 1197;
                    break;
                }
            } else if (character == ')') {
                if (brackets.top() == '(')
                    brackets.pop();
                else {
                    corrupted = true;
                    points1 += 3;
                    break;
                }
            } else if (character == ']') {
                if (brackets.top() == '[')
                    brackets.pop();
                else {
                    corrupted = true;
                    points1 += 57;
                    break;
                }
            } else if (character == '>') {
                if (brackets.top() == '<')
                    brackets.pop();
                else {
                    corrupted = true;
                    points1 += 25137;
                    break;
                }
            }
        }
        if (corrupted) {
            brackets = {};
            continue;
        }
        long score = 0;
        while (!brackets.empty()) {
            score *= 5;
            if (brackets.top() == '(') score += 1;
            if (brackets.top() == '[') score += 2;
            if (brackets.top() == '{') score += 3;
            if (brackets.top() == '<') score += 4;
            brackets.pop();
            if (score < 0) {
                score = __LONG_MAX__;
                brackets = {};
                break;
            }
        }
        points2.push_back(score);
    }
    std::sort(points2.begin(), points2.end());
    std::vector<long>::iterator it = points2.begin();
    std::advance(it, points2.size() / 2);
    std::cout << "Part 1: " << points1 << "\nPart 2: " << *it << std::endl;
}