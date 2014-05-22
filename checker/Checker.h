#pragma once
#include <vector>

#include "World.h"
#include "Model.h"

class CheckerResult {
public:
    CheckerResult() {
        steps = 0;
    }

    std::shared_ptr<Model> counterExample;
    bool isProven() const {
        return !counterExample.get();
    }

    unsigned steps;
};

CheckerResult Check(World& world);
CheckerResult CheckOptimized(World& world);
