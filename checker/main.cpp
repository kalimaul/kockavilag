#include <iostream>
#include "World.h"
#include "Model.h"

bool bruteForce(const Cube* cubes, unsigned begin, unsigned size,
        const Model& baseModel) {
    if (begin == size) {
        baseModel.print();
        for (const auto& rule : baseModel.world.rules) {
            if (!rule->isSatisfied(baseModel)) {
                return false;
            }
        }
        return true;
    }

    Cube current = cubes[begin];

    Model newColumn = baseModel;
    newColumn.below[current] = table;
    if (bruteForce(cubes, begin + 1, size, newColumn)) {
        return true;
    }

    for (unsigned i = 0; i < size; ++i) {
        Model model = baseModel;
        model.below[current] = cubes[i];
        if (bruteForce(cubes, begin + 1, size, model)) {
            return true;
        }
    }

    return false;
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " <filename>\n";
        return 0;
    }

    std::string filename = argv[1];
    World world(filename);

#if false
    for(Cube c : world.cubes) {
        std::cout << "cube " << c << "\n";
    }
#endif

    std::vector<Cube> cubes(world.cubes.begin(), world.cubes.end());
    Model baseModel(world);

    std::cout << "result: " << bruteForce(&cubes[0], 0, cubes.size(), baseModel)
            << "\n";

    return 0;
}
