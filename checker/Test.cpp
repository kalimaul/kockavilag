#include "Test.h"
#include "World.h"
#include "Model.h"
#include "Checker.h"

#include <iostream>
#include <memory>

typedef bool (*TestFunction)(World&);
static std::list<TestFunction> tests;

class TestHolder {
public:
    TestHolder(TestFunction tf) {
        tests.push_back(tf);
    }
};

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
    for (TestFunction tf : tests) {
        RunTest(tf);
    }
}

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

#define TESTL(L, fun, ret) \
bool TOKENPASTE2(Test, L) (World& world) { \
    fun \
    return ret; \
} \
    TestHolder TOKENPASTE2(t, L) ( TOKENPASTE2(Test,L) );

#define TEST(fun, ret) TESTL(__LINE__, fun, ret)
#define CUBE(x) world.addCube(x);
#define IN(x) world.addInputRule(x);
#define OUT(x) world.addOutputRule(x);

TEST(CUBE("A") CUBE("B"), true)
TEST(IN(new OnRule("A", "B")) OUT(new OnRule("A", "B")), true)
TEST(IN(new AboveRule("A", "B")) OUT(new OnRule("A", "B")), true)


/// BEGIN TESTING


TEST(
        IN(new OnRule("B", "C"))
        IN(new OnRule("A", "B"))
        OUT(new AboveRule("A", "C")),
        true)
TEST(
        IN(new OnRule("A", "B"))
        IN(new OnRule("B", "A"))
        OUT(new OnRule("A", "B"))
        OUT(new OnRule("B", "A")),
        true)

TEST(
        IN(new OnRule("A", "B"))
        IN(new OnRule("B", "C"))
        IN(new OnRule("C", "D"))
        OUT(new AboveRule("D", "A")),
        false)

TEST(
        CUBE("B")
        CUBE("A");
        IN(new OnRule("B", "A"))
        OUT(new OnTableRule("A")),
        true)

TEST(
        IN(new OnTableRule("B"))
        IN(new NegatedRule(new OnTableRule("A")))
        OUT(new OnRule("A", "B")),
        true)

