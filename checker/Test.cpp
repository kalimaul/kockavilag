#include "Test.h"
#include "World.h"
#include "Model.h"
#include "Checker.h"

#include <iostream>
#include <memory>

bool Test01(World& world) {
    return true;
}

bool Test02(World& world) {
    world.addCube("A");
    return true;
}

bool Test03(World& world) {
    world.addCube("A");
    world.addCube("B");
    return true;
}

bool Test04(World& world) {
    world.addRule(new OnRule("A", "B"));
    return true;
}

static unsigned counter = 1;
template<class T>
void RunTest(const T& function) {
    World world;
    bool expectedResult = function(world);
    world.addCubesFromRules();
    bool ok = Check(world) == expectedResult;
    std::cout << counter++ << ": " << (ok ? "OK" : "FAIL") << "\n";
}

void RunAllTests() {
    RunTest(Test01);
    RunTest(Test02);
    RunTest(Test03);
    RunTest(Test04);
}
