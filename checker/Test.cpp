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
    CheckerResult result = CheckOptimized(world);
    bool ok = result.isProven() == expectedResult;
    std::cout << counter++ << ": " << (ok ? "PASS" : "FAIL");
    std::cout << ", steps: " << result.steps;

    if (!result.isProven()) {
        std::cout << ", counter example: ";
        result.counterExample->print();
    }

    std::cout << "\n";
}


void SizeTest() {
    for (unsigned i = 0; i < 6; ++i) {
        World world;
        for (unsigned j = 0; j < i; ++j) {
            world.addCube(BaseCube::AsCube(boost::lexical_cast<std::string>(j)));
        }
        CheckerResult result = CheckOptimized(world);
        std::cout << "World of size " << i << " -> "<< result.steps << " steps.\n";
    }
}

void Towers(unsigned n) {
    World world;
    for (unsigned j = 0; j < (2 * n - 1); ++j) {
        world.addCube(BaseCube::AsCube(std::string("A") + boost::lexical_cast<std::string>(j)));
    }

    world.addInputRule(new OnTableRule(BaseCube::AsSymbol("X0")));
    world.addInputRule(new OnTableRule(BaseCube::AsSymbol("Y0")));

    for (unsigned i = 0; i < n; ++i) {
        std::string asNum1 = boost::lexical_cast<std::string>(i);
        std::string asNum2 = boost::lexical_cast<std::string>(i + 1);
        world.addInputRule(new OnRule(BaseCube::AsSymbol(std::string("X") + asNum2), BaseCube::AsSymbol(std::string("X") + asNum1)));
        world.addInputRule(new OnRule(BaseCube::AsSymbol(std::string("Y") + asNum2), BaseCube::AsSymbol(std::string("Y") + asNum1)));
    }

    world.addOutputRule(new EqualsRule(BaseCube::AsSymbol("X0"), BaseCube::AsSymbol("Y1")));

    world.addCubesFromRules();
    CheckerResult result = CheckOptimized(world);
    std::cout << "Towers " << n  << " -> " << result.steps << " steps, proven: " << result.isProven() << "\n";
}

void RunTowers() {
    for (unsigned i = 2; i < 5; ++i) {
        Towers(i);
    }
}

void RunAllTests() {
    for (TestFunction tf : tests) {
        RunTest(tf);
    }

    SizeTest();
    RunTowers();
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
#define CUBE(x) BaseCube::AsCube(x)
#define SYMBOL(x) BaseCube::AsSymbol(x)
#define IN(x) world.addInputRule(x);
#define OUT(x) world.addOutputRule(x);


/// BEGIN TESTING

TEST(
        IN(new OnRule(CUBE("B"), CUBE("C")))
        IN(new OnRule(CUBE("A"), CUBE("B")))
        OUT(new AboveRule(CUBE("A"), CUBE("C"))),
        true)
TEST(
        IN(new OnRule(CUBE("A"), CUBE("B")))
        IN(new OnRule(CUBE("B"), CUBE("A")))
        OUT(new OnRule(CUBE("A"), CUBE("B")))
        OUT(new OnRule(CUBE("B"), CUBE("A"))),
        true)

TEST(
        IN(new OnRule(CUBE("A"), CUBE("B")))
        IN(new OnRule(CUBE("B"), CUBE("C")))
        IN(new OnRule(CUBE("C"), CUBE("D")))
        OUT(new AboveRule(CUBE("D"), CUBE("A"))),
        false)

TEST(
        IN(new OnRule(CUBE("B"), CUBE("A")))
        OUT(new OnTableRule(CUBE("A"))),
        true)

TEST(
        IN(new OnTableRule(CUBE("B")))
        IN(new NegatedRule(new OnTableRule(CUBE("A"))))
        OUT(new OnRule(CUBE("A"), CUBE("B"))),
        true)

TEST(
        IN(new OnTableRule(SYMBOL("X")))
        IN(new OnRule(CUBE("A"), CUBE("B")))
        OUT(new OnRule(CUBE("A"), SYMBOL("X"))),
        true)

TEST(
        IN(new OnTableRule(CUBE("A")))
        IN(new NothingOnTopRule(CUBE("B")))
        IN(new NegatedRule(new NothingOnTopRule(CUBE("C"))))
        IN(new OnTableRule(SYMBOL("X")))
        IN(new OnTableRule(SYMBOL("Y")))
        OUT(new NegatedRule(new OnRule(CUBE("B"), CUBE("D")))),
        true)

