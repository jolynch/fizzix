/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "fizformulatests.h"

static FizFormulaTests suite_FizFormulaTests;

static CxxTest::List Tests_FizFormulaTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FizFormulaTests( "fizformulatests.h", 16, "FizFormulaTests", suite_FizFormulaTests, Tests_FizFormulaTests );

static class TestDescription_FizFormulaTests_testFormula : public CxxTest::RealTestDescription {
public:
 TestDescription_FizFormulaTests_testFormula() : CxxTest::RealTestDescription( Tests_FizFormulaTests, suiteDescription_FizFormulaTests, 19, "testFormula" ) {}
 void runTest() { suite_FizFormulaTests.testFormula(); }
} testDescription_FizFormulaTests_testFormula;

static class TestDescription_FizFormulaTests_testOperators : public CxxTest::RealTestDescription {
public:
 TestDescription_FizFormulaTests_testOperators() : CxxTest::RealTestDescription( Tests_FizFormulaTests, suiteDescription_FizFormulaTests, 62, "testOperators" ) {}
 void runTest() { suite_FizFormulaTests.testOperators(); }
} testDescription_FizFormulaTests_testOperators;

#include <cxxtest/Root.cpp>
