#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../common/common.h"

class Rule {
   public:
    std::string input;
    std::string output;
    Rule(std::string input, std::string output) {
        this->input = input;
        this->output = output;
    }
};

std::vector<long long> count_commons(std::string input) {
    long long mostCommon = 0;
    long long leastCommon = std::count(input.begin(), input.end(), input[0]);

    std::set<char> characterSet(input.begin(), input.end());
    for (char character : characterSet) {
        size_t occurences = std::count(input.begin(), input.end(), character);
        if (occurences > mostCommon) mostCommon = occurences;
        if (occurences < leastCommon) leastCommon = occurences;
    }
    return {leastCommon, mostCommon};
}

int main() {
    auto input = split(read_inputs(), "\n");
    auto polymerTemplate = input[0];
    std::vector<Rule> rules;
    for (int i = 2; i < input.size(); ++i) {
        auto ruleset = split(input[i], " -> ");
        rules.push_back(
            *new Rule(ruleset[0], ruleset[0][0] + ruleset[1] + ruleset[0][1]));
    }

    std::vector<long long> part1;
    for (int i = 0; i < 40; ++i) {
        auto tempTemplate = polymerTemplate;
        int inserted = 0;
        for (int j = 0; j < polymerTemplate.length() - 1; ++j) {
            for (auto rule : rules) {
                if (rule.input ==
                    polymerTemplate.substr(j, rule.input.length())) {
                    tempTemplate =
                        tempTemplate.substr(0, j + inserted) + rule.output +
                        tempTemplate.substr(rule.input.length() + j + inserted,
                                            tempTemplate.length());
                    inserted += rule.output.length() - rule.input.length();
                    break;
                }
            }
        }
        rules.insert(rules.begin(), *new Rule(polymerTemplate, tempTemplate));
        polymerTemplate = tempTemplate;
        if (i == 9) part1 = count_commons(polymerTemplate);
    }
    auto part2 = count_commons(polymerTemplate);
    std::cout << "Part 1: " << part1[1] - part1[0] << part2[1] - part2[0]
              << std::endl;
}