#pragma once

#include "Cube.h"

class World;

class Model {
public:
    Model(const World& world) :
            world(world) {
    }

    bool areInputRulesSatisfied() const;
    bool areOutputRulesSatisfied() const;

    bool isProof() const {
        return !areInputRulesSatisfied() || areOutputRulesSatisfied();
    }

    void print() const;

    const Cube* getBelow(const Cube& cube) const;
    const Cube* getAbove(const Cube& cube) const;

    bool isOnBottom(const Cube& cube) const {
        return getBelow(cube) == nullptr;
    }

    bool isOnTop(const Cube& cube) const {
        return getAbove(cube) == nullptr;
    }

    std::map<Cube, Cube> below;
    const World& world;
};
