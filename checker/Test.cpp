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
    }

    std::cout << "\n";
}


void SizeTest() {
    for (unsigned i = 0; i < 6; ++i) {
        World world;
        for (unsigned j = 0; j < i; ++j) {
            world.addCube(BaseCube::AsCube(boost::lexical_cast<std::string>(j)));
        }
        CheckerResult result = Check(world);
        std::cout << "World of size " << i << " -> "<< result.steps << " steps.\n";
    }
}

void RunAllTests() {
    for (TestFunction tf : tests) {
        RunTest(tf);
    }

    SizeTest();
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

