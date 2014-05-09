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
    world.cubes.insert(x);
    world.cubes.insert(y);
}

bool OnRule::isSatisfied(const Model& model) const {
    const auto& it = model.below.find(x);
    if (it == model.below.end()) {
        return false;
    }

    return it->second == y;
}

void OnTableRule::AddCubesToWorld(World& world) const {
    world.cubes.insert(x);
}

bool OnTableRule::isSatisfied(const Model& model) const {
    const auto& it = model.below.find(x);
    if (it != model.below.end()) {
        return false;
    }

    return true;
}

void NothingOnTopRule::AddCubesToWorld(World& world) const {
    world.cubes.insert(x);
}

bool NothingOnTopRule::isSatisfied(const Model& model) const {
    for (const auto& it : model.below) {
        if (it.second == x) {
            return false;
        }
    }

    return true;
}

void AboveRule::AddCubesToWorld(World& world) const {
    world.cubes.insert(x);
    world.cubes.insert(y);
}

bool AboveRule::isSatisfied(const Model& model) const {
    Cube current = x;
    current = model.below.find(current)->second;

    while (model.below.find(current) != model.below.end()) {
        if (current == y) {
            return true;
        }

        current = model.below.find(current)->second;
    }

    return false;
}
