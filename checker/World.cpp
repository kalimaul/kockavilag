#include "World.h"
#include <fstream>

World::World(const std::string& filename) {
    std::ifstream file(filename);
    while (file.good()) {
        Rule* rule = Rule::buildRule(file);
        assert(rule);
        rules.push_back(std::shared_ptr<Rule>(rule));
    }

    rules.push_back(std::shared_ptr<Rule>(new AllOnTableAxiom));

    for (const auto& rule : rules) {
        rule->AddCubesToWorld(*this);
    }
}
