#include "Rule.h"
#include "Model.h"
#include "World.h"

bool NegatedRule::isSatisfied(const Model& model) const {
    return !rule->isSatisfied(model);
}

void NegatedRule::AddCubesToWorld(World& world) const {
    rule->AddCubesToWorld(world);
}

void OnRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
    world.addCube(y);
}

bool OnRule::isSatisfied(const Model& model) const {
    const Cube* cube = model.getBelow(x);
    if (!cube) {
        return false;
    }

    return *cube == y;
}

void OnTableRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
}

bool OnTableRule::isSatisfied(const Model& model) const {
    return model.getBelow(x) == nullptr;
}

void NothingOnTopRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
}

bool NothingOnTopRule::isSatisfied(const Model& model) const {
    return model.getAbove(x) == nullptr;
}

void AboveRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
    world.addCube(y);
}

bool AboveRule::isSatisfied(const Model& model) const {
    Cube current = x;

    while (model.below.find(current) != model.below.end()) {
        current = model.below.find(current)->second;

        if (current == y) {
            return true;
        }
    }

    return false;
}
