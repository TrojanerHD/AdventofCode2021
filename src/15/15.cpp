#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"

class Node {
   public:
    int x;
    int y;
    int value;
    int distance = INT32_MAX;
    bool visited = false;
    Node(int x, int y, int value) {
        this->x = x;
        this->y = y;
        this->value = value;
    }
};

std::vector<Node>::iterator getNeighborNode(std::vector<Node>& path, Node node,
                                            std::vector<int> offset) {
    return std::find_if(path.begin(), path.end(),
                        [node, offset](Node tempNode) {
                            return tempNode.x == node.x + offset[0] &&
                                   tempNode.y == node.y + offset[1];
                        });
}

std::vector<Node> dijkstra(std::vector<Node> path) {
    std::vector<Node> result;
    while (!path.empty()) {
        std::vector<Node>::iterator finalNode = path.begin();
        for (std::vector<Node>::iterator it = path.begin(); it != path.end();
             ++it)
            if (it->distance < finalNode->distance) finalNode = it;

        finalNode->visited = true;
        std::vector<std::vector<Node>::iterator> editNodes;
        std::vector<Node>::iterator it =
            getNeighborNode(path, *finalNode, {-1, 0});
        if (it != path.end()) editNodes.push_back(it);
        it = getNeighborNode(path, *finalNode, {1, 0});
        if (it != path.end()) editNodes.push_back(it);
        it = getNeighborNode(path, *finalNode, {0, -1});
        if (it != path.end()) editNodes.push_back(it);
        it = getNeighborNode(path, *finalNode, {0, 1});
        if (it != path.end()) editNodes.push_back(it);
        for (auto node : editNodes) {
            int distance = finalNode->distance + node->value;
            if (distance < node->distance) node->distance = distance;
        }
        result.push_back(*finalNode);
        path.erase(finalNode);
    }
    return result;
}

int main() {
    auto input = split(read_inputs(), "\n");

    std::vector<Node> inputs;

    for (size_t y = 0; y < input.size(); ++y) {
        for (size_t x = 0; x < input[y].length(); ++x) {
            Node node = *new Node(x, y, input[y][x] - '0');
            inputs.push_back(node);
        }
    }
    (*std::find_if(inputs.begin(), inputs.end(), [](Node node) {
        return node.x == 0 && node.y == 0;
    })).distance = 0;
    auto part1 = dijkstra(inputs);
    for (size_t y = 0; y < 5; ++y)
        for (size_t x = 0; x <= y; ++x) {
            if (x == 0 && y == 0) continue;
            for (auto node : part1) {
                auto newValue = (node.value + x + y) % 9;
                if (newValue == 0) newValue = 9;
                inputs.push_back(*new Node(node.x + input[0].length() * x,
                                           node.y + input[0].length() * y,
                                           newValue));
                inputs.push_back(*new Node(node.x + input[0].length() * x,
                                           node.y + input[0].length() * y,
                                           newValue));
            }
        }
    auto part2 = dijkstra(inputs);
    auto temp = std::find_if(part2.begin(), part2.end(), [input](Node node) {
        return node.x == input[0].length() * 5 - 1 &&
               node.y == input.size() * 5 - 1;
    });
    std::cout << "Part 1: "
              << (*std::find_if(part1.begin(), part1.end(),
                                [input](Node node) {
                                    return node.x == input[0].length() - 1 &&
                                           node.y == input.size() - 1;
                                }))
                     .distance
              << "\nPart 2: "
              << (*std::find_if(part2.begin(), part2.end(),
                                [input](Node node) {
                                    return node.x ==
                                               input[0].length() * 5 - 1 &&
                                           node.y == input.size() * 5 - 1;
                                }))
                     .distance
              << std::endl;
}