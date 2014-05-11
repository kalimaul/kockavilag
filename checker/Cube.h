#pragma once
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <boost/lexical_cast.hpp>

typedef std::string Cube;
typedef Cube CubeSymbol;

class Interpretation;

struct BaseCube {
    static BaseCube AsCube(const std::string& name) {
        BaseCube bc;
        bc.cubeName = name;
        return bc;
    }

    static BaseCube AsSymbol(const std::string& name) {
        BaseCube bc;
        bc.symbolName = name;
        return bc;
    }

    Cube cubeName;
    CubeSymbol symbolName;

    Cube getCube(const Interpretation& interpretation) const;
    bool isSymbol() const {
        return !symbolName.empty();
    }
};
