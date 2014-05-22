#pragma once

#include "Cube.h"
#include <map>

class Interpretation {
public:
    void print() const;

    void AddSymbol(const CubeSymbol& symbol, const Cube& cube) {
        symbols[symbol] = cube;
    }

    bool HasSymbol(const CubeSymbol& symbol) const {
        return symbols.find(symbol) != symbols.end();
    }
protected:

    std::map<CubeSymbol, Cube> symbols;

    friend class BaseCube;
};
