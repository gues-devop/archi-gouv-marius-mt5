#include "math/vector.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("vectors can be added") {
    const Vector first(1, 2, 3);
    const Vector second(4, 5, 6);

    const Vector result = first + second;

    REQUIRE(result.x() == 5);
    REQUIRE(result.y() == 7);
    REQUIRE(result.z() == 9);
}

TEST_CASE("vectors can be subtracted") {
    const Vector first(-1, 4, 0);
    const Vector second(-5, 2, 1);

    const Vector result = first - second;

    REQUIRE(result.x() == 4);
    REQUIRE(result.y() == 2);
    REQUIRE(result.z() == -1);
}

TEST_CASE("vectors can be multiplied by a scalar") {
    const Vector vector(1, 2, 3);

    const Vector result = vector * 2;

    REQUIRE(result.x() == 2);
    REQUIRE(result.y() == 4);
    REQUIRE(result.z() == 6);
}

TEST_CASE("a scalar can multiply a vector") {
    const Vector vector(1, 2, 3);

    const Vector result = 2 * vector;

    REQUIRE(result.x() == 2);
    REQUIRE(result.y() == 4);
    REQUIRE(result.z() == 6);
}

TEST_CASE("vectors can calculate a dot product") {
    const Vector first(1, 2, 3);
    const Vector second(4, 5, 6);

    REQUIRE(first.dot(second) == 32);
}

TEST_CASE("vectors can calculate their length") {
    const Vector vector(0, 3, 4);

    REQUIRE(vector.length() == 5);
}

TEST_CASE("vectors can be normalised") {
    const Vector vector(0, 0, 2);

    const Vector result = vector.normalised();

    REQUIRE(result.x() == 0);
    REQUIRE(result.y() == 0);
    REQUIRE(result.z() == 1);
}

TEST_CASE("a vector can be normalised in any direction") {
    const Vector vector(3, 4, 0);

    const Vector result = vector.normalised();

    REQUIRE(result.x() == Catch::Approx(3.0 / 5.0));
    REQUIRE(result.y() == Catch::Approx(4.0 / 5.0));
    REQUIRE(result.z() == 0);
}
