#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

#include "../common/common.h"

int main() {
    auto lines = split(read_inputs(), "\n");
    std::stack<char> brackets;
    int points1 = 0;
		int points2 = 0;
    for (auto line : lines) {
        for (auto character : line) {
            std::regex r("[{\\(\\[<]");
            std::string characterString(1, character);
            if (std::regex_match(characterString, r))
                brackets.push(character);
            else if (character == '}') {
                if (brackets.top() == '{') {
                    brackets.pop();
										continue;
                } else {
                    points1 += 1197;
										break;
								}
            } else if (character == ')') {
                if (brackets.top() == '(') {
                    brackets.pop();
										continue;
                } else {
                    points1 += 3;
										break;
								}
            } else if (character == ']') {
                if (brackets.top() == '[') {
                    brackets.pop();
										continue;
                } else {
                    points1 += 57;
										break;
								}
            } else if (character == '>') {
                if (brackets.top() == '<') {
                    brackets.pop();
										continue;
                } else {
                    points1 += 25137;
										break;
								}
            }
        }
    }
    std::cout << "Part 1: " << points1 << std::endl;
}