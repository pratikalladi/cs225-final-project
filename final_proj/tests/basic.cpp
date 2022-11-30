#include <catch2/catch_test_macros.hpp>


#include <iostream>
#include <sstream>
#include <string>

#include "graph.h"
#include "algo.h"

using namespace std;

TEST_CASE("sumDigits", "[valgrind][weight=1]"){
    SECTION("Base cases work") {
        REQUIRE(1 == 1);
    }
    SECTION("Multiple digits sum correctly") {
        REQUIRE(9 == 9);
    }
}
//change when developed...