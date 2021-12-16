#include <algorithm>
#include <iostream>

#include "../common/common.h"

class Connection {
   public:
    std::string input;
    std::string output;
    Connection(std::string input, std::string output) {
        this->input = input;
        this->output = output;
    }
};
void check_to_end2(std::vector<Connection> caves, std::string search, int& ends,
                   std::vector<std::string> visited, bool twice) {
    for (auto cave : caves) {
        if (cave.input == search && cave.output != "start") {
            bool tempTwice = twice;
            bool skip = false;
            if (std::find(visited.begin(), visited.end(), cave.output) !=
                visited.end())
                if (!tempTwice)
                    tempTwice = true;
                else
                    skip = true;
            if (!skip) {
                auto tempVisited = visited;
                if (islower(cave.output[0])) tempVisited.push_back(cave.output);
                if (cave.output == "end") {
                    ++ends;
                    continue;
                }
                check_to_end2(caves, cave.output, ends, tempVisited, tempTwice);
            }
        }
        if (cave.output == search && cave.input != "start") {
            bool tempTwice = twice;
            bool skip = false;
            if (std::find(visited.begin(), visited.end(), cave.input) !=
                visited.end())
                if (!tempTwice)
                    tempTwice = true;
                else
                    skip = true;
            if (!skip) {
                auto tempVisited = visited;
                if (islower(cave.input[0])) tempVisited.push_back(cave.input);
                if (cave.input == "end") {
                    ++ends;
                    continue;
                }
                check_to_end2(caves, cave.input, ends, tempVisited, tempTwice);
            }
        }
    }
}

void check_to_end(std::vector<Connection> caves, std::string search, int& ends,
                  std::vector<std::string> visited) {
    for (auto cave : caves) {
        if (cave.input == search &&
            std::find(visited.begin(), visited.end(), cave.output) ==
                visited.end() &&
            cave.output != "start") {
            auto tempVisited = visited;
            if (islower(cave.output[0])) tempVisited.push_back(cave.output);
            if (cave.output == "end") {
                ++ends;
                continue;
            }
            check_to_end(caves, cave.output, ends, tempVisited);
        }
        if (cave.output == search &&
            std::find(visited.begin(), visited.end(), cave.input) ==
                visited.end() &&
            cave.input != "start") {
            auto tempVisited = visited;
            if (islower(cave.input[0])) tempVisited.push_back(cave.input);
            if (cave.input == "end") {
                ++ends;
                continue;
            }
            check_to_end(caves, cave.input, ends, tempVisited);
        }
    }
}

int main() {
    std::vector<std::string> inputs = split(read_inputs(), "\n");
    std::vector<Connection> caves{};
    for (auto input : inputs) {
        std::vector<std::string> io = split(input, "-");
        caves.push_back(*new Connection(io[0], io[1]));
    }
    int ends = 0;
    int ends2 = 0;
    check_to_end(caves, "start", ends, {});
    check_to_end2(caves, "start", ends2, {}, false);
    std::cout << "Part 1: " << ends << "\nPart 2: " << ends2 << std::endl;
}