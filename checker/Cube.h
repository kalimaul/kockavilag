#pragma once
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <boost/lexical_cast.hpp>

typedef unsigned long Cube;
typedef Cube CubeSymbol;

class Interpretation;

Cube nameToID(const std::string& name);
std::string IDToName(const Cube& id);

struct BaseCube {
    static BaseCube AsCube(const std::string& name) {
        BaseCube bc;
        bc.cubeName = nameToID(name);
        return bc;
    }

    static BaseCube AsSymbol(const std::string& name) {
        BaseCube bc;
        bc.symbolName = nameToID(name);
        return bc;
    }

    BaseCube() {
        cubeName = 0;
        symbolName = 0;
    }

    Cube cubeName;
    CubeSymbol symbolName;

    Cube getCube(const Interpretation& interpretation) const;
    bool isSymbol() const {
        return symbolName != 0;
    }
};
