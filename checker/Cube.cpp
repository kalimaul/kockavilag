#include "Cube.h"
#include "Interpretation.h"

Cube BaseCube::getCube(const Interpretation& interpretation) const {
    if (!cubeName.empty()) {
        return cubeName;
    }

    const auto& it = interpretation.cubes.find(symbolName);
    assert(it != interpretation.cubes.end());
    return it->second;
}
