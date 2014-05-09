#include "Checker.h"

bool bruteForce(const Cube* cubes, unsigned begin, unsigned size,
        const Model& baseModel) {
    std::cout << begin << " - " << size << " ";
    baseModel.print();
    bool found = true;

    for (const auto& rule : baseModel.world.rules) {
        if (!rule->isSatisfied(baseModel)) {
            found = false;
            break;
        }
    }

    if (found) {
        return true;
    } else if (begin == size) {
        return false;
    }

    Cube current = cubes[begin];

    if (bruteForce(cubes, begin + 1, size, baseModel)) {
        return true;
    }

    for (unsigned i = begin; i < size - 1; ++i) {
        Model model = baseModel;
        model.below[current] = cubes[i + 1];
        if (bruteForce(cubes, begin + 1, size, model)) {
            return true;
        }
    }

    return false;
}

bool Check(const World& world) {
    std::vector<Cube> cubeList;
    cubeList.insert(cubeList.end(), world.cubes.begin(), world.cubes.end());
    return bruteForce(&cubeList[0], 0, cubeList.size(), Model(world));
}
