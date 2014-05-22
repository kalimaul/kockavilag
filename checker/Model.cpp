#include <iostream>

#include "Model.h"
#include "World.h"
#include "Interpretation.h"

bool Model::areInputRulesSatisfied(const Interpretation& interpretation) const {
    for (const auto& rule : world.inputRules) {
        if (!rule->isSatisfied(*this, interpretation)) {
            return false;
        }
    }

    return true;
}

bool Model::areOutputRulesSatisfied(const Interpretation& interpretation) const {
    for (const auto& rule : world.outputRules) {
        if (!rule->isSatisfied(*this, interpretation)) {
            return false;
        }
    }

    return true;
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
