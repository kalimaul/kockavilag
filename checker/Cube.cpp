#include "Cube.h"
#include "Interpretation.h"

Cube cubeIDCounter = 1;
std::map<std::string, Cube> nameToIDMap;

Cube nameToID(const std::string& name) {
    const auto& it = nameToIDMap.find(name);
    if (it == nameToIDMap.end()) {
        ++cubeIDCounter;
        nameToIDMap[name] = cubeIDCounter;
        return cubeIDCounter;
    } else {
        return it->second;
    }
}

std::string IDToName(const Cube& id) {
    for (const auto& it : nameToIDMap) {
        if (it.second == id) {
            return it.first;
        }
    }

    return "U";
}

Cube BaseCube::getCube(const Interpretation& interpretation) const {
    if (cubeName != 0) {
        return cubeName;
    }

    const auto& it = interpretation.symbols.find(symbolName);
    assert(it != interpretation.symbols.end());
    return it->second;
}
