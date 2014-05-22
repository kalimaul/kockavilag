#include "World.h"
#include <fstream>

void World::addCubesFromRules() {
    for (const auto& rule : inputRules) {
        rule->AddCubesToWorld(*this);
    }

    for (const auto& rule : outputRules) {
        rule->AddCubesToWorld(*this);
    }

    std::sort(cubes.begin(), cubes.end());
    cubes.erase(std::unique(cubes.begin(), cubes.end()), cubes.end());

    std::sort(symbols.begin(), symbols.end());
    symbols.erase(std::unique(symbols.begin(), symbols.end()), symbols.end());
}

