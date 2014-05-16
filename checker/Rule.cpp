#include "Rule.h"
#include "Model.h"
#include "World.h"

bool NegatedRule::isSatisfied(const Model& model, const Interpretation& interpretation) const {
    return !rule->isSatisfied(model, interpretation);
}

void NegatedRule::AddCubesToWorld(World& world) const {
    rule->AddCubesToWorld(world);
}

void OnRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
    world.addCube(y);
}

bool OnRule::isSatisfied(const Model& model, const Interpretation& interpretation) const {
    const Cube* cube = model.getBelow(x.getCube(interpretation));
    if (!cube) {
        return false;
    }

    return *cube == y.getCube(interpretation);
}

void OnTableRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
}

bool OnTableRule::isSatisfied(const Model& model, const Interpretation& interpretation) const {
    return model.getBelow(x.getCube(interpretation)) == nullptr;
}

void NothingOnTopRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
}

bool NothingOnTopRule::isSatisfied(const Model& model, const Interpretation& interpretation) const {
    return model.getAbove(x.getCube(interpretation)) == nullptr;
}

void AboveRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
    world.addCube(y);
}

bool AboveRule::isSatisfied(const Model& model, const Interpretation& interpretation) const {
    Cube current = x.getCube(interpretation);

    while (model.below.find(current) != model.below.end()) {
        current = model.below.find(current)->second;

        if (current == y.getCube(interpretation)) {
            return true;
        }
    }

    return false;
}

void EqualsRule::AddCubesToWorld(World& world) const {
    world.addCube(x);
    world.addCube(y);
}

bool EqualsRule::isSatisfied(const Model& model, const Interpretation& interpretation) const {
    Cube realX = x.getCube(interpretation);
    Cube realY = y.getCube(interpretation);

    return realX == realY;
}
