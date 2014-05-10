#include "Model.h"
#include "World.h"
#include <iostream>

void Model::print() const {
    for (const Cube& it : world.cubes) {
        if (isOnTop(it)) {
            Cube current = it;
            while (!isOnBottom(current)) {
                std::cout << current;
                current = *getBelow(current);
            }

            std::cout << current << "| ";
        }
    }

    std::cout << "\n";
}

bool Model::isComplete() const {
    return below.size() == world.cubes.size();
}

const Cube* Model::getBelow(const Cube& cube) const {
    const auto& it = below.find(cube);
    if (it == below.end()) {
        return nullptr;
    }

    return &it->second;
}

const Cube* Model::getAbove(const Cube& cube) const {
    for (const auto& it : below) {
        if (it.second == cube) {
            return &it.first;
        }
    }

    return nullptr;
}
