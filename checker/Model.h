#pragma once

#include "Cube.h"

class World;

class Model {
public:
    std::map<Cube, Cube> below;
    bool isComplete() const;
    const World& world;
};
