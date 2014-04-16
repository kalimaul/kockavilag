#include <iostream>
#include "World.h"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " <filename>\n";
        return 0;
    }

    std::string filename = argv[1];
    World world(filename);

    for(Cube c : world.cubes) {
        std::cout << "cube " << c << "\n";
    }

    return 0;
}
