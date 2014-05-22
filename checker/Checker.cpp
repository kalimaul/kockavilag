#include "Checker.h"
#include "Interpretation.h"

void checkAllModels(const Model& baseModel, CheckerResult& result, const Interpretation& interpretation) {
    if (baseModel.fixedCubes == baseModel.world.cubes.size()) {
        ++result.steps;
#if 0
        baseModel.print();
        std::cout << "\n";
#endif

        bool found = baseModel.isProof(interpretation);
        if (!found && !result.counterExample.get()) {
            result.counterExample.reset(new Model(baseModel));
            result.counterExample->invalidInterpretation.reset(new Interpretation(interpretation));
        }
    } else {
        {
            Model newModel = baseModel;
            ++newModel.fixedCubes;
            checkAllModels(newModel, result, interpretation);
        }

        Cube current = baseModel.world.cubes[baseModel.fixedCubes];

        for (unsigned i = 0; i < baseModel.fixedCubes; ++i) {
            {
                Model model = baseModel;
                model.setBelow(current, baseModel.world.cubes[i]);
                ++model.fixedCubes;
                checkAllModels(model, result, interpretation);
            }

            if (result.counterExample.get()) {
                return;
            }

            if (baseModel.isOnBottom(baseModel.world.cubes[i])) {
                Model model = baseModel;
                model.setBelow(baseModel.world.cubes[i], current);
                ++model.fixedCubes;
                checkAllModels(model, result, interpretation);
            }

            if (result.counterExample.get()) {
                return;
            }
        }
    }
}

void checkAllInterpretations(unsigned currentSymbol, const Model& baseModel, CheckerResult& result,
        const Interpretation& interpretation) {
#if 0
    std::cout << currentSymbol << "\n";
    interpretation.print();
    std::cout << "\n";
#endif

    if (currentSymbol == baseModel.world.symbols.size()) {
        checkAllModels(baseModel, result, interpretation);
    } else {
        for (unsigned i = 0; i < baseModel.world.cubes.size(); ++i) {
            Interpretation newInterp = interpretation;
            newInterp.AddSymbol(baseModel.world.symbols[currentSymbol], baseModel.world.cubes[i]);
            checkAllInterpretations(currentSymbol + 1, baseModel, result, newInterp);
            if (result.counterExample.get()) {
                return;
            }
        }
    }
}

CheckerResult Check(World& world) {
    CheckerResult res;
    world.addCubesFromRules();
    Interpretation interp;
    checkAllInterpretations(0, Model(world), res, interp);
    return res;
}

CheckerResult CheckOptimized(World& world) {
    return Check(world);
}

