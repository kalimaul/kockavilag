#include <iostream>

#include "Model.h"
#include "World.h"
#include "Interpretation.h"

bool Model::checkProof(unsigned currentSymbol, const Interpretation& interpretation) const {
    if (currentSymbol == world.symbols.size()) {
#if 0
        this->print();
        interpretation.print();
        std::cout << "\n";
#endif
        bool good = !interpretation.areInputRulesSatisfied() || interpretation.areOutputRulesSatisfied();
        if (!good && !invalidInterpretation.get()) {
            invalidInterpretation.reset(new Interpretation(interpretation));
        }

        return good;
    } else {
        for (unsigned i = 0; i < world.cubes.size(); ++i) {
            bool existingInterp = false;
            // TODO don't generate these invalid permutations
            for (const auto& it : interpretation.cubes) {
                if (it.second == world.cubes[i]) {
                    existingInterp = true;
                    break;
                }
            }

            if (!existingInterp) {
                Interpretation newInterp = interpretation;
                newInterp.cubes[world.symbols[currentSymbol]] = world.cubes[i];
                bool ret = checkProof(currentSymbol + 1, newInterp);

                if (!ret) {
                    return false;
                }
            }
        }

        return true;
    }
}

bool Model::isProof() const {
    Interpretation beginInterp(*this);
    return checkProof(0, beginInterp);
}

void Model::print() const {
    std::cout << "Model: ";
    for (const Cube& it : world.cubes) {
        if (isOnTop(it)) {
            Cube current = it;
            while (!isOnBottom(current)) {
                std::cout << IDToName(current);
                current = *getBelow(current);
            }

            std::cout << IDToName(current) << "| ";
        }
    }

    if (invalidInterpretation.get()) {
        std::cout << ", ";
        invalidInterpretation->print();
    }
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
