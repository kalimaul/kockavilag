#pragma once
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <boost/lexical_cast.hpp>

#if false
class Cube {
public:
    Cube(const std::string& name) :
            name(name) {
    }
    const std::string& getName() {
        return name;
    }
protected:
    std::string name;
};
#else
typedef int Cube;
const Cube table = (Cube) -1;
#endif
