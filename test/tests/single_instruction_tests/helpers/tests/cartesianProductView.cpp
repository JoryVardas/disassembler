#include "../cartesianProductView.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <fmt/format.h>

using namespace Testing::Helpers;

TEST_CASE("CartesianProductContainer", "[helper test]") {
    SECTION("begin and end") {
        SECTION("Single vector") {
            std::vector<int> vec1;
            vec1.emplace_back(1);
            CartesianProductView view{vec1};
            REQUIRE(view.begin() != view.end());
            REQUIRE(view.begin() == view.begin());
            REQUIRE(view.end() == view.end());
        }
        SECTION("Multiple vectors") {
            std::vector<int> vec1;
            vec1.emplace_back(1);
            std::vector<int> vec2;
            vec2.emplace_back(1);
            CartesianProductView view{vec1, vec2};
            REQUIRE(view.begin() != view.end());
            REQUIRE(view.begin() == view.begin());
            REQUIRE(view.end() == view.end());
        }
    }
    SECTION("begin and end") {
        SECTION("Single vector") {
            std::vector<int> vec1;
            vec1.emplace_back(1);
            CartesianProductView view{vec1};
            REQUIRE(view.begin() != view.end());
            REQUIRE(view.begin() == view.begin());
            REQUIRE(view.end() == view.end());
        }
        SECTION("Multiple vectors") {
            std::vector<int> vec1;
            vec1.emplace_back(1);
            std::vector<int> vec2;
            vec2.emplace_back(1);
            CartesianProductView view{vec1, vec2};
            REQUIRE(view.begin() != view.end());
            REQUIRE(view.begin() == view.begin());
            REQUIRE(view.end() == view.end());
        }
    }
    SECTION("Single vector single value") {
        std::vector<int> vec1;
        vec1.emplace_back(1);
        CartesianProductView view{vec1};
        auto view_iterator = view.begin();
        REQUIRE(view_iterator != view.end());
        REQUIRE(std::get<0>(*(view_iterator++)) == 1);
        REQUIRE(view_iterator == view.end());
    }
    SECTION("Single vector multiple values") {
        std::vector<int> vec1;
        vec1.emplace_back(1);
        vec1.emplace_back(2);
        vec1.emplace_back(3);
        CartesianProductView view{vec1};
        auto view_iterator = view.begin();
        REQUIRE(view_iterator != view.end());
        REQUIRE(std::get<0>(*(view_iterator++)) == 1);
        REQUIRE(std::get<0>(*(view_iterator++)) == 2);
        REQUIRE(std::get<0>(*(view_iterator++)) == 3);
        REQUIRE(view_iterator == view.end());
    }
    SECTION("Two vectors of single values") {
        std::vector<int> vec1;
        vec1.emplace_back(1);
        std::vector<int> vec2;
        vec2.emplace_back(5);
        CartesianProductView view{vec1, vec2};
        auto view_iterator = view.begin();
        // view_iterator++;
        REQUIRE(view_iterator != view.end());
        auto val1 = *(view_iterator++);
        REQUIRE(std::get<0>(val1) == 1);
        REQUIRE(std::get<1>(val1) == 5);
        REQUIRE(view_iterator == view.end());
    }
    SECTION("Two vectors multiple values") {
        std::vector<int> vec1;
        vec1.emplace_back(1);
        vec1.emplace_back(2);
        vec1.emplace_back(3);
        std::vector<int> vec2;
        vec2.emplace_back(4);
        vec2.emplace_back(5);
        vec2.emplace_back(6);
        CartesianProductView view{vec1, vec2};
        auto view_iterator = view.begin();
        auto testVal = *view_iterator;
        auto val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 4);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 6);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 4);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 6);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 3);
        REQUIRE(std::get<1>(val) == 4);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 3);
        REQUIRE(std::get<1>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 3);
        REQUIRE(std::get<1>(val) == 6);
        REQUIRE(view_iterator == view.end());
    }
    SECTION("Three vectors multiple values") {
        std::vector<int> vec1;
        vec1.emplace_back(1);
        vec1.emplace_back(2);
        std::vector<int> vec2;
        vec2.emplace_back(3);
        vec2.emplace_back(4);
        std::vector<int> vec3;
        vec3.emplace_back(5);
        vec3.emplace_back(6);
        CartesianProductView view{vec1, vec2, vec3};
        auto view_iterator = view.begin();
        auto testVal = *view_iterator;
        auto val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 3);
        REQUIRE(std::get<2>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 3);
        REQUIRE(std::get<2>(val) == 6);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 4);
        REQUIRE(std::get<2>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 1);
        REQUIRE(std::get<1>(val) == 4);
        REQUIRE(std::get<2>(val) == 6);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 3);
        REQUIRE(std::get<2>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 3);
        REQUIRE(std::get<2>(val) == 6);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 4);
        REQUIRE(std::get<2>(val) == 5);
        val = *(view_iterator++);
        REQUIRE(std::get<0>(val) == 2);
        REQUIRE(std::get<1>(val) == 4);
        REQUIRE(std::get<2>(val) == 6);
        REQUIRE(view_iterator == view.end());
    }
}