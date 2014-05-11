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
    world.addInputRule(new OnRule("A", "B"));
    world.addOutputRule(new OnRule("A", "B"));
    return true;
}

bool Test05(World& world) {
    world.addInputRule(new AboveRule("A", "B"));
    world.addOutputRule(new OnRule("A", "B"));
    return true;
}

bool Test06(World& world) {
    world.addInputRule(new OnRule("B", "C"));
    world.addInputRule(new OnRule("A", "B"));
    world.addOutputRule(new AboveRule("A", "C"));
    return true;
}

bool Test07(World& world) {
    world.addInputRule(new OnRule("A", "B"));
    world.addInputRule(new OnRule("B", "A"));
    world.addOutputRule(new OnRule("A", "B"));
    world.addOutputRule(new OnRule("B", "A"));
    return true;
}

bool Test08(World& world) {
    world.addInputRule(new OnRule("A", "B"));
    world.addInputRule(new OnRule("B", "C"));
    world.addInputRule(new OnRule("C", "D"));
    world.addOutputRule(new AboveRule("D", "A"));
    return false;
}

bool Test09(World& world) {
    world.addCube("B");
    world.addCube("A");
    world.addInputRule(new OnRule("B", "A"));
    world.addOutputRule(new OnTableRule("A"));
    return true;
}

static unsigned counter = 1;
template<class T>
void RunTest(const T& function) {
    World world;
    bool expectedResult = function(world);
    world.addCubesFromRules();
    CheckerResult result = Check(world);
    bool ok = result.isProven() == expectedResult;
    std::cout << counter++ << ": " << (ok ? "PASS" : "FAIL");
    std::cout << ", steps: " << result.steps;

    if (!result.isProven()) {
        std::cout << ", counter example: ";
        result.counterExample->print();
    } else {
        std::cout << "\n";
    }
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
