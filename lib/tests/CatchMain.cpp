#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1: All test cases reside in other .cpp files", "[multi-file:1]") {}

// Compile & run:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -c CatchMain.cpp
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o FilterTestCases CatchMain.o FilterTestCases.cpp && FilterTestCases --success
//
// - cl -EHsc -I%CATCH_SINGLE_INCLUDE% -c CatchMain.cpp
// - cl -EHsc -I%CATCH_SINGLE_INCLUDE% -Fe020-TestCase.exe CatchMain.obj 020-TestCase-2.cpp && 020-TestCase --success
