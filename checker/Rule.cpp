#include "Rule.h"
#include "Model.h"
#include "World.h"

Rule* Rule::buildRule(std::istream& stream) {
    Rule* ret = nullptr;

    std::string first;
    stream >> first;
    if (first == "!") {
        ret = new NegatedRule(buildRule(stream));
    } else if (first == "On") {
        Cube arg1, arg2;
        stream >> arg1 >> arg2;
        ret = new OnRule(arg1, arg2);
    } else if (first == "A") {
        Cube arg1, arg2;
        stream >> arg1 >> arg2;
        ret = new AtopRule(arg1, arg2);
    } else if (first == "T") {
        Cube arg1;
        stream >> arg1;
        ret = new TableRule(arg1);
    } else if (first == "E") {
        Cube arg1;
        stream >> arg1;
        ret = new EmptyRule(arg1);
    }

    return ret;
}

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
    assert(model.isComplete());

    const auto& it = model.below.find(x);
    if (it == model.below.end()) {
        return false;
    }

    return it->second == y;
}

void TableRule::AddCubesToWorld(World& world) const {
    world.cubes.insert(x);
}

bool TableRule::isSatisfied(const Model& model) const {
    assert(model.isComplete());

    const auto& it = model.below.find(x);
    if (it == model.below.end()) {
        return false;
    }

    return it->second == table;
}

void EmptyRule::AddCubesToWorld(World& world) const {
    world.cubes.insert(x);
}

bool EmptyRule::isSatisfied(const Model& model) const {
    assert(model.isComplete());

    for (const auto& it : model.below) {
        if (it.second == x) {
            return false;
        }
    }

    return true;
}

void AtopRule::AddCubesToWorld(World& world) const {
    world.cubes.insert(x);
    world.cubes.insert(y);
}

bool AtopRule::isSatisfied(const Model& model) const {
    assert(model.isComplete());

    Cube current = x;
    current = model.below.find(current)->second;

    while (current != table && model.below.find(current) != model.below.end()) {
        if (current == y) {
            return true;
        }

        current = model.below.find(current)->second;
    }

    return false;
}

Cube AllOnTableAxiom::getBottom(const Cube& from, const Model& model) const {
    Cube current = from;
    while (current != table && model.below.find(current) != model.below.end()) {
        current = model.below.find(current)->second;

        if (current == from) {
            return from;
        }
    }

    return current;
}

bool AllOnTableAxiom::isSatisfied(const Model& model) const {
    for (const auto& it : model.below) {
        Cube bottom = getBottom(it.first, model);
        if (bottom != table) {
            return false;
        }
    }

    return true;
}
