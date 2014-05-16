#include "Interpretation.h"
#include "Rule.h"
#include "World.h"

void Interpretation::print() const {
    std::cout << "Interpretation: ";
    for (const auto& it : cubes) {
        std::cout << IDToName(it.first) << " -> " << IDToName(it.second) << " ";
    }
}

bool Interpretation::areInputRulesSatisfied() const {
    for (const auto& rule : model.world.inputRules) {
        if (!rule->isSatisfied(model, *this)) {
            return false;
        }
    }

    return true;
}

bool Interpretation::areOutputRulesSatisfied() const {
    for (const auto& rule : model.world.outputRules) {
        if (!rule->isSatisfied(model, *this)) {
            return false;
        }
    }

    return true;
}
