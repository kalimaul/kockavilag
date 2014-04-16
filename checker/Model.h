#pragma once

#include "Cube.h"

class World;

class Model {
public:
    Model(const World& world) :
            world(world) {
    }

    void print() const;

    std::map<Cube, Cube> below;
    bool isComplete() const;
    const World& world;
};
