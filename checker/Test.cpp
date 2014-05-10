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

bool Test05(World& world) {
    world.addRule(new AboveRule("A", "B"));
    return true;
}

bool Test06(World& world) {
    world.addRule(new AboveRule("A", "C"));
    world.addRule(new OnRule("A", "B"));
    return true;
}

bool Test07(World& world) {
    world.addRule(new OnRule("A", "B"));
    world.addRule(new OnRule("B", "A"));
    return false;
}

bool Test08(World& world) {
    world.addRule(new OnRule("A", "B"));
    world.addRule(new OnRule("B", "C"));
    world.addRule(new OnRule("C", "D"));
    return true;
}

bool Test09(World& world) {
    world.addCube("B");
    world.addCube("A");
    world.addRule(new OnRule("B", "A"));
    return true;
}

static unsigned counter = 1;
template<class T>
void RunTest(const T& function) {
    World world;
    bool expectedResult = function(world);
    world.addCubesFromRules();
    bool ok = Check(world) == expectedResult;
    std::cout << counter++ << ": " << (ok ? "PASS" : "FAIL") << "\n";
}

void RunAllTests() {
    RunTest(Test01);
    RunTest(Test02);
    RunTest(Test03);
    RunTest(Test04);
    RunTest(Test05);
    RunTest(Test06);
    RunTest(Test07);
    RunTest(Test08);
    RunTest(Test09);
}
