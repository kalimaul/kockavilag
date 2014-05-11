#include "Checker.h"

void bruteForce(unsigned currentCube, const Model& baseModel, CheckerResult& result) {
    if (currentCube == baseModel.world.cubes.size()) {
        ++result.steps;
        //baseModel.print();

        bool found = baseModel.isProof();
        if (!found && !result.counterExample.get()) {
            result.counterExample.reset(new Model(baseModel));
        }
    } else {
        bruteForce(currentCube + 1, baseModel, result);

        Cube current = baseModel.world.cubes[currentCube];

        for (unsigned i = 0; i < currentCube; ++i) {
            {
                Model model = baseModel;
                const Cube* above = model.getAbove(baseModel.world.cubes[i]);
                if (above) {
                    model.below[*above] = current;
                }
                model.below[current] = baseModel.world.cubes[i];
                bruteForce(currentCube + 1, model, result);
            }

            if (baseModel.below.find(baseModel.world.cubes[i]) == baseModel.below.end()) {
                Model model = baseModel;
                model.below[baseModel.world.cubes[i]] = current;
                bruteForce(currentCube + 1, model, result);
            }
        }
    }
}

CheckerResult Check(const World& world) {
    CheckerResult res;
    bruteForce(0, Model(world), res);
    return res;
}

