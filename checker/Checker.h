#pragma once
#include <vector>

#include "World.h"
#include "Model.h"

class CheckerResult {
public:
    CheckerResult(const Model& model) {
        Model* res = new Model(model);
        result.reset(res);
    }

    CheckerResult() {
    }

    std::shared_ptr<Model> result;
    operator bool() const {
        return result.get();
    }
};

CheckerResult Check(const World& world);
