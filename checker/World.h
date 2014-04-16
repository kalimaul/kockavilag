#pragma once

#include "Cube.h"
#include "Rule.h"

class World {
public:
    World(const std::string& filename);
    std::list<std::shared_ptr<Rule>> rules;
    std::set<Cube> cubes;
};
