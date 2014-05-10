#include "Checker.h"

CheckerResult bruteForce(const Cube* cubes, unsigned begin, unsigned size,
        const Model& baseModel) {
    if (begin == size) {
        //baseModel.print();
    }

    bool found = true;

    for (const auto& rule : baseModel.world.rules) {
        if (!rule->isSatisfied(baseModel)) {
            found = false;
            break;
        }
    }

    if (found) {
        return baseModel;
    } else if (begin == size) {
        return CheckerResult();
    }

    Cube current = cubes[begin];

    CheckerResult res = bruteForce(cubes, begin + 1, size, baseModel);
    if (res) {
        return res;
    }

    for (unsigned i = 0; i < begin; ++i) {
        {
            Model model = baseModel;
            model.below[current] = cubes[i];
            CheckerResult res = bruteForce(cubes, begin + 1, size, model);
            if (res) {
                return res;
            }
        }

        if (baseModel.below.find(cubes[i]) == baseModel.below.end()) {
            Model model = baseModel;
            model.below[cubes[i]] = current;
            CheckerResult res = bruteForce(cubes, begin + 1, size, model);
            if (res) {
                return res;
            }
        }
    }

    return CheckerResult();
}

CheckerResult Check(const World& world) {
    std::vector<Cube> cubeList;
    cubeList.insert(cubeList.end(), world.cubes.begin(), world.cubes.end());
    return bruteForce(&cubeList[0], 0, cubeList.size(), Model(world));
}
