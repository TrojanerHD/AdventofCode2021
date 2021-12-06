#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../common/common.h"

int main(){
	const std::vector<std::string> stringInputs = split(read_inputs(), ",");
	std::vector<int> inputs;
	// Stolen from https://stackoverflow.com/a/15619863/9634099
	std::transform(stringInputs.begin(), stringInputs.end(), std::back_inserter(inputs), [](const std::string& str) { return stoi(str);});

	for (int i = 0; i < 80; ++i) {
		for (int j = 0; j < inputs.size(); ++j) {
			if (inputs[j] == 0) {
				inputs.push_back(9);
				inputs[j] = 7;
			}
			inputs[j]--;
		}
	}

	std::cout << "Part 1: " << inputs.size() << std::endl;
}