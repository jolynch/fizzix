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
#include "SimpleTest.h"

static SimpleTest suite_SimpleTest;

static CxxTest::List Tests_SimpleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SimpleTest( "SimpleTest.h", 10, "SimpleTest", suite_SimpleTest, Tests_SimpleTest );

static class TestDescription_SimpleTest_testEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_testEquality() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 13, "testEquality" ) {}
 void runTest() { suite_SimpleTest.testEquality(); }
} testDescription_SimpleTest_testEquality;

static class TestDescription_SimpleTest_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_testAddition() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 21, "testAddition" ) {}
 void runTest() { suite_SimpleTest.testAddition(); }
} testDescription_SimpleTest_testAddition;

static class TestDescription_SimpleTest_TestMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_TestMultiplication() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 27, "TestMultiplication" ) {}
 void runTest() { suite_SimpleTest.TestMultiplication(); }
} testDescription_SimpleTest_TestMultiplication;

static class TestDescription_SimpleTest_testComparison : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_testComparison() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 34, "testComparison" ) {}
 void runTest() { suite_SimpleTest.testComparison(); }
} testDescription_SimpleTest_testComparison;

static class TestDescription_SimpleTest_testTheWorldIsCrazy : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_testTheWorldIsCrazy() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 40, "testTheWorldIsCrazy" ) {}
 void runTest() { suite_SimpleTest.testTheWorldIsCrazy(); }
} testDescription_SimpleTest_testTheWorldIsCrazy;

static class TestDescription_SimpleTest_test_Failure : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_test_Failure() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 45, "test_Failure" ) {}
 void runTest() { suite_SimpleTest.test_Failure(); }
} testDescription_SimpleTest_test_Failure;

static class TestDescription_SimpleTest_test_TS_WARN_macro : public CxxTest::RealTestDescription {
public:
 TestDescription_SimpleTest_test_TS_WARN_macro() : CxxTest::RealTestDescription( Tests_SimpleTest, suiteDescription_SimpleTest, 51, "test_TS_WARN_macro" ) {}
 void runTest() { suite_SimpleTest.test_TS_WARN_macro(); }
} testDescription_SimpleTest_test_TS_WARN_macro;

#include <cxxtest/Root.cpp>
