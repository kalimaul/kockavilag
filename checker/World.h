#pragma once

#include "Cube.h"
#include "Rule.h"

class World {
public:
    World(const std::list<std::shared_ptr<Rule>>& rules) :
            rules(rules) {
        addCubesFromRules();
    }

    World() {
    }

    void addCubesFromRules() {
        for (const auto& rule : rules) {
            rule->AddCubesToWorld(*this);
        }
    }

    void addRule(Rule* rule) {
        rules.push_back(std::shared_ptr<Rule>(rule));
    }

    void addCube(const Cube& cube) {
        cubes.insert(cube);
    }

    std::list<std::shared_ptr<Rule>> rules;
    std::set<Cube> cubes;
};
