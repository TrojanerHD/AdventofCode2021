#include <string>
#include <vector>

std::string read_inputs();
std::vector<std::string> split(std::string target, std::string delim);
std::vector<int> string_vector_to_int_vector(std::vector<std::string> input);
uint64_t binary_to_decimal(std::string binary);