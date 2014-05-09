#include "Model.h"
#include "World.h"
#include <iostream>

void Model::print() const {
    for (const auto& it : world.cubes) {
        const auto& mapIt = below.find(it);
        if (mapIt == below.end()) {
            std::cout << it << "| ";
        }
    }
    for (const auto& it : below) {
        std::cout << it.first << " -> " << it.second << " ";
    }

    std::cout << "\n";
}

bool Model::isComplete() const {
    return below.size() == world.cubes.size();
}
