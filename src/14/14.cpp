#include <math.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/common.h"

void increase(std::unordered_map<std::string, long long>& map,
              std::string input, int increment = 1) {
    std::unordered_map<std::string, long long>::iterator it = map.find(input);
    (*it).second += increment;
}

void insertOrIncrease(std::unordered_map<char, long long>& map, char input,
                      long long increment = 1) {
    std::unordered_map<char, long long>::iterator it = map.find(input);
    if (it == map.end())
        map.insert({input, increment});
    else
        (*it).second += increment;
}

std::vector<long long> count_commons(
    std::unordered_map<std::string, long long> input, std::string original) {
    std::pair<char, long long> mostCommon{'A', 0};
    std::pair<char, long long> leastCommon{'A', __LONG_LONG_MAX__};
    std::unordered_map<char, long long> map;
    for (auto kv : input) {
        insertOrIncrease(map, kv.first[0], kv.second);
    }
    insertOrIncrease(map, original[original.length() - 1], 1);

    for (auto kv : map) {
        if (kv.second > mostCommon.second) mostCommon = kv;
        if (kv.second < leastCommon.second) leastCommon = kv;
    }

    return {leastCommon.second, mostCommon.second};
}

int main() {
    auto input = split(read_inputs(), "\n");
    auto polymerTemplate = input[0];
    std::unordered_map<std::string, std::string> rules;
    for (int i = 2; i < input.size(); ++i) {
        auto ruleset = split(input[i], " -> ");
        rules.insert({ruleset[0], ruleset[1]});
    }

    std::unordered_map<std::string, long long> result;
    std::unordered_map<std::string, long long> resultPart1;

    for (auto rule : rules) result.insert({rule.first, 0});

    for (int i = 0; i < polymerTemplate.length() - 1; ++i) {
        std::string resolve =
            std::string() + polymerTemplate[i] + polymerTemplate[i + 1];
        increase(result, resolve);
    }

    for (int j = 0; j < 40; ++j) {
        auto tempResult = result;
        for (std::unordered_map<std::string, long long>::iterator it =
                 result.begin();
             it != result.end(); ++it) {
            if ((*it).second == 0) continue;
            for (auto rule : rules) {
                auto resolve = std::string() + (*it).first[0] + (*it).first[1];
                if (rule.first == resolve) {
                    auto first = (*it).first[0] + rule.second;
                    auto second = rule.second + (*it).first[1];
                    increase(tempResult, first, (*it).second);
                    increase(tempResult, second, (*it).second);
                    (*tempResult.find((*it).first)).second -= (*it).second;
                    break;
                }
            }
        }
        result = tempResult;
        if (j == 9)
         resultPart1 = result;
    }

    auto part1 = count_commons(resultPart1, polymerTemplate);
    auto part2 = count_commons(result, polymerTemplate);
    std::cout << "Part 1: " << part1[1] - part1[0]
              << "\nPart 2: " << part2[1] - part2[0] << std::endl;
}