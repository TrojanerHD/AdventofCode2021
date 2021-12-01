#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// Stolen from https://stackoverflow.com/a/40699396/9634099
std::vector<std::string> split(std::string target, std::string delim) {
    std::vector<std::string> v;
    if (!target.empty()) {
        size_t start = 0;
        do {
            size_t x = target.find(delim, start);
            if (x == std::string::npos) break;

            v.push_back(target.substr(start, x - start));
            start = x + 1;
        } while (true);

        v.push_back(target.substr(start));
    }
    return v;
}

std::string read_inputs() {
    std::ifstream file("values.txt");
    if (file.is_open()) {
        std::string line;
        std::string values;
        auto firstIteration = true;
        while (getline(file, line)) {
            if (!firstIteration)
                values += "\n";
            else
                firstIteration = false;
            values += line;
        }
        return values;
    }
    return nullptr;
}

int main() {
    std::string values = read_inputs();
    std::vector<std::string> v = split(values, "\n");
    int previous = stoi(v[0]);
    int total = 0;
    for (auto i = 1; i < v.size(); i++) {
        if (stoi(v[i]) > previous) total++;
        previous = stoi(v[i]);
    }

    std::cout << "Part 1: " << total << std::endl;

    previous = 0;
    auto total2 = 0;
    for (auto i = 0; i < v.size() - 2; i++) {
        auto calculated = 0;
        calculated += stoi(v[i]);
        calculated += stoi(v[i + 1]);
        calculated += stoi(v[i + 2]);
        if (i == 0) {
            previous = calculated;
            continue;
        }
        if (calculated > previous) total2++;
        previous = calculated;
    }

    std::cout << "Part 2: " << total2 << std::endl;
}