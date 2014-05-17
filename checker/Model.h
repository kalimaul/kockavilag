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

    const Cube* getBelow(const Cube& cube) const {
        const auto& it = below.find(cube);
        if (it == below.end()) {
            return nullptr;
        }

        return &it->second;
    }

    const Cube* getAbove(const Cube& cube) const {
        const auto& it = above.find(cube);
        if (it == above.end()) {
            return nullptr;
        }

        return &it->second;
    }

    bool isOnBottom(const Cube& cube) const {
        return getBelow(cube) == nullptr;
    }

    bool isOnTop(const Cube& cube) const {
        return getAbove(cube) == nullptr;
    }

    const World& world;
    unsigned fixedCubes;

    // TODO store this somewhere else
    mutable std::shared_ptr<Interpretation> invalidInterpretation;

    void setBelow(const Cube& x, const Cube& y) {
        const Cube* aboveC = getAbove(y);
        if (aboveC) {
            below[*aboveC] = x;
            above[x] = *aboveC;
        }

        above[y] = x;
        below[x] = y;
    }

protected:
    std::map<Cube, Cube> above;
    std::map<Cube, Cube> below;
};
