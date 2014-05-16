#pragma once

#include "Cube.h"

class World;
class Interpretation;

class Model {
public:
    Model(const World& world) :
            world(world), fixedCubes(0) {
    }

    bool checkProof(unsigned currentSymbol, const Interpretation& interpretation) const;
    bool isProof() const;

    void print() const;

    const Cube* getBelow(const Cube& cube) const;
    const Cube* getAbove(const Cube& cube) const;

    bool isOnBottom(const Cube& cube) const {
        return getBelow(cube) == nullptr;
    }

    bool isOnTop(const Cube& cube) const {
        return getAbove(cube) == nullptr;
    }

    // TODO slow backwards lookup, switch to bimap
    std::map<Cube, Cube> below;
    const World& world;
    unsigned fixedCubes;

    // TODO store this somewhere else
    mutable std::shared_ptr<Interpretation> invalidInterpretation;
};
