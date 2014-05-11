#pragma once

#include "Model.h"

class Interpretation {
public:
    Interpretation(const Model& model) :
            model(model) {
    }

    bool areInputRulesSatisfied() const;
    bool areOutputRulesSatisfied() const;

    void print() const;

    std::map<CubeSymbol, Cube> cubes;
    const Model& model;
};
