#include "Interpretation.h"
#include "Rule.h"
#include "World.h"

void Interpretation::print() const {
    std::cout << "Interpretation: ";
    for (const auto& it : symbols) {
        std::cout << IDToName(it.first) << " -> " << IDToName(it.second) << " ";
    }
}
