#include "catch.hpp"
#include "lib.hpp"
TEST_CASE("distance") {
    REQUIRE(distance(0, 0, 3, 4) == 5);
    REQUIRE(distance(-3, -4, 0, 0) == 5);
    REQUIRE(distance(-10, -10, -5, 2) == 13);
    REQUIRE(distance(-1, -1, 5, 7) == 10);
    REQUIRE(distance(0, 0, 0, 0) == 0);
    REQUIRE(distance(10, 10, 10, 10) == 0);
    REQUIRE(distance(-10, -10, -10, -10) == 0);
}

TEST_CASE("getRotation") {
    REQUIRE(getRotation(0, 0, 0, -5) == -90.0F);
    REQUIRE(getRotation(0, 0, -5, 0) == 180.0F);
    REQUIRE(getRotation(10, 10, 10, 15) == 90.0F);
    REQUIRE(getRotation(10, 10, 15, 10) == 0.0F);
    REQUIRE(getRotation(0, 0, -5, 5) == 135.0F);
    REQUIRE(getRotation(0, 0, 5, 5) == 45.0F);
    REQUIRE(getRotation(0, 0, 5, -5) == -45.0F);
    REQUIRE(getRotation(0, 0, -5, -5) == -135.0F);
}

TEST_CASE("IsBuildingPossible") {
    REQUIRE(IsBuildingPossible(100, 100, 85, 90, 30) == true);
    REQUIRE(IsBuildingPossible(-100, -100, -85, -90, 40) == true);
    REQUIRE(IsBuildingPossible(100, 100, 85, 90, 10) == false);
    REQUIRE(IsBuildingPossible(100, 100, 30, 90, 30) == false);
    REQUIRE(IsBuildingPossible(100, 100, 85, 50, 30) == false);
    REQUIRE(IsBuildingPossible(100, 100, 10, 30, 10) == false);
}
