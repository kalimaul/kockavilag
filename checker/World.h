#pragma once

#include "Cube.h"
#include "Rule.h"

class World {
public:
    void addCubesFromRules();

    void addInputRule(Rule* rule) {
        inputRules.push_back(std::shared_ptr<Rule>(rule));
    }

    void addOutputRule(Rule* rule) {
        outputRules.push_back(std::shared_ptr<Rule>(rule));
    }

    void addCube(const Cube& cube) {
        cubes.push_back(cube);
    }

    std::list<std::shared_ptr<Rule>> inputRules;
    std::list<std::shared_ptr<Rule>> outputRules;
    std::vector<Cube> cubes;
};
