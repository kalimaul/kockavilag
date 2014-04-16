#pragma once
#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <boost/lexical_cast.hpp>

#if true
typedef std::string Cube;
const Cube table = "|";
#else
typedef int Cube;
const Cube table = (Cube) -1;
#endif
