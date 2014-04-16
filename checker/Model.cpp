#include "Model.h"
#include "World.h"

bool Model::isComplete() const {
    return below.size() == world.cubes.size();
}
