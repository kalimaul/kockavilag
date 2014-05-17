#include "Checker.h"

void bruteForce(const Model& baseModel, CheckerResult& result) {
    if (baseModel.fixedCubes == baseModel.world.cubes.size()) {
        ++result.steps;
        //baseModel.print();

        bool found = baseModel.isProof();
        if (!found && !result.counterExample.get()) {
            result.counterExample.reset(new Model(baseModel));
        }
    } else {
        {
            Model newModel = baseModel;
            ++newModel.fixedCubes;
            bruteForce(newModel, result);
        }

        Cube current = baseModel.world.cubes[baseModel.fixedCubes];

        for (unsigned i = 0; i < baseModel.fixedCubes; ++i) {
            {
                Model model = baseModel;
                model.setBelow(current, baseModel.world.cubes[i]);
                ++model.fixedCubes;
                bruteForce(model, result);
            }

            if (baseModel.isOnBottom(baseModel.world.cubes[i])) {
                Model model = baseModel;
                model.setBelow(baseModel.world.cubes[i], current);
                ++model.fixedCubes;
                bruteForce(model, result);
            }
        }
    }
}

CheckerResult Check(const World& world) {
    CheckerResult res;
    bruteForce(Model(world), res);
    return res;
}

CheckerResult CheckOptimized(const World& world) {
    CheckerResult res;
    Model model(world);
    bruteForce(model, res);
    return res;
}

