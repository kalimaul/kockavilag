#include "Rule.h"
#include "Model.h"
#include "World.h"

Rule* Rule::buildRule(std::istream& stream) {
    Rule* ret = nullptr;

    std::string first;
    stream >> first;
    if (first == "On") {
        int arg1, arg2;
        stream >> arg1 >> arg2;
        ret = new OnRule(arg1, arg2);
    } else if (first == "T") {
        int arg1;
        stream >> arg1;
        ret = new TableRule(arg1);
    }

    return ret;
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
